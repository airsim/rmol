// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/service/FacSupervisor.hpp>
// AIRRAC Common
#include <airrac/factory/FacAirracServiceContext.hpp>
#include <airrac/service/AIRRAC_ServiceContext.hpp>

namespace AIRRAC {

  FacAirracServiceContext* FacAirracServiceContext::_instance = NULL;

  // //////////////////////////////////////////////////////////////////////
  FacAirracServiceContext::~FacAirracServiceContext() {
    _instance = NULL;
  }

  // //////////////////////////////////////////////////////////////////////
  FacAirracServiceContext& FacAirracServiceContext::instance() {

    if (_instance == NULL) {
      _instance = new FacAirracServiceContext();
      assert (_instance != NULL);
      
      stdair::FacSupervisor::instance().registerServiceFactory (_instance);
    }
    return *_instance;
  }

  // //////////////////////////////////////////////////////////////////////
  AIRRAC_ServiceContext& FacAirracServiceContext::create() {
    AIRRAC_ServiceContext* aServiceContext_ptr = NULL;

    aServiceContext_ptr = new AIRRAC_ServiceContext();
    assert (aServiceContext_ptr != NULL);

    // The new object is added to the Bom pool
    _pool.push_back (aServiceContext_ptr);

    return *aServiceContext_ptr;
  }

}
