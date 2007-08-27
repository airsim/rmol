// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/basic/BasConst_LATUS_Service.hpp>
#include <latus/com/basic/ModuleDescription.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacServiceContext.hpp>
#include <latus/com/service/ServiceContext.hpp>
#include <latus/com/service/LATUS_Service_Internal.hpp>
#include <latus/com/service/Logger.hpp>
// LATUS Simulator
#include <latus/sim/service/LATUS_SIM.hpp>
// LATUS Travel Solution Provider
#include <latus/tsp/service/LATUS_TSP.hpp>
// LATUS Inventory
#include <latus/inv/service/LATUS_INV.hpp>

namespace LATUS {

  namespace COM {
  
    LATUS_Service_Internal* LATUS_Service_Internal::_instance = NULL;
  
    // //////////////////////////////////////////////////////////////////////
    LATUS_Service_Internal::LATUS_Service_Internal () {
      // Initialise
      init ();
    }

    // //////////////////////////////////////////////////////////////////////
    LATUS_Service_Internal::~LATUS_Service_Internal () {
      _instance = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    LATUS_Service_Internal& LATUS_Service_Internal::instance () {
      if (_instance == NULL) {
        _instance = new LATUS_Service_Internal();
        assert (_instance != NULL);
      
        FacSupervisor::instance().registerLatusService (_instance);
      }
      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_Service_Internal::init () {
      // TODO: create the services based on a XML configuration file.

      // Register the Simulator module
      const ModuleDescription lSimModule (ModuleDescription::SIM,
                                          DEFAULT_LATUS_SIM_MODULE_NAME);
      _serviceContextManager.createAndRegisterSpecificServiceContext (lSimModule);

      // Register the Travel Service Provider (TSP) module
      const ModuleDescription lTspModule (ModuleDescription::TSP,
                                          DEFAULT_LATUS_TSP_MODULE_NAME);
      _serviceContextManager.createAndRegisterSpecificServiceContext (lTspModule);

      // Register the Inventory module for BA
      const ModuleDescription lInvBAModule (ModuleDescription::INV,
                                            DEFAULT_LATUS_INV1_MODULE_NAME);
      _serviceContextManager.createAndRegisterSpecificServiceContext (lInvBAModule);
      ServiceContext& lInvBAServiceContext = getServiceContext (lInvBAModule);
      lInvBAServiceContext.setOwnerAirlineCode (DEFAULT_LATUS_INV1_MODULE_NAME);

      // Register the Inventory module for AA
      const ModuleDescription lInvAAModule (ModuleDescription::INV,
                                            DEFAULT_LATUS_INV2_MODULE_NAME);
      _serviceContextManager.createAndRegisterSpecificServiceContext (lInvAAModule);
      ServiceContext& lInvAAServiceContext = getServiceContext (lInvAAModule);
      lInvAAServiceContext.setOwnerAirlineCode (DEFAULT_LATUS_INV2_MODULE_NAME);
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_Service_Internal::
    createAndRegisterSpecificServiceContext (const ModuleDescription& iModuleDescription) {
      // Delegate to the underlying ServiceContext Manager
      _serviceContextManager.createAndRegisterSpecificServiceContext (iModuleDescription);
    }

    // //////////////////////////////////////////////////////////////////////
    ServiceContext& LATUS_Service_Internal::
    getServiceContext (const ModuleDescription& iModuleDescription) const {
      // Delegate to the underlying ServiceContext Manager
      return _serviceContextManager.getSpecificContext (iModuleDescription);
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_Service_Internal::
    setLogParameters (const LOG::EN_LogLevel iLogLevel,
                      std::ostream& ioLogStream) {
      Logger::instance().setLogParameters (iLogLevel, ioLogStream);
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_Service_Internal::
    setSimulationRunNumber (const int iSimulationRunNumber) {
      const ModuleDescription lSimModule (ModuleDescription::SIM,
                                          DEFAULT_LATUS_SIM_MODULE_NAME);
      ServiceContext& lSimServiceContext = getServiceContext (lSimModule);
      lSimServiceContext.setSimulationRunNumber (iSimulationRunNumber);
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_Service_Internal::
    setDemandInputFilename (const std::string& iInputFilename) {
      const ModuleDescription lSimModule (ModuleDescription::SIM,
                                          DEFAULT_LATUS_SIM_MODULE_NAME);
      ServiceContext& lSimServiceContext = getServiceContext (lSimModule);
      lSimServiceContext.setDemandInputFilename (iInputFilename);
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_Service_Internal::
    setStartDate (const DateTime_T& iStartDate) {
      const ModuleDescription lSimModule (ModuleDescription::SIM,
                                          DEFAULT_LATUS_SIM_MODULE_NAME);
      ServiceContext& lSimServiceContext = getServiceContext (lSimModule);
      lSimServiceContext.setStartDate (iStartDate);
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_Service_Internal::
    setEndDate (const DateTime_T& iEndDate) {
      const ModuleDescription lSimModule (ModuleDescription::SIM,
                                          DEFAULT_LATUS_SIM_MODULE_NAME);
      ServiceContext& lSimServiceContext = getServiceContext (lSimModule);
      lSimServiceContext.setEndDate (iEndDate);
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_Service_Internal::
    setScheduleInputFilename (const std::string& iInputFilename) {
      const ModuleDescription lTspModule (ModuleDescription::TSP,
                                          DEFAULT_LATUS_TSP_MODULE_NAME);
      ServiceContext& lTspServiceContext = getServiceContext (lTspModule);
      lTspServiceContext.setScheduleInputFilename (iInputFilename);
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_Service_Internal::simulate () const {

      // Parse the CSV-formatted schedule input file, and generate the
      // corresponding Inventories for the airlines.
      const ModuleDescription lTspModule (ModuleDescription::TSP,
                                          DEFAULT_LATUS_TSP_MODULE_NAME);
      ServiceContext& lTspServiceContext = getServiceContext (lTspModule);
      TSP::LATUS_TSP::generateInventories (DEFAULT_LATUS_TSP_MODULE_NAME);

      // Call the main entry of the Simulator Service
      const ModuleDescription lSimModule (ModuleDescription::SIM,
                                          DEFAULT_LATUS_SIM_MODULE_NAME);
      ServiceContext& lSimServiceContext = getServiceContext (lSimModule);
      SIM::LATUS_SIM::simulate (DEFAULT_LATUS_SIM_MODULE_NAME);
    }

  }
}
