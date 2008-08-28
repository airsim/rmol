// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream>
#include <cmath>
#include <list>
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
    lEmsrValueList.sort();
    lEmsrValueList.reverse();

    assert (lEmsrValueList.size() >= lCabinCapacity);

    // Copy the EMSR sorted values to the BPV.
    EmsrValueList_T::iterator currentValue = lEmsrValueList.begin();
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
    
    /*
    // Number of classes/buckets: n
    const short nbOfClasses = ioBucketHolder.getSize();
    for (int s = 1; s <= iCabinCapacity; s++){
      double maxEmsrValue = 0.0;
      int highestBucket = 1;
      
      for(ioBucketHolder.begin();
          ioBucketHolder.hasNotReachedEnd();
          ioBucketHolder.iterate()){
        Bucket& currentBucket = ioBucketHolder.getCurrentBucket();
        
        // Compute EMSR value of the seat #s for class j
        double emsrForsj=0;
        // Evaluate if this class j has the highest EMSR value for
        // seat #s.  If so, maxEMSRValue is the EMSR value of j, and
        // j becomes temporarily the highest class.
        
        if(emsrForsj >= maxEmsrValue){
          maxEmsrValue = emsrForsj;
          ioBucketHolder.tag();
        }
      }
      
      Bucket& theHighestBucket = ioBucketHolder.getTaggedBucket();
      theHighestBucket._protection += 1.0;
    }
    */
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
