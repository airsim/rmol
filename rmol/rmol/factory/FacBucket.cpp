// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// RMOL
#include <rmol/factory/FacSupervisor.hpp>
#include <rmol/factory/FacBucket.hpp>

namespace RMOL {

  FacBucket* FacBucket::_instance = NULL;

  // //////////////////////////////////////////////////////////////////////
  FacBucket::~FacBucket () {
    _instance = NULL;
  }

  // //////////////////////////////////////////////////////////////////////
  FacBucket& FacBucket::instance () {

    if (_instance == NULL) {
      _instance = new FacBucket();
      assert (_instance != NULL);
      
      FacSupervisor::instance().registerFactory (_instance);
    }
    return *_instance;
  }

  // //////////////////////////////////////////////////////////////////////
  Bucket& FacBucket::create (const FldYieldRange& iYieldRange) {
    Bucket* aBucket_ptr = NULL;

    aBucket_ptr = new Bucket (iYieldRange);
    assert (aBucket_ptr != NULL);

    // The new object is added to the Bom pool
    _pool.push_back (aBucket_ptr);

    return *aBucket_ptr;
  }

  // //////////////////////////////////////////////////////////////////////
  Bucket& FacBucket::create (const FldYieldRange& iYieldRange,
                             const Demand& iDemand) {
    Bucket* aBucket_ptr = NULL;

    aBucket_ptr = new Bucket (iYieldRange, iDemand);
    assert (aBucket_ptr != NULL);

    // The new object is added to the Bom pool
    _pool.push_back (aBucket_ptr);

    return *aBucket_ptr;
  }

}
