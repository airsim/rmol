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
  BucketHolder::BucketHolder () : _cabinCapacity (100.0) {
  }

  // //////////////////////////////////////////////////////////////////////
  BucketHolder::BucketHolder (const double iCabinCapacity) :
    _cabinCapacity (iCabinCapacity) {
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
    ioOut << "Class; Mean; Std Dev; Protection; Bkg Limit; " << std::endl;

    BucketList_T::const_iterator itBucket = _bucketList.begin();
    for (short j=1; itBucket != _bucketList.end(); itBucket++, j++) {
      const Bucket& currentBucket = *itBucket;
      
      const double pj = currentBucket.getUpperYield();
      const double mj = currentBucket.getMean();
      const double sj = currentBucket.getStandardDeviation();
      const double yj = currentBucket.getProtection();
      const double bj = currentBucket.getBookingLimit();
      ioOut << j << "; " << std::fixed << std::setprecision (2)
            << pj << "; " << mj << "; " << sj << "; " << yj << "; " << bj
            << std::endl;
    }

    ioOut << "Note: Cabin Capacity = " << _cabinCapacity
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
  void BucketHolder::calculateOptimalRevenue () {
    _optimalRevenue = 0.0;

    for (BucketList_T::const_iterator itBucket = _bucketList.begin();
         itBucket != _bucketList.end(); itBucket++) {
      const Bucket& currentBucket = *itBucket;
      
      const double currentPrice = currentBucket.getAverageYield();
      const double currentProtection = currentBucket.getProtection();
      const double bucketOptimalRevenue = currentPrice * currentProtection;
      _optimalRevenue += bucketOptimalRevenue;
    }
  }
  
}
