#ifndef __LATUS_COM_SVC_SERVICE_CONTEXT_MANAGER_HPP
#define __LATUS_COM_SVC_SERVICE_CONTEXT_MANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <string>
// LATUS
#include <latus/LatusTypes.hpp>
#include <latus/com/basic/ModuleDescription.hpp>

namespace LATUS {

  namespace COM {

    // Forward declarations
    class ServiceContext;
    
    /** Type for the list of specific service contexts. */
    typedef std::map<const std::string,
                     ServiceContext*> ServiceContextList_T;
    
    /** Inner class holding the context for the LATUS Service object. */
    class ServiceContextManager {
      /** The LATUS_Service class should be the sole class to get access to
          ServiceContext content: general users do not want to bother
          with a context interface. */
      friend class LATUS_ServiceAbstract;
    private:
      /** Get the Specific Service Context (NULL if it does not exist). */
      ServiceContext* getSpecificContext (const ModuleDescription&) const;

      /** Add a specific ServiceContext object to the dedicated list.
          <br>Note that the ServiceContext should have been initialised
          with its ModuleDescription (type and name). */
      void registerSpecificServiceContext (ServiceContext& ioSpecific);

      
    private:
      /** Constructors. */
      ServiceContextManager ();
      ServiceContextManager (const ServiceContextManager&);
      void init ();
      
      /** Destructor. */
      ~ServiceContextManager();

    private:
      // List of specific contexts (for each specific module, e.g., SIM)
      ServiceContextList_T _specificContextList;
    };

  }
}
#endif // __LATUS_COM_SVC_SERVICE_CONTEXT_MANAGER_HPP
