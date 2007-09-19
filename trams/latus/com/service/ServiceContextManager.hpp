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
    class Inventory;
    
    /** Type for the list of specific service contexts. */
    typedef std::map<ModuleDescription, ServiceContext*,
                     ModuleDescriptionComparator> ServiceContextList_T;

    /** Type for the list of Inventory service contexts only. */
    typedef std::map<AirlineCode_T, ServiceContext*> InvServiceContextList_T;
    
    /** Type for the list of Revenue Management System (RMS) service contexts
        only. */
    typedef std::map<AirlineCode_T, ServiceContext*> RmsServiceContextList_T;
    
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
      static const int getSimulationRunNumber ();

      /** Get the demand input filename (for test purposes). */
      static const std::string& getDemandInputFilename ();

      /** Get the schedule input filename (for test purposes). */
      static const std::string& getScheduleInputFilename ();

      /** Get the start date of the simulation. */
      static const DateTime_T& getStartDate ();

      /** Get the end date of the simulation. */
      static const DateTime_T& getEndDate ();

      /** Get the owner airline code. */
      static const AirlineCode_T&
      getOwnerAirlineCode (const std::string& iModuleName);
      
      
      // //////// Setters for the external callers ///////
      /** Set the number of simulations to be run. */
      static void setSimulationRunNumber (const int);

      /** Set the demand input filename (for test purposes). */
      static void setDemandInputFilename (const std::string&);

      /** Set the schedule input filename (for test purposes). */
      static void setScheduleInputFilename (const std::string&);

      /** Set the start date of the simulation. */
      static void setStartDate (const DateTime_T&);
      
      /** Set the end date of the simulation. */
      static void setEndDate (const DateTime_T&);

      /** Set the owner airline code. */
      static void setOwnerAirlineCode (const AirlineCode_T&,
                                       const std::string& iModuleName);
      
      
      // //////// Getters for the internal BOM ///////
      /** Get the WorldSchedule object reference. */
      static WorldSchedule& getWorldSchedule ();
      
      /** Get the Network object reference. */
      static Network& getNetwork ();

      /** Get the Inventory object reference. */
      static Inventory& getInventory (const std::string& iModuleName);

      /** Get the Inventory object reference. */
      static Inventory& getAirlineInventory (const AirlineCode_T&);

      
      // //////// Setters for the internal BOM ///////
      /** Set the WorldSchedule object reference. */
      static void setWorldSchedule (WorldSchedule& ioWorldSchedule);
      
      /** Set the Network object reference. */
      static void setNetwork (Network& ioNetwork);
      
      /** Set the Inventory object reference. */
      static void setInventory (Inventory& ioInventory,
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

      /** Get the Inventory Specific Service Context.
          <br>Note that an assertion will fail if there is no corresponding
          specific service context registered. */
      static ServiceContext& getInvSpecificContext (const AirlineCode_T&);
      
      /** Get the number of registered Inventory specific service contexts. */
      static unsigned short getInvSpecificContextNumber();
      
      /** Get the number of registered RMS specific service contexts. */
      static unsigned short getRmsSpecificContextNumber();
      
      /** Create and register a specific SIM ServiceContext object.
          <br>The SIM ServiceContext is initialised with a default module name.
          <br>That method calls createAndRegisterSpecificServiceContext()
          with the module type (i.e., SIM). */
      static void createAndRegisterSpecificSimServiceContext ();

      /** Create and register a specific CRS ServiceContext object.
          <br>The CRS ServiceContext is initialised with a default module name.
          <br>That method calls createAndRegisterSpecificServiceContext()
          with the module type (i.e., CRS). */
      static void createAndRegisterSpecificCrsServiceContext ();

      /** Create and register a specific TSP ServiceContext object.
          <br>The TSP ServiceContext is initialised with a default module name.
          <br>That method calls createAndRegisterSpecificServiceContext()
          with the module type (i.e., TSP). */
      static void createAndRegisterSpecificTspServiceContext ();

      /** Create and register a specific INV ServiceContext object.
          <br>The INV ServiceContext is initialised with the given module name.
          <br>That method calls createAndRegisterSpecificServiceContext()
          with the module type (i.e., INV). */
      void createAndRegisterSpecificInvServiceContextInternal (const AirlineCode_T&);

      /** Create and register a specific INV ServiceContext object.
          <br>The INV ServiceContext is initialised with the given module name.
          <br>That method calls createAndRegisterSpecificServiceContext()
          with the module type (i.e., INV). */
      static void createAndRegisterSpecificInvServiceContext (const AirlineCode_T&);

      /** Create and register a specific RMS ServiceContext object.
          <br>The RMS ServiceContext is initialised with the given module name.
          <br>That method calls createAndRegisterSpecificServiceContext()
          with the module type (i.e., RMS). */
      void createAndRegisterSpecificRmsServiceContextInternal (const AirlineCode_T&);

      /** Create and register a specific RMS ServiceContext object.
          <br>The RMS ServiceContext is initialised with the given module name.
          <br>That method calls createAndRegisterSpecificServiceContext()
          with the module type (i.e., RMS). */
      static void createAndRegisterSpecificRmsServiceContext (const AirlineCode_T&);

      /** Create and register a specific ServiceContext object (i.e., add it
          to the dedicated list).
          <br>The ServiceContext is initialised with the given
          ModuleDescription (type and name). */
      static void createAndRegisterSpecificServiceContext (const ModuleDescription&);

      /** Create and register a specific ServiceContext object (i.e., add it
          to the dedicated list).
          <br>The ServiceContext is initialised with the given
          ModuleDescription (type and name). */
      void createAndRegisterSpecificServiceContextInternal (const ModuleDescription&);

      /** For each Inventory specific service context, set the reference on
          the corresponding Inventory BOM object. */
      void registerInventoriesWithinServiceContexts() const;

      
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
      /** List for all the specific service contexts, without regard to their
          module types. Hence, that list contains the SIM specific service
          context as well as those for INV, CRS, etc. */
      ServiceContextList_T _specificContextList;

      /** List of Inventory (INV) specific service contexts only.
          <br>That list of Inventory (INV) specific service contexts is included
          in the general one (_specificContextList). */
      InvServiceContextList_T _invSpecificContextList;

      /** List of Revenue Management System (RMS) specific service contexts
          only.
          <br>That list of Revenue Management System (RMS) specific service
          contexts is included in the general one (_specificContextList). */
      RmsServiceContextList_T _rmsSpecificContextList;
    };

  }
}
#endif // __LATUS_COM_SVC_SERVICE_CONTEXT_MANAGER_HPP
