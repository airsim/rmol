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
    const int LATUS_ServiceAbstract::getSimulationRunNumber () {
      return ServiceContextManager::getSimulationRunNumber ();
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string& LATUS_ServiceAbstract::getDemandInputFilename () {
      return ServiceContextManager::getDemandInputFilename ();
    }

    // //////////////////////////////////////////////////////////////////////
    const DateTime_T& LATUS_ServiceAbstract::getStartDate () {
      return ServiceContextManager::getStartDate ();
    }

    // //////////////////////////////////////////////////////////////////////
    const DateTime_T& LATUS_ServiceAbstract::getEndDate () {
      return ServiceContextManager::getEndDate ();
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string& LATUS_ServiceAbstract::getScheduleInputFilename () {
      return ServiceContextManager::getScheduleInputFilename ();
    }

     // //////////////////////////////////////////////////////////////////////
    const std::string& LATUS_ServiceAbstract::getWorldScheduleOutputFilename () {
      return ServiceContextManager::getWorldScheduleOutputFilename ();
    }

    // //////////////////////////////////////////////////////////////////////
    const AirlineCode_T& LATUS_ServiceAbstract::
    getOwnerAirlineCode (const std::string& iModuleName) {
      return ServiceContextManager::getOwnerAirlineCode (iModuleName);
    }

    // //////////////////////////////////////////////////////////////////////
    WholeDemand& LATUS_ServiceAbstract::getWholeDemand () {
      return ServiceContextManager::getWholeDemand ();
    }
      
    // //////////////////////////////////////////////////////////////////////
    WorldSchedule& LATUS_ServiceAbstract::getWorldSchedule () {
      return ServiceContextManager::getWorldSchedule ();
    }
      
    // //////////////////////////////////////////////////////////////////////
    Network& LATUS_ServiceAbstract::getNetwork () {
      return ServiceContextManager::getNetwork ();
    }

    // //////////////////////////////////////////////////////////////////////
    Inventory& LATUS_ServiceAbstract::
    getInventory (const std::string& iModuleName) {
      return ServiceContextManager::getInventory (iModuleName);
    }

    // //////////////////////////////////////////////////////////////////////
    Inventory& LATUS_ServiceAbstract::
    getAirlineInventory (const AirlineCode_T& iAirlineCode) {
      return ServiceContextManager::getAirlineInventory (iAirlineCode);
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::
    setSimulationRunNumber (const int iSimulationRunNumber) {
      ServiceContextManager::setSimulationRunNumber (iSimulationRunNumber);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::
    setDemandInputFilename (const std::string& iInputFilename) {
      ServiceContextManager::setDemandInputFilename (iInputFilename);
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::
    setStartDate (const DateTime_T& iStartDate) {
      ServiceContextManager::setStartDate (iStartDate);
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::
    setEndDate (const DateTime_T& iEndDate) {
      ServiceContextManager::setEndDate (iEndDate);
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::
    setScheduleInputFilename (const std::string& iInputFilename) {
      ServiceContextManager::setScheduleInputFilename (iInputFilename);
    }

     // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::
    setWorldScheduleOutputFilename (const std::string& iOutputFilename) {
      ServiceContextManager::setWorldScheduleOutputFilename (iOutputFilename);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::
    setWholeDemand (WholeDemand& ioWholeDemand) {
      ServiceContextManager::setWholeDemand (ioWholeDemand);
    }
      
    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::
    setWorldSchedule (WorldSchedule& ioWorldSchedule) {
      ServiceContextManager::setWorldSchedule (ioWorldSchedule);
    }
      
    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::setNetwork (Network& ioNetwork) {
      ServiceContextManager::setNetwork (ioNetwork);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::setInventory (Inventory& ioInventory,
                                              const std::string& iModuleName) {
      ServiceContextManager::setInventory (ioInventory, iModuleName);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::
    createAndRegisterSpecificSimServiceContext () {
      ServiceContextManager::createAndRegisterSpecificSimServiceContext ();
    }
      
    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::
    createAndRegisterSpecificDegServiceContext () {
      ServiceContextManager::createAndRegisterSpecificDegServiceContext ();
    }
      
    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::createAndRegisterSpecificCrsServiceContext () {
      ServiceContextManager::createAndRegisterSpecificCrsServiceContext ();
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::createAndRegisterSpecificTspServiceContext () {
      ServiceContextManager::createAndRegisterSpecificTspServiceContext ();
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::
    createAndRegisterSpecificInvServiceContext (const AirlineCode_T& iAirlineCode) {
      ServiceContextManager::
        createAndRegisterSpecificInvServiceContext (iAirlineCode);
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::
    createAndRegisterSpecificRmsServiceContext (const AirlineCode_T& iAirlineCode) {
      ServiceContextManager::
        createAndRegisterSpecificRmsServiceContext (iAirlineCode);
    }

    // //////////////////////////////////////////////////////////////////////
    unsigned short LATUS_ServiceAbstract::getInvSpecificContextNumber() {
      return ServiceContextManager::getInvSpecificContextNumber();
    }
      
    // //////////////////////////////////////////////////////////////////////
    unsigned short LATUS_ServiceAbstract::getRmsSpecificContextNumber() {
      return ServiceContextManager::getRmsSpecificContextNumber();
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_ServiceAbstract::registerInventoriesWithinServiceContexts() {
      ServiceContextManager::instance().
        registerInventoriesWithinServiceContexts();
    }
      
  }
}
