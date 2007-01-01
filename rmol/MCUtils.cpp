// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream>
#include <cmath>
// RMOL
#include "PartialSumList.hpp"
#include "VariateList.hpp"
#include "Gaussian.hpp"
#include "MCUtils.hpp"

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  void MCUtils::
  optimialOptimisationByMCIntegration (const int K, 
				       const double iCabinCapacity,
				       BucketList_T& ioBucketList) {
    // Number of classes/buckets: n
    const short nbOfClasses = ioBucketList.size();

    /** 
	Initialise the partial sum vector representing the last step within
	the algorithm below.
	<br>At the beginning of the algorithm, the partial sums need to be
	null. Then, the generated demand (variates) will be added 
	incrementally.
    */
    PartialSumList_T previousPartialSumList;
    for (int k=1 ; k <= K; k++) {
      previousPartialSumList.push_back (0.0);
    }

    /** 
	Iterate on the classes/buckets, from 1 to n-1.
	Note that n-1 corresponds to the size of the parameter list,
	i.e., n corresponds to the number of classes/buckets.
    */
    int Kj = K;
    int lj = 0;
    BucketList_T::iterator itBucket = ioBucketList.begin();
    BucketList_T::iterator itNextBucket = ioBucketList.begin();
    itNextBucket++;
    for (short j=1 ; j <= nbOfClasses - 1; itBucket++, itNextBucket++, j++) {
      /** Retrieve Bucket(j) (current) and Bucket(j+1) (next). */
      Bucket& currentBucket = *itBucket;
      const Bucket& nextBucket = *itNextBucket;

      // STEP 1.
      /** 
	  Initialise the random generator with the distribution parameters of
	  the demand for the current class/bucket, j.
      */
      const FldDistributionParameters& aDistribParams = 
	currentBucket.getDistributionParameters();
      const Gaussian gaussianDemandGenerator (aDistribParams);

      /** DEBUG
	  std::cout << "[" << j << "]: " << Kj << " values with N ( " 
	  << aDistribParams.getMean() << ", "
	  << aDistribParams.getStandardDeviation() << ")." << std::endl;
      */

      /**
	 Iterate on the random draws: generate random variates, d(j,k)
	 for the current class/bucket demand, j, and for k=1 to Kj.
      */
      VariateList_T aVariateList;
      PartialSumList_T currentPartialSumList;
      for (int k=1; k <= Kj; k++) {
	const double djk = gaussianDemandGenerator.generateVariate();
	aVariateList.push_back (djk);

	/** 
	    Calculate the partial sums:
	    <br>
	    S(j,k) = d(1,k) + d(2,k) + ... + d(j,k), for a given k and j=1 to n-1
	    Note that n-1 corresponds to the size of the parameter list,
	    i.e., n corresponds to the number of classes/buckets.
	    <br>
	    Hence: S(j,k) = S'(j-1, l+k) + d(j,k). 
	*/
	const double spjm1lpk = previousPartialSumList.at (lj + k - 1);
	const double sjk = spjm1lpk + djk;
	currentPartialSumList.push_back (sjk);

	/* DEBUG
	   std::cout << "d(" << j << ", " << k << "); " << djk 
	   << "; S'(" << j-1 << ", " << lj+k << "); " << spjm1lpk
	   << "; S(" << j << ", " << k << "); " << sjk << std::endl;
	*/
      }

      // STEP 2.
      /**
	 Sort the partial sum vectors S(j,k) on k, for the current j.
	 The STL implements the introsort algorithm, which has a worst case
	 complexity of O (N log N): http://www.sgi.com/tech/stl/sort.html
      */
      std::sort (currentPartialSumList.begin(), currentPartialSumList.end());

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
	  std::cout << "p(j+1)/p(j) = " << pj1 / pj << ", lj = " << lj 
	  << ", Kj = " << Kj << " => " << Kj - lj << " points above y(j)" 
	  << std::endl;
      */

      /** Consistency check. */
      assert (lj >= 1 && lj < Kj);

      // Update Kj for the next loop
      Kj = Kj - lj;

      /** 
	  The optimal protection is defined as:
	  y(j) = 1/2 [S(j,lj) + S(j, lj+1)]
      */
      const double sjl = currentPartialSumList.at (lj - 1);
      const double sjlp1 = currentPartialSumList.at (lj + 1 - 1);
      const double yj = (sjl + sjlp1) / 2;

      /** DEBUG
	  std::cout << "S(j,l) = " << sjl << ", S(j,l+1) = " << sjlp1 
	  << ", y(j) = " << yj << std::endl;
      */

      // Set the protection for Bucket(j) (j ranging from 1 to n-1)
      currentBucket.setProtection (yj);

      /** S'(j,k) = S(j,k). */
      previousPartialSumList = currentPartialSumList;
    }

    // Set the protection of Bucket(n) to be equal to the capacity:
    Bucket& currentBucket = *itBucket;
    currentBucket.setProtection (iCabinCapacity);
  }

}
