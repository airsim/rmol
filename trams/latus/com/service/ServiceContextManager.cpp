// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacServiceContext.hpp>
#include <latus/com/service/ServiceContextManager.hpp>
#include <latus/com/service/ServiceContext.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    ServiceContextManager* ServiceContextManager::_instance = NULL;
  
    // //////////////////////////////////////////////////////////////////////
    ServiceContextManager::ServiceContextManager () {
      init ();
    }
  
    // //////////////////////////////////////////////////////////////////////
    ServiceContextManager::
    ServiceContextManager (const ServiceContextManager&) {
      init ();
    }

    // //////////////////////////////////////////////////////////////////////
    ServiceContextManager::~ServiceContextManager() {
    }

    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::init () {
    }

    // //////////////////////////////////////////////////////////////////////
    ServiceContextManager& ServiceContextManager::instance () {
      if (_instance == NULL) {
        _instance = new ServiceContextManager();
        assert (_instance != NULL);
      
        FacSupervisor::instance().registerServiceContextManager (_instance);
      }
      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::
    createAndRegisterSpecificServiceContext (const ModuleDescription& iModuleDescription) {

      // Create a Service Context specific to the (*this) Service
      ServiceContext& lSpecificServiceContext =
        FacServiceContext::instance().create (iModuleDescription);

      // Register that specific Service Context
      const bool insertSucceeded =
        _specificContextList.
        insert (ServiceContextList_T::
                value_type (lSpecificServiceContext.getModuleDescription(),
                            &lSpecificServiceContext)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion of the specific context in ServiceContextManager failed for "
                         << lSpecificServiceContext.getModuleName());
        assert (insertSucceeded == true);
      }
    }

    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::
    createAndRegisterSpecificSimServiceContext(const std::string& iModuleName) {
      const ModuleDescription lSimModule (ModuleDescription::SIM, iModuleName);
      createAndRegisterSpecificServiceContext (lSimModule);
    }

    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::
    createAndRegisterSpecificCrsServiceContext(const std::string& iModuleName) {
      const ModuleDescription lCrsModule (ModuleDescription::CRS, iModuleName);
      createAndRegisterSpecificServiceContext (lCrsModule);
    }

    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::
    createAndRegisterSpecificTspServiceContext(const std::string& iModuleName) {
      const ModuleDescription lTspModule (ModuleDescription::TSP, iModuleName);
      createAndRegisterSpecificServiceContext (lTspModule);
    }

    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::
    createAndRegisterSpecificInvServiceContext(const std::string& iModuleName) {
      const ModuleDescription lInvModule (ModuleDescription::INV, iModuleName);
      createAndRegisterSpecificServiceContext (lInvModule);
    }

    // //////////////////////////////////////////////////////////////////////
    ServiceContext& ServiceContextManager::
    getSpecificContextInternal (const ModuleDescription& iModuleDescription) const {
      ServiceContext* oServiceContext_ptr = NULL;
      
      ServiceContextList_T::const_iterator itContext =
        _specificContextList.find (iModuleDescription);

      if (itContext != _specificContextList.end()) {
        oServiceContext_ptr = itContext->second;
      }

      assert (oServiceContext_ptr != NULL);
      return *oServiceContext_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    ServiceContext& ServiceContextManager::
    getSpecificContext (const ModuleDescription& iModuleDescription) {
      return instance().getSpecificContextInternal (iModuleDescription);
    }
    
    // //////////////////////////////////////////////////////////////////////
    const int ServiceContextManager::
    getSimulationRunNumber (const std::string& iModuleName) {
      const ModuleDescription lSimModule (ModuleDescription::SIM, iModuleName);
      ServiceContext& lSimServiceContext = getSpecificContext (lSimModule);
      return lSimServiceContext.getSimulationRunNumber();
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string& ServiceContextManager::
    getDemandInputFilename (const std::string& iModuleName) {
      const ModuleDescription lSimModule (ModuleDescription::SIM, iModuleName);
      ServiceContext& lSimServiceContext = getSpecificContext (lSimModule);
      return lSimServiceContext.getDemandInputFilename();
    }

    // //////////////////////////////////////////////////////////////////////
    const DateTime_T& ServiceContextManager::
    getStartDate (const std::string& iModuleName) {
      const ModuleDescription lSimModule (ModuleDescription::SIM, iModuleName);
      ServiceContext& lSimServiceContext = getSpecificContext (lSimModule);
      return lSimServiceContext.getStartDate();
    }

    // //////////////////////////////////////////////////////////////////////
    const DateTime_T& ServiceContextManager::
    getEndDate (const std::string& iModuleName) {
      const ModuleDescription lSimModule (ModuleDescription::SIM, iModuleName);
      ServiceContext& lSimServiceContext = getSpecificContext (lSimModule);
      return lSimServiceContext.getEndDate();
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string& ServiceContextManager::
    getScheduleInputFilename (const std::string& iModuleName) {
      const ModuleDescription lTspModule (ModuleDescription::TSP, iModuleName);
      ServiceContext& lTspServiceContext = getSpecificContext (lTspModule);
      return lTspServiceContext.getScheduleInputFilename();
    }

    // //////////////////////////////////////////////////////////////////////
    WorldSchedule& ServiceContextManager::
    getWorldSchedule (const std::string& iModuleName) {
      const ModuleDescription lTspModule (ModuleDescription::TSP, iModuleName);
      ServiceContext& lTspServiceContext = getSpecificContext (lTspModule);
      return lTspServiceContext.getWorldSchedule();
    }
      
    // //////////////////////////////////////////////////////////////////////
    Network& ServiceContextManager::
    getNetwork (const std::string& iModuleName) {
      const ModuleDescription lTspModule (ModuleDescription::TSP, iModuleName);
      ServiceContext& lTspServiceContext = getSpecificContext (lTspModule);
      return lTspServiceContext.getNetwork();
    }

    // //////////////////////////////////////////////////////////////////////
    const AirlineCode_T& ServiceContextManager::
    getOwnerAirlineCode (const std::string& iModuleName) {
      const ModuleDescription lInvModule (ModuleDescription::INV, iModuleName);
      ServiceContext& lInvServiceContext = getSpecificContext (lInvModule);
      return lInvServiceContext.getOwnerAirlineCode();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::
    setSimulationRunNumber (const int iSimulationRunNumber,
                            const std::string& iModuleName) {
      const ModuleDescription lSimModule (ModuleDescription::SIM, iModuleName);
      ServiceContext& lSimServiceContext = getSpecificContext (lSimModule);
      lSimServiceContext.setSimulationRunNumber (iSimulationRunNumber);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::
    setDemandInputFilename (const std::string& iInputFilename,
                            const std::string& iModuleName) {
      const ModuleDescription lSimModule (ModuleDescription::SIM, iModuleName);
      ServiceContext& lSimServiceContext = getSpecificContext (lSimModule);
      lSimServiceContext.setDemandInputFilename (iInputFilename);
    }

    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::
    setStartDate (const DateTime_T& iStartDate,
                  const std::string& iModuleName) {
      const ModuleDescription lSimModule (ModuleDescription::SIM, iModuleName);
      ServiceContext& lSimServiceContext = getSpecificContext (lSimModule);
      lSimServiceContext.setStartDate (iStartDate);
    }

    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::
    setEndDate (const DateTime_T& iEndDate,
                const std::string& iModuleName) {
      const ModuleDescription lSimModule (ModuleDescription::SIM, iModuleName);
      ServiceContext& lSimServiceContext = getSpecificContext (lSimModule);
      lSimServiceContext.setEndDate (iEndDate);
    }

    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::
    setScheduleInputFilename (const std::string& iInputFilename,
                              const std::string& iModuleName) {
      const ModuleDescription lTspModule (ModuleDescription::TSP, iModuleName);
      ServiceContext& lTspServiceContext = getSpecificContext (lTspModule);
      lTspServiceContext.setScheduleInputFilename (iInputFilename);
    }

    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::
    setWorldSchedule (WorldSchedule& ioWorldSchedule,
                      const std::string& iModuleName) {
      const ModuleDescription lTspModule (ModuleDescription::TSP, iModuleName);
      ServiceContext& lTspServiceContext = getSpecificContext (lTspModule);
      lTspServiceContext.setWorldSchedule (ioWorldSchedule);
    }
      
    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::setNetwork (Network& ioNetwork,
                                            const std::string& iModuleName) {
      const ModuleDescription lTspModule (ModuleDescription::TSP, iModuleName);
      ServiceContext& lTspServiceContext = getSpecificContext (lTspModule);
      lTspServiceContext.setNetwork (ioNetwork);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::
    setOwnerAirlineCode (const AirlineCode_T& iAirlineCode,
                         const std::string& iModuleName) {
      const ModuleDescription lInvModule (ModuleDescription::INV, iModuleName);
      ServiceContext& lInvServiceContext = getSpecificContext (lInvModule);
      lInvServiceContext.setOwnerAirlineCode (iAirlineCode);
    }
    
  }
}
