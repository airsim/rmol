// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream>
#include <cmath>
#include <list>
#include <algorithm>
// StdAir
#include <stdair/stdair_rm_types.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/VirtualClassStruct.hpp>
// RMOL
#include <rmol/bom/Emsr.hpp>
#include <rmol/bom/EmsrUtils.hpp>

namespace RMOL {
  // //////////////////////////////////////////////////////////////////
  void Emsr::heuristicOptimisationByEmsrA (stdair::LegCabin& ioLegCabin) {
    stdair::VirtualClassList_T& lVirtualClassList =
      ioLegCabin.getVirtualClassList ();
    const stdair::CabinCapacity_T& lCabinCapacity =
      ioLegCabin.getOfferedCapacity();

    /** 
        Iterate on the classes/buckets, from 1 to n-1.
        Note that n-1 corresponds to the size of the parameter list,
        i.e., n corresponds to the number of classes/buckets.
    */
    stdair::VirtualClassList_T::iterator itVC =lVirtualClassList.begin();
    assert (itVC != lVirtualClassList.end());
    
    stdair::VirtualClassStruct& lFirstVC = *itVC;
    lFirstVC.setCumulatedBookingLimit (lCabinCapacity);
    ++itVC;
    for (; itVC != lVirtualClassList.end(); ++itVC) {
      stdair::VirtualClassStruct& lNextVC = *itVC;

      // Initialise the protection for class/bucket j.
      stdair::ProtectionLevel_T lProtectionLevel = 0.0;

      for(stdair::VirtualClassList_T::iterator itHigherVC =
            lVirtualClassList.begin(); itHigherVC != itVC; ++itHigherVC) {
        stdair::VirtualClassStruct& lHigherVC = *itHigherVC;
        const double lPartialProtectionLevel =
          EmsrUtils::computeProtectionLevel (lHigherVC, lNextVC);
        lProtectionLevel += lPartialProtectionLevel;
      }
      stdair::VirtualClassList_T::iterator itCurrentVC = itVC; --itCurrentVC;
      stdair::VirtualClassStruct& lCurrentVC = *itCurrentVC;
      lCurrentVC.setCumulatedProtection (lProtectionLevel);

      // Compute the booking limit for the class/bucket j+1 (can be negative).
      const double lBookingLimit = lCabinCapacity - lProtectionLevel;
      
      // Set the booking limit for class/bucket j+1.
      lNextVC.setCumulatedBookingLimit (lBookingLimit);   
    }
  }

  // //////////////////////////////////////////////////////////////////
  void Emsr::heuristicOptimisationByEmsrB (stdair::LegCabin& ioLegCabin) {
    stdair::VirtualClassList_T& lVirtualClassList =
      ioLegCabin.getVirtualClassList ();
    const stdair::CabinCapacity_T& lCabinCapacity =
      ioLegCabin.getOfferedCapacity();
    
    /** 
        Iterate on the classes/buckets, from 1 to n-1.
        Note that n-1 corresponds to the size of the parameter list,
        i.e., n corresponds to the number of classes/buckets.
    */
    stdair::VirtualClassList_T::iterator itVC =lVirtualClassList.begin();
    assert (itVC != lVirtualClassList.end());
    
    stdair::VirtualClassStruct& lFirstVC = *itVC;
    lFirstVC.setCumulatedBookingLimit (lCabinCapacity);
    ++itVC;
    stdair::VirtualClassStruct lAggregatedVC = lFirstVC;
    for (; itVC != lVirtualClassList.end(); ++itVC) {
      stdair::VirtualClassStruct& lNextVC = *itVC;

      // Compute the protection level for the aggregated class/bucket
      // using the Little-Wood formular.
      const stdair::ProtectionLevel_T lProtectionLevel =
        EmsrUtils::computeProtectionLevel (lAggregatedVC, lNextVC);

      // Set the protection level for class/bucket j.
      stdair::VirtualClassList_T::iterator itCurrentVC = itVC; --itCurrentVC;
      stdair::VirtualClassStruct& lCurrentVC = *itCurrentVC;
      lCurrentVC.setCumulatedProtection (lProtectionLevel);

      // Compute the booking limit for class/bucket j+1 (can be negative).
      const double lBookingLimit = lCabinCapacity - lProtectionLevel;
      
      // Set the booking limit for class/bucket j+1.
      lNextVC.setCumulatedBookingLimit (lBookingLimit);

      // Compute the aggregated class/bucket of classes/buckets 1,..,j.
      EmsrUtils::computeAggregatedVirtualClass (lAggregatedVC, lNextVC);

    } 
  }

  // //////////////////////////////////////////////////////////////////
  void Emsr::heuristicOptimisationByEmsr (stdair::LegCabin& ioLegCabin) {
    stdair::VirtualClassList_T& lVirtualClassList =
      ioLegCabin.getVirtualClassList ();
    const stdair::CabinCapacity_T& lCapacity = ioLegCabin.getOfferedCapacity();
    ioLegCabin.emptyBidPriceVector();
    stdair::BidPriceVector_T& lBidPriceVector =
      ioLegCabin.getBidPriceVector();
    
    // Cabin capacity in integer.
    const int lCabinCapacity = static_cast<const int> (lCapacity);

    // List of all EMSR values.
    stdair::EmsrValueList_T lEmsrValueList;

    /** 
        Iterate on the classes/buckets, from 1 to n.
        Note that n-1 corresponds to the size of the parameter list,
        i.e., n corresponds to the number of classes/buckets.
    */
    for (stdair::VirtualClassList_T::iterator itVC = lVirtualClassList.begin();
         itVC != lVirtualClassList.end(); ++itVC) {
      stdair::VirtualClassStruct& lCurrentVC = *itVC;
      for (int k = 1; k <= lCabinCapacity; ++k) {
        const double emsrValue = EmsrUtils::computeEmsrValue (k, lCurrentVC);
        lEmsrValueList.push_back(emsrValue);
      }
    }

    // Sort the EMSR values from high to low.
    std::sort(lEmsrValueList.rbegin(), lEmsrValueList.rend());

    // Sanity check
    const int lEmsrValueListSize = lEmsrValueList.size();
    assert (lEmsrValueListSize >= lCabinCapacity);

    // Copy the EMSR sorted values to the BPV.
    stdair::EmsrValueList_T::const_iterator itCurrentValue =
      lEmsrValueList.begin();
    for (int j = 0; j < lCabinCapacity; ++j, ++itCurrentValue) {
      const double lBidPrice = *itCurrentValue;
      lBidPriceVector.push_back (lBidPrice);
    }
    lEmsrValueList.clear();
    
    // Build the protection levels and booking limits.
    if (lVirtualClassList.size() > 1) {
      int lCapacityIndex = 0;
      for (stdair::VirtualClassList_T::iterator itVC =lVirtualClassList.begin();
           itVC != lVirtualClassList.end();) {
        stdair::VirtualClassStruct& lCurrentVC = *itVC;
        if (itVC != lVirtualClassList.end()) {
          ++itVC;
        }
        stdair::VirtualClassStruct& lNextVC = *itVC;
        const stdair::Yield_T lNextYield = lNextVC.getYield();
        while ((lCapacityIndex < lCabinCapacity)
               && (lBidPriceVector.at(lCapacityIndex) > lNextYield)) {
            ++lCapacityIndex;
        }
        lCurrentVC.setCumulatedProtection (lCapacityIndex);
        lNextVC.setCumulatedBookingLimit (lCapacity - lCapacityIndex);
      }
    }
  }

}
