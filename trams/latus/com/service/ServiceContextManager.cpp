// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/factory/FacServiceContext.hpp>
#include <latus/com/service/ServiceContextManager.hpp>
#include <latus/com/service/ServiceContext.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    ServiceContextManager::ServiceContextManager () {
      init ();
    }
  
    // //////////////////////////////////////////////////////////////////////
    ServiceContextManager::
    ServiceContextManager (const ServiceContextManager&) {
      init ();
    }

    // //////////////////////////////////////////////////////////////////////
    ServiceContextManager::~ServiceContextManager() {
    }

    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::init () {
    }

    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::
    createAndRegisterSpecificServiceContext (const ModuleDescription& iModuleDescription) {

      // Create a Service Context specific to the (*this) Service
      ServiceContext& lSpecificServiceContext =
        FacServiceContext::instance().create (iModuleDescription);

      // Register that specific Service Context
      const bool insertSucceeded =
        _specificContextList.
        insert (ServiceContextList_T::
                value_type (lSpecificServiceContext.getModuleDescription(),
                            &lSpecificServiceContext)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion of the specific context in ServiceContextManager failed for "
                         << lSpecificServiceContext.getModuleName());
        assert (insertSucceeded == true);
      }
    }

    // //////////////////////////////////////////////////////////////////////
    ServiceContext& ServiceContextManager::
    getSpecificContext (const ModuleDescription& iModuleDescription) const {
      ServiceContext* oServiceContext_ptr = NULL;
      
      ServiceContextList_T::const_iterator itContext =
        _specificContextList.find (iModuleDescription);

      if (itContext != _specificContextList.end()) {
        oServiceContext_ptr = itContext->second;
      }

      assert (oServiceContext_ptr != NULL);
      return *oServiceContext_ptr;
    }
    
  }
}
