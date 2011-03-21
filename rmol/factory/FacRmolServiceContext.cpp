// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/service/FacSupervisor.hpp>
// RMOL
#include <rmol/factory/FacRmolServiceContext.hpp>
#include <rmol/service/RMOL_ServiceContext.hpp>

namespace RMOL {

  FacRmolServiceContext* FacRmolServiceContext::_instance = NULL;

  // //////////////////////////////////////////////////////////////////////
  FacRmolServiceContext::~FacRmolServiceContext() {
    _instance = NULL;
  }

  // //////////////////////////////////////////////////////////////////////
  FacRmolServiceContext& FacRmolServiceContext::instance() {

    if (_instance == NULL) {
      _instance = new FacRmolServiceContext();
      assert (_instance != NULL);
      
      stdair::FacSupervisor::instance().registerServiceFactory (_instance);
    }
    return *_instance;
  }

  // //////////////////////////////////////////////////////////////////////
  RMOL_ServiceContext& FacRmolServiceContext::create() {
    RMOL_ServiceContext* aServiceContext_ptr = NULL;

    aServiceContext_ptr = new RMOL_ServiceContext();
    assert (aServiceContext_ptr != NULL);

    // The new object is added to the Bom pool
    _pool.push_back (aServiceContext_ptr);

    return *aServiceContext_ptr;
  }

}
