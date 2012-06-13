// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/VirtualClassStruct.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/basic/RandomGeneration.hpp>
#include <stdair/basic/BasConst_General.hpp>
// RMOL
#include <rmol/basic/BasConst_General.hpp>
#include <rmol/bom/MCOptimiser.hpp>

namespace RMOL {

  // // //////////////////////////////////////////////////////////////////////
  void MCOptimiser::
  optimalOptimisationByMCIntegration (stdair::LegCabin& ioLegCabin) { 
    // Retrieve the segment-cabin
    const stdair::SegmentCabinList_T lSegmentCabinList =
      stdair::BomManager::getList<stdair::SegmentCabin> (ioLegCabin);
    stdair::SegmentCabinList_T::const_iterator itSC = lSegmentCabinList.begin();
    assert (itSC != lSegmentCabinList.end());
    const stdair::SegmentCabin* lSegmentCabin_ptr = *itSC;
    assert (lSegmentCabin_ptr != NULL);
    
    // Retrieve the class list.
    const stdair::BookingClassList_T lBookingClassList =
      stdair::BomManager::getList<stdair::BookingClass> (*lSegmentCabin_ptr);

    // Retrieve the remaining cabin capacity.
    const stdair::Availability_T& lCap = ioLegCabin.getAvailabilityPool();
    const int lCapacity = static_cast<const int> (lCap);
    const stdair::UnsignedIndex_T lCapacityIndex =
      static_cast<const stdair::UnsignedIndex_T> ((lCapacity+abs(lCapacity))/2);
    
    // Retrieve the virtual class list.
    stdair::VirtualClassList_T& lVCList = ioLegCabin.getVirtualClassList();

    // Parse the virtual class list and compute the protection levels.
    stdair::VirtualClassList_T::iterator itCurrentVC = lVCList.begin();
    assert (itCurrentVC != lVCList.end());
    stdair::VirtualClassList_T::iterator itNextVC = itCurrentVC; ++itNextVC;

    // Initialise  the partial sum holder with the demand sample of the first
    // virtual class.
    stdair::VirtualClassStruct& lFirstVC = *itCurrentVC;
    stdair::GeneratedDemandVector_T lPartialSumHolder =
      lFirstVC.getGeneratedDemandVector();      

    // Initialise the booking limit for the first class, which is equal to
    // the remaining capacity.
    lFirstVC.setCumulatedBookingLimit (lCap);

    // Initialise bid price vector with the first element (index 0) equal to
    // the highest yield.
    ioLegCabin.emptyBidPriceVector();
    stdair::BidPriceVector_T& lBPV = ioLegCabin.getBidPriceVector();
    //const stdair::Yield_T& y1 = lFirstVC.getYield ();
    //lBPV.push_back (y1);
    stdair::UnsignedIndex_T idx = 1;    
    
    for (; itNextVC != lVCList.end(); ++itCurrentVC, ++itNextVC) {
      // Get the yields of the two classes.
      stdair::VirtualClassStruct& lCurrentVC = *itCurrentVC;
      stdair::VirtualClassStruct& lNextVC = *itNextVC;
      const stdair::Yield_T& yj = lCurrentVC.getYield ();
      const stdair::Yield_T& yj1 = lNextVC.getYield ();

      // Consistency check: the yield/price of a higher class/bucket 
      // (with the j index lower) must be higher.
      assert (yj > yj1);

      // Sort the partial sum holder.
      std::sort (lPartialSumHolder.begin(), lPartialSumHolder.end());
      const stdair::UnsignedIndex_T K = lPartialSumHolder.size ();

      // Compute the optimal index lj = floor {[y(j)-y(j+1)]/y(j) . K}
      const double ljdouble = std::floor (K * (yj - yj1) / yj);
      stdair::UnsignedIndex_T lj =
        static_cast<stdair::UnsignedIndex_T> (ljdouble);
      
      // Consistency check. 
      assert (lj >= 1 && lj < K);

      //  The optimal protection: p(j) = 1/2 [S(j,lj) + S(j, lj+1)]
      const double sjl = lPartialSumHolder.at (lj - 1);
      const double sjlp1 = lPartialSumHolder.at (lj + 1 - 1);
      const double pj = (sjl + sjlp1) / 2;

      // Set the cumulated protection level for the current class.
      lCurrentVC.setCumulatedProtection (pj);
      // Set the cumulated booking limit for the next class.
      lNextVC.setCumulatedBookingLimit (lCap - pj);

      /** Compute the Bid-Price (Opportunity Cost) at index x
          (capacity) for x between p(j-1) et p(j). This OC can be
          proven to be equal to y(j) * Proba (D1 +...+ Dj >= x | D1 > p1,
          D1 + D2 > p2, ..., D1 +... + D(j-1) > p(j-1)). */
      const stdair::UnsignedIndex_T pjint = static_cast<const int> (pj);
      stdair::GeneratedDemandVector_T::iterator itLowerBound =
        lPartialSumHolder.begin();
      for (; idx <= pjint && idx <= lCapacityIndex; ++idx) {
        itLowerBound =
          std::lower_bound (itLowerBound, lPartialSumHolder.end(), idx);
        const stdair::UnsignedIndex_T pos =
          itLowerBound - lPartialSumHolder.begin();

        const stdair::BidPrice_T lBP = yj * (K - pos) / K;
        lBPV.push_back (lBP);
      }

      // Update the partial sum holder.
      const stdair::GeneratedDemandVector_T& lNextPSH =
        lNextVC.getGeneratedDemandVector();
      assert (K <= lNextPSH.size());
      for (stdair::UnsignedIndex_T i = 0; i < K - lj; ++i) {
        lPartialSumHolder.at(i) = lPartialSumHolder.at(i + lj) + lNextPSH.at(i);
      }
      lPartialSumHolder.resize (K - lj);
    }
    
    /** Compute the Bid-Price (Opportunity Cost) at index x
          (capacity) for x between p(j-1) et cabin capacity. This OC can be
          proven to be equal to y(n) * Proba (D1 +...+ Dn >= x | D1 > p1,
          D1 + D2 > p2, ..., D1 +... + D(n-1) > p(n-1)). */
    stdair::VirtualClassStruct& lLastVC = *itCurrentVC;
    const stdair::Yield_T& yn = lLastVC.getYield();
    stdair::GeneratedDemandVector_T::iterator itLowerBound =
      lPartialSumHolder.begin();
    for (; idx <= lCapacityIndex; ++idx) {
      itLowerBound =
        std::lower_bound (itLowerBound, lPartialSumHolder.end(), idx);
      const stdair::UnsignedIndex_T pos =
        itLowerBound - lPartialSumHolder.begin();
      const stdair::UnsignedIndex_T K = lPartialSumHolder.size();
      const stdair::BidPrice_T lBP = yn * (K - pos) / K;
      lBPV.push_back (lBP);
    }
  }

  // ///////////////////////////////////////////////////////////////////
  stdair::GeneratedDemandVector_T MCOptimiser::
  generateDemandVector (const stdair::MeanValue_T& iMean,
                        const stdair::StdDevValue_T& iStdDev,
                        const stdair::NbOfSamples_T& K) {
    stdair::GeneratedDemandVector_T oDemandVector;
    if (iStdDev > 0) {
      stdair::RandomGeneration lGenerator (stdair::DEFAULT_RANDOM_SEED);
      for (unsigned int i = 0; i < K; ++i) {
        stdair::RealNumber_T lDemandSample =
          lGenerator.generateNormal (iMean, iStdDev);
        oDemandVector.push_back (lDemandSample);        
      }
    } else {
      for (unsigned int i = 0; i < K; ++i) {
        oDemandVector.push_back (iMean);
      }
    }
    return oDemandVector;
  }

  // /////////////////////////////////////////////////////////////////////////
  void MCOptimiser::
  optimisationByMCIntegration (stdair::LegCabin& ioLegCabin) {
    // Number of MC samples
    stdair::NbOfSamples_T K = DEFAULT_NUMBER_OF_DRAWS_FOR_MC_SIMULATION;

    const stdair::YieldLevelDemandMap_T& lYieldDemandMap =
      ioLegCabin.getYieldLevelDemandMap();
    assert (!lYieldDemandMap.empty());

    std::ostringstream oStr;
    oStr << "Yield list ";
    for (stdair::YieldLevelDemandMap_T::const_iterator itYD =
           lYieldDemandMap.begin();
         itYD != lYieldDemandMap.end(); ++itYD) {
      const stdair::Yield_T& y = itYD->first;
      oStr << y << " ";
    }

    STDAIR_LOG_DEBUG (oStr.str());
    ioLegCabin.emptyBidPriceVector();
    stdair::BidPriceVector_T& lBidPriceVector =
      ioLegCabin.getBidPriceVector();
    const stdair::Availability_T& lAvailabilityPool =
      ioLegCabin.getAvailabilityPool();
    // Initialise the minimal bid price to 1.0 (just to avoid problems
    // of division by zero).
    const stdair::BidPrice_T& lMinBP = 1.0;

    stdair::YieldLevelDemandMap_T::const_reverse_iterator itCurrentYD =
      lYieldDemandMap.rbegin();
    stdair::YieldLevelDemandMap_T::const_reverse_iterator itNextYD = itCurrentYD;
    ++itNextYD;
    
    // Initialise the partial sum holder
    stdair::MeanStdDevPair_T lMeanStdDevPair = itCurrentYD->second;
    stdair::GeneratedDemandVector_T lPartialSumHolder =
      generateDemandVector(lMeanStdDevPair.first, lMeanStdDevPair.second, K);
    
    stdair::UnsignedIndex_T idx = 1;
    for (; itNextYD!=lYieldDemandMap.rend(); ++itCurrentYD, ++itNextYD) {
      const stdair::Yield_T& yj = itCurrentYD->first;
      const stdair::Yield_T& yj1 = itNextYD->first;      
      // Consistency check: the yield/price of a higher class/bucket 
      // (with the j index lower) must be higher.
      assert (yj > yj1);
      // Sort the partial sum holder.
      std::sort (lPartialSumHolder.begin(), lPartialSumHolder.end());
      // STDAIR_LOG_DEBUG ("Partial sums : max = " << lPartialSumHolder.back()
      //                   << " min = " << lPartialSumHolder.front());
      K = lPartialSumHolder.size ();
      // Compute the optimal index lj = floor {[y(j)-y(j+1)]/y(j) . K}
      const double ljdouble = std::floor (K * (yj - yj1) / yj);
      stdair::UnsignedIndex_T lj =
        static_cast<stdair::UnsignedIndex_T> (ljdouble);
      // Consistency check. 
      assert (lj >= 1 && lj < K);
      //  The optimal protection: p(j) = 1/2 [S(j,lj) + S(j, lj+1)]
      const double sjl = lPartialSumHolder.at (lj - 1);
      const double sjlp1 = lPartialSumHolder.at (lj + 1 - 1);
      const double pj = (sjl + sjlp1) / 2;
      /** Compute the Bid-Price (Opportunity Cost) at index x
          (capacity) for x between p(j-1) et p(j). This OC can be
          proven to be equal to y(j) * Proba (D1 +...+ Dj >= x | D1 > p1,
          D1 + D2 > p2, ..., D1 +... + D(j-1) > p(j-1)). */
      const stdair::UnsignedIndex_T pjint = static_cast<const int> (pj);
      stdair::GeneratedDemandVector_T::iterator itLowerBound =
        lPartialSumHolder.begin();
      for (; idx <= pjint && idx <= lAvailabilityPool; ++idx) {
        itLowerBound =
          std::lower_bound (itLowerBound, lPartialSumHolder.end(), idx);
        const stdair::UnsignedIndex_T pos =
          itLowerBound - lPartialSumHolder.begin();        

        const stdair::BidPrice_T lBP = yj * (K - pos) / K;
        lBidPriceVector.push_back (lBP);
      }
      // Update the partial sum holder.
      lMeanStdDevPair = itNextYD->second;
      const stdair::GeneratedDemandVector_T& lNextDV =
        generateDemandVector (lMeanStdDevPair.first,
                              lMeanStdDevPair.second, K - lj);
      for (stdair::UnsignedIndex_T i = 0; i < K - lj; ++i) {
        lPartialSumHolder.at(i) = lPartialSumHolder.at(i + lj) + lNextDV.at(i);
      }
      lPartialSumHolder.resize (K - lj);      
    }
    /** Compute the Bid-Price (Opportunity Cost) at index x
          (capacity) for x between p(j-1) et cabin capacity. This OC can be
          proven to be equal to y(n) * Proba (D1 +...+ Dn >= x | D1 > p1,
          D1 + D2 > p2, ..., D1 +... + D(n-1) > p(n-1)). */
    /** But if this value is too low it will be replaced by a fixed minimal
        value.
        This is a form of protection between partners.
     */
    // STDAIR_LOG_DEBUG ("Partial sums : max = " << lPartialSumHolder.back()
    //                   << " min = " << lPartialSumHolder.front());
    
    std::sort (lPartialSumHolder.begin(), lPartialSumHolder.end());
    const stdair::Yield_T& yn = itCurrentYD->first;
    stdair::GeneratedDemandVector_T::iterator itLowerBound =
      lPartialSumHolder.begin();
    K = lPartialSumHolder.size();
    
    bool lMinBPReached = false;
    for (; idx <= lAvailabilityPool; ++idx) {
      itLowerBound =
        std::lower_bound (itLowerBound, lPartialSumHolder.end(), idx);
      
      if (!lMinBPReached) {
        const stdair::UnsignedIndex_T pos =
          itLowerBound - lPartialSumHolder.begin();      
        stdair::BidPrice_T lBP = yn * (K - pos) / K;
        
        if (lBP < lMinBP) {
          lBP = lMinBP; lMinBPReached = true;
        }       
        
        lBidPriceVector.push_back (lBP);
        
      } else {        
        lBidPriceVector.push_back (lMinBP);
      }      
      
    }
    
    // Updating the bid price values
    ioLegCabin.updatePreviousBidPrice();
    ioLegCabin.setCurrentBidPrice (lBidPriceVector.back());

    // Compute and display the bid price variation after optimisation
    const stdair::BidPrice_T lPreviousBP = ioLegCabin.getPreviousBidPrice();
    stdair::BidPrice_T lNewBP = ioLegCabin.getCurrentBidPrice();
    // Check
    assert (lPreviousBP != 0);
    stdair::BidPrice_T lBidPriceDelta = lNewBP - lPreviousBP;
        
    double lBidPriceVariation = 100*lBidPriceDelta/lPreviousBP;
    
    STDAIR_LOG_DEBUG ("Bid price: previous value " << lPreviousBP
                      << ", new value " << lNewBP
                      << ", variation " << lBidPriceVariation << " %"
                      <<", BPV size " << lBidPriceVector.size());
  }
  
}
