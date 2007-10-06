// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/basic/BasConst_LATUS_Service.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/service/LATUS_ServiceAbstract.hpp>
#include <latus/com/service/Logger.hpp>
// LATUS General
#include <latus/LATUS_Service.hpp>
// LATUS Simulator
#include <latus/sim/service/LATUS_SIM.hpp>
// LATUS Discrete-Event Generator
#include <latus/deg/service/LATUS_DEG.hpp>
// LATUS Travel Solution Provider
#include <latus/tsp/service/LATUS_TSP.hpp>
// LATUS Inventory
#include <latus/inv/service/LATUS_INV.hpp>

namespace LATUS {

  // //////////////////////////////////////////////////////////////////////
  LATUS_Service::LATUS_Service () {
    // Initialise
    init ();
  }

  // //////////////////////////////////////////////////////////////////////
  LATUS_Service::~LATUS_Service () {
  }

  // //////////////////////////////////////////////////////////////////////
  void LATUS_Service::init () {
    // TODO: create the services based on a XML configuration file.

    // Register the Simulator (SIM) module
    COM::LATUS_ServiceAbstract::createAndRegisterSpecificSimServiceContext();

    // Register the Discrete-Event Generator (DEG) module
    COM::LATUS_ServiceAbstract::createAndRegisterSpecificDegServiceContext();

    // Register the Central Reservation System (CRS) module
    COM::LATUS_ServiceAbstract::createAndRegisterSpecificCrsServiceContext();

    // Register the Travel Service Provider (TSP) module
    COM::LATUS_ServiceAbstract::createAndRegisterSpecificTspServiceContext();

    // Register the Inventory module for BA
    COM::LATUS_ServiceAbstract::
      createAndRegisterSpecificInvServiceContext (COM::DEFAULT_LATUS_INV1_AIRLINE_CODE);

    // Register the Inventory module for AA
    COM::LATUS_ServiceAbstract::
      createAndRegisterSpecificInvServiceContext (COM::DEFAULT_LATUS_INV2_AIRLINE_CODE);
  }

  // //////////////////////////////////////////////////////////////////////
  void LATUS_Service::setLogParameters (const LOG::EN_LogLevel iLogLevel,
                                        std::ostream& ioLogStream) {
    COM::Logger::instance().setLogParameters (iLogLevel, ioLogStream);
  }

  // //////////////////////////////////////////////////////////////////////
  void LATUS_Service::setSimulationRunNumber (const int iSimulationRunNumber) {
    COM::LATUS_ServiceAbstract::setSimulationRunNumber (iSimulationRunNumber);
  }

  // //////////////////////////////////////////////////////////////////////
  void LATUS_Service::
  setScheduleInputFilename (const std::string& iInputFilename) {
    COM::LATUS_ServiceAbstract::setScheduleInputFilename (iInputFilename);
  }

  // //////////////////////////////////////////////////////////////////////
  void LATUS_Service::
  setDemandInputFilename (const std::string& iInputFilename) {
    COM::LATUS_ServiceAbstract::setDemandInputFilename (iInputFilename);
  }

  // //////////////////////////////////////////////////////////////////////
  void LATUS_Service::
  setWorldScheduleOutputFilename (const std::string& iOutputFilename) {
    COM::LATUS_ServiceAbstract::setWorldScheduleOutputFilename (iOutputFilename);
  }

  // //////////////////////////////////////////////////////////////////////
  void LATUS_Service::setStartDate (const boost::gregorian::date& iStartDate) {
    COM::LATUS_ServiceAbstract::setStartDate (iStartDate);
  }

  // //////////////////////////////////////////////////////////////////////
  void LATUS_Service::setEndDate (const boost::gregorian::date& iEndDate) {
    COM::LATUS_ServiceAbstract::setEndDate (iEndDate);
  }

  // //////////////////////////////////////////////////////////////////////
  void LATUS_Service::simulate () const {
    // Parse the CSV-formatted demand input file, and generate the
    // corresponding Demand (BOM) objects.
    DEG::LATUS_DEG::generateDemands ();

    // Parse the CSV-formatted schedule input file, and generate the
    // corresponding Inventories for the airlines.
    TSP::LATUS_TSP::generateInventories ();

    // Set the references to Inventory BOM objects within each of
    // the Inventory specific contexts.
    COM::LATUS_ServiceAbstract::registerInventoriesWithinServiceContexts ();

    // Call the main entry of the Simulator Service
    SIM::LATUS_SIM::simulate ();

    // Clean all the instantiated (BOM & Service) objects, so as to free
    // the corresponding memory.
    COM::FacSupervisor::instance().cleanFactory();
  }

}
