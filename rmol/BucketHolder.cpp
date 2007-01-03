// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iostream>
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
    ioOut << "Cabin capacity: " << _cabinCapacity << std::endl;

    BucketList_T::const_iterator itBucket = _bucketList.begin();
    for (short j=1; itBucket != _bucketList.end(); itBucket++, j++) {
      const Bucket& currentBucket = *itBucket;
      
      const double yj = currentBucket.getProtection();
      const double bj = currentBucket.getBookingLimit();
      ioOut << "Protection[" << j << "] = " << yj 
	    << ", BookingLimit[" << j << "] = " << bj 
	    << std::endl;
    }

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

}
