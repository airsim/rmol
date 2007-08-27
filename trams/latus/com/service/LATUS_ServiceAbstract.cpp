// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/factory/FacServiceContext.hpp>
#include <latus/com/service/ServiceContext.hpp>
#include <latus/com/service/LATUS_ServiceAbstract.hpp>
#include <latus/com/service/LATUS_Service_Internal.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    LATUS_ServiceAbstract::LATUS_ServiceAbstract () {
    }

    // //////////////////////////////////////////////////////////////////////
    LATUS_ServiceAbstract::~LATUS_ServiceAbstract () {
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::
    createAndRegisterSpecificServiceContext (const ModuleDescription& iModuleDescription) {
      // Create and register a Service Context specific to the given module
      LATUS_Service_Internal::instance().
        createAndRegisterSpecificServiceContext (iModuleDescription);
    }

    // //////////////////////////////////////////////////////////////////////
    ServiceContext& LATUS_ServiceAbstract::
    getServiceContext (const ModuleDescription& iModuleDescription) {
      return LATUS_Service_Internal::instance().
        getServiceContext (iModuleDescription);
    }

  }
}
