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
// RMOL
#include <rmol/bom/VariateList.hpp>
#include <rmol/bom/Gaussian.hpp>
#include <rmol/bom/Emsr.hpp>
#include <rmol/bom/BucketHolder.hpp>
#include <rmol/bom/EmsrUtils.hpp>
#include <rmol/bom/Bucket.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////
  void Emsr::
  heuristicOptimisationByEmsr (const ResourceCapacity_T iCabinCapacity,
                               BucketHolder& ioBucketHolder,
                               BidPriceVector_T& ioBidPriceVector) {
    // Number of classes/buckets: n
    const short nbOfClasses = ioBucketHolder.getSize();

    // Cabin capacity in integer.
    const int lCabinCapacity = static_cast<const int>(iCabinCapacity);

    // List of all EMSR values.
    EmsrValueList_T lEmsrValueList;

    /** 
        Iterate on the classes/buckets, from 1 to n.
        Note that n-1 corresponds to the size of the parameter list,
        i.e., n corresponds to the number of classes/buckets.
    */
    ioBucketHolder.begin();
    for (short j = 1; j <= nbOfClasses; j++, ioBucketHolder.iterate()) {
      Bucket& currentBucket = ioBucketHolder.getCurrentBucket();
      for (int k = 1; k <= lCabinCapacity; ++k) {
        const double emsrValue = EmsrUtils::computeEmsrValue (k, currentBucket);
        lEmsrValueList.push_back(emsrValue);
      }
    }

    // Sort the EMSR values from high to low.
    std::sort(lEmsrValueList.rbegin(), lEmsrValueList.rend());

    // Sanity check
    const int lEmsrValueListSize = lEmsrValueList.size();
    assert (lEmsrValueListSize >= lCabinCapacity);

    // Copy the EMSR sorted values to the BPV.
    EmsrValueList_T::const_iterator currentValue = lEmsrValueList.begin();
    for (int j = 0; j < lCabinCapacity; ++j, ++currentValue) {
      const double bidPrice = *currentValue;
      ioBidPriceVector.push_back(bidPrice);
    }
    lEmsrValueList.clear();
    
    // Build the protection levels and booking limits.
    if (nbOfClasses > 1) {
      int capacityIndex = 0;
      ioBucketHolder.begin();
      for (short j = 1; j <= nbOfClasses - 1; j++, ioBucketHolder.iterate()) {
        Bucket& currentBucket = ioBucketHolder.getCurrentBucket();
        Bucket& nextBucket = ioBucketHolder.getNextBucket();
        const double lNextYield = nextBucket.getAverageYield();
        while ((capacityIndex < lCabinCapacity)
               && (ioBidPriceVector.at(capacityIndex) > lNextYield)) {
            ++capacityIndex;
        }
        currentBucket.setCumulatedProtection (capacityIndex);
        nextBucket.setCumulatedBookingLimit (iCabinCapacity - capacityIndex);
      }
    }
  }

  // //////////////////////////////////////////////////////////////////
  void Emsr::
  heuristicOptimisationByEmsrA (const ResourceCapacity_T iCabinCapacity,
                                BucketHolder& ioBucketHolder) {
    // Number of classes/buckets: n
    const short nbOfClasses = ioBucketHolder.getSize();

    /** 
        Iterate on the classes/buckets, from 1 to n-1.
        Note that n-1 corresponds to the size of the parameter list,
        i.e., n corresponds to the number of classes/buckets.
    */
    ioBucketHolder.begin();
    Bucket& firstBucket = ioBucketHolder.getCurrentBucket();
    firstBucket.setCumulatedBookingLimit (iCabinCapacity);
    for (short j = 1; j <= nbOfClasses - 1; j++, ioBucketHolder.iterate()) {
      Bucket& nextBucket = ioBucketHolder.getNextBucket();

      // Initialise the protection for class/bucket j.
      double lProtectionLevel = 0.0;
      
      ioBucketHolder.begin();
      for(short k = 1; k <= j; k++) {
        Bucket& currentBucket = ioBucketHolder.getCurrentBucket();
        const double lPartialProtectionLevel =
          EmsrUtils::computeProtectionLevel (currentBucket, nextBucket);
        lProtectionLevel += lPartialProtectionLevel;
        if (k < j) {
          ioBucketHolder.iterate();
        }
      }
      Bucket& currentBucket = ioBucketHolder.getCurrentBucket();
      currentBucket.setCumulatedProtection (lProtectionLevel);

      // Compute the booking limit for the class/bucket j+1 (can be negative).
      const double lBookingLimit = iCabinCapacity - lProtectionLevel;
      
      // Set the booking limit for class/bucket j+1.
      nextBucket.setCumulatedBookingLimit (lBookingLimit);   
    }
  }

  // //////////////////////////////////////////////////////////////////
  void Emsr::heuristicOptimisationByEmsrAwithSellup 
  (const ResourceCapacity_T iCabinCapacity,
   BucketHolder& ioBucketHolder,
   SellupProbabilityVector_T& iSellupProbabilityVector){
   
    // Number of classes/Buckets: n
    const short nbOfBuckets = ioBucketHolder.getSize();

    // Set the booking limit of the highest class to the cabin capacity
    ioBucketHolder.begin();
    Bucket& highestBucket = ioBucketHolder.getCurrentBucket();
    highestBucket.setCumulatedBookingLimit (iCabinCapacity);
    
    // Set the booking limit for the rest n-1 classes
    // by iterating on the classes/Buckets from 1 to n-1
    for (short j=1; j <= nbOfBuckets-1; j++, ioBucketHolder.iterate()) {
      // Get the next class/bucket  (the next high fare class)
      Bucket& nextBucket = ioBucketHolder.getNextBucket();
      
      // Get the probability of sell-up from nextBucket to the next higher
      double sellupProbability = iSellupProbabilityVector[j-1];

      // Initialize protection level for the current class j
      double lProtectionLevel = 0.0;
      
      // Sum the protection levels for each higher fare class
      ioBucketHolder.begin();
      for (short k=1; k<=j; k++) {
        Bucket& higherBucket = ioBucketHolder.getCurrentBucket();

        double lPRotectionLevelAgainstAHigherBucket = 0.0;

        if (k == j) {
          lPRotectionLevelAgainstAHigherBucket =
            EmsrUtils::computeProtectionLevelwithSellup 
            (higherBucket, nextBucket, sellupProbability);
        } else {
          lPRotectionLevelAgainstAHigherBucket =
            EmsrUtils::computeProtectionLevelwithSellup 
            (higherBucket, nextBucket, 0);
          ioBucketHolder.iterate();
        }
      
        lProtectionLevel += lPRotectionLevelAgainstAHigherBucket;
      }

      // Set cumulated protection level for class j
      Bucket& currentBucket = ioBucketHolder.getCurrentBucket();
      currentBucket.setCumulatedProtection (lProtectionLevel);

      // Compute the booking limit for the class j+1 (can be negative) 
      const double lBookingLimit = iCabinCapacity - lProtectionLevel;

      // Set the booking limit for class j+1
      nextBucket.setCumulatedBookingLimit (lBookingLimit);
    }  
  }

  // //////////////////////////////////////////////////////////////////
  void Emsr::
  heuristicOptimisationByEmsrB (const ResourceCapacity_T iCabinCapacity,
                                BucketHolder& ioBucketHolder,
                                Bucket& ioAggregatedBucket) {
    // Number of classes/buckets: n
    const short nbOfClasses = ioBucketHolder.getSize();

    /** 
        Iterate on the classes/buckets, from 1 to n-1.
        Note that n-1 corresponds to the size of the parameter list,
        i.e., n corresponds to the number of classes/buckets.
    */
    ioBucketHolder.begin();
    Bucket& firstBucket = ioBucketHolder.getCurrentBucket();
    firstBucket.setCumulatedBookingLimit (iCabinCapacity);
    for (short j = 1; j <= nbOfClasses - 1; j++, ioBucketHolder.iterate()) {
      Bucket& currentBucket = ioBucketHolder.getCurrentBucket();
      Bucket& nextBucket = ioBucketHolder.getNextBucket();

      // Compute the aggregated class/bucket of classes/buckets 1,..,j.
      EmsrUtils::computeAggregatedBucket (ioAggregatedBucket,
                                          currentBucket);

      // Compute the protection level for the aggregated class/bucket
      // using the Little-Wood formular.
      const double lProtectionLevel =
        EmsrUtils::computeProtectionLevel (ioAggregatedBucket, nextBucket);

      // Set the protection level for class/bucket j.
      currentBucket.setCumulatedProtection (lProtectionLevel);

      // Compute the booking limit for class/bucket j+1 (can be negative).
      const double lBookingLimit = iCabinCapacity - lProtectionLevel;
      
      // Set the booking limit for class/bucket j+1.
      nextBucket.setCumulatedBookingLimit (lBookingLimit);
    }
  
  }
}
