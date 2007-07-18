#ifndef __LATUS_COM_SVC_LATUS_SERVICEABSTRACT_HPP
#define __LATUS_COM_SVC_LATUS_SERVICEABSTRACT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/ModuleDescription.hpp>
#include <latus/com/service/ServiceAbstract.hpp>
#include <latus/com/service/ServiceContextManager.hpp>

namespace LATUS {

  namespace COM {

    /** Base class representing each module interface (service). */
    class LATUS_ServiceAbstract : public ServiceAbstract {
    public:
      /** Constructor. */
      LATUS_ServiceAbstract (const ModuleDescription&);

      /** Destructor. */
      ~LATUS_ServiceAbstract();
      
      /** Get the specific context. */
      ServiceContext& getServiceContext() const;
      
      /** Add a specific ServiceContext object to the dedicated list. */
      void registerSpecificServiceContext (ServiceContext& ioSpecific);

      /** Get the type of the specific module. */
      ModuleDescription::EN_ModuleType getModuleType() const {
        return _moduleDescription.getType();
      }

      /** Get the name of the specific module. */
      const std::string& getModuleName() const {
        return _moduleDescription.getName();
      }
      
    protected:
      /** Default Constructors. */
      LATUS_ServiceAbstract ();
      LATUS_ServiceAbstract (const LATUS_ServiceAbstract&);

      /** Initialiser.
          <br>A Service Context specific to the current service is created
          and registered through the ServiceContextManager. */
      void init ();
      
    protected:
      /** Specific Module. */
      COM::ModuleDescription _moduleDescription;
      
      /** Common Service Context. */
      ServiceContextManager _serviceContextManager;
    };
    
  }
}
#endif // __LATUS_COM_SVC_LATUS_SERVICEABSTRACT_HPP
