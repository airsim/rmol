// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/basic/BasConst_ServiceContextManagement.hpp>
#include <latus/com/bom/WorldSchedule.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacServiceContext.hpp>
#include <latus/com/service/ServiceContextManager.hpp>
#include <latus/com/service/ServiceContext.hpp>
#include <latus/com/service/Logger.hpp>
// LATUS General
#include <latus/LatusTypes.hpp>

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
    createAndRegisterSpecificServiceContextInternal (const ModuleDescription& iModuleDescription) {

      // Create a Service Context specific to the (*this) Service
      ServiceContext& lSpecificServiceContext =
        FacServiceContext::instance().create (iModuleDescription);

      // Register that specific Service Context within the exhaustive list
      const bool insertSucceeded =
        _specificContextList.
        insert (ServiceContextList_T::
                value_type (lSpecificServiceContext.getModuleDescription(),
                            &lSpecificServiceContext)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion of the specific context in "
                         << "ServiceContextManager failed for "
                         << lSpecificServiceContext.getModuleName());
        assert (insertSucceeded == true);
      }
    }

    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::
    createAndRegisterSpecificServiceContext (const ModuleDescription& iModuleDescription) {
      instance().
        createAndRegisterSpecificServiceContextInternal (iModuleDescription);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::createAndRegisterSpecificSimServiceContext () {
      const ModuleDescription lSimModule (ModuleDescription::SIM,
                                          DEFAULT_LATUS_SIM_MODULE_NAME);
      createAndRegisterSpecificServiceContext (lSimModule);
    }

    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::createAndRegisterSpecificCrsServiceContext () {
      const ModuleDescription lCrsModule (ModuleDescription::CRS,
                                          DEFAULT_LATUS_CRS_MODULE_NAME);
      createAndRegisterSpecificServiceContext (lCrsModule);
    }

    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::createAndRegisterSpecificTspServiceContext () {
      const ModuleDescription lTspModule (ModuleDescription::TSP,
                                          DEFAULT_LATUS_TSP_MODULE_NAME);
      createAndRegisterSpecificServiceContext (lTspModule);
    }

    // //////////////////////////////////////////////////////////////////////
    std::string getDefaultInvModuleName (const AirlineCode_T& iAirlineCode) {
      std::ostringstream ostr;
      ostr << DEFAULT_LATUS_INV_ROOT_MODULE_NAME << iAirlineCode;
      return ostr.str();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::
    createAndRegisterSpecificInvServiceContextInternal (const AirlineCode_T& iAirlineCode) {
      // Build the Inventory module name (as the concatenation of "INV" and of
      // the owner airline code).
      const std::string& lModuleName = getDefaultInvModuleName (iAirlineCode);

      // Register a specific service context for that airline Inventory.
      const ModuleDescription lInvModule (ModuleDescription::INV, lModuleName);
      createAndRegisterSpecificServiceContext (lInvModule);

      // Set the owner airline code
      setOwnerAirlineCode (iAirlineCode, lModuleName);

      // Register the Inventory specific service context within
      // the Inventory-related list.
      ServiceContext& lSpecificServiceContext = getSpecificContext (lInvModule);
      const bool insertSucceeded = _invSpecificContextList.
        insert (InvServiceContextList_T::
                value_type (iAirlineCode, &lSpecificServiceContext)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion of the specific context in "
                         << "ServiceContextManager failed for "
                         << lSpecificServiceContext.getModuleName());
        assert (insertSucceeded == true);
      }
    }

    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::
    createAndRegisterSpecificInvServiceContext (const AirlineCode_T& iAirlineCode) {
      instance().
        createAndRegisterSpecificInvServiceContextInternal (iAirlineCode);
    }

    // //////////////////////////////////////////////////////////////////////
    std::string getDefaultRmsModuleName (const AirlineCode_T& iAirlineCode) {
      std::ostringstream ostr;
      ostr << DEFAULT_LATUS_RMS_ROOT_MODULE_NAME << iAirlineCode;
      return ostr.str();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::
    createAndRegisterSpecificRmsServiceContextInternal (const AirlineCode_T& iAirlineCode) {
      // Build the RMS module name (as the concatenation of "RMS" and of
      // the owner airline code).
      const std::string& lModuleName = getDefaultRmsModuleName (iAirlineCode);

      // Register a specific service context for that airline RMS.
      const ModuleDescription lRmsModule (ModuleDescription::RMS, lModuleName);
      createAndRegisterSpecificServiceContext (lRmsModule);

      // Set the owner airline code
      setOwnerAirlineCode (iAirlineCode, lModuleName);

      // Register the RMS specific service context within
      // the RMS-related list.
      ServiceContext& lSpecificServiceContext = getSpecificContext (lRmsModule);
      const bool insertSucceeded = _rmsSpecificContextList.
        insert (RmsServiceContextList_T::
                value_type (iAirlineCode, &lSpecificServiceContext)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion of the specific context in "
                         << "ServiceContextManager failed for "
                         << lSpecificServiceContext.getModuleName());
        assert (insertSucceeded == true);
      }
    }

    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::
    createAndRegisterSpecificRmsServiceContext (const AirlineCode_T& iAirlineCode) {
      instance().
        createAndRegisterSpecificRmsServiceContextInternal (iAirlineCode);
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
    ServiceContext& ServiceContextManager::
    getInvSpecificContext (const AirlineCode_T& iAirlineCode) {
      ServiceContext* oServiceContext_ptr = NULL;
      
      InvServiceContextList_T::const_iterator itInvContext =
        instance()._invSpecificContextList.find (iAirlineCode);
      if (itInvContext != instance()._invSpecificContextList.end()) {
        oServiceContext_ptr = itInvContext->second;
        
      } else {
        LATUS_LOG_ERROR ("There is no Inventory specific context registered "
                         << "for the airline " << iAirlineCode
                         << ". [Hint] Check that the configuration file "
                         << "contains an entry for that airline.");
      }
      assert (oServiceContext_ptr != NULL);

      return *oServiceContext_ptr;
    }

    // //////////////////////////////////////////////////////////////////////
    unsigned short ServiceContextManager::getInvSpecificContextNumber() {
      return instance()._invSpecificContextList.size();
    }
      
    // //////////////////////////////////////////////////////////////////////
    unsigned short ServiceContextManager::getRmsSpecificContextNumber() {
      return instance()._rmsSpecificContextList.size();
    }
      
    // //////////////////////////////////////////////////////////////////////
    const int ServiceContextManager::getSimulationRunNumber () {
      const ModuleDescription lSimModule (ModuleDescription::SIM,
                                          DEFAULT_LATUS_SIM_MODULE_NAME);
      ServiceContext& lSimServiceContext = getSpecificContext (lSimModule);
      return lSimServiceContext.getSimulationRunNumber();
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string& ServiceContextManager::getDemandInputFilename () {
      const ModuleDescription lSimModule (ModuleDescription::SIM,
                                          DEFAULT_LATUS_SIM_MODULE_NAME);
      ServiceContext& lSimServiceContext = getSpecificContext (lSimModule);
      return lSimServiceContext.getDemandInputFilename();
    }

    // //////////////////////////////////////////////////////////////////////
    const DateTime_T& ServiceContextManager::getStartDate () {
      const ModuleDescription lSimModule (ModuleDescription::SIM,
                                          DEFAULT_LATUS_SIM_MODULE_NAME);
      ServiceContext& lSimServiceContext = getSpecificContext (lSimModule);
      return lSimServiceContext.getStartDate();
    }

    // //////////////////////////////////////////////////////////////////////
    const DateTime_T& ServiceContextManager::getEndDate () {
      const ModuleDescription lSimModule (ModuleDescription::SIM,
                                          DEFAULT_LATUS_SIM_MODULE_NAME);
      ServiceContext& lSimServiceContext = getSpecificContext (lSimModule);
      return lSimServiceContext.getEndDate();
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string& ServiceContextManager::getScheduleInputFilename () {
      const ModuleDescription lTspModule (ModuleDescription::TSP,
                                          DEFAULT_LATUS_TSP_MODULE_NAME);
      ServiceContext& lTspServiceContext = getSpecificContext (lTspModule);
      return lTspServiceContext.getScheduleInputFilename();
    }

    // //////////////////////////////////////////////////////////////////////
    const AirlineCode_T& ServiceContextManager::
    getOwnerAirlineCode (const std::string& iModuleName) {
      const ModuleDescription lInvModule (ModuleDescription::INV, iModuleName);
      ServiceContext& lInvServiceContext = getSpecificContext (lInvModule);
      return lInvServiceContext.getOwnerAirlineCode();
    }

    // //////////////////////////////////////////////////////////////////////
    WorldSchedule& ServiceContextManager::getWorldSchedule () {
      const ModuleDescription lTspModule (ModuleDescription::TSP,
                                          DEFAULT_LATUS_TSP_MODULE_NAME);
      ServiceContext& lTspServiceContext = getSpecificContext (lTspModule);
      return lTspServiceContext.getWorldSchedule();
    }
      
    // //////////////////////////////////////////////////////////////////////
    Network& ServiceContextManager::getNetwork () {
      const ModuleDescription lTspModule (ModuleDescription::TSP,
                                          DEFAULT_LATUS_TSP_MODULE_NAME);
      ServiceContext& lTspServiceContext = getSpecificContext (lTspModule);
      return lTspServiceContext.getNetwork();
    }

    // //////////////////////////////////////////////////////////////////////
    Inventory& ServiceContextManager::
    getInventory (const std::string& iModuleName) {
      const ModuleDescription lInvModule (ModuleDescription::INV, iModuleName);
      ServiceContext& lInvServiceContext = getSpecificContext (lInvModule);
      return lInvServiceContext.getInventory();
    }

    // //////////////////////////////////////////////////////////////////////
    Inventory& ServiceContextManager::
    getAirlineInventory (const AirlineCode_T& iAirlineCode) {
      const ServiceContext& lInvServiceContext =
        getInvSpecificContext (iAirlineCode);
      return lInvServiceContext.getInventory();
    }

    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::
    setSimulationRunNumber (const int iSimulationRunNumber) {
      const ModuleDescription lSimModule (ModuleDescription::SIM,
                                          DEFAULT_LATUS_SIM_MODULE_NAME);
      ServiceContext& lSimServiceContext = getSpecificContext (lSimModule);
      lSimServiceContext.setSimulationRunNumber (iSimulationRunNumber);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::
    setDemandInputFilename (const std::string& iInputFilename) {
      const ModuleDescription lSimModule (ModuleDescription::SIM,
                                          DEFAULT_LATUS_SIM_MODULE_NAME);
      ServiceContext& lSimServiceContext = getSpecificContext (lSimModule);
      lSimServiceContext.setDemandInputFilename (iInputFilename);
    }

    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::
    setStartDate (const DateTime_T& iStartDate) {
      const ModuleDescription lSimModule (ModuleDescription::SIM,
                                          DEFAULT_LATUS_SIM_MODULE_NAME);
      ServiceContext& lSimServiceContext = getSpecificContext (lSimModule);
      lSimServiceContext.setStartDate (iStartDate);
    }

    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::
    setEndDate (const DateTime_T& iEndDate) {
      const ModuleDescription lSimModule (ModuleDescription::SIM,
                                          DEFAULT_LATUS_SIM_MODULE_NAME);
      ServiceContext& lSimServiceContext = getSpecificContext (lSimModule);
      lSimServiceContext.setEndDate (iEndDate);
    }

    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::
    setScheduleInputFilename (const std::string& iInputFilename) {
      const ModuleDescription lTspModule (ModuleDescription::TSP,
                                          DEFAULT_LATUS_TSP_MODULE_NAME);
      ServiceContext& lTspServiceContext = getSpecificContext (lTspModule);
      lTspServiceContext.setScheduleInputFilename (iInputFilename);
    }

    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::
    setOwnerAirlineCode (const AirlineCode_T& iAirlineCode,
                         const std::string& iModuleName) {
      const ModuleDescription lInvModule (ModuleDescription::INV, iModuleName);
      ServiceContext& lInvServiceContext = getSpecificContext (lInvModule);
      lInvServiceContext.setOwnerAirlineCode (iAirlineCode);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::
    setWorldSchedule (WorldSchedule& ioWorldSchedule) {
      const ModuleDescription lTspModule (ModuleDescription::TSP,
                                          DEFAULT_LATUS_TSP_MODULE_NAME);
      ServiceContext& lTspServiceContext = getSpecificContext (lTspModule);
      lTspServiceContext.setWorldSchedule (ioWorldSchedule);
    }
      
    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::setNetwork (Network& ioNetwork) {
      const ModuleDescription lTspModule (ModuleDescription::TSP,
                                          DEFAULT_LATUS_TSP_MODULE_NAME);
      ServiceContext& lTspServiceContext = getSpecificContext (lTspModule);
      lTspServiceContext.setNetwork (ioNetwork);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::setInventory (Inventory& ioInventory,
                                              const std::string& iModuleName) {
      const ModuleDescription lTspModule (ModuleDescription::TSP, iModuleName);
      ServiceContext& lTspServiceContext = getSpecificContext (lTspModule);
      lTspServiceContext.setInventory (ioInventory);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void ServiceContextManager::
    registerInventoriesWithinServiceContexts() const {

      // Retrieve the reference on the WorldSchedule object, which is the
      // root of the BOM.
      const WorldSchedule& lWorldSchedule = getWorldSchedule ();
      
      // For each Inventory specific service context, set the reference
      // on the corresponding BOM Inventory object.
      for (InvServiceContextList_T::const_iterator itInvContext =
             _invSpecificContextList.begin();
           itInvContext != _invSpecificContextList.end(); ++itInvContext) {
        // Retrieve the Inventory specific service context
        ServiceContext* lServiceContext_ptr = itInvContext->second;
        assert (lServiceContext_ptr != NULL);

        // Get the corresponding owner airline code.
        const AirlineCode_T& lAirlineOwner =
          lServiceContext_ptr->getOwnerAirlineCode();

        // Within the (BOM) WorldSchedule object, retrieve the corresponding
        // (BOM) Inventory object.
        Inventory* lInventory_ptr = lWorldSchedule.getInventory (lAirlineOwner);
        if (lInventory_ptr == NULL) {
          LATUS_LOG_ERROR ("No Inventory has been built for the airline "
                           << lAirlineOwner
                           << ". [Hint] Check that the Schedule input file "
                           << "contains a schedule for that airline.");
          throw InventoryNotFoundException();
        }
        assert (lInventory_ptr != NULL);

        // Store a reference on the (BOM) Inventory object (for that airline).
        lServiceContext_ptr->setInventory (*lInventory_ptr);
      }
    }
    
  }
}
