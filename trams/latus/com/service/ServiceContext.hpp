#ifndef __LATUS_COM_SVC_SERVICE_CONTEXT_HPP
#define __LATUS_COM_SVC_SERVICE_CONTEXT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
// Boost (Extended STL)
#include <boost/date_time/gregorian/gregorian.hpp>
// LATUS General
#include <latus/LatusTypes.hpp>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/basic/ModuleDescription.hpp>
#include <latus/com/service/ServiceAbstract.hpp>

namespace LATUS {

  namespace COM {

    // Forward declarations
    class WholeDemand;
    class WorldSchedule;
    class Network;
    class Inventory;

    /** Inner class holding the context for the LATUS Service object. */
    class ServiceContext : public ServiceAbstract {
      // The ServiceContextManager class should be the sole class to
      // get access to the ServiceContext content: general users do not
      // want to bother with a context interface.
      friend class ServiceContextManager;
      friend class FacServiceContext;
    private:
      // //////// GETTERS /////////
      /** Get the demand input filename. */
      const std::string& getDemandInputFilename () const {
        return _demandInputFilename;
      }
      
      /** Get the schedule input filename. */
      const std::string& getScheduleInputFilename () const {
        return _scheduleInputFilename;
      }
      
      /** Get the number of simulations to be run. */
      const int getSimulationRunNumber () const {
        return _simulationRunNumber;
      }
      
      /** Get the start date of the simulation. */
      const DateTime_T& getStartDate () const {
        return _startDate;
      }

      /** Get the end date of the simulation. */
      const DateTime_T& getEndDate () const {
        return _endDate;
      }

      /** Get the owner airline code. */
      const AirlineCode_T& getOwnerAirlineCode () const {
        return _ownerAirlineCode;
      }


      // //////// SETTERS /////////
      /** Set the demand input filename. */
      void setDemandInputFilename (const std::string& iInputFilename) {
        _demandInputFilename = iInputFilename;
      }
      
      /** Set the schedule input filename. */
      void setScheduleInputFilename (const std::string& iInputFilename) {
        _scheduleInputFilename = iInputFilename;
      }
      
      /** Set the number of simulations to be run. */
      void setSimulationRunNumber (const int iSimulationRunNumber) {
        _simulationRunNumber = iSimulationRunNumber;
      }
      
      /** Set the start date of the simulation. */
      void setStartDate (const DateTime_T& iStartDate) {
        _startDate = iStartDate;
      }

      /** Set the end date of the simulation. */
      void setEndDate (const DateTime_T& iEndDate) {
        _endDate = iEndDate;
      }

      /** Set the owner airline code. */
      void setOwnerAirlineCode (const AirlineCode_T& iAirlineCode) {
        _ownerAirlineCode = iAirlineCode;
      }


    private:
      // //////// Getters for the internal BOM /////////
      /** Get the WholeDemand object reference. */
      WholeDemand& getWholeDemand () const;
      
      /** Get the WorldSchedule object reference. */
      WorldSchedule& getWorldSchedule () const;
      
      /** Get the Network object reference. */
      Network& getNetwork () const;
      
      /** Get the Inventory object reference. */
      Inventory& getInventory () const;
      

      // //////// Setters for the internal BOM ///////
      /** Set the WholeDemand object reference. */
      void setWholeDemand (WholeDemand& ioWholeDemand) {
        _wholeDemand = &ioWholeDemand;
      }
      
      /** Set the WorldSchedule object reference. */
      void setWorldSchedule (WorldSchedule& ioWorldSchedule) {
        _worldSchedule = &ioWorldSchedule;
      }
      
      /** Set the Network object reference. */
      void setNetwork (Network& ioNetwork) {
        _network = &ioNetwork;
      }
      
      /** Set the Inventory object reference. */
      void setInventory (Inventory& ioInventory) {
        _inventory = &ioInventory;
      }
      

    private:
      // Attributes
      /** Get the whole module description (type and name). */
      const ModuleDescription& getModuleDescription() const;

      /** Get the type of the module. */
      const ModuleDescription::EN_ModuleType getModuleType() const;

      /** Get the name of the module. */
      const std::string& getModuleName() const;

      
    private:
      // /////// Construction / initialisation ////////
      /** Constructors. */
      ServiceContext ();
      ServiceContext (const ServiceContext&);
      ServiceContext (const ModuleDescription&);
      void init ();
      
      /** Destructor. */
      ~ServiceContext();

      
    private:
      // /////// Parameters set by the external clients ///////
      /** Desccription (mainly, type and name) of the module (normally, COM). */
      ModuleDescription _moduleDescription;
      
      /** (SIM Service Context) Demand input filename. */
      std::string _demandInputFilename;

      /** (TSP Service Context) Schedule input filename. */
      std::string _scheduleInputFilename;

      /** (SIM Service Context) Number of simulations to be run. */
      int _simulationRunNumber;

      /** (SIM Service Context) Simulation length (time length) / date range
          for the simulation. */
      DateTime_T _startDate;
      DateTime_T _endDate;

      /** (INV and RMS Service Contexts) Owner airline code. */
      AirlineCode_T _ownerAirlineCode;

    private:
      // ////////// BOM holders //////////
      /** (DEG ServiceContext) Whole Demand. */
      WholeDemand* _wholeDemand;

      /** (TSP ServiceContext) World Schedule. */
      WorldSchedule* _worldSchedule;

      /** (TSP ServiceContext) Network. */
      Network* _network;

      /** (INV ServiceContext) Inventory. */
      Inventory* _inventory;
    };

  }
}
#endif // __LATUS_COM_SVC_SERVICE_CONTEXT_HPP
