// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// RMOL
#include <rmol/bom/BucketHolder.hpp>
#include <rmol/factory/FacSupervisor.hpp>
#include <rmol/factory/FacBucketHolder.hpp>

namespace RMOL {

  FacBucketHolder* FacBucketHolder::_instance = NULL;

  // //////////////////////////////////////////////////////////////////////
  FacBucketHolder::~FacBucketHolder () {
    _instance = NULL;
  }

  // //////////////////////////////////////////////////////////////////////
  FacBucketHolder& FacBucketHolder::instance () {

    if (_instance == NULL) {
      _instance = new FacBucketHolder();
      assert (_instance != NULL);
      
      FacSupervisor::instance().registerBomFactory (_instance);
    }
    return *_instance;
  }

  // //////////////////////////////////////////////////////////////////////
  BucketHolder& FacBucketHolder::create (const double iCabinCapacity) {
    BucketHolder* aBucketHolder_ptr = NULL;

    aBucketHolder_ptr = new BucketHolder (iCabinCapacity);
    assert (aBucketHolder_ptr != NULL);

    // The new object is added to the Bom pool
    _pool.push_back (aBucketHolder_ptr);

    return *aBucketHolder_ptr;
  }

  // //////////////////////////////////////////////////////////////////////
  void FacBucketHolder::addBucket (BucketHolder& ioBucketHolder, 
				   Bucket& ioBucket) {
    ioBucketHolder._bucketList.push_back (&ioBucket);
  }

}
