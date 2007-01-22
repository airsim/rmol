// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iostream>
#include <iomanip>
// RMOL
#include "BucketHolder.hpp"

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  BucketHolder::BucketHolder () :
    _cabinCapacity (100.0),
    _totalMeanDemand (0.0), _demandFactor (0.0), _optimalRevenue (0.0) {
  }

  // //////////////////////////////////////////////////////////////////////
  BucketHolder::BucketHolder (const double iCabinCapacity) :
    _cabinCapacity (iCabinCapacity),
    _totalMeanDemand (0.0), _demandFactor (0.0), _optimalRevenue (0.0) {
  }

  // //////////////////////////////////////////////////////////////////////
  BucketHolder::~BucketHolder() {
    _bucketList.clear ();
  }

  // //////////////////////////////////////////////////////////////////////
  const short BucketHolder::getSize () const {
    return _bucketList.size();
  }

  // //////////////////////////////////////////////////////////////////////
  void BucketHolder::toStream (std::ostream& ioOut) const {
    // Generate a CSV (Comma Separated Values) output
    ioOut << "Class; Price; Mean; Std Dev; Protection; Cum. Protection; Cum. Bkg Limit; "
          << std::endl;

    BucketList_T::const_iterator itBucket = _bucketList.begin();
    for (short j=1; itBucket != _bucketList.end(); itBucket++, j++) {
      const Bucket& currentBucket = *itBucket;
      
      const double pj = currentBucket.getUpperYield();
      const double mj = currentBucket.getMean();
      const double sj = currentBucket.getStandardDeviation();
      const double proj = currentBucket.getProtection();
      const double yj = currentBucket.getCumulatedProtection();
      const double bj = currentBucket.getCumulatedBookingLimit();
      ioOut << j << "; " << std::fixed << std::setprecision (2)
            << pj << "; " << mj << "; " << sj << "; " << proj << "; " << yj
            << "; " << bj << std::endl;
    }

    ioOut << "Cabin Capacity = " << _cabinCapacity
          << "; Total Mean Demand = " << _totalMeanDemand
          << "; Demand Factor = " << _demandFactor
          << "; Optimal Revenue = " << _optimalRevenue << std::endl;

  }

  // //////////////////////////////////////////////////////////////////////
  void BucketHolder::display () const {
    toStream (std::cout);
  }

  // //////////////////////////////////////////////////////////////////////
  Bucket& BucketHolder::getCurrentBucket () {
    return *_itCurrentBucket;
  }

  // //////////////////////////////////////////////////////////////////////
  Bucket& BucketHolder::getNextBucket () {
    return *_itNextBucket;
  }

  // //////////////////////////////////////////////////////////////////////
  void BucketHolder::addBucket (const Bucket& iBucket) {
    _bucketList.push_back (iBucket);
  }

  // //////////////////////////////////////////////////////////////////////
  void BucketHolder::begin () {
    _itCurrentBucket = _bucketList.begin();
    _itNextBucket = _bucketList.begin();
    if (_itNextBucket != _bucketList.end()) {
      _itNextBucket++;
    }
  }

  // //////////////////////////////////////////////////////////////////////
  void BucketHolder::iterate () {
    if (_itCurrentBucket != _bucketList.end()) {
      _itCurrentBucket++;
    }
    if (_itNextBucket != _bucketList.end()) {
      _itNextBucket++;
    }
  }

  // //////////////////////////////////////////////////////////////////////
  void BucketHolder::calculateMeanDemandAndOptimalRevenue () {
    _totalMeanDemand = 0.0;
    _optimalRevenue = 0.0;

    for (BucketList_T::const_iterator itBucket = _bucketList.begin();
         itBucket != _bucketList.end(); itBucket++) {
      const Bucket& currentBucket = *itBucket;

      // Mean Demand
      const double currentMeanDemand = currentBucket.getMean();
      _totalMeanDemand += currentMeanDemand;

      // Optimal Revenue
      const double currentPrice = currentBucket.getAverageYield();
      const double currentProtection = currentBucket.getProtection();
      const double bucketOptimalRevenue = currentPrice * currentProtection;
      _optimalRevenue += bucketOptimalRevenue;
    }

    if (_cabinCapacity != 0.0) {
      _demandFactor = _totalMeanDemand / _cabinCapacity;
    }
  }
  
  // //////////////////////////////////////////////////////////////////////
  void BucketHolder::calculateProtectionAndBookingLimits () {
    // Number of classes/buckets: n
    const short nbOfClasses = getSize();

    /** 
        Iterate on the classes/buckets, from 1 to n-1.
        Note that n-1 corresponds to the size of the parameter list,
        i.e., n corresponds to the number of classes/buckets.
    */
    begin();
    Bucket& firstBucket = getCurrentBucket();

    // Set the cumulated booking limit of Bucket(1) to be equal to the capacity
    firstBucket.setCumulatedBookingLimit (_cabinCapacity);

    /** Set the protection of Bucket(1) to be equal to the cumulated protection
        of that first Bucket. */
    firstBucket.setProtection (firstBucket.getCumulatedProtection());

    for (short j=1 ; j <= nbOfClasses - 1; j++, iterate()) {
      /** Retrieve Bucket(j) (current) and Bucket(j+1) (next). */
      Bucket& currentBucket = getCurrentBucket();
      Bucket& nextBucket = getNextBucket();

      /**
         Set the cumulated booking limit for Bucket(j+1)
         (j ranging from 1 to n-1).
      */
      const double yjm1 = currentBucket.getCumulatedProtection();
      nextBucket.setCumulatedBookingLimit (_cabinCapacity - yjm1);

      /** Set the protection of Bucket(1) to be equal to
          the cumulated protection of that first Bucket. */
      const double yj = nextBucket.getCumulatedProtection();
      nextBucket.setProtection (yj - yjm1);
    }
  }

  // //////////////////////////////////////////////////////////////////////
  void BucketHolder::recalculate () {
    // Re-calculate the booking limits
    calculateProtectionAndBookingLimits();
    
    // Re-calculate the Optimal Revenue
    calculateMeanDemandAndOptimalRevenue();
  }

}
