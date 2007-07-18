// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/factory/FacServiceContext.hpp>
#include <latus/com/service/ServiceContext.hpp>
#include <latus/com/service/LATUS_ServiceAbstract.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    LATUS_ServiceAbstract::LATUS_ServiceAbstract () :
      _moduleDescription (ModuleDescription::SIM, "SIM1") {
      init();
    }

    // //////////////////////////////////////////////////////////////////////
    LATUS_ServiceAbstract::
    LATUS_ServiceAbstract (const LATUS_ServiceAbstract& iService) :
      _moduleDescription (ModuleDescription::SIM, "SIM1") {
      init();
    }

    // //////////////////////////////////////////////////////////////////////
    LATUS_ServiceAbstract::
    LATUS_ServiceAbstract (const ModuleDescription& iModuleDescription) :
      _moduleDescription (iModuleDescription) {
      init();
    }

    // //////////////////////////////////////////////////////////////////////
    LATUS_ServiceAbstract::~LATUS_ServiceAbstract () {
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::init () {
      // Create a Service Context specific to the (*this) Service
      ServiceContext& lSpecificContext =
        FacServiceContext::instance().create (_moduleDescription);

      // Register that specific Service Context
      _serviceContextManager.registerSpecificServiceContext (lSpecificContext);
    }

    // //////////////////////////////////////////////////////////////////////
    ServiceContext& LATUS_ServiceAbstract::getServiceContext() const {

      ServiceContext* lSpecificContext_ptr =
        _serviceContextManager.getSpecificContext (_moduleDescription);

      assert (lSpecificContext_ptr != NULL);
      return *lSpecificContext_ptr;
    }

  }
  
}
