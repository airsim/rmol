// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <string>
#include <sstream>
// StdAir
#include <stdair/basic/BasChronometer.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/bom/StudyStatManager.hpp>
#include <rmol/bom/VariateList.hpp>
#include <rmol/bom/Gaussian.hpp>
#include <rmol/bom/Bucket.hpp>
#include <rmol/bom/BucketHolder.hpp>
#include <rmol/bom/PartialSumHolder.hpp>
#include <rmol/bom/PartialSumHolderHolder.hpp>
//#include <rmol/bom/Resource.hpp>
#include <rmol/bom/MCOptimiser.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  void MCOptimiser::
  optimalOptimisationByMCIntegration(const int K, 
                                     const ResourceCapacity_T iCabinCapacity,
                                     BucketHolder& ioBucketHolder,
                                     PartialSumHolderHolder& ioPSHolderHolder,
                                     BidPriceVector_T& ioBidPriceVector){
    // Retrieve the BucketHolder
    // BucketHolder& ioBucketHolder = ioResource.getBucketHolder();

    // Number of classes/buckets: n
    const short nbOfClasses = ioBucketHolder.getSize();

    /** 
        Initialise the partial sum vector representing the last step within
        the algorithm below.
        <br>At the beginning of the algorithm, the partial sums need to be
        null. Then, the generated demand (variates) will be added 
        incrementally.
    */
    ioPSHolderHolder.begin();
    PartialSumHolder& firstPartialSumHolder = 
      ioPSHolderHolder.getCurrentPartialSumHolder();
    firstPartialSumHolder.initSize (K);

    for (int k=1 ; k <= K; k++) {
      firstPartialSumHolder.addPartialSum (0.0);
    }

    /** 
        Iterate on the classes/buckets, from 1 to n-1.
        Note that n-1 corresponds to the size of the parameter list,
        i.e., n corresponds to the number of classes/buckets.
    */
    ioBucketHolder.begin();
    ioPSHolderHolder.iterate();
    int Kj = K;
    int lj = 0;
    const int cabinCapacityInt = static_cast<int> (iCabinCapacity);
    for (short j = 1 ; j <= nbOfClasses - 1; 
	 ++j, ioBucketHolder.iterate(), ioPSHolderHolder.iterate()) {
      /** Retrieve Bucket(j) (current) and Bucket(j+1) (next). */
      Bucket& currentBucket = ioBucketHolder.getCurrentBucket();
      Bucket& nextBucket = ioBucketHolder.getNextBucket();

      // STEP 1.
      /** 
          Initialise the random generator with the distribution parameters of
          the demand for the current class/bucket, j.
      */
      const FldDistributionParameters& aDistribParams = 
        currentBucket.getDistributionParameters();
      Gaussian gaussianDemandGenerator (aDistribParams);

      /** DEBUG
          STDAIR_LOG_DEBUG ("[" << j << "]: " << Kj << " values with N ( " 
          << aDistribParams.getMean() << ", "
          << aDistribParams.getStandardDeviation() << ").");
      */

      /**
         Iterate on the random draws: generate random variates, d(j,k)
         for the current class/bucket demand, j, and for k=1 to Kj.
      */
      VariateList_T aVariateList;

      PartialSumHolder& previousPartialSumList = 
        ioPSHolderHolder.getPreviousPartialSumHolder();
      PartialSumHolder& currentPartialSumList = 
        ioPSHolderHolder.getCurrentPartialSumHolder();
      currentPartialSumList.initSize (Kj);
      for (int k=1; k <= Kj; k++) {
        const double djk = gaussianDemandGenerator.generateVariate();
        aVariateList.push_back (djk);

        /** 
            Calculate the partial sums:
            <br>
            S(j,k)= d(1,k) + d(2,k) + ... + d(j,k),for a given k and j=1 to n-1
            Note that n-1 corresponds to the size of the parameter list,
            i.e., n corresponds to the number of classes/buckets.
            <br>
            Hence: S(j,k) = S'(j-1, l+k) + d(j,k). 
        */
        const double spjm1lpk = 
          previousPartialSumList.getPartialSum (lj + k - 1);
        const double sjk = spjm1lpk + djk;
        currentPartialSumList.addPartialSum (sjk);

        /* DEBUG
           STDAIR_LOG_DEBUG ("d(" << j << ", " << k << "); " << djk 
           << "; S'(" << j-1 << ", " << lj+k << "); " << spjm1lpk
           << "; S(" << j << ", " << k << "); " << sjk);
        */
      }

      // STEP 2.
      /**
         Sort the partial sum vectors S(j,k) on k, for the current j.
      */
      currentPartialSumList.sort ();

      /** Retrieve the prices for Bucket(j) and Bucket(j+1). */
      const double pj = currentBucket.getAverageYield();
      const double pj1 = nextBucket.getAverageYield();

      /** Consistency check: the yield/price of a higher class/bucket 
          (with the j index lower) must be higher. */
      assert (pj > pj1);

      /** 
          The optimal index is defined as:
          lj = floor {[p(j)-p(j+1)]/p(j) . K}
      */
      const double ljdouble = std::floor (Kj * (pj - pj1) / pj);
      lj = static_cast<int> (ljdouble);

      /** DEBUG 
      STDAIR_LOG_DEBUG ("p(j+1)/p(j) = " << pj1 / pj << ", lj = " << lj 
                      << ", Kj = " << Kj << " => " << Kj - lj
                      << " points above y(j)");
      */

      /** Consistency check. */
      assert (lj >= 1 && lj < Kj);

      /** 
          The optimal protection is defined as:
          y(j) = 1/2 [S(j,lj) + S(j, lj+1)]
      */
      const double sjl = currentPartialSumList.getPartialSum (lj - 1);
      const double sjlp1 = currentPartialSumList.getPartialSum (lj + 1 - 1);
      const double yj = (sjl + sjlp1) / 2;

      /** DEBUG
          STDAIR_LOG_DEBUG ("S(j,l) = " << sjl << ", S(j,l+1) = " << sjlp1 
          << ", y(j) = " << yj);
      */

      // Set the cumulated protection for Bucket(j) (j ranging from 1 to n-1)
      currentBucket.setCumulatedProtection (yj);

      /** Compute the Bid-Price (Opportunity Cost) at index x
          (capacity) for x between y(j-1) et y(j). This OC can be
          proven to be equal to p(j)*Proba(D1+...+Dk>=x | D1 > y1,
          D1+D2 > y2, ..., D1+...+D(k-1) > y(k-1)). 
      */
      
      // Get the previous cumulated protection y(j-1).
      const double yjm1 = ioBucketHolder.getPreviousCumulatedProtection ();
      const int yjm1int = static_cast<int> (yjm1);
      const int yjint = static_cast<int> (yj);
      int currentIndex = 0;

      for (int x = yjm1int + 1; 
           x <= yjint && x <= cabinCapacityInt; ++x) {
        currentIndex = currentPartialSumList.getLowerBound (x);
        const double bidPriceAtX = pj * (Kj - currentIndex) / Kj;
        ioBidPriceVector.push_back (bidPriceAtX);
      }   

      /** Update Kj for the next loop. */
      Kj = Kj - lj;

      /** S'(j,k) = S(j,k). 
	  <br>The previousPartialSumList (S') now becomes equal to the 
	  currentPartialSumList (S) (by iteration on ioPSHolderHolder). */
    }

    // Set the protection of Bucket(n) to be equal to the capacity
    Bucket& currentBucket = ioBucketHolder.getCurrentBucket();
    currentBucket.setCumulatedProtection (iCabinCapacity);

    /** Compute the Bid-Price (Opportunity Cost) at index x
          (capacity) for x between y(n-1) et cabin capacity. This OC can be
          proven to be equal to p(n)*Proba(D1+...+Dn>=x | D1 > y1,
          D1+D2 > y2, ..., D1+...+D(n-1) > y(n-1)). */
         
    // Get the previous cumulated protection y(n-1).
    const double ynm1 = ioBucketHolder.getPreviousCumulatedProtection ();

    if (ynm1 < iCabinCapacity) {
      // STEP 1.
      const FldDistributionParameters& aDistribParams = 
        currentBucket.getDistributionParameters();
      Gaussian gaussianDemandGenerator (aDistribParams);
      
      VariateList_T aVariateList;
      
      PartialSumHolder& previousPartialSumList = 
        ioPSHolderHolder.getPreviousPartialSumHolder();
      PartialSumHolder& currentPartialSumList = 
        ioPSHolderHolder.getCurrentPartialSumHolder();
      currentPartialSumList.initSize (Kj);
      
      for (int k = 1; k <= Kj; ++k) {
        const double djk = gaussianDemandGenerator.generateVariate();
        aVariateList.push_back (djk);
        
        const double spjm1lpk = 
          previousPartialSumList.getPartialSum (lj + k - 1);
        const double sjk = spjm1lpk + djk;
        currentPartialSumList.addPartialSum (sjk);
      }
      
      // STEP 2.
      currentPartialSumList.sort ();
      
      const int ynm1int = static_cast<int> (ynm1);
      const double pn = currentBucket.getAverageYield();
      int currentIndex = 0;
      for (int x = ynm1int + 1; x <= cabinCapacityInt; ++x) {
        currentIndex = currentPartialSumList.getLowerBound (x);
        const double bidPriceAtX = pn * (Kj - currentIndex) / Kj;
        ioBidPriceVector.push_back (bidPriceAtX);
      } 
    }
    
    /**
       Re-calculate the values (protections, bkg limits and cumulated
       booking limits, the optimal revenue.
    */
    ioBucketHolder.recalculate ();
  }

  // //////////////////////////////////////////////////////////////////////
  void MCOptimiser::
  optimalOptimisationByMCIntegration(const int K, 
                                     const ResourceCapacity_T iCabinCapacity,
                                     BucketHolder& ioBucketHolder,
                                     PartialSumHolderHolder& ioPSHolderHolder,
                                     BidPriceVector_T& ioBidPriceVector,
                                     StudyStatManager& ioStudyStatManager){
    // Retrieve the BucketHolder
    // BucketHolder& ioBucketHolder = ioResource.getBucketHolder();

    stdair::BasChronometer lDrawBasChronometer;
    stdair::BasChronometer lSortBasChronometer;
    stdair::BasChronometer lBVPCalculationBasChronometer;

    // Number of classes/buckets: n
    const short nbOfClasses = ioBucketHolder.getSize();

    /** 
        Initialise the partial sum vector representing the last step within
        the algorithm below.
        <br>At the beginning of the algorithm, the partial sums need to be
        null. Then, the generated demand (variates) will be added 
        incrementally.
    */
    ioPSHolderHolder.begin();
    PartialSumHolder& firstPartialSumHolder = 
      ioPSHolderHolder.getCurrentPartialSumHolder();
    firstPartialSumHolder.initSize (K);

    for (int k=1 ; k <= K; k++) {
      firstPartialSumHolder.addPartialSum (0.0);
    }

    /** 
        Iterate on the classes/buckets, from 1 to n-1.
        Note that n-1 corresponds to the size of the parameter list,
        i.e., n corresponds to the number of classes/buckets.
    */
    ioBucketHolder.begin();
    ioPSHolderHolder.iterate();
    int Kj = K;
    int lj = 0;
    const int cabinCapacityInt = static_cast<int> (iCabinCapacity);
    for (short j = 1 ; j <= nbOfClasses - 1; 
	 ++j, ioBucketHolder.iterate(), ioPSHolderHolder.iterate()) {
      // DEBUG
      STDAIR_LOG_DEBUG ("K" << j << " = " << Kj);

      /** Retrieve Bucket(j) (current) and Bucket(j+1) (next). */
      Bucket& currentBucket = ioBucketHolder.getCurrentBucket();
      Bucket& nextBucket = ioBucketHolder.getNextBucket();

      // STEP 1.
      /** 
          Initialise the random generator with the distribution parameters of
          the demand for the current class/bucket, j.
      */
      const FldDistributionParameters& aDistribParams = 
        currentBucket.getDistributionParameters();
      Gaussian gaussianDemandGenerator (aDistribParams);

      /** DEBUG
          STDAIR_LOG_DEBUG ("[" << j << "]: " << Kj << " values with N ( " 
          << aDistribParams.getMean() << ", "
          << aDistribParams.getStandardDeviation() << ").");
      */

      /**
         Iterate on the random draws: generate random variates, d(j,k)
         for the current class/bucket demand, j, and for k=1 to Kj.
      */
      VariateList_T aVariateList;

      PartialSumHolder& previousPartialSumList = 
        ioPSHolderHolder.getPreviousPartialSumHolder();
      PartialSumHolder& currentPartialSumList = 
        ioPSHolderHolder.getCurrentPartialSumHolder();
      currentPartialSumList.initSize (Kj);
      lDrawBasChronometer.start();
      for (int k=1; k <= Kj; k++) {
        const double djk = gaussianDemandGenerator.generateVariate();
        aVariateList.push_back (djk);

        /** 
            Calculate the partial sums:
            <br>
            S(j,k)= d(1,k) + d(2,k) + ... + d(j,k),for a given k and j=1 to n-1
            Note that n-1 corresponds to the size of the parameter list,
            i.e., n corresponds to the number of classes/buckets.
            <br>
            Hence: S(j,k) = S'(j-1, l+k) + d(j,k). 
        */
        const double spjm1lpk = 
          previousPartialSumList.getPartialSum (lj + k - 1);
        const double sjk = spjm1lpk + djk;
        currentPartialSumList.addPartialSum (sjk);

        /* DEBUG
           STDAIR_LOG_DEBUG ("d(" << j << ", " << k << "); " << djk 
           << "; S'(" << j-1 << ", " << lj+k << "); " << spjm1lpk
           << "; S(" << j << ", " << k << "); " << sjk);
        */
      }

      const double lDrawTimeValue = lDrawBasChronometer.elapsed();
      ioStudyStatManager.addMeasure ("DrawTime", lDrawTimeValue);
      
      // STEP 2.
      /**
         Sort the partial sum vectors S(j,k) on k, for the current j.
      */
      lSortBasChronometer.start();
      currentPartialSumList.sort ();
      const double lSortTimeValue = lSortBasChronometer.elapsed();
      ioStudyStatManager.addMeasure ("SortTime", lSortTimeValue);
      
      /** Retrieve the prices for Bucket(j) and Bucket(j+1). */
      const double pj = currentBucket.getAverageYield();
      const double pj1 = nextBucket.getAverageYield();

      /** Consistency check: the yield/price of a higher class/bucket 
          (with the j index lower) must be higher. */
      assert (pj > pj1);

      /** 
          The optimal index is defined as:
          lj = floor {[p(j)-p(j+1)]/p(j) . K}
      */
      const double ljdouble = std::floor (Kj * (pj - pj1) / pj);
      lj = static_cast<int> (ljdouble);
      
      /** DEBUG 
          STDAIR_LOG_DEBUG ("p(j+1)/p(j) = " << pj1 / pj << ", lj = " << lj 
          << ", Kj = " << Kj << " => " << Kj - lj << " points above y(j)");
      */
          
      /** Consistency check. */
      assert (lj >= 1 && lj < Kj);

      /** 
          The optimal protection is defined as:
          y(j) = 1/2 [S(j,lj) + S(j, lj+1)]
      */
      const double sjl = currentPartialSumList.getPartialSum (lj - 1);
      const double sjlp1 = currentPartialSumList.getPartialSum (lj + 1 - 1);
      const double yj = (sjl + sjlp1) / 2;

      /** DEBUG
          STDAIR_LOG_DEBUG ("S(j,l) = " << sjl << ", S(j,l+1) = " << sjlp1 
          << ", y(j) = " << yj);
      */

      // Set the cumulated protection for Bucket(j) (j ranging from 1 to n-1)
      currentBucket.setCumulatedProtection (yj);

      /** Compute the Bid-Price (Opportunity Cost) at index x
          (capacity) for x between y(j-1) et y(j). This OC can be
          proven to be equal to p(j)*Proba(D1+...+Dk>=x | D1 > y1,
          D1+D2 > y2, ..., D1+...+D(k-1) > y(k-1)). 
      */
      
      // Get the previous cumulated protection y(j-1).
      const double yjm1 = ioBucketHolder.getPreviousCumulatedProtection ();
      const int yjm1int = static_cast<int> (yjm1);
      const int yjint = static_cast<int> (yj);
      int currentIndex = 0;

      lBVPCalculationBasChronometer.start();
      for (int x = yjm1int + 1; 
           x <= yjint && x <= cabinCapacityInt; ++x) {
        currentIndex = currentPartialSumList.getLowerBound (x);
        const double bidPriceAtX = pj * (Kj - currentIndex) / Kj;
        ioBidPriceVector.push_back (bidPriceAtX);
      }   
      const double lBVPCalculationTimeValue =
        lBVPCalculationBasChronometer.elapsed();
      ioStudyStatManager.addMeasure ("BVPCalculationTime",
                                     lBVPCalculationTimeValue);

      /** Update Kj for the next loop. */
      Kj = Kj - lj;

      /** S'(j,k) = S(j,k). 
	  <br>The previousPartialSumList (S') now becomes equal to the 
	  currentPartialSumList (S) (by iteration on ioPSHolderHolder). */
    }

    // Set the protection of Bucket(n) to be equal to the capacity
    Bucket& currentBucket = ioBucketHolder.getCurrentBucket();
    currentBucket.setCumulatedProtection (iCabinCapacity);

    /** Compute the Bid-Price (Opportunity Cost) at index x
          (capacity) for x between y(n-1) et cabin capacity. This OC can be
          proven to be equal to p(n)*Proba(D1+...+Dn>=x | D1 > y1,
          D1+D2 > y2, ..., D1+...+D(n-1) > y(n-1)). */
    
    // Get the previous cumulated protection y(n-1).
    const double ynm1 = ioBucketHolder.getPreviousCumulatedProtection ();

    if (ynm1 < iCabinCapacity) {
      // STEP 1.
      const FldDistributionParameters& aDistribParams = 
        currentBucket.getDistributionParameters();
      Gaussian gaussianDemandGenerator (aDistribParams);
      
      VariateList_T aVariateList;
      
      PartialSumHolder& previousPartialSumList = 
        ioPSHolderHolder.getPreviousPartialSumHolder();
      PartialSumHolder& currentPartialSumList = 
        ioPSHolderHolder.getCurrentPartialSumHolder();
      currentPartialSumList.initSize (Kj);
      
      lDrawBasChronometer.start();
      for (int k = 1; k <= Kj; ++k) {
        const double djk = gaussianDemandGenerator.generateVariate();
        aVariateList.push_back (djk);
        
        const double spjm1lpk = 
          previousPartialSumList.getPartialSum (lj + k - 1);
        const double sjk = spjm1lpk + djk;
        currentPartialSumList.addPartialSum (sjk);
      }
      
      const double lDrawTimeValue = lDrawBasChronometer.elapsed();
      ioStudyStatManager.addMeasure ("DrawTime", lDrawTimeValue);
      
      // STEP 2.
      lSortBasChronometer.start();
      currentPartialSumList.sort ();
      const double lSortTimeValue = lSortBasChronometer.elapsed();
      ioStudyStatManager.addMeasure ("SortTime", lSortTimeValue);
      
      const int ynm1int = static_cast<int> (ynm1);
      const double pn = currentBucket.getAverageYield();
      int currentIndex = 0;
      
      lBVPCalculationBasChronometer.start();
      for (int x = ynm1int + 1; x <= cabinCapacityInt; ++x) {
        currentIndex = currentPartialSumList.getLowerBound (x);
        const double bidPriceAtX = pn * (Kj - currentIndex) / Kj;
        ioBidPriceVector.push_back (bidPriceAtX);
      }
      const double lBVPCalculationTimeValue =
        lBVPCalculationBasChronometer.elapsed();
      ioStudyStatManager.addMeasure ("BVPCalculationTime",
                                     lBVPCalculationTimeValue);
    }
    
    /**
       Re-calculate the values (protections, bkg limits and cumulated
       booking limits, the optimal revenue.
    */
    ioBucketHolder.recalculate ();
  }

  // ////////////////////////////////////////////////////////////////////////
  void MCOptimiser::
  legOptimisationByMC (const ResourceCapacity_T iCabinCapacity,
                       BucketHolder& ioBucketHolder,
                       BidPriceVector_T& ioBidPriceVector) {

    ioBucketHolder.begin();

    // Get the first bucket (the one with the highest average yield).
    Bucket& lFirstBucket = ioBucketHolder.getCurrentBucket();

    GeneratedDemandVector_T lPartialSumVector =
      lFirstBucket.getGeneratedDemandVector ();

    // Sort the vector from high to low.
    std::sort (lPartialSumVector.begin(), lPartialSumVector.end(),
               std::greater<double>());

    // Get the number of draws (K).
    const unsigned int K = lPartialSumVector.size();

    // Number of classes/buckets: n
    const short nbOfClasses = ioBucketHolder.getSize();
    
    /** 
        Iterate on the classes/buckets, from 1 to n-1.
        Note that n-1 corresponds to the size of the parameter list,
        i.e., n corresponds to the number of classes/buckets.
    */
    unsigned int Kj = K;
    //const int cabinCapacityInt = static_cast<int> (iCabinCapacity);
    for (short j = 1 ; j <= nbOfClasses - 1; ++j, ioBucketHolder.iterate()) {
      // DEBUG
      STDAIR_LOG_DEBUG ("K" << j << " = " << Kj);
      
      /** Retrieve Bucket(j) (current) and Bucket(j+1) (next). */
      Bucket& currentBucket = ioBucketHolder.getCurrentBucket();
      Bucket& nextBucket = ioBucketHolder.getNextBucket();

      /** Retrieve the prices for Bucket(j) and Bucket(j+1). */
      const double pj = currentBucket.getAverageYield();
      const double pj1 = nextBucket.getAverageYield();

      /** 
          The optimal index is defined as: 
          lj = floor {[p(j+1)/p(j)] . K}
      */
      const unsigned int lj = Kj - std::floor (Kj * (pj - pj1) / pj);

      // DEBUG
      STDAIR_LOG_DEBUG ("l" << j << " = " << lj);

      /*
      STDAIR_LOG_DEBUG ("p(j+1) = " << pj1 << std::endl
                        << "p(j) = " << pj << std::endl
                        << "Kj = " << Kj);
      */
      
      /** Consistency check. */
      assert (lj >= 1 && lj < Kj);

      /** 
          The optimal protection is defined as:
          y(j) = 1/2 [S(j,lj) + S(j, lj+1)]
      */
      const double sjl = lPartialSumVector.at (lj - 1);
      const double sjlp1 = lPartialSumVector.at (lj + 1 - 1);
      const double yj = (sjl + sjlp1) / 2;

      // Set the cumulated protection for Bucket(j) (j ranging from 1 to n-1)
      currentBucket.setCumulatedProtection (yj);

      /** Update Kj for the next loop. */
      Kj = lj;
      lPartialSumVector.resize (Kj);

      // Generated demand of the (j+1)th bucket for the next iteration.
      const GeneratedDemandVector_T& lNextGeneratedDemandVector =
        nextBucket.getGeneratedDemandVector ();

      for (unsigned int i = 0; i < Kj; ++i) {
        const double lGeneratedDemand = lNextGeneratedDemandVector.at(i);
        lPartialSumVector.at(i) += lGeneratedDemand;
      }

      // Sort the vector from high to low.
      std::sort (lPartialSumVector.begin(), lPartialSumVector.end(),
                 std::greater<double>());
    }

    // Set the protection of Bucket(n) to be equal to the capacity
    Bucket& currentBucket = ioBucketHolder.getCurrentBucket();
    currentBucket.setCumulatedProtection (iCabinCapacity);

    /**
       Re-calculate the values (protections, bkg limits and cumulated
       booking limits, the optimal revenue.
    */
    ioBucketHolder.recalculate ();
  }

}
