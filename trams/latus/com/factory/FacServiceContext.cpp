// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/basic/ModuleDescription.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacServiceContext.hpp>
#include <latus/com/service/ServiceContext.hpp>

namespace LATUS {

  namespace COM {

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
    ServiceContext& FacServiceContext::
    create (const ModuleDescription& iModuleDescription) {
      ServiceContext* aServiceContext_ptr = NULL;

      aServiceContext_ptr = new ServiceContext (iModuleDescription);
      assert (aServiceContext_ptr != NULL);

      // The new object is added to the Bom pool
      _pool.push_back (aServiceContext_ptr);

      return *aServiceContext_ptr;
    }

  }
}
