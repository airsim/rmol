// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/service/ServiceContextManager.hpp>
#include <latus/com/service/ServiceContext.hpp>

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
    registerSpecificServiceContext (ServiceContext& ioSpecificService) {

      const bool insertSucceeded =
        _specificContextList.
        insert (ServiceContextList_T::
                value_type (ioSpecificService.getModuleName(),
                            &ioSpecificService)).second;
      if (insertSucceeded == false) {
        // TODO: debug
      }

    }

    // //////////////////////////////////////////////////////////////////////
    ServiceContext* ServiceContextManager::
    getSpecificContext (const ModuleDescription& iModuleDescription) const {
      ServiceContext* oServiceContext_ptr = NULL;
      
      ServiceContextList_T::const_iterator itContext =
        _specificContextList.find (iModuleDescription.getName());

      if (itContext != _specificContextList.end()) {
        oServiceContext_ptr = itContext->second;
      }

      return oServiceContext_ptr;
    }
    
  }
}
