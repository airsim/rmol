// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/service/ServiceContext.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    ServiceContext::ServiceContext () :
      _moduleDescription (ModuleDescription::COM, "COM") {
      init ();
    }
  
    // //////////////////////////////////////////////////////////////////////
    ServiceContext::ServiceContext (const ServiceContext& iServiceContext) :
      _moduleDescription (iServiceContext.getModuleType(),
                          iServiceContext.getModuleName()) {
      init ();
    }

    // //////////////////////////////////////////////////////////////////////
    ServiceContext::
    ServiceContext (const ModuleDescription& iModuleDescription) :
      _moduleDescription (iModuleDescription.getType(),
                          iModuleDescription.getName()) {
      init ();
    }

    // //////////////////////////////////////////////////////////////////////
    ServiceContext::~ServiceContext() {
    }

    // //////////////////////////////////////////////////////////////////////
    void ServiceContext::init () {
    }

    // //////////////////////////////////////////////////////////////////////
    ModuleDescription::EN_ModuleType ServiceContext::getModuleType() const {
      return _moduleDescription.getType();
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string& ServiceContext::getModuleName() const {
      return _moduleDescription.getName();
    }

  }
}
