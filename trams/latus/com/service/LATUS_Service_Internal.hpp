#ifndef __LATUS_SVC_LATUS_SERVICE_INTERNAL_HPP
#define __LATUS_SVC_LATUS_SERVICE_INTERNAL_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iostream>
#include <string>
// LATUS Common
#include <latus/com/service/ServiceContext.hpp>
#include <latus/com/service/ServiceContextManager.hpp>
// LATUS General
#include <latus/LatusTypes.hpp>

namespace LATUS {

  namespace COM {
  
    /** Interface for the LATUS Services. */
    class LATUS_Service_Internal {
      // Friends
      friend class FacSupervisor;
      friend class LATUS_ServiceAbstract;
    public:
      /** Provide the unique instance.
          <br>The singleton is instantiated when first used.
          @return LATUS_Service_Internal& */
      static LATUS_Service_Internal& instance();
    
      /** Set the logger parameters (level and stream). */
      void setLogParameters (const LOG::EN_LogLevel iLogLevel,
                             std::ostream& ioLogStream);

      /** Set the number of simulations to be run. */
      void setSimulationRunNumber (const int);

      /** Set the demand input filename (for test purposes). */
      void setDemandInputFilename (const std::string&);

      /** Set the schedule input filename (for test purposes). */
      void setScheduleInputFilename (const std::string&);

      /** Set the start date of the simulation. */
      void setStartDate (const DateTime_T&);

      /** Set the end date of the simulation. */
      void setEndDate (const DateTime_T&);

      /** Simulate. */
      void simulate () const;

    private:
      /** Initialiser. */
      void init ();
    
    
    private:
      // /////// Construction & Initialisation ////////
      // Constructor is private in order to ensure the singleton pattern.
      /** Constructor. */
      LATUS_Service_Internal ();

      /** Destructor.
          <br>The Destruction put the _instance to NULL
          in order to be clean for the next
          LATUS_Service_Internal::instance(). */
      ~LATUS_Service_Internal();
    
      /** The unique instance.*/
      static LATUS_Service_Internal* _instance;

    
    private:
      // //////// Service Context Management ///////    
      /** Add a specific ServiceContext object to the dedicated list.
          <br>Note that the ServiceContext should have been initialised
          with its ModuleDescription (type and name). */
      void createAndRegisterSpecificServiceContext (const ModuleDescription&);

      /** Get the Specific Service Context (NULL if it does not exist). */
      ServiceContext& getServiceContext (const ModuleDescription&) const;

      /** Common Service Context. */
      ServiceContextManager _serviceContextManager;
    };
  }
}
#endif // __LATUS_SVC_LATUS_SERVICE_INTERNAL_HPP
