#ifndef __LATUS_COM_SVC_SERVICE_CONTEXT_MANAGER_HPP
#define __LATUS_COM_SVC_SERVICE_CONTEXT_MANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <string>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/basic/ModuleDescription.hpp>
#include <latus/com/basic/ModuleDescriptionComparator.hpp>

namespace LATUS {

  namespace COM {

    // Forward declarations
    class ServiceContext;
    class WorldSchedule;
    class Network;
    
    /** Type for the list of specific service contexts. */
    typedef std::map<ModuleDescription, ServiceContext*,
                     ModuleDescriptionComparator> ServiceContextList_T;
    
    /** Inner class holding the context for the LATUS Service object.
        <br>The ServiceContextManager class implementation should be the sole
        part of the code to get access to ServiceContext content: general
        developers do not want to bother with a context interface.
        <br>Only the LATUS_Service and LATUS_ServiceAbstract classes (i.e.,
        all the Latus specific Service classes) gets an access to the
        ServiceContextManager interface: general developers do not want to
        bother with that interface.
        <br>All that means that, from within a Latus specific Service class
        implementation, getting or setting a parameter is done via the
        dedicated getters and setters (which then cascade the call to the
        ServiceContextManager singleton, which in turn cascades the call to
        the appropriate ServiceContext). */
    class ServiceContextManager {
      // Friends
      friend class FacSupervisor;
      friend class LATUS_ServiceAbstract;
    private:
      // /////// Interface to LATUS_Service ////////
      /** Provide the unique instance.
          <br>The singleton is instantiated when first used.
          @return ServiceContextManager& */
      static ServiceContextManager& instance();

      // //////// Getters for the external callers ///////
      /** Get the number of simulations to be run. */
      static const int getSimulationRunNumber (const std::string& iModuleName);

      /** Get the demand input filename (for test purposes). */
      static const std::string&
      getDemandInputFilename (const std::string& iModuleName);

      /** Get the schedule input filename (for test purposes). */
      static const std::string&
      getScheduleInputFilename (const std::string& iModuleName);

      /** Get the start date of the simulation. */
      static const DateTime_T& getStartDate (const std::string& iModuleName);

      /** Get the end date of the simulation. */
      static const DateTime_T& getEndDate (const std::string& iModuleName);

      /** Get the owner airline code. */
      static const AirlineCode_T&
      getOwnerAirlineCode (const std::string& iModuleName);
      
      
      // //////// Setters for the external callers ///////
      /** Set the number of simulations to be run. */
      static void setSimulationRunNumber (const int,
                                          const std::string& iModuleName);

      /** Set the demand input filename (for test purposes). */
      static void setDemandInputFilename (const std::string&,
                                          const std::string& iModuleName);

      /** Set the schedule input filename (for test purposes). */
      static void setScheduleInputFilename (const std::string&,
                                            const std::string& iModuleName);

      /** Set the start date of the simulation. */
      static void setStartDate (const DateTime_T&,
                                const std::string& iModuleName);
      
      /** Set the end date of the simulation. */
      static void setEndDate (const DateTime_T&,
                              const std::string& iModuleName);

      /** Set the owner airline code. */
      static void setOwnerAirlineCode (const AirlineCode_T&,
                                       const std::string& iModuleName);
      
      
      // //////// Getters for the internal BOM ///////
      /** Set the WorldSchedule object reference. */
      static WorldSchedule& getWorldSchedule (const std::string& iModuleName);
      
      /** Set the Network object reference. */
      static Network& getNetwork (const std::string& iModuleName);

      
      // //////// Setters for the internal BOM ///////
      /** Set the WorldSchedule object reference. */
      static void setWorldSchedule (WorldSchedule& ioWorldSchedule,
                                    const std::string& iModuleName);
      
      /** Set the Network object reference. */
      static void setNetwork (Network& ioNetwork,
                              const std::string& iModuleName);
      
      
    private:
      // /////// Context Management ////////
      /** Get the Specific Service Context.
          <br>Note that an assertion will fail if there is no corresponding
          specific service context registered. */
      static ServiceContext& getSpecificContext (const ModuleDescription&);

      /** Get the Specific Service Context.
          <br>Note that an assertion will fail if there is no corresponding
          specific service context registered. */
      ServiceContext& getSpecificContextInternal(const ModuleDescription&)const;

      /** Create and register a specific SIM ServiceContext object.
          <br>The SIM ServiceContext is initialised with the given module name.
          <br>That method calls createAndRegisterSpecificServiceContext()
          with the module type (i.e., SIM). */
      void createAndRegisterSpecificSimServiceContext (const std::string& iModuleName);

      /** Create and register a specific CRS ServiceContext object.
          <br>The CRS ServiceContext is initialised with the given module name.
          <br>That method calls createAndRegisterSpecificServiceContext()
          with the module type (i.e., CRS). */
      void createAndRegisterSpecificCrsServiceContext (const std::string& iModuleName);

      /** Create and register a specific TSP ServiceContext object.
          <br>The TSP ServiceContext is initialised with the given module name.
          <br>That method calls createAndRegisterSpecificServiceContext()
          with the module type (i.e., TSP). */
      void createAndRegisterSpecificTspServiceContext (const std::string& iModuleName);

      /** Create and register a specific INV ServiceContext object.
          <br>The INV ServiceContext is initialised with the given module name.
          <br>That method calls createAndRegisterSpecificServiceContext()
          with the module type (i.e., INV). */
      void createAndRegisterSpecificInvServiceContext (const std::string& iModuleName);

      /** Create and register a specific ServiceContext object (i.e., add it
          to the dedicated list).
          <br>The ServiceContext is initialised with the given
          ModuleDescription (type and name). */
      void createAndRegisterSpecificServiceContext (const ModuleDescription&);

      
    private:
      // /////// Construction & Initialisation ////////
      // Constructor is private in order to ensure the singleton pattern.
      /** Constructors. */
      ServiceContextManager ();
      ServiceContextManager (const ServiceContextManager&);
      void init ();
      
      /** Destructor.
          <br>The Destruction put the _instance to NULL
          in order to be clean for the next
          ServiceContextManager::instance(). */
      ~ServiceContextManager();

      /** The unique instance.*/
      static ServiceContextManager* _instance;

    private:
      // List of specific contexts (for each specific module, e.g., SIM)
      ServiceContextList_T _specificContextList;
    };

  }
}
#endif // __LATUS_COM_SVC_SERVICE_CONTEXT_MANAGER_HPP
