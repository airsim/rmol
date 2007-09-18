#ifndef __LATUS_COM_SVC_LATUS_SERVICEABSTRACT_HPP
#define __LATUS_COM_SVC_LATUS_SERVICEABSTRACT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/basic/ModuleDescription.hpp>
#include <latus/com/service/ServiceAbstract.hpp>

namespace LATUS {

  // Forward declarations
  class LATUS_Service;

  namespace COM {

    // Forward declarations
    class WorldSchedule;
    class Network;

    /** Base class representing each module interface (service),
        and giving an interface to the context for the LATUS Service object.
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
    class LATUS_ServiceAbstract : public ServiceAbstract {
      friend class LATUS::LATUS_Service;
    protected:
      /** Constructor. */
      LATUS_ServiceAbstract (const ModuleDescription&);

      /** Destructor. */
      ~LATUS_ServiceAbstract();


    protected:
      /** Default Constructors. */
      LATUS_ServiceAbstract ();
      LATUS_ServiceAbstract (const LATUS_ServiceAbstract&);


    protected:
      // /////// Context Management ////////
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
      /** Create and register a specific SIM ServiceContext object.
          <br>That method in turn calls
          ServiceContextManager::createAndRegisterSpecificServiceContext(). */
      static void
      createAndRegisterSpecificSimServiceContext (const std::string& iModuleName);
      
      /** Create and register a specific CRS ServiceContext object.
          <br>That method in turn calls
          ServiceContextManager::createAndRegisterSpecificServiceContext(). */
      static void
      createAndRegisterSpecificCrsServiceContext (const std::string& iModuleName);

      /** Create and register a specific TSP ServiceContext object.
          <br>That method in turn calls
          ServiceContextManager::createAndRegisterSpecificServiceContext(). */
      static void
      createAndRegisterSpecificTspServiceContext (const std::string& iModuleName);

      /** Create and register a specific INV ServiceContext object.
          <br>That method in turn calls
          ServiceContextManager::createAndRegisterSpecificServiceContext(). */
      static void
      createAndRegisterSpecificInvServiceContext (const std::string& iModuleName);

    };
    
  }
}
#endif // __LATUS_COM_SVC_LATUS_SERVICEABSTRACT_HPP
