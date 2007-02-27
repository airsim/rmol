// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// RMOL
#include <rmol/service/ServiceContext.hpp>
#include <rmol/factory/FacSupervisor.hpp>
#include <rmol/factory/FacServiceContext.hpp>

namespace RMOL {

  FacServiceContext* FacServiceContext::_instance = NULL;

  // //////////////////////////////////////////////////////////////////////
  FacServiceContext::~FacServiceContext () {
    _instance = NULL;
  }

  // //////////////////////////////////////////////////////////////////////
  FacServiceContext& FacServiceContext::instance () {

    if (_instance == NULL) {
      _instance = new FacServiceContext();
      assert (_instance != NULL);
      
      FacSupervisor::instance().registerServiceFactory (_instance);
    }
    return *_instance;
  }

  // //////////////////////////////////////////////////////////////////////
  ServiceContext& FacServiceContext::create () {
    ServiceContext* aServiceContext_ptr = NULL;

    aServiceContext_ptr = new ServiceContext ();
    assert (aServiceContext_ptr != NULL);

    // The new object is added to the Bom pool
    _pool.push_back (aServiceContext_ptr);

    return *aServiceContext_ptr;
  }

  // //////////////////////////////////////////////////////////////////////
  ServiceContext& FacServiceContext::
  create (const ResourceCapacity_T iResourceCapacity) {
    ServiceContext* aServiceContext_ptr = NULL;

    aServiceContext_ptr = new ServiceContext (iResourceCapacity);
    assert (aServiceContext_ptr != NULL);

    // The new object is added to the Bom pool
    _pool.push_back (aServiceContext_ptr);

    return *aServiceContext_ptr;
  }

}
