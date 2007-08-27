#ifndef __LATUS_COM_SVC_LATUS_SERVICEABSTRACT_HPP
#define __LATUS_COM_SVC_LATUS_SERVICEABSTRACT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/ModuleDescription.hpp>
#include <latus/com/service/ServiceAbstract.hpp>

namespace LATUS {

  namespace COM {

    // Forward declarations
    class ServiceContext;

    /** Base class representing each module interface (service). */
    class LATUS_ServiceAbstract : public ServiceAbstract {
    public:
      /** Constructor. */
      LATUS_ServiceAbstract (const ModuleDescription&);

      /** Destructor. */
      ~LATUS_ServiceAbstract();
      
      /** Get the service context specific to the given module description
          (type and name). */
      static ServiceContext& getServiceContext (const ModuleDescription&);
      
      /** Add a specific ServiceContext object to the dedicated list. */
      static void createAndRegisterSpecificServiceContext (const ModuleDescription&);

    protected:
      /** Default Constructors. */
      LATUS_ServiceAbstract ();
      LATUS_ServiceAbstract (const LATUS_ServiceAbstract&);
    };
    
  }
}
#endif // __LATUS_COM_SVC_LATUS_SERVICEABSTRACT_HPP
