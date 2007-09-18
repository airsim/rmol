// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/service/ServiceContextManager.hpp>
#include <latus/com/service/LATUS_ServiceAbstract.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    LATUS_ServiceAbstract::LATUS_ServiceAbstract () {
    }

    // //////////////////////////////////////////////////////////////////////
    LATUS_ServiceAbstract::~LATUS_ServiceAbstract () {
    }

    // //////////////////////////////////////////////////////////////////////
    const int LATUS_ServiceAbstract::
    getSimulationRunNumber (const std::string& iModuleName) {
      return ServiceContextManager::instance().
        getSimulationRunNumber (iModuleName);
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string& LATUS_ServiceAbstract::
    getDemandInputFilename (const std::string& iModuleName) {
      return ServiceContextManager::instance().
        getDemandInputFilename (iModuleName);
    }

    // //////////////////////////////////////////////////////////////////////
    const DateTime_T& LATUS_ServiceAbstract::
    getStartDate (const std::string& iModuleName) {
      return ServiceContextManager::instance().getStartDate (iModuleName);
    }

    // //////////////////////////////////////////////////////////////////////
    const DateTime_T& LATUS_ServiceAbstract::
    getEndDate (const std::string& iModuleName) {
      return ServiceContextManager::instance().getEndDate (iModuleName);
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string& LATUS_ServiceAbstract::
    getScheduleInputFilename (const std::string& iModuleName) {
      return ServiceContextManager::instance().
        getScheduleInputFilename (iModuleName);
    }

    // //////////////////////////////////////////////////////////////////////
    const AirlineCode_T& LATUS_ServiceAbstract::
    getOwnerAirlineCode (const std::string& iModuleName) {
      return ServiceContextManager::instance().getOwnerAirlineCode(iModuleName);
    }
    
    // //////////////////////////////////////////////////////////////////////
    WorldSchedule& LATUS_ServiceAbstract::
    getWorldSchedule (const std::string& iModuleName) {
      return ServiceContextManager::instance().getWorldSchedule (iModuleName);
    }
      
    // //////////////////////////////////////////////////////////////////////
    Network& LATUS_ServiceAbstract::
    getNetwork (const std::string& iModuleName) {
      return ServiceContextManager::instance().getNetwork (iModuleName);
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::
    setSimulationRunNumber (const int iSimulationRunNumber,
                            const std::string& iModuleName) {
      ServiceContextManager::instance().
        setSimulationRunNumber (iSimulationRunNumber, iModuleName);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::
    setDemandInputFilename (const std::string& iInputFilename,
                            const std::string& iModuleName) {
      ServiceContextManager::instance().
        setDemandInputFilename (iInputFilename, iModuleName);
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::
    setStartDate (const DateTime_T& iStartDate,
                  const std::string& iModuleName) {
      ServiceContextManager::instance().setStartDate (iStartDate, iModuleName);
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::
    setEndDate (const DateTime_T& iEndDate,
                const std::string& iModuleName) {
      ServiceContextManager::instance().setEndDate (iEndDate, iModuleName);
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::
    setScheduleInputFilename (const std::string& iInputFilename,
                              const std::string& iModuleName) {
      ServiceContextManager::instance().
        setScheduleInputFilename (iInputFilename, iModuleName);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::
    setOwnerAirlineCode (const AirlineCode_T& iAirlineCode,
                         const std::string& iModuleName) {
      ServiceContextManager::instance().
        setOwnerAirlineCode (iAirlineCode, iModuleName);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::
    setWorldSchedule (WorldSchedule& ioWorldSchedule,
                      const std::string& iModuleName) {
      ServiceContextManager::instance().
        setWorldSchedule (ioWorldSchedule, iModuleName);
    }
      
    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::setNetwork (Network& ioNetwork,
                                            const std::string& iModuleName) {
      ServiceContextManager::instance().setNetwork (ioNetwork, iModuleName);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::
    createAndRegisterSpecificSimServiceContext(const std::string& iModuleName) {
      ServiceContextManager::instance().
        createAndRegisterSpecificSimServiceContext (iModuleName);
    }
      
    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::
    createAndRegisterSpecificCrsServiceContext(const std::string& iModuleName) {
      ServiceContextManager::instance().
        createAndRegisterSpecificCrsServiceContext (iModuleName);
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::
    createAndRegisterSpecificTspServiceContext(const std::string& iModuleName) {
      ServiceContextManager::instance().
        createAndRegisterSpecificTspServiceContext (iModuleName);
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::
    createAndRegisterSpecificInvServiceContext(const std::string& iModuleName) {
      ServiceContextManager::instance().
        createAndRegisterSpecificInvServiceContext (iModuleName);
    }

  }
}
