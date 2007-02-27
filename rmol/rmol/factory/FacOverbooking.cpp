// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// RMOL
#include <rmol/bom/Overbooking.hpp>
#include <rmol/factory/FacSupervisor.hpp>
#include <rmol/factory/FacOverbooking.hpp>

namespace RMOL {

  FacOverbooking* FacOverbooking::_instance = NULL;

  // //////////////////////////////////////////////////////////////////////
  FacOverbooking::~FacOverbooking () {
    _instance = NULL;
  }

  // //////////////////////////////////////////////////////////////////////
  FacOverbooking& FacOverbooking::instance () {

    if (_instance == NULL) {
      _instance = new FacOverbooking();
      assert (_instance != NULL);
      
      FacSupervisor::instance().registerBomFactory (_instance);
    }
    return *_instance;
  }

  // //////////////////////////////////////////////////////////////////////
  Overbooking& FacOverbooking::create (const FldOverbookingPolicy& iPolicy) {
    Overbooking* aOverbooking_ptr = NULL;

    aOverbooking_ptr = new Overbooking (iPolicy);
    assert (aOverbooking_ptr != NULL);

    // The new object is added to the Bom pool
    _pool.push_back (aOverbooking_ptr);

    return *aOverbooking_ptr;
  }

}
