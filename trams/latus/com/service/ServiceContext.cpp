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
    ServiceContext::
    ServiceContext (const ModuleDescription& iModuleDescription) :
      _worldSchedule (NULL), _network (NULL),
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
    const ModuleDescription& ServiceContext::getModuleDescription() const {
      return _moduleDescription;
    }

    // //////////////////////////////////////////////////////////////////////
    const ModuleDescription::EN_ModuleType ServiceContext::
    getModuleType() const {
      return _moduleDescription.getType();
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string& ServiceContext::getModuleName() const {
      return _moduleDescription.getName();
    }

    // //////////////////////////////////////////////////////////////////////
    WorldSchedule& ServiceContext::getWorldSchedule () const {
      assert (_worldSchedule != NULL);
      return *_worldSchedule;
    }

    // //////////////////////////////////////////////////////////////////////
    Network& ServiceContext::getNetwork () const {
      assert (_network != NULL);
      return *_network;
    }
  }
}
