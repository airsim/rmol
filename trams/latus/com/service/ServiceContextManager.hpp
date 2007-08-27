#ifndef __LATUS_COM_SVC_SERVICE_CONTEXT_MANAGER_HPP
#define __LATUS_COM_SVC_SERVICE_CONTEXT_MANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <string>
// LATUS Common
#include <latus/com/basic/ModuleDescription.hpp>
#include <latus/com/basic/ModuleDescriptionComparator.hpp>

namespace LATUS {

  namespace COM {

    // Forward declarations
    class ServiceContext;
    
    /** Type for the list of specific service contexts. */
    typedef std::map<ModuleDescription, ServiceContext*,
                     ModuleDescriptionComparator> ServiceContextList_T;
    
    /** Inner class holding the context for the LATUS Service object. */
    class ServiceContextManager {
      /** The LATUS_Service class should be the sole class to get access to
          ServiceContext content: general users do not want to bother
          with a context interface. */
      friend class LATUS_Service_Internal;
    private:
      /** Get the Specific Service Context.
          <br>Note that an assertion will fail if there is no corresponding
          specific service context registered. */
      ServiceContext& getSpecificContext (const ModuleDescription&) const;

      /** Create and register a specific ServiceContext object (i.e., add it
          to the dedicated list).
          <br>The ServiceContext is initialised with the given
          ModuleDescription (type and name). */
    void createAndRegisterSpecificServiceContext (const ModuleDescription&);

      
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
