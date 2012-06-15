// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// Boost
#include <boost/make_shared.hpp>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/basic/BasChronometer.hpp>
#include <stdair/basic/ContinuousAttributeLite.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BomRetriever.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/YieldFeatures.hpp>
#include <stdair/bom/AirportPair.hpp>
#include <stdair/bom/PosChannel.hpp>
#include <stdair/bom/DatePeriod.hpp>
#include <stdair/bom/TimePeriod.hpp>
#include <stdair/bom/AirlineClassList.hpp>
#include <stdair/basic/BasConst_Request.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/OnDDate.hpp>
#include <stdair/bom/OnDDateTypes.hpp>
#include <stdair/command/CmdBomManager.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/STDAIR_Service.hpp>
// RMOL
#include <rmol/basic/BasConst_RMOL_Service.hpp>
#include <rmol/factory/FacRmolServiceContext.hpp>
#include <rmol/command/InventoryParser.hpp>
#include <rmol/command/Optimiser.hpp>
#include <rmol/command/PreOptimiser.hpp>
#include <rmol/command/Forecaster.hpp>
#include <rmol/service/RMOL_ServiceContext.hpp>
#include <rmol/RMOL_Service.hpp>

namespace RMOL {

  // ////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service()
  : _rmolServiceContext (NULL),
    _previousForecastDate (stdair::Date_T (2000, 1, 1)) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service (const RMOL_Service& iService) :
    _rmolServiceContext (NULL),
    _previousForecastDate (stdair::Date_T (2000, 1, 1)) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service (const stdair::BasLogParams& iLogParams) :
    _rmolServiceContext (NULL),
    _previousForecastDate (stdair::Date_T (2000, 1, 1)) {

    // Initialise the STDAIR service handler
    stdair::STDAIR_ServicePtr_T lSTDAIR_Service_ptr =
      initStdAirService (iLogParams);
    
    // Initialise the service context
    initServiceContext();

    // Add the StdAir service context to the RMOL service context
    // \note RMOL owns the STDAIR service resources here.
    const bool ownStdairService = true;
    addStdAirService (lSTDAIR_Service_ptr, ownStdairService);

    // Initialise the (remaining of the) context
    initRmolService();
  }

  // ////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service (const stdair::BasLogParams& iLogParams,
                              const stdair::BasDBParams& iDBParams) :
    _rmolServiceContext (NULL),
    _previousForecastDate (stdair::Date_T (2000, 1, 1)) {

    // Initialise the STDAIR service handler
    stdair::STDAIR_ServicePtr_T lSTDAIR_Service_ptr =
      initStdAirService (iLogParams, iDBParams);
    
    // Initialise the service context
    initServiceContext();

    // Add the StdAir service context to the RMOL service context
    // \note RMOL owns the STDAIR service resources here.
    const bool ownStdairService = true;
    addStdAirService (lSTDAIR_Service_ptr, ownStdairService);

    // Initialise the (remaining of the) context
    initRmolService();
  }

  // ////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service (stdair::STDAIR_ServicePtr_T ioSTDAIRServicePtr)
    : _rmolServiceContext (NULL),
      _previousForecastDate (stdair::Date_T (2000, 1, 1)) {
    
    // Initialise the context
    initServiceContext();
    
    // Add the StdAir service context to the RMOL service context.
    // \note RMOL does not own the STDAIR service resources here.
    const bool doesNotOwnStdairService = false;
    addStdAirService (ioSTDAIRServicePtr, doesNotOwnStdairService);

    // Initialise the (remaining of the) context
    initRmolService();
  }

  // ////////////////////////////////////////////////////////////////////
  RMOL_Service::~RMOL_Service() {
    // Delete/Clean all the objects from memory
    finalise();
  }

  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::finalise() {
    assert (_rmolServiceContext != NULL);
    // Reset the (Boost.)Smart pointer pointing on the STDAIR_Service object.
    _rmolServiceContext->reset();
  }

  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::initServiceContext() {
    // Initialise the service context
    RMOL_ServiceContext& lRMOL_ServiceContext = 
      FacRmolServiceContext::instance().create();
    _rmolServiceContext = &lRMOL_ServiceContext;
  }

  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  addStdAirService (stdair::STDAIR_ServicePtr_T ioSTDAIR_Service_ptr,
                    const bool iOwnStdairService) {

    // Retrieve the RMOL service context
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;

    // Store the STDAIR service object within the (AIRINV) service context
    lRMOL_ServiceContext.setSTDAIR_Service (ioSTDAIR_Service_ptr,
                                            iOwnStdairService);
  }

  // ////////////////////////////////////////////////////////////////////
  stdair::STDAIR_ServicePtr_T RMOL_Service::
  initStdAirService (const stdair::BasLogParams& iLogParams) {
    
    /**
     * Initialise the STDAIR service handler.
     *
     * \note The (Boost.)Smart Pointer keeps track of the references
     *       on the Service object, and deletes that object when it is
     *       no longer referenced (e.g., at the end of the process).
     */
    stdair::STDAIR_ServicePtr_T lSTDAIR_Service_ptr = 
      boost::make_shared<stdair::STDAIR_Service> (iLogParams);
    
    return lSTDAIR_Service_ptr;
  }

  // //////////////////////////////////////////////////////////////////////
  stdair::STDAIR_ServicePtr_T RMOL_Service::
  initStdAirService (const stdair::BasLogParams& iLogParams,
                     const stdair::BasDBParams& iDBParams) {

    /**
     * Initialise the STDAIR service handler.
     *
     * \note The (Boost.)Smart Pointer keeps track of the references
     *       on the Service object, and deletes that object when it is
     *       no longer referenced (e.g., at the end of the process).
     */
    stdair::STDAIR_ServicePtr_T lSTDAIR_Service_ptr = 
      boost::make_shared<stdair::STDAIR_Service> (iLogParams, iDBParams);
    
    return lSTDAIR_Service_ptr;
  }
  
  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::initRmolService() {
    // Do nothing at this stage. A sample BOM tree may be built by
    // calling the buildSampleBom() method
  }

  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  parseAndLoad (const stdair::CabinCapacity_T& iCabinCapacity,
                const stdair::Filename_T& iInputFileName) {

    // Retrieve the RMOL service context
    if (_rmolServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The RMOL service has not"
                                                    " been initialised");
    }
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext; 
    const bool doesOwnStdairService =
      lRMOL_ServiceContext.getOwnStdairServiceFlag();

    // Retrieve the StdAir service object from the (RMOL) service context
    stdair::STDAIR_Service& lSTDAIR_Service =
      lRMOL_ServiceContext.getSTDAIR_Service();
    stdair::BomRoot& lPersistentBomRoot = 
      lSTDAIR_Service.getPersistentBomRoot();

    /**
     * 1. Build a dummy inventory with a leg-cabin which has the given capacity.
     */
    lSTDAIR_Service.buildDummyInventory (iCabinCapacity);

    /**
     * 2. Complete the BOM tree with the optimisation problem specification
     */
    InventoryParser::parseInputFileAndBuildBom (iInputFileName, 
						lPersistentBomRoot);  
 
    /**
     * 3. Delegate the complementary building of objects and links by the
     *    appropriate levels/components
     */
    /**
     * Let the revenue accounting (i.e., the AirRAC component) build the yields.
    AIRRAC::AIRRAC_Service& lAIRRAC_Service =
      lRMOL_ServiceContext.getAIRRAC_Service();
    lAIRRAC_Service.buildSampleBom();
     */   

    /**
     * 4. Build the complementary objects/links for the current component (here,
     *    RMOL)
     */ 
    buildComplementaryLinks (lPersistentBomRoot);
    
    /**
     * 5. Have RMOL clone the whole persistent BOM tree, only when the StdAir
     *    service is owned by the current component (RMOL here).
     */
    if (doesOwnStdairService == true) {
 
      //
      clonePersistentBom ();
    }
  }
  
  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::buildSampleBom() {

    // Retrieve the RMOL service context
    if (_rmolServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The RMOL service has not"
                                                    " been initialised");
    }
    assert (_rmolServiceContext != NULL);

    // Retrieve the RMOL service context and whether it owns the Stdair
    // service
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;
    const bool doesOwnStdairService =
      lRMOL_ServiceContext.getOwnStdairServiceFlag();

    // Retrieve the StdAir service object from the (RMOL) service context
    stdair::STDAIR_Service& lSTDAIR_Service =
      lRMOL_ServiceContext.getSTDAIR_Service();   
    stdair::BomRoot& lPersistentBomRoot = 
      lSTDAIR_Service.getPersistentBomRoot();

    /**
     * 1. Have StdAir build the whole BOM tree, only when the StdAir service is
     *    owned by the current component (RMOL here)
     */
    if (doesOwnStdairService == true) {
      //
      lSTDAIR_Service.buildSampleBom();
    }

    /**
     * 2. Delegate the complementary building of objects and links by the
     *    appropriate levels/components
     */
    /**
     * Let the revenue accounting (i.e., the AirRAC component) build the yields.
    AIRRAC::AIRRAC_Service& lAIRRAC_Service =
      lRMOL_ServiceContext.getAIRRAC_Service();
    lAIRRAC_Service.buildSampleBom();
     */   
  
    /**
     * 3. Build the complementary objects/links for the current component (here,
     *    RMOL)
     */ 
    buildComplementaryLinks (lPersistentBomRoot);
    
    /**
     * 4. Have RMOL clone the whole persistent BOM tree, only when the StdAir
     *    service is owned by the current component (RMOL here).
     */
    if (doesOwnStdairService == true) {
 
      //
      clonePersistentBom ();
    }
  } 

  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::clonePersistentBom () {   

    // Retrieve the RMOL service context
    if (_rmolServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException("The RMOL service has not "
                                                   "been initialised");
    }
    assert (_rmolServiceContext != NULL);

    // Retrieve the RMOL service context and whether it owns the Stdair
    // service
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;
    const bool doesOwnStdairService =
      lRMOL_ServiceContext.getOwnStdairServiceFlag();

    // Retrieve the StdAir service object from the (RMOL) service context
    stdair::STDAIR_Service& lSTDAIR_Service =
      lRMOL_ServiceContext.getSTDAIR_Service();
 
    /**
     * 1. Have RMOL clone the whole persistent BOM tree, only when the StdAir
     *    service is owned by the current component (RMOL here).
     */
    if (doesOwnStdairService == true) {
 
      //
      lSTDAIR_Service.clonePersistentBom ();
    }

    /**
     * 2. Build the complementary links on the clone BOM root object
     */ 
    stdair::BomRoot& lBomRoot = 
      lSTDAIR_Service.getBomRoot();
    buildComplementaryLinks (lBomRoot); 
  }     

  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::buildComplementaryLinks (stdair::BomRoot& ioBomRoot) { 

    // Retrieve the RMOL service context
    if (_rmolServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException("The RMOL service has not "
                                                   "been initialised");
    }
    assert (_rmolServiceContext != NULL);

    // Retrieve the RMOL service context and whether it owns the Stdair
    // service
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;

    // Retrieve the StdAir service object from the (RMOL) service context
    stdair::STDAIR_Service& lSTDAIR_Service =
      lRMOL_ServiceContext.getSTDAIR_Service();

    /**
     * Create the links between the dummy leg cabin the and the dummy segment 
     * cabin.
     */
    lSTDAIR_Service.buildDummyLegSegmentAccesses (ioBomRoot);
  }   

  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::optimalOptimisationByMCIntegration (const int K) {
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;

    // Retrieve the StdAir service
    stdair::STDAIR_Service& lSTDAIR_Service =
      lRMOL_ServiceContext.getSTDAIR_Service();   
    // TODO: gsabatier
    // Replace the getPersistentBomRoot method by the getBomRoot method,
    // in order to work on the clone Bom root instead of the persistent one.
    // Does not work for now because virtual classes are not cloned.
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getPersistentBomRoot();

    //
    stdair::LegCabin& lLegCabin =
      stdair::BomRetriever::retrieveDummyLegCabin (lBomRoot);

    stdair::BasChronometer lOptimisationChronometer;
    lOptimisationChronometer.start();

    Optimiser::optimalOptimisationByMCIntegration (K, lLegCabin);

    const double lOptimisationMeasure = lOptimisationChronometer.elapsed();
    
    // DEBUG
    STDAIR_LOG_DEBUG ("Optimisation by Monte-Carlo performed in "
                      << lOptimisationMeasure);
    STDAIR_LOG_DEBUG ("Result: " << lLegCabin.displayVirtualClassList());

    std::ostringstream logStream;
    stdair::BidPriceVector_T lBidPriceVector = lLegCabin.getBidPriceVector();
    logStream << "Bid-Price Vector (BPV): ";
    const unsigned int size = lBidPriceVector.size();
    
    for (unsigned int i = 0; i < size - 1; ++i) {
      const double bidPrice = lBidPriceVector.at(i);
      logStream << std::fixed << std::setprecision (2) << bidPrice << ", ";
    }
    const double bidPrice = lBidPriceVector.at(size -1);
    logStream << std::fixed << std::setprecision (2) << bidPrice;
    STDAIR_LOG_DEBUG (logStream.str());
  }

  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::optimalOptimisationByDP() {
  }
  
  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::heuristicOptimisationByEmsr() {
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;

    // Retrieve the StdAir service
    stdair::STDAIR_Service& lSTDAIR_Service =
      lRMOL_ServiceContext.getSTDAIR_Service();    
    // TODO: gsabatier
    // Replace the getPersistentBomRoot method by the getBomRoot method,
    // in order to work on the clone Bom root instead of the persistent one.
    // Does not work for now because virtual classes are not cloned.
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getPersistentBomRoot();

    //
    stdair::LegCabin& lLegCabin =
      stdair::BomRetriever::retrieveDummyLegCabin (lBomRoot);

    stdair::BasChronometer lOptimisationChronometer;
    lOptimisationChronometer.start();
    
    Optimiser::heuristicOptimisationByEmsr (lLegCabin);
    
    const double lOptimisationMeasure = lOptimisationChronometer.elapsed();
    // DEBUG
    STDAIR_LOG_DEBUG ("Optimisation EMSR performed in "
                      << lOptimisationMeasure);
    STDAIR_LOG_DEBUG ("Result: " << lLegCabin.displayVirtualClassList());

    stdair::BidPriceVector_T lBidPriceVector = lLegCabin.getBidPriceVector();
    std::ostringstream logStream;
    logStream << "Bid-Price Vector (BPV): ";
    stdair::UnsignedIndex_T idx = 0;
    for (stdair::BidPriceVector_T::const_iterator itBP = lBidPriceVector.begin();
         itBP != lBidPriceVector.end(); ++itBP) {
      if (idx != 0) {
        logStream << ", ";
      }
      const stdair::BidPrice_T& lBidPrice = *itBP;
      logStream << std::fixed << std::setprecision (2) << lBidPrice;
    }
    // DEBUG
    STDAIR_LOG_DEBUG (logStream.str());
  }

  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::heuristicOptimisationByEmsrA() {
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;

    // Retrieve the StdAir service
    stdair::STDAIR_Service& lSTDAIR_Service =
      lRMOL_ServiceContext.getSTDAIR_Service();     
    // TODO: gsabatier
    // Replace the getPersistentBomRoot method by the getBomRoot method,
    // in order to work on the clone Bom root instead of the persistent one.
    // Does not work for now because virtual classes are not cloned. 
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getPersistentBomRoot();

    //
    stdair::LegCabin& lLegCabin =
      stdair::BomRetriever::retrieveDummyLegCabin (lBomRoot);

    Optimiser::heuristicOptimisationByEmsrA (lLegCabin);

    // DEBUG
    STDAIR_LOG_DEBUG ("Result: " << lLegCabin.displayVirtualClassList());
    
  }

  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::heuristicOptimisationByEmsrB() {
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;

    // Retrieve the StdAir service
    stdair::STDAIR_Service& lSTDAIR_Service =
      lRMOL_ServiceContext.getSTDAIR_Service();    
    // TODO: gsabatier
    // Replace the getPersistentBomRoot method by the getBomRoot method,
    // in order to work on the clone Bom root instead of the persistent one.
    // Does not work for now because virtual classes are not cloned.
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getPersistentBomRoot();

    //
    stdair::LegCabin& lLegCabin =
      stdair::BomRetriever::retrieveDummyLegCabin (lBomRoot);

    Optimiser::heuristicOptimisationByEmsrB (lLegCabin);

    // DEBUG
    STDAIR_LOG_DEBUG ("Result: " << lLegCabin.displayVirtualClassList());
  }

  // ////////////////////////////////////////////////////////////////////
  const stdair::SegmentCabin& RMOL_Service::
  retrieveDummySegmentCabin(const bool isForFareFamilies) {
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;

    // Retrieve the StdAir service
    stdair::STDAIR_Service& lSTDAIR_Service =
      lRMOL_ServiceContext.getSTDAIR_Service();
    // TODO: gsabatier
    // Replace the getPersistentBomRoot method by the getBomRoot method,
    // in order to work on the clone Bom root instead of the persistent one.
    // Does not work for now because virtual classes are not cloned.
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getPersistentBomRoot();

    const stdair::SegmentCabin& lSegmentCabin = 
      stdair::BomRetriever::retrieveDummySegmentCabin(lBomRoot, 
                                                      isForFareFamilies);
    return lSegmentCabin;
    
  }

  // ////////////////////////////////////////////////////////////////////
  bool RMOL_Service::
  optimise (stdair::FlightDate& ioFlightDate,
            const stdair::DateTime_T& iRMEventTime,
            const stdair::UnconstrainingMethod& iUnconstrainingMethod,
            const stdair::ForecastingMethod& iForecastingMethod, 
            const stdair::PreOptimisationMethod& iPreOptimisationMethod,
            const stdair::OptimisationMethod& iOptimisationMethod,
            const stdair::PartnershipTechnique& iPartnershipTechnique) {

    
    STDAIR_LOG_DEBUG ("Forecast & Optimisation");
    
    const stdair::PartnershipTechnique::EN_PartnershipTechnique& lPartnershipTechnique =
      iPartnershipTechnique.getTechnique();
    
    switch (lPartnershipTechnique) {      
    case stdair::PartnershipTechnique::NONE:{
      // DEBUG
      STDAIR_LOG_DEBUG ("Forecast");
      
      // 1. Forecasting
      const bool isForecasted = Forecaster::forecast (ioFlightDate,
                                                      iRMEventTime,
                                                      iUnconstrainingMethod,
                                                      iForecastingMethod);
      // DEBUG
      STDAIR_LOG_DEBUG ("Forecast successful: " << isForecasted);

      if (isForecasted == true) {
        // 2a. MRT or FA
        // DEBUG
        STDAIR_LOG_DEBUG ("Pre-optimise");
        
        const bool isPreOptimised =
          PreOptimiser::preOptimise (ioFlightDate, iPreOptimisationMethod);
        
        // DEBUG
        STDAIR_LOG_DEBUG ("Pre-Optimise successful: " << isPreOptimised);

        if (isPreOptimised == true) {
          // 2b. Optimisation
          // DEBUG
          STDAIR_LOG_DEBUG ("Optimise");
          const bool optimiseSucceeded = 
            Optimiser::optimise (ioFlightDate, iOptimisationMethod);
          // DEBUG
          STDAIR_LOG_DEBUG ("Optimise successful: " << optimiseSucceeded);
          return optimiseSucceeded ;
        }
      }
      break;
    }
    case stdair::PartnershipTechnique::RAE_DA:
    case stdair::PartnershipTechnique::IBP_DA:{
      if (_previousForecastDate < iRMEventTime.date()) {
        forecastOnD (iRMEventTime);
        resetDemandInformation (iRMEventTime);
        projectAggregatedDemandOnLegCabins (iRMEventTime);
        optimiseOnD (iRMEventTime);
      }
      break;
    }
    case stdair::PartnershipTechnique::RAE_YP:
    case stdair::PartnershipTechnique::IBP_YP:
    case stdair::PartnershipTechnique::IBP_YP_U:{
      if (_previousForecastDate < iRMEventTime.date()) {
        forecastOnD (iRMEventTime);
        resetDemandInformation (iRMEventTime);
        projectOnDDemandOnLegCabinsUsingYP (iRMEventTime);
        optimiseOnD (iRMEventTime);
      }
      break;
    }
    case stdair::PartnershipTechnique::RMC:{
      if (_previousForecastDate < iRMEventTime.date()) {
        forecastOnD (iRMEventTime);
        resetDemandInformation (iRMEventTime);        
        updateBidPrice (iRMEventTime);
        projectOnDDemandOnLegCabinsUsingDYP (iRMEventTime);
        optimiseOnDUsingRMCooperation (iRMEventTime);
      }
      break;
    }
    case stdair::PartnershipTechnique::A_RMC:{
      if (_previousForecastDate < iRMEventTime.date()) {
        forecastOnD (iRMEventTime);
        resetDemandInformation (iRMEventTime);        
        updateBidPrice (iRMEventTime);
        projectOnDDemandOnLegCabinsUsingDYP (iRMEventTime);
        optimiseOnDUsingAdvancedRMCooperation (iRMEventTime);
      }
      break;
    }
    default:{
      assert (false);
      break;
      }
    }
    return false;  
  }
  
  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::forecastOnD (const stdair::DateTime_T& iRMEventTime) {

    if (_rmolServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The Rmol service "
                                                    "has not been initialised");
    }
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;

    // Retrieve the bom root
    stdair::STDAIR_Service& lSTDAIR_Service =
      lRMOL_ServiceContext.getSTDAIR_Service();
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getBomRoot();

    // Retrieve the date from the RM event
    const stdair::Date_T lDate = iRMEventTime.date();

    _previousForecastDate = lDate;

    const stdair::InventoryList_T& lInventoryList =
      stdair::BomManager::getList<stdair::Inventory> (lBomRoot);
    assert (!lInventoryList.empty());
    for (stdair::InventoryList_T::const_iterator itInv = lInventoryList.begin();
         itInv != lInventoryList.end(); ++itInv) {
      const stdair::Inventory* lInventory_ptr = *itInv;
      assert (lInventory_ptr != NULL);
      const bool hasOnDDateList =
        stdair::BomManager::hasList<stdair::OnDDate> (*lInventory_ptr);
      if (hasOnDDateList == true) {
        const stdair::OnDDateList_T lOnDDateList =
          stdair::BomManager::getList<stdair::OnDDate> (*lInventory_ptr);

        for (stdair::OnDDateList_T::const_iterator itOD = lOnDDateList.begin();
             itOD != lOnDDateList.end(); ++itOD) {
          stdair::OnDDate* lOnDDate_ptr = *itOD;
          assert (lOnDDate_ptr != NULL);
          
          const stdair::Date_T& lDepartureDate = lOnDDate_ptr->getDate();
          stdair::DateOffset_T lDateOffset = lDepartureDate - lDate;
          stdair::DTD_T lDTD = short (lDateOffset.days());
          
          stdair::DCPList_T::const_iterator itDCP =
            std::find (stdair::DEFAULT_DCP_LIST.begin(),
                       stdair::DEFAULT_DCP_LIST.end(), lDTD);
          // Check if the forecast for this O&D date needs to be forecasted.
          if (itDCP != stdair::DEFAULT_DCP_LIST.end()) {
            // Retrieve the total forecast map.
            const stdair::CabinForecastMap_T& lTotalForecastMap =
              lOnDDate_ptr->getTotalForecastMap();
            
            // Browse the map and make a forecast for every cabin.
            for (stdair::CabinForecastMap_T::const_iterator itCF =
                   lTotalForecastMap.begin();
                 itCF != lTotalForecastMap.end(); ++itCF) {
              const stdair::CabinCode_T lCabinCode = itCF->first;
              stdair::YieldFeatures* lYieldFeatures_ptr =
                getYieldFeatures(*lOnDDate_ptr, lCabinCode, lBomRoot);
              if (lYieldFeatures_ptr == NULL) {
                STDAIR_LOG_ERROR ("Cannot find yield corresponding to "
                                  << "the O&D date"
                                  << lOnDDate_ptr->toString()
                                  << " Cabin " << lCabinCode);
                assert (false);
              }
              forecastOnD (*lYieldFeatures_ptr, *lOnDDate_ptr, lCabinCode, lDTD,
                           lBomRoot);
            }
          }
        }
      }
    }    
  }

  // ///////////////////////////////////////////////////////////////////
  stdair::YieldFeatures* RMOL_Service::
  getYieldFeatures(const stdair::OnDDate& iOnDDate,
                   const stdair::CabinCode_T& iCabinCode,
                   stdair::BomRoot& iBomRoot) {

    const stdair::AirportCode_T& lOrigin = iOnDDate.getOrigin();
    const stdair::AirportCode_T& lDestination = iOnDDate.getDestination();

    const stdair::Date_T& lDepartureDate = iOnDDate.getDate();
    
    // Build the airport pair key out of O&D and get the airport pair object
    const stdair::AirportPairKey lAirportPairKey(lOrigin, lDestination);
    stdair::AirportPair* lAirportPair_ptr = stdair::BomManager::
      getObjectPtr<stdair::AirportPair> (iBomRoot,
                                         lAirportPairKey.toString());
    if (lAirportPair_ptr == NULL) {
      STDAIR_LOG_ERROR ("Cannot find yield corresponding to the airport "
                        << "pair: " << lAirportPairKey.toString());
      assert (false);
    }  

    // Retrieve the corresponding date period to lDepartureDate.
    const stdair::DatePeriodList_T lDatePeriodList =
      stdair::BomManager::getList<stdair::DatePeriod> (*lAirportPair_ptr);
    for (stdair::DatePeriodList_T::const_iterator itDatePeriod =
           lDatePeriodList.begin();
         itDatePeriod != lDatePeriodList.end(); ++itDatePeriod) {
      const stdair::DatePeriod* lDatePeriod_ptr = *itDatePeriod;
      assert (lDatePeriod_ptr != NULL);
      
      const bool isDepartureDateValid =
        lDatePeriod_ptr->isDepartureDateValid (lDepartureDate);
      
      if (isDepartureDateValid == true) {
        // Retrieve the PoS-Channel.
        // TODO: Use POS and Channel from demand instead of default
        const stdair::PosChannelKey lPosChannelKey (stdair::DEFAULT_POS,
                                                    stdair::DEFAULT_CHANNEL);
        stdair::PosChannel* lPosChannel_ptr = stdair::BomManager::
          getObjectPtr<stdair::PosChannel> (*lDatePeriod_ptr,
                                            lPosChannelKey.toString());
        if (lPosChannel_ptr == NULL) {
          STDAIR_LOG_ERROR ("Cannot find yield corresponding to the PoS-"
                            << "Channel: " << lPosChannelKey.toString());
          assert (false);
        }
        // Retrieve the yield features.
        const stdair::TimePeriodList_T lTimePeriodList = stdair::
          BomManager::getList<stdair::TimePeriod> (*lPosChannel_ptr);
        for (stdair::TimePeriodList_T::const_iterator itTimePeriod =
               lTimePeriodList.begin();
             itTimePeriod != lTimePeriodList.end(); ++itTimePeriod) {
          const stdair::TimePeriod* lTimePeriod_ptr = *itTimePeriod;
          assert (lTimePeriod_ptr != NULL);
          
          // TODO: Use trip type from demand instead of default value.
          const stdair::YieldFeaturesKey lYieldFeaturesKey (stdair::TRIP_TYPE_ONE_WAY,
                                                            iCabinCode);
          stdair::YieldFeatures* oYieldFeatures_ptr = stdair::BomManager::
            getObjectPtr<stdair::YieldFeatures>(*lTimePeriod_ptr,
                                                lYieldFeaturesKey.toString());
          if (oYieldFeatures_ptr != NULL) {
            return oYieldFeatures_ptr;
          }
        }
      }
    }
    return NULL;
    
  }

  
  // ///////////////////////////////////////////////////////////////////
  void RMOL_Service::
  forecastOnD (const stdair::YieldFeatures& iYieldFeatures,
               stdair::OnDDate& iOnDDate,
               const stdair::CabinCode_T& iCabinCode,
               const stdair::DTD_T& iDTD,
               stdair::BomRoot& iBomRoot) {

    const stdair::AirlineClassListList_T lAirlineClassListList =
      stdair::BomManager::getList<stdair::AirlineClassList> (iYieldFeatures);
    assert (lAirlineClassListList.begin() != lAirlineClassListList.end());

    // Yield order check
    stdair::AirlineClassListList_T::const_iterator  itACL =
      lAirlineClassListList.begin();
    stdair::Yield_T lPreviousYield((*itACL)->getYield());
    ++itACL;
    for (; itACL != lAirlineClassListList.end(); ++itACL) {
      const stdair::AirlineClassList* lAirlineClassList = *itACL;
      const stdair::Yield_T& lYield = lAirlineClassList->getYield();
      if (lYield <= lPreviousYield) {
        lPreviousYield = lYield;
      }
      else{
        STDAIR_LOG_ERROR ("Yields should be given in a descendant order"
                          << " in the yield input file") ;
        assert (false);
      }
    }
    // Proportion factor list initialisation
    // Each element corresponds to a yield rule
    stdair::ProportionFactorList_T lProportionFactorList;
    stdair::ProportionFactor_T lPreviousProportionFactor = 0;

    // Retrieve the minimal willingness to pay associated to the demand
    const stdair::WTPDemandPair_T& lTotalForecast =
      iOnDDate.getTotalForecast (iCabinCode);
    const stdair::WTP_T& lMinWTP = lTotalForecast.first;
   
    // Retrieve the remaining percentage of booking requests
    const stdair::ContinuousAttributeLite<stdair::FloatDuration_T>
      lArrivalPattern (stdair::DEFAULT_DTD_PROB_MAP);
     
    STDAIR_LOG_DEBUG (lArrivalPattern.displayCumulativeDistribution());
    const stdair::Probability_T lRemainingProportion =
      lArrivalPattern.getRemainingProportion(-float(iDTD));

    // Compute the characteristics (mean and std dev) of the total
    // forecast demand to come
    const stdair::MeanStdDevPair_T lForecatsMeanStdDevPair =
      lTotalForecast.second;
    const stdair::MeanValue_T& lMeanValue =
      lForecatsMeanStdDevPair.first;
    const stdair::MeanValue_T& lRemainingMeanValue =
      lRemainingProportion*lMeanValue;
    const stdair::StdDevValue_T& lStdDevValue =
      lForecatsMeanStdDevPair.second;
    const stdair::StdDevValue_T& lRemainingStdDevValue =
      lRemainingProportion*lStdDevValue;

    // Retrieve the frat5 coef corresponding to the input dtd
    stdair::DTDFratMap_T::const_iterator itDFC =
      stdair::DEFAULT_DTD_FRAT5COEF_MAP.find(iDTD);
    if (itDFC == stdair::DEFAULT_DTD_FRAT5COEF_MAP.end()) {
      STDAIR_LOG_ERROR ("Cannot find frat5 coef for DTD = " << iDTD );
      assert (false);
    }
    stdair::RealNumber_T lFrat5Coef =
      stdair::DEFAULT_DTD_FRAT5COEF_MAP.at(iDTD);

    STDAIR_LOG_DEBUG ("Remaining proportion " << lRemainingProportion
                      << " Total " << lMeanValue
                      << " StdDev " << lStdDevValue
                      << "Frat5 Coef " << lFrat5Coef);

    std::ostringstream oStr;
    // Compute the "forecast demand to come" proportion by class
    itACL = lAirlineClassListList.begin();
    for (; itACL != lAirlineClassListList.end(); ++itACL) {
      const stdair::AirlineClassList* lAirlineClassList_ptr = *itACL;
      const stdair::Yield_T& lYield = lAirlineClassList_ptr->getYield();
      stdair::ProportionFactor_T lProportionFactor =
        exp ((lYield - lMinWTP)*log(0.5)/(lMinWTP*(lFrat5Coef-1.0)));
      // If the yield is smaller than minimal WTP, the factor is greater than 1.
      // In that case it should be modified and put to 1.
      lProportionFactor = std::min (lProportionFactor, 1.0);
      lProportionFactorList.push_back(lProportionFactor - lPreviousProportionFactor);      
      lPreviousProportionFactor = lProportionFactor;
      oStr << lAirlineClassList_ptr->toString() << lProportionFactor << " ";
    }

    STDAIR_LOG_DEBUG (oStr.str());

    // Sanity check
    assert (lAirlineClassListList.size() == lProportionFactorList.size());

    STDAIR_LOG_DEBUG ("Forecast for " << iOnDDate.describeKey()
                      << " " << iDTD << " days to departure");

    // store the forecast demand to come characteristics in the booking classes
    stdair::ProportionFactorList_T::const_iterator itPF =
      lProportionFactorList.begin();
    itACL = lAirlineClassListList.begin();
    for (; itACL != lAirlineClassListList.end(); ++itACL, ++itPF) {
      const stdair::AirlineClassList* lAirlineClassList_ptr = *itACL;
      const stdair::ProportionFactor_T& lProportionFactor = *itPF;
      stdair::MeanValue_T lMeanValue = lProportionFactor*lRemainingMeanValue;
      stdair::StdDevValue_T lStdDevValue =
        lProportionFactor*lRemainingStdDevValue;
      setOnDForecast(*lAirlineClassList_ptr, lMeanValue, lStdDevValue,
                     iOnDDate, iCabinCode, iBomRoot);
    }  
    
  }

  // ///////////////////////////////////////////////////////////////////
  void RMOL_Service::
  setOnDForecast (const stdair::AirlineClassList& iAirlineClassList,
                  const stdair::MeanValue_T& iMeanValue,
                  const stdair::StdDevValue_T& iStdDevValue,
                  stdair::OnDDate& iOnDDate,
                  const stdair::CabinCode_T& iCabinCode,
                  stdair::BomRoot& iBomRoot) {
    
    const stdair::AirportCode_T& lOrigin = iOnDDate.getOrigin();
    const stdair::AirportCode_T& lDestination = iOnDDate.getDestination();

    const stdair::Date_T& lDepartureDate = iOnDDate.getDate();

    const stdair::AirlineCodeList_T& lAirlineCodeList =
      iAirlineClassList.getAirlineCodeList();

    // Retrieve the class list (one class per airline)
    const stdair::ClassList_StringList_T& lClassList_StringList =
      iAirlineClassList.getClassCodeList();
    assert (!lClassList_StringList.empty());
    stdair::ClassCodeList_T lClassCodeList;
    for (stdair::ClassList_StringList_T::const_iterator itCL =
           lClassList_StringList.begin();
         itCL != lClassList_StringList.end(); ++itCL){
      const stdair::ClassList_String_T& lClassList_String = *itCL;
      assert (lClassList_String.size() > 0);
      stdair::ClassCode_T lFirstClass;
      lFirstClass.append (lClassList_String, 0, 1);
      lClassCodeList.push_back(lFirstClass);
    }

    // Sanity check
    assert (lAirlineCodeList.size() == lClassCodeList.size());
    assert (!lAirlineCodeList.empty());

    if (lAirlineCodeList.size() == 1) {
      // Store the forecast information in the case of a single segment
      stdair::AirlineCode_T lAirlineCode = lAirlineCodeList.front();
      stdair::ClassCode_T lClassCode = lClassCodeList.front();
      stdair::Yield_T lYield = iAirlineClassList.getYield();
      setOnDForecast(lAirlineCode, lDepartureDate, lOrigin,
                     lDestination, iCabinCode, lClassCode,
                     iMeanValue, iStdDevValue, lYield, iBomRoot);      
    } else {
      // Store the forecast information in the case of a multiple segment
      
      stdair::Yield_T lYield = iAirlineClassList.getYield();
      for (stdair::AirlineCodeList_T::const_iterator itAC =
             lAirlineCodeList.begin();
           itAC != lAirlineCodeList.end(); ++itAC) {
        const stdair::AirlineCode_T& lAirlineCode = *itAC;
        setOnDForecast(lAirlineCodeList, lAirlineCode, lDepartureDate, lOrigin,
                       lDestination, iCabinCode, lClassCodeList,
                       iMeanValue, iStdDevValue, lYield, iBomRoot);
      }      
    }
  }

  // ///////////////////////////////////////////////////////////////////
  void RMOL_Service::
  setOnDForecast (const stdair::AirlineCode_T& iAirlineCode,
                  const stdair::Date_T& iDepartureDate,
                  const stdair::AirportCode_T& iOrigin,
                  const stdair::AirportCode_T& iDestination,
                  const stdair::CabinCode_T& iCabinCode,
                  const stdair::ClassCode_T& iClassCode,
                  const stdair::MeanValue_T& iMeanValue,
                  const stdair::StdDevValue_T& iStdDevValue,
                  const stdair::Yield_T& iYield,
                  stdair::BomRoot& iBomRoot) {
    stdair::Inventory* lInventory_ptr = iBomRoot.getInventory(iAirlineCode);
    if (lInventory_ptr == NULL) {
      STDAIR_LOG_ERROR ("Cannot find the inventory corresponding"
                        << " to the airline" << iAirlineCode) ;
      assert(false);
    }
    const stdair::OnDDateList_T lOnDDateList =
      stdair::BomManager::getList<stdair::OnDDate> (*lInventory_ptr);
    assert (!lOnDDateList.empty());
    bool lFoundOnDDate = false;
    for (stdair::OnDDateList_T::const_iterator itOD = lOnDDateList.begin();
         itOD != lOnDDateList.end(); ++itOD) {
      stdair::OnDDate* lOnDDate_ptr = *itOD;
      assert (lOnDDate_ptr != NULL);
      const stdair::Date_T& lDepartureDate = lOnDDate_ptr->getDate();
      const stdair::AirportCode_T& lOrigin = lOnDDate_ptr->getOrigin();
      const stdair::AirportCode_T& lDestination = lOnDDate_ptr->getDestination();
      const bool hasSegmentDateList =
        stdair::BomManager::hasList<stdair::SegmentDate> (*lOnDDate_ptr);
      if (hasSegmentDateList == false) {
        STDAIR_LOG_ERROR ("The O&D date " << lOnDDate_ptr->describeKey()
                          << "has not been correctly initialized : SegmentDate list is missing");
        assert (false);
      }
      const stdair::SegmentDateList_T& lSegmentDateList =
        stdair::BomManager::getList<stdair::SegmentDate> (*lOnDDate_ptr);
      // Check if the the O&D date is the one we are looking for
      if (lDepartureDate == iDepartureDate && lOrigin == iOrigin &&
          lDestination == iDestination && lSegmentDateList.size() == 1) {       
        stdair::CabinClassPair_T lCabinClassPair (iCabinCode, iClassCode);
        stdair::CabinClassPairList_T lCabinClassPairList;
        lCabinClassPairList.push_back(lCabinClassPair);
        const stdair::MeanStdDevPair_T lMeanStdDevPair (iMeanValue, iStdDevValue);
        const stdair::WTPDemandPair_T lWTPDemandPair (iYield, lMeanStdDevPair);
        lOnDDate_ptr->setDemandInformation(lCabinClassPairList, lWTPDemandPair);
        lFoundOnDDate = true;
        STDAIR_LOG_DEBUG (iAirlineCode << " Class " << iClassCode
                          << " Mean " << iMeanValue
                          << " Std Dev " << iStdDevValue);
        break;
      }
    }

    if (!lFoundOnDDate) {
      STDAIR_LOG_ERROR ("Cannot find class " << iClassCode << " in cabin "
                        << iCabinCode << " for the segment "
                        << iOrigin << "-" << iDestination << " with"
                        << " the airline " << iAirlineCode);
      assert(false);
    }
  }
  
  // ///////////////////////////////////////////////////////////////////       
  void RMOL_Service::
  setOnDForecast (const stdair::AirlineCodeList_T& iAirlineCodeList,
                  const stdair::AirlineCode_T& iAirlineCode,
                  const stdair::Date_T& iDepartureDate,
                  const stdair::AirportCode_T& iOrigin,
                  const stdair::AirportCode_T& iDestination,
                  const stdair::CabinCode_T& iCabinCode,
                  const stdair::ClassCodeList_T& iClassCodeList,
                  const stdair::MeanValue_T& iMeanValue,
                  const stdair::StdDevValue_T& iStdDevValue,
                  const stdair::Yield_T& iYield,
                  stdair::BomRoot& iBomRoot) {    
    stdair::Inventory* lInventory_ptr = iBomRoot.getInventory(iAirlineCode);
    if (lInventory_ptr == NULL) {
      STDAIR_LOG_ERROR ("Cannot find the inventory corresponding"
                        << " to the airline" << iAirlineCode) ;
      assert(false);
    }
    const stdair::OnDDateList_T lOnDDateList =
      stdair::BomManager::getList<stdair::OnDDate> (*lInventory_ptr);
    assert (!lOnDDateList.empty());
    bool lFoundOnDDate = false;
    for (stdair::OnDDateList_T::const_iterator itOD = lOnDDateList.begin();
         itOD != lOnDDateList.end(); ++itOD) {
      stdair::OnDDate* lOnDDate_ptr = *itOD;
      assert (lOnDDate_ptr != NULL);
      const stdair::Date_T& lDepartureDate = lOnDDate_ptr->getDate();
      const stdair::AirportCode_T& lOrigin = lOnDDate_ptr->getOrigin();
      const stdair::AirportCode_T& lDestination = lOnDDate_ptr->getDestination();
      const bool hasSegmentDateList =
        stdair::BomManager::hasList<stdair::SegmentDate> (*lOnDDate_ptr);
      if (hasSegmentDateList == false) {
        STDAIR_LOG_ERROR ("The O&D date " << lOnDDate_ptr->describeKey()
                          << "has not been correctly initialized : SegmentDate list is missing");
        assert (false);
      }
      const stdair::SegmentDateList_T& lSegmentDateList =
        stdair::BomManager::getList<stdair::SegmentDate> (*lOnDDate_ptr);
      // Check if the O&D date might be the one we are looking for.
      // There still is a test to go through to see if the combination of airlines is right.
      if (lDepartureDate == iDepartureDate && lOrigin == iOrigin &&
          lDestination == iDestination && lSegmentDateList.size() == iAirlineCodeList.size()) {
        const stdair::SegmentDateList_T& lSegmentDateList =
          stdair::BomManager::getList<stdair::SegmentDate> (*lOnDDate_ptr);        
        stdair::AirlineCodeList_T::const_iterator itAC = iAirlineCodeList.begin();
        stdair::SegmentDateList_T::const_iterator itSD = lSegmentDateList.begin();
        for (;itAC != iAirlineCodeList.end(); ++itAC, ++itSD) {
          const stdair::AirlineCode_T lForecastAirlineCode = *itAC;
          const stdair::SegmentDate* lSegmentDate_ptr = *itSD;
          // Check if the operating airline is a different one and check if it
          // is the airline that we are looking for.
          const stdair::SegmentDate* lOperatingSegmentDate_ptr =
            lSegmentDate_ptr->getOperatingSegmentDate ();
          if (lOperatingSegmentDate_ptr != NULL) {
            const stdair::FlightDate* lOperatingFD_ptr =
              stdair::BomManager::getParentPtr<stdair::FlightDate>(*lOperatingSegmentDate_ptr);
            const stdair::AirlineCode_T lOperatingAirlineCode =
              lOperatingFD_ptr->getAirlineCode();
            if (lOperatingAirlineCode != lForecastAirlineCode) {
              break;
            }
          } else {
            const stdair::AirlineCode_T lOperatingAirlineCode =
              lOnDDate_ptr->getAirlineCode();
            if (lOperatingAirlineCode != lForecastAirlineCode) {
              break;
            }
          }          
        }
        if (itAC == iAirlineCodeList.end()) {lFoundOnDDate = true;}
      }
      if (lFoundOnDDate) {        
        stdair::CabinClassPairList_T lCabinClassPairList;
        for (stdair::ClassCodeList_T::const_iterator itCC = iClassCodeList.begin();
             itCC != iClassCodeList.end(); ++itCC) {
          const stdair::ClassCode_T lClassCode = *itCC;
          stdair::CabinClassPair_T lCabinClassPair (iCabinCode, lClassCode);
          lCabinClassPairList.push_back(lCabinClassPair);
        }
        const stdair::MeanStdDevPair_T lMeanStdDevPair (iMeanValue, iStdDevValue);
        const stdair::YieldDemandPair_T lYieldDemandPair (iYield, lMeanStdDevPair);
        lOnDDate_ptr->setDemandInformation(lCabinClassPairList, lYieldDemandPair);
        lFoundOnDDate = true;
        std::ostringstream oACStr;
        for (stdair::AirlineCodeList_T::const_iterator itAC = iAirlineCodeList.begin();
             itAC != iAirlineCodeList.end(); ++itAC) {
          if (itAC == iAirlineCodeList.begin()) {
            oACStr << *itAC;
          }
          else {
            oACStr << "-" << *itAC;
          }
        }
        std::ostringstream oCCStr;
        for (stdair::ClassCodeList_T::const_iterator itCC = iClassCodeList.begin();
             itCC != iClassCodeList.end(); ++itCC) {
          if (itCC == iClassCodeList.begin()) {
            oCCStr << *itCC;
          }
          else {
            oCCStr << "-" << *itCC;
          }
        }
        
        STDAIR_LOG_DEBUG (oACStr.str() << " Classes " << oCCStr.str()
                          << " Mean " << iMeanValue << " Std Dev " << iStdDevValue);        
        break;
      }
    }
    if (!lFoundOnDDate) {
      STDAIR_LOG_ERROR ("Cannot find the required multi-segment O&D date:  "
                        << iOrigin << "-" << iDestination << " " << iDepartureDate);
      assert(false);
    }
  }
  
  // ///////////////////////////////////////////////////////////////////
  void RMOL_Service::
  resetDemandInformation (const stdair::DateTime_T& iRMEventTime) {
    if (_rmolServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The Rmol service "
                                                    "has not been initialised");
    }
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;
    
    // Retrieve the bom root
    stdair::STDAIR_Service& lSTDAIR_Service =
      lRMOL_ServiceContext.getSTDAIR_Service();
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getBomRoot();

    const stdair::InventoryList_T lInventoryList =
      stdair::BomManager::getList<stdair::Inventory> (lBomRoot);
    assert (!lInventoryList.empty());
    for (stdair::InventoryList_T::const_iterator itInv = lInventoryList.begin();
         itInv != lInventoryList.end(); ++itInv) {
      const stdair::Inventory* lInventory_ptr = *itInv;
      assert (lInventory_ptr != NULL);
      resetDemandInformation (iRMEventTime, *lInventory_ptr);
    }
  }

  // ///////////////////////////////////////////////////////////////////
  void RMOL_Service::
  resetDemandInformation (const stdair::DateTime_T& iRMEventTime,
                          const stdair::Inventory& iInventory) {
    
    const stdair::FlightDateList_T lFlightDateList =
      stdair::BomManager::getList<stdair::FlightDate> (iInventory);
    assert (!lFlightDateList.empty());
    for (stdair::FlightDateList_T::const_iterator itFD = lFlightDateList.begin();
         itFD != lFlightDateList.end(); ++itFD) {
      const stdair::FlightDate* lFlightDate_ptr = *itFD;
      assert (lFlightDate_ptr != NULL);
      
      // Retrieve the date from the RM event
      const stdair::Date_T lDate = iRMEventTime.date();
      
      const stdair::Date_T& lDepartureDate = lFlightDate_ptr->getDepartureDate();
      stdair::DateOffset_T lDateOffset = lDepartureDate - lDate;
      stdair::DTD_T lDTD = short (lDateOffset.days());
      
      stdair::DCPList_T::const_iterator itDCP =
        std::find (stdair::DEFAULT_DCP_LIST.begin(), stdair::DEFAULT_DCP_LIST.end(), lDTD);
      // Check if the demand forecast info corresponding to this flight date needs to be reset.
      if (itDCP != stdair::DEFAULT_DCP_LIST.end()) {
        // Check if the flight date holds a list of leg dates.
        // If so, find all leg cabin and reset the forecast they are holding.
        const bool hasLegDateList =
          stdair::BomManager::hasList<stdair::LegDate> (*lFlightDate_ptr);
        if (hasLegDateList == true) {
          const stdair::LegDateList_T lLegDateList =
            stdair::BomManager::getList<stdair::LegDate> (*lFlightDate_ptr);
          assert (!lLegDateList.empty());
          for (stdair::LegDateList_T::const_iterator itLD = lLegDateList.begin();
               itLD != lLegDateList.end(); ++itLD) {
            const stdair::LegDate* lLegDate_ptr = *itLD;
            assert (lLegDate_ptr != NULL);
            const stdair::LegCabinList_T lLegCabinList =
              stdair::BomManager::getList<stdair::LegCabin> (*lLegDate_ptr);
            assert (!lLegCabinList.empty());
            for (stdair::LegCabinList_T::const_iterator itLC = lLegCabinList.begin();
                 itLC != lLegCabinList.end(); ++itLC) {
              stdair::LegCabin* lLegCabin_ptr = *itLC;
              assert (lLegCabin_ptr != NULL);
              lLegCabin_ptr->emptyYieldLevelDemandMap();
            }
          }
        }
      }
    }
  }
  
  // ///////////////////////////////////////////////////////////////////
  void RMOL_Service::projectAggregatedDemandOnLegCabins(const stdair::DateTime_T& iRMEventTime) {

    if (_rmolServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The Rmol service "
                                                    "has not been initialised");
    }
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;
    
    // Retrieve the bom root
    stdair::STDAIR_Service& lSTDAIR_Service =
      lRMOL_ServiceContext.getSTDAIR_Service();
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getBomRoot();

    // Retrieve the date from the RM event
    const stdair::Date_T lDate = iRMEventTime.date();

    const stdair::InventoryList_T lInventoryList =
      stdair::BomManager::getList<stdair::Inventory> (lBomRoot);
    assert (!lInventoryList.empty());
    for (stdair::InventoryList_T::const_iterator itInv = lInventoryList.begin();
         itInv != lInventoryList.end(); ++itInv) {
      const stdair::Inventory* lInventory_ptr = *itInv;
      assert (lInventory_ptr != NULL);
      const stdair::OnDDateList_T lOnDDateList =
        stdair::BomManager::getList<stdair::OnDDate> (*lInventory_ptr);
      assert (!lOnDDateList.empty());
      for (stdair::OnDDateList_T::const_iterator itOD = lOnDDateList.begin();
           itOD != lOnDDateList.end(); ++itOD) {
        stdair::OnDDate* lOnDDate_ptr = *itOD;
        assert (lOnDDate_ptr != NULL);

        const stdair::Date_T& lDepartureDate = lOnDDate_ptr->getDate();
        stdair::DateOffset_T lDateOffset = lDepartureDate - lDate;
        stdair::DTD_T lDTD = short (lDateOffset.days());
      
        stdair::DCPList_T::const_iterator itDCP =
          std::find (stdair::DEFAULT_DCP_LIST.begin(), stdair::DEFAULT_DCP_LIST.end(), lDTD);
        // Check if the forecast for this O&D date needs to be projected.
        if (itDCP != stdair::DEFAULT_DCP_LIST.end()) {

          // Browse the demand info map.
          const stdair::StringDemandStructMap_T& lStringDemandStructMap =
            lOnDDate_ptr->getDemandInfoMap ();
          for (stdair::StringDemandStructMap_T::const_iterator itStrDS = lStringDemandStructMap.begin();
               itStrDS != lStringDemandStructMap.end(); ++itStrDS) {
            std::string lCabinClassPath = itStrDS->first;
            const stdair::YieldDemandPair_T& lYieldDemandPair =
              itStrDS->second;
            const stdair::CabinClassPairList_T& lCabinClassPairList =
              lOnDDate_ptr->getCabinClassPairList(lCabinClassPath);
            const stdair::NbOfSegments_T& lNbOfSegments = lOnDDate_ptr->getNbOfSegments();
            // Sanity check
            assert (lCabinClassPairList.size() == lNbOfSegments);
            
            const stdair::SegmentDateList_T lOnDSegmentDateList =
              stdair::BomManager::getList<stdair::SegmentDate> (*lOnDDate_ptr);
            // Sanity check
            assert (lOnDSegmentDateList.size() == lNbOfSegments);
            stdair::CabinClassPairList_T::const_iterator itCCP = lCabinClassPairList.begin();
            stdair::SegmentDateList_T::const_iterator itSD = lOnDSegmentDateList.begin();
            for (; itSD != lOnDSegmentDateList.end(); ++itCCP, ++itSD) {
              const stdair::SegmentDate* lSegmentDate_ptr = *itSD;
              const stdair::SegmentDate* lOperatingSegmentDate_ptr =
                lSegmentDate_ptr->getOperatingSegmentDate ();
              assert (lSegmentDate_ptr != NULL);
              // Only operated legs receive the demand information.
              if (lOperatingSegmentDate_ptr == NULL) {
                const stdair::CabinCode_T lCabinCode = itCCP->first;
                const stdair::ClassCode_T lClassCode = itCCP->second;
                const stdair::SegmentCabin* lSegmentCabin_ptr =
                  stdair::BomManager::getObjectPtr<stdair::SegmentCabin> (*lSegmentDate_ptr,
                                                                          lCabinCode);
                assert (lSegmentCabin_ptr != NULL);
                // Retrieve the booking class (level of aggregation of demand).
                // The yield of the class is assigned to all types of demand for it.
                const stdair::BookingClass* lBookingClass_ptr =
                  stdair::BomManager::getObjectPtr<stdair::BookingClass> (*lSegmentCabin_ptr,
                                                                          lClassCode);
                assert (lBookingClass_ptr != NULL);
                const stdair::LegCabinList_T lLegCabinList =
                  stdair::BomManager::getList<stdair::LegCabin> (*lSegmentCabin_ptr);
                assert (!lLegCabinList.empty());
                const int lNbOfLegs = lLegCabinList.size();
                // Determine the yield (equally distributed over legs).
                const stdair::Yield_T& lYield = lBookingClass_ptr->getYield()/lNbOfLegs;
                const stdair::MeanStdDevPair_T& lMeanStdDevPair =
                  lYieldDemandPair.second;
                const stdair::MeanValue_T& lMeanValue = lMeanStdDevPair.first;
                const stdair::StdDevValue_T& lStdDevValue = lMeanStdDevPair.second;
                for (stdair::LegCabinList_T::const_iterator itLC = lLegCabinList.begin();
                     itLC != lLegCabinList.end(); ++itLC) {
                  stdair::LegCabin* lLegCabin_ptr = *itLC;
                  assert (lLegCabin_ptr != NULL);
                  lLegCabin_ptr->addDemandInformation (lYield, lMeanValue, lStdDevValue);
                }
              }
            }
          }
        }
      }
    }
  }

  // ///////////////////////////////////////////////////////////////////
  void RMOL_Service::projectOnDDemandOnLegCabinsUsingYP(const stdair::DateTime_T& iRMEventTime) {

    if (_rmolServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The Rmol service "
                                                    "has not been initialised");
    }
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;
    
    // Retrieve the bom root
    stdair::STDAIR_Service& lSTDAIR_Service =
      lRMOL_ServiceContext.getSTDAIR_Service();
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getBomRoot();

    // Retrieve the date from the RM event
    const stdair::Date_T lDate = iRMEventTime.date();

    const stdair::InventoryList_T lInventoryList =
      stdair::BomManager::getList<stdair::Inventory> (lBomRoot);
    assert (!lInventoryList.empty());
    for (stdair::InventoryList_T::const_iterator itInv = lInventoryList.begin();
         itInv != lInventoryList.end(); ++itInv) {
      const stdair::Inventory* lInventory_ptr = *itInv;
      assert (lInventory_ptr != NULL);
      const stdair::OnDDateList_T lOnDDateList =
        stdair::BomManager::getList<stdair::OnDDate> (*lInventory_ptr);
      assert (!lOnDDateList.empty());
      for (stdair::OnDDateList_T::const_iterator itOD = lOnDDateList.begin();
           itOD != lOnDDateList.end(); ++itOD) {
        stdair::OnDDate* lOnDDate_ptr = *itOD;
        assert (lOnDDate_ptr != NULL);

        const stdair::Date_T& lDepartureDate = lOnDDate_ptr->getDate();
        stdair::DateOffset_T lDateOffset = lDepartureDate - lDate;
        stdair::DTD_T lDTD = short (lDateOffset.days());
      
        stdair::DCPList_T::const_iterator itDCP =
          std::find (stdair::DEFAULT_DCP_LIST.begin(), stdair::DEFAULT_DCP_LIST.end(), lDTD);
        // Check if the forecast for this O&D date needs to be projected.
        if (itDCP != stdair::DEFAULT_DCP_LIST.end()) {

          // Browse the demand info map.
          const stdair::StringDemandStructMap_T& lStringDemandStructMap =
            lOnDDate_ptr->getDemandInfoMap ();
          for (stdair::StringDemandStructMap_T::const_iterator itStrDS = lStringDemandStructMap.begin();
               itStrDS != lStringDemandStructMap.end(); ++itStrDS) {
            std::string lCabinClassPath = itStrDS->first;
            const stdair::YieldDemandPair_T& lYieldDemandPair =
              itStrDS->second;
            const stdair::CabinClassPairList_T& lCabinClassPairList =
              lOnDDate_ptr->getCabinClassPairList(lCabinClassPath);
            const stdair::NbOfSegments_T& lNbOfSegments = lOnDDate_ptr->getNbOfSegments();
            // Sanity check
            assert (lCabinClassPairList.size() == lNbOfSegments);
            
            const stdair::SegmentDateList_T lOnDSegmentDateList =
              stdair::BomManager::getList<stdair::SegmentDate> (*lOnDDate_ptr);
            // Sanity check
            assert (lOnDSegmentDateList.size() == lNbOfSegments);
            stdair::CabinClassPairList_T::const_iterator itCCP = lCabinClassPairList.begin();
            stdair::SegmentDateList_T::const_iterator itSD = lOnDSegmentDateList.begin();
            for (; itSD != lOnDSegmentDateList.end(); ++itCCP, ++itSD) {
              const stdair::SegmentDate* lSegmentDate_ptr = *itSD;
              assert (lSegmentDate_ptr != NULL);
              const stdair::SegmentDate* lOperatingSegmentDate_ptr =
                lSegmentDate_ptr->getOperatingSegmentDate ();
              // Only operated legs receive the demand information.
              if (lOperatingSegmentDate_ptr == NULL) {
                const stdair::CabinCode_T lCabinCode = itCCP->first;
                const stdair::ClassCode_T lClassCode = itCCP->second;
                const stdair::SegmentCabin* lSegmentCabin_ptr =
                  stdair::BomManager::getObjectPtr<stdair::SegmentCabin> (*lSegmentDate_ptr,
                                                                          lCabinCode);
                assert (lSegmentCabin_ptr != NULL);
                const stdair::LegCabinList_T lLegCabinList =
                  stdair::BomManager::getList<stdair::LegCabin> (*lSegmentCabin_ptr);
                assert (!lLegCabinList.empty());
                const int lNbOfLegs = lLegCabinList.size();
                // Determine the yield (equally distributed over segments and then legs).
                const stdair::MeanStdDevPair_T& lMeanStdDevPair =
                  lYieldDemandPair.second;
                const stdair::Yield_T& lYield = lYieldDemandPair.first/(lNbOfLegs*lNbOfSegments);
                const stdair::MeanValue_T& lMeanValue = lMeanStdDevPair.first;
                const stdair::StdDevValue_T& lStdDevValue = lMeanStdDevPair.second;
                for (stdair::LegCabinList_T::const_iterator itLC = lLegCabinList.begin();
                     itLC != lLegCabinList.end(); ++itLC) {
                  stdair::LegCabin* lLegCabin_ptr = *itLC;
                  assert (lLegCabin_ptr != NULL);
                  lLegCabin_ptr->addDemandInformation (lYield, lMeanValue, lStdDevValue);
                }
              }
            }
          }
        }
      }
    }
  }

  // ///////////////////////////////////////////////////////////////////
  void RMOL_Service::optimiseOnD (const stdair::DateTime_T& iRMEventTime) {

    if (_rmolServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The Rmol service "
                                                    "has not been initialised");
    }
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;

    // Retrieve the bom root
    stdair::STDAIR_Service& lSTDAIR_Service =
      lRMOL_ServiceContext.getSTDAIR_Service();
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getBomRoot();

    // Retrieve the date from the RM event
    const stdair::Date_T lDate = iRMEventTime.date();

    const stdair::InventoryList_T& lInvList =
      stdair::BomManager::getList<stdair::Inventory> (lBomRoot);
    for (stdair::InventoryList_T::const_iterator itInv = lInvList.begin();
         itInv != lInvList.end(); ++itInv) {
      stdair::Inventory* lCurrentInv_ptr = *itInv;
      assert (lCurrentInv_ptr != NULL);

      const stdair::FlightDateList_T& lFlightDateList =
	stdair::BomManager::getList<stdair::FlightDate> (*lCurrentInv_ptr);
      for (stdair::FlightDateList_T::const_iterator itFlightDate =
	     lFlightDateList.begin();
	   itFlightDate != lFlightDateList.end(); ++itFlightDate) {
	stdair::FlightDate* lCurrentFlightDate_ptr = *itFlightDate;
	assert (lCurrentFlightDate_ptr != NULL);

        const stdair::Date_T& lCurrentDepartureDate = lCurrentFlightDate_ptr->getDepartureDate();
        stdair::DateOffset_T lDateOffset = lCurrentDepartureDate - lDate;
        stdair::DTD_T lDTD = short (lDateOffset.days());
      
        stdair::DCPList_T::const_iterator itDCP =
          std::find (stdair::DEFAULT_DCP_LIST.begin(), stdair::DEFAULT_DCP_LIST.end(), lDTD);
        // Check if the optimisation is needed.
        if (itDCP != stdair::DEFAULT_DCP_LIST.end()) {
          STDAIR_LOG_DEBUG ("Optimisation using O&D forecast: " << lCurrentInv_ptr->getAirlineCode()
                            << " Departure " << lCurrentDepartureDate << " DTD " << lDTD);
          Optimiser::optimiseUsingOnDForecast (*lCurrentFlightDate_ptr);
        }
      }
    }    
  }

  // ///////////////////////////////////////////////////////////////////
  void RMOL_Service::updateBidPrice (const stdair::DateTime_T& iRMEventTime) {

    if (_rmolServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The Rmol service "
                                                    "has not been initialised");
    }
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;

    // Retrieve the bom root
    stdair::STDAIR_Service& lSTDAIR_Service =
      lRMOL_ServiceContext.getSTDAIR_Service();
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getBomRoot();

    // Retrieve the date from the RM event
    const stdair::Date_T lDate = iRMEventTime.date();

    const stdair::InventoryList_T& lInvList =
      stdair::BomManager::getList<stdair::Inventory> (lBomRoot);

    for (stdair::InventoryList_T::const_iterator itInv = lInvList.begin();
         itInv != lInvList.end(); ++itInv) {
      stdair::Inventory* lCurrentInv_ptr = *itInv;
      assert (lCurrentInv_ptr != NULL);
      
      const stdair::FlightDateList_T& lFlightDateList =
	stdair::BomManager::getList<stdair::FlightDate> (*lCurrentInv_ptr);
      for (stdair::FlightDateList_T::const_iterator itFlightDate =
	     lFlightDateList.begin();
	   itFlightDate != lFlightDateList.end(); ++itFlightDate) {
	stdair::FlightDate* lCurrentFlightDate_ptr = *itFlightDate;
	assert (lCurrentFlightDate_ptr != NULL);

        const stdair::Date_T& lCurrentDepartureDate = lCurrentFlightDate_ptr->getDepartureDate();
        stdair::DateOffset_T lDateOffset = lCurrentDepartureDate - lDate;
        stdair::DTD_T lDTD = short (lDateOffset.days());
      
        stdair::DCPList_T::const_iterator itDCP =
          std::find (stdair::DEFAULT_DCP_LIST.begin(), stdair::DEFAULT_DCP_LIST.end(), lDTD);
        // Check if the operation is needed.
        if (itDCP != stdair::DEFAULT_DCP_LIST.end()) {
          updateBidPrice (*lCurrentFlightDate_ptr, lBomRoot);
        }
      }
    }
  }

  // ///////////////////////////////////////////////////////////////////
  void RMOL_Service::updateBidPrice (const stdair::FlightDate& iFlightDate,
                                          stdair::BomRoot& iBomRoot) {
    const stdair::SegmentDateList_T& lSegmentDateList =
      stdair::BomManager::getList<stdair::SegmentDate> (iFlightDate);
    const stdair::AirlineCode_T& lOptAC = iFlightDate.getAirlineCode();
    const std::string lFDKeyStr = iFlightDate.describeKey();
    
    for (stdair::SegmentDateList_T::const_iterator itSegmentDate = lSegmentDateList.begin();
         itSegmentDate != lSegmentDateList.end(); ++itSegmentDate) {
      stdair::SegmentDate* lSegmentDate_ptr = *itSegmentDate;
      assert (lSegmentDate_ptr != NULL);
      const bool hasSegmentDateList =
        stdair::BomManager::hasList<stdair::SegmentDate>(*lSegmentDate_ptr);
      if (hasSegmentDateList == true) {
        const stdair::LegDateList_T& lLegDateList =
          stdair::BomManager::getList<stdair::LegDate>(*lSegmentDate_ptr);
        // Get the list of marketing carriers segments.
        // These are part of maketing partners inventories images held by the operating airline.
        const stdair::SegmentDateList_T& lMktSegmentDateList =
          stdair::BomManager::getList<stdair::SegmentDate>(*lSegmentDate_ptr);
        for (stdair::SegmentDateList_T::const_iterator itMktSD = lMktSegmentDateList.begin();
             itMktSD != lMktSegmentDateList.end(); ++itMktSD) {
          // Get the marketing airline code.
          stdair::SegmentDate* lMktSD_ptr = *itMktSD;
          assert (lMktSD_ptr != NULL);
          stdair::FlightDate* lMktFD_ptr =
            stdair::BomManager::getParentPtr<stdair::FlightDate>(*lMktSD_ptr);
          assert (lMktFD_ptr != NULL);
          const stdair::AirlineCode_T& lMktAC = lMktFD_ptr->getAirlineCode();
          // Get the (real) marketer inventory.
          const stdair::Inventory* lMktInv_ptr =
            stdair::BomManager::getObjectPtr<stdair::Inventory>(iBomRoot,lMktAC);
          assert (lMktInv_ptr != NULL);
          // Get the image of the operating airline inventory held by the marketer.
          const stdair::Inventory* lOptInv_ptr =
            stdair::BomManager::getObjectPtr<stdair::Inventory>(*lMktInv_ptr,lOptAC);
          assert (lOptInv_ptr != NULL);
          // Find the image of the concerned flight date.
          const stdair::FlightDate* lOptFD_ptr =
            stdair::BomManager::getObjectPtr<stdair::FlightDate>(*lOptInv_ptr,lFDKeyStr);
          assert (lOptFD_ptr != NULL);
          // Browse the list of leg dates in the real operating inventory.
          // Retrieve the image of each leg date.
          for (stdair::LegDateList_T::const_iterator itLD = lLegDateList.begin();
               itLD != lLegDateList.end(); ++itLD) {
            const stdair::LegDate* lLD_ptr = *itLD;
            assert (lLD_ptr != NULL);
            const std::string lLDKeyStr = lLD_ptr->describeKey();
            stdair::LegDate* lOptLD_ptr =
              stdair::BomManager::getObjectPtr<stdair::LegDate>(*lOptFD_ptr,lLDKeyStr);
            assert (lOptLD_ptr != NULL);
            const stdair::LegCabinList_T& lLegCabinList_T =
              stdair::BomManager::getList<stdair::LegCabin>(*lLD_ptr);
            // Browse the list of leg cabins in the real operating inventory.
            // Retrieve the image of each leg cabin and update the bid price of the real and send it to the image.
            for (stdair::LegCabinList_T::const_iterator itLC = lLegCabinList_T.begin();
                 itLC != lLegCabinList_T.end(); ++itLC) {
              stdair::LegCabin* lLC_ptr = *itLC;
              assert (lLC_ptr != NULL);
              const std::string lLCKeyStr = lLC_ptr->describeKey();
              stdair::LegCabin* lOptLC_ptr =
                stdair::BomManager::getObjectPtr<stdair::LegCabin>(*lOptLD_ptr, lLCKeyStr);
              assert (lOptLC_ptr != NULL);
              // Update the current bid price of the real leg.
              lLC_ptr->updateCurrentBidPrice();
              // Update the previous bid price (store the current).
              lOptLC_ptr->updatePreviousBidPrice();
              // Update the current bid price.
              lOptLC_ptr->setCurrentBidPrice (lLC_ptr->getCurrentBidPrice());

              STDAIR_LOG_DEBUG ("Update bid price of " << lLC_ptr->getFullerKey()
                                << " : " << lOptLC_ptr->getCurrentBidPrice()
                                << " Availability pool " << lLC_ptr->getAvailabilityPool());
            }
          }
        }
      }
    }
  }

  // ///////////////////////////////////////////////////////////////////
  void RMOL_Service::projectOnDDemandOnLegCabinsUsingDA(const stdair::DateTime_T& iRMEventTime) {

    if (_rmolServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The Rmol service "
                                                    "has not been initialised");
    }
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;
    
    // Retrieve the bom root
    stdair::STDAIR_Service& lSTDAIR_Service =
      lRMOL_ServiceContext.getSTDAIR_Service();
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getBomRoot();

    // Retrieve the date from the RM event
    const stdair::Date_T lDate = iRMEventTime.date();

    const stdair::InventoryList_T lInventoryList =
      stdair::BomManager::getList<stdair::Inventory> (lBomRoot);
    assert (!lInventoryList.empty());
    for (stdair::InventoryList_T::const_iterator itInv = lInventoryList.begin();
         itInv != lInventoryList.end(); ++itInv) {
      const stdair::Inventory* lInventory_ptr = *itInv;
      assert (lInventory_ptr != NULL);
      const stdair::OnDDateList_T lOnDDateList =
        stdair::BomManager::getList<stdair::OnDDate> (*lInventory_ptr);
      assert (!lOnDDateList.empty());
      for (stdair::OnDDateList_T::const_iterator itOD = lOnDDateList.begin();
           itOD != lOnDDateList.end(); ++itOD) {
        stdair::OnDDate* lOnDDate_ptr = *itOD;
        assert (lOnDDate_ptr != NULL);

        const stdair::Date_T& lDepartureDate = lOnDDate_ptr->getDate();
        stdair::DateOffset_T lDateOffset = lDepartureDate - lDate;
        stdair::DTD_T lDTD = short (lDateOffset.days());
      
        stdair::DCPList_T::const_iterator itDCP =
          std::find (stdair::DEFAULT_DCP_LIST.begin(), stdair::DEFAULT_DCP_LIST.end(), lDTD);
        // Check if the forecast for this O&D date needs to be projected.
        if (itDCP != stdair::DEFAULT_DCP_LIST.end()) {

          // Browse the demand info map.
          const stdair::StringDemandStructMap_T& lStringDemandStructMap =
            lOnDDate_ptr->getDemandInfoMap ();
          for (stdair::StringDemandStructMap_T::const_iterator itStrDS = lStringDemandStructMap.begin();
               itStrDS != lStringDemandStructMap.end(); ++itStrDS) {
            std::string lCabinClassPath = itStrDS->first;
            const stdair::YieldDemandPair_T& lYieldDemandPair = itStrDS->second;
            const stdair::CabinClassPairList_T& lCabinClassPairList =
              lOnDDate_ptr->getCabinClassPairList(lCabinClassPath);
            const stdair::NbOfSegments_T& lNbOfSegments = lOnDDate_ptr->getNbOfSegments();
            // Sanity check
            assert (lCabinClassPairList.size() == lNbOfSegments);

            //
            const stdair::SegmentDateList_T lOnDSegmentDateList =
              stdair::BomManager::getList<stdair::SegmentDate> (*lOnDDate_ptr);
            // Sanity check
            assert (lOnDSegmentDateList.size() == lNbOfSegments);
            stdair::CabinClassPairList_T::const_iterator itCCP = lCabinClassPairList.begin();
            stdair::SegmentDateList_T::const_iterator itSD = lOnDSegmentDateList.begin();
            // List of bid prices that will be used to easily compute displacement-ajusted yields.
            std::list<stdair::BidPrice_T> lBidPriceList;
            // The sum of bid prices that will be stored in the list above.
            stdair::BidPrice_T lTotalBidPrice = 0;
            // Retrieve the bid prices
            for (; itSD != lOnDSegmentDateList.end(); ++itCCP, ++itSD) {
              // Get the operating segment cabin (it holds the bid price information).
              const stdair::SegmentDate* lSegmentDate_ptr = *itSD;
              assert (lSegmentDate_ptr != NULL);
              // Get the operating airline code and check if it is the airline we are looking for.
              const stdair::SegmentDate* lOperatingSegmentDate_ptr =
                lSegmentDate_ptr->getOperatingSegmentDate ();
              if (lOperatingSegmentDate_ptr != NULL) {
                lSegmentDate_ptr = lOperatingSegmentDate_ptr;
              }
              const stdair::CabinCode_T lCabinCode = itCCP->first;
              const stdair::SegmentCabin* lSegmentCabin_ptr =
                stdair::BomManager::getObjectPtr<stdair::SegmentCabin> (*lSegmentDate_ptr,
                                                                        lCabinCode);
              assert (lSegmentCabin_ptr != NULL);
              stdair::BidPrice_T lBidPrice = 0;
              const stdair::LegCabinList_T lLegCabinList =
                stdair::BomManager::getList<stdair::LegCabin>(*lSegmentCabin_ptr);
              for (stdair::LegCabinList_T::const_iterator itLC = lLegCabinList.begin();
                   itLC != lLegCabinList.end(); ++itLC) {
                const stdair::LegCabin* lLegCabin_ptr = *itLC;
                assert (lLegCabin_ptr != NULL);
                lBidPrice += lLegCabin_ptr->getCurrentBidPrice();
              }
              lBidPriceList.push_back (lBidPrice);
              lTotalBidPrice += lBidPrice;
            }            
            
            
            itCCP = lCabinClassPairList.begin();
            itSD = lOnDSegmentDateList.begin();
            std::list<stdair::BidPrice_T>::const_iterator itBP = lBidPriceList.begin();
            for (; itSD != lOnDSegmentDateList.end(); ++itCCP, ++itSD, ++itBP) {
              stdair::BidPrice_T lBidPrice = *itBP;
              stdair::BidPrice_T lComplementaryBidPrice = lTotalBidPrice - lBidPrice;
              const stdair::SegmentDate* lSegmentDate_ptr = *itSD;
              assert (lSegmentDate_ptr != NULL);
              const stdair::SegmentDate* lOperatingSegmentDate_ptr =
                lSegmentDate_ptr->getOperatingSegmentDate ();
              // Only operated legs receive the demand information.
              if (lOperatingSegmentDate_ptr == NULL) {
                const stdair::CabinCode_T lCabinCode = itCCP->first;
                const stdair::ClassCode_T lClassCode = itCCP->second;
                const stdair::SegmentCabin* lSegmentCabin_ptr =
                  stdair::BomManager::getObjectPtr<stdair::SegmentCabin> (*lSegmentDate_ptr,
                                                                          lCabinCode);
                assert (lSegmentCabin_ptr != NULL);
                const stdair::LegCabinList_T lLegCabinList =
                  stdair::BomManager::getList<stdair::LegCabin> (*lSegmentCabin_ptr);
                assert (!lLegCabinList.empty());                
                // Determine the displacement-adjusted yield.
                // It is set to 100 (positive small value), if the computed value is negative.                
                const stdair::Yield_T& lDAYield =
                  std::max(100., lYieldDemandPair.first - lComplementaryBidPrice);
                
                                
                stdair::Yield_T lYield = lDAYield;
                // In order to be protected against important variations of partners' bid price,
                // the displacement adjusted yield is noy allowed to get out of a certain range.
                // This range is here chosen to be from 80% to 100% of the (static rule) prorated yield.
                /*
                const int lNbOfLegs = lLegCabinList.size();
                const stdair::Yield_T& lStaticProrationYield =
                  lDemandStruct.getYield()/(lNbOfLegs*lNbOfSegments); 
                if (lDAYield < 0.8*lStaticProrationYield){
                  lYield = 0.8*lStaticProrationYield;
                }
                if (lDAYield > lStaticProrationYield) {
                  lYield = lStaticProrationYield;
                }
                */
                const stdair::MeanStdDevPair_T& lMeanStdDevPair =
                  lYieldDemandPair.second;
                const stdair::MeanValue_T& lMeanValue = lMeanStdDevPair.first;
                const stdair::StdDevValue_T& lStdDevValue = lMeanStdDevPair.second;
                for (stdair::LegCabinList_T::const_iterator itLC = lLegCabinList.begin();
                     itLC != lLegCabinList.end(); ++itLC) {
                  stdair::LegCabin* lLegCabin_ptr = *itLC;
                  assert (lLegCabin_ptr != NULL);
                  lLegCabin_ptr->addDemandInformation (lYield, lMeanValue, lStdDevValue);
                }
              }
            }
          }
        }
      }
    }
  }

  // ///////////////////////////////////////////////////////////////////
  void RMOL_Service::projectOnDDemandOnLegCabinsUsingDYP(const stdair::DateTime_T& iRMEventTime) {

    if (_rmolServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The Rmol service "
                                                    "has not been initialised");
    }
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;
    
    // Retrieve the bom root
    stdair::STDAIR_Service& lSTDAIR_Service =
      lRMOL_ServiceContext.getSTDAIR_Service();
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getBomRoot();
    
    const stdair::InventoryList_T lInventoryList =
      stdair::BomManager::getList<stdair::Inventory> (lBomRoot);
    assert (!lInventoryList.empty());
    for (stdair::InventoryList_T::const_iterator itInv = lInventoryList.begin();
         itInv != lInventoryList.end(); ++itInv) {
      const stdair::Inventory* lInventory_ptr = *itInv;
      assert (lInventory_ptr != NULL);
      projectOnDDemandOnLegCabinsUsingDYP (iRMEventTime, *lInventory_ptr);
    }
  }

  // ///////////////////////////////////////////////////////////////////
  void RMOL_Service::projectOnDDemandOnLegCabinsUsingDYP(const stdair::DateTime_T& iRMEventTime,
                                                         const stdair::Inventory& iInventory) {
    
    const stdair::OnDDateList_T lOnDDateList =
      stdair::BomManager::getList<stdair::OnDDate> (iInventory);
    assert (!lOnDDateList.empty());
    for (stdair::OnDDateList_T::const_iterator itOD = lOnDDateList.begin();
         itOD != lOnDDateList.end(); ++itOD) {
      stdair::OnDDate* lOnDDate_ptr = *itOD;
      assert (lOnDDate_ptr != NULL);
      
      // Retrieve the date from the RM event
      const stdair::Date_T lDate = iRMEventTime.date();

      const stdair::Date_T& lDepartureDate = lOnDDate_ptr->getDate();
      stdair::DateOffset_T lDateOffset = lDepartureDate - lDate;
      stdair::DTD_T lDTD = short (lDateOffset.days());
      
      stdair::DCPList_T::const_iterator itDCP =
        std::find (stdair::DEFAULT_DCP_LIST.begin(), stdair::DEFAULT_DCP_LIST.end(), lDTD);
      // Check if the forecast for this O&D date needs to be projected.
      if (itDCP != stdair::DEFAULT_DCP_LIST.end()) {
        
        // Browse the demand info map.
        const stdair::StringDemandStructMap_T& lStringDemandStructMap =
          lOnDDate_ptr->getDemandInfoMap ();
        for (stdair::StringDemandStructMap_T::const_iterator itStrDS = lStringDemandStructMap.begin();
             itStrDS != lStringDemandStructMap.end(); ++itStrDS) {
          std::string lCabinClassPath = itStrDS->first;
          const stdair::YieldDemandPair_T& lYieldDemandPair = itStrDS->second;
          const stdair::CabinClassPairList_T& lCabinClassPairList =
            lOnDDate_ptr->getCabinClassPairList(lCabinClassPath);
          const stdair::NbOfSegments_T& lNbOfSegments = lOnDDate_ptr->getNbOfSegments();
          // Sanity check
          assert (lCabinClassPairList.size() == lNbOfSegments);
          
          //
          const stdair::SegmentDateList_T lOnDSegmentDateList =
              stdair::BomManager::getList<stdair::SegmentDate> (*lOnDDate_ptr);
          // Sanity check
          assert (lOnDSegmentDateList.size() == lNbOfSegments);
          stdair::CabinClassPairList_T::const_iterator itCCP = lCabinClassPairList.begin();
          stdair::SegmentDateList_T::const_iterator itSD = lOnDSegmentDateList.begin();
          // The sum of bid prices of all cabins.
          stdair::BidPrice_T lTotalBidPrice = 0;
          for (; itSD != lOnDSegmentDateList.end(); ++itCCP, ++itSD) {
            // Get the operating segment cabin (it holds the bid price information).
            const stdair::SegmentDate* lSegmentDate_ptr = *itSD;
            assert (lSegmentDate_ptr != NULL);
            // Get the operating airline code and check if it is the airline we are looking for.
            const stdair::SegmentDate* lOperatingSegmentDate_ptr =
              lSegmentDate_ptr->getOperatingSegmentDate ();
            if (lOperatingSegmentDate_ptr != NULL) {
              lSegmentDate_ptr = lOperatingSegmentDate_ptr;
            }
            const stdair::CabinCode_T lCabinCode = itCCP->first;
            const stdair::SegmentCabin* lSegmentCabin_ptr =
              stdair::BomManager::getObjectPtr<stdair::SegmentCabin> (*lSegmentDate_ptr,
                                                                      lCabinCode);
            assert (lSegmentCabin_ptr != NULL);
            const stdair::LegCabinList_T lLegCabinList =
              stdair::BomManager::getList<stdair::LegCabin>(*lSegmentCabin_ptr);
            for (stdair::LegCabinList_T::const_iterator itLC = lLegCabinList.begin();
                 itLC != lLegCabinList.end(); ++itLC) {
              const stdair::LegCabin* lLegCabin_ptr = *itLC;
              assert (lLegCabin_ptr != NULL);
              lTotalBidPrice += lLegCabin_ptr->getCurrentBidPrice();
            }
          }            
          
          
          itCCP = lCabinClassPairList.begin();
          itSD = lOnDSegmentDateList.begin();
          for (; itSD != lOnDSegmentDateList.end(); ++itCCP, ++itSD) {
            const stdair::SegmentDate* lSegmentDate_ptr = *itSD;
            assert (lSegmentDate_ptr != NULL);
            const stdair::SegmentDate* lOperatingSegmentDate_ptr =
              lSegmentDate_ptr->getOperatingSegmentDate ();
            // Only operated legs receive the demand information.
            if (lOperatingSegmentDate_ptr == NULL) {
              const stdair::CabinCode_T lCabinCode = itCCP->first;
              const stdair::ClassCode_T lClassCode = itCCP->second;
              const stdair::SegmentCabin* lSegmentCabin_ptr =
                stdair::BomManager::getObjectPtr<stdair::SegmentCabin> (*lSegmentDate_ptr,
                                                                        lCabinCode);
              assert (lSegmentCabin_ptr != NULL);
              const stdair::LegCabinList_T lLegCabinList =
                stdair::BomManager::getList<stdair::LegCabin> (*lSegmentCabin_ptr);
              assert (!lLegCabinList.empty());
              const stdair::Yield_T& lYield = lYieldDemandPair.first;            
              const stdair::MeanStdDevPair_T& lMeanStdDevPair =
                lYieldDemandPair.second;
              const stdair::MeanValue_T& lMeanValue = lMeanStdDevPair.first;
              const stdair::StdDevValue_T& lStdDevValue = lMeanStdDevPair.second;
              for (stdair::LegCabinList_T::const_iterator itLC = lLegCabinList.begin();
                   itLC != lLegCabinList.end(); ++itLC) {
                stdair::LegCabin* lLegCabin_ptr = *itLC;
                assert (lLegCabin_ptr != NULL);
                const stdair::BidPrice_T& lBidPrice = lLegCabin_ptr->getCurrentBidPrice();
                const stdair::RealNumber_T lDynamicYieldProrationFactor = lBidPrice / lTotalBidPrice;
                const stdair::Yield_T lProratedYield = lDynamicYieldProrationFactor*lYield;
                lLegCabin_ptr->addDemandInformation (lProratedYield, lMeanValue, lStdDevValue);
                
                // STDAIR_LOG_DEBUG ("Addding demand information to leg-cabin " << lLegCabin_ptr->getFullerKey()
                //                   << " Total yield " << lYield << " Proration factor "
                //                   << lDynamicYieldProrationFactor << " Prorated yield " << lProratedYield
                //                   << " Mean demand " << lMeanValue << " StdDev " << lStdDevValue);
              }
            }
          }
        }
      }
    }
  }

  // ///////////////////////////////////////////////////////////////////
  void RMOL_Service::optimiseOnDUsingRMCooperation (const stdair::DateTime_T& iRMEventTime) {

    if (_rmolServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The Rmol service "
                                                    "has not been initialised");
    }
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;

    // Retrieve the bom root
    stdair::STDAIR_Service& lSTDAIR_Service =
      lRMOL_ServiceContext.getSTDAIR_Service();
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getBomRoot();

    // Retrieve the date from the RM event
    const stdair::Date_T lDate = iRMEventTime.date();

    // Browse the list of inventories and optimise within each one independently.
    const stdair::InventoryList_T& lInvList =
      stdair::BomManager::getList<stdair::Inventory> (lBomRoot);
    for (stdair::InventoryList_T::const_iterator itInv = lInvList.begin();
         itInv != lInvList.end(); ++itInv) {
      stdair::Inventory* lCurrentInv_ptr = *itInv;
      assert (lCurrentInv_ptr != NULL);
      
      double lMaxBPVariation = 1.0;
      short lIterationCounter = 0;
      // Iterate until the variation is under the wanted level or the maximal number of iterations is reached.
      while (lMaxBPVariation > 0.01 && lIterationCounter < 10) {
        lMaxBPVariation = 0.0;
        lIterationCounter++;
        const stdair::FlightDateList_T& lFlightDateList =
          stdair::BomManager::getList<stdair::FlightDate> (*lCurrentInv_ptr);
        for (stdair::FlightDateList_T::const_iterator itFlightDate =
               lFlightDateList.begin();
             itFlightDate != lFlightDateList.end(); ++itFlightDate) {
          stdair::FlightDate* lCurrentFlightDate_ptr = *itFlightDate;
          assert (lCurrentFlightDate_ptr != NULL);
          
          const stdair::Date_T& lCurrentDepartureDate = lCurrentFlightDate_ptr->getDepartureDate();
          stdair::DateOffset_T lDateOffset = lCurrentDepartureDate - lDate;
          stdair::DTD_T lDTD = short (lDateOffset.days());
          
          stdair::DCPList_T::const_iterator itDCP =
            std::find (stdair::DEFAULT_DCP_LIST.begin(), stdair::DEFAULT_DCP_LIST.end(), lDTD);
          // Check if the optimisation is needed.
          if (itDCP != stdair::DEFAULT_DCP_LIST.end()) {
            const double lBPVariation = Optimiser::optimiseUsingOnDForecast (*lCurrentFlightDate_ptr);
            lMaxBPVariation = std::max(lMaxBPVariation, lBPVariation);
          }
        }
        // Update the prorated yields for the current inventory.
        resetDemandInformation (iRMEventTime, *lCurrentInv_ptr);
        projectOnDDemandOnLegCabinsUsingDYP (iRMEventTime, *lCurrentInv_ptr);
      }
    }
  }

   
  // ///////////////////////////////////////////////////////////////////
  void RMOL_Service::optimiseOnDUsingAdvancedRMCooperation (const stdair::DateTime_T& iRMEventTime) {

    if (_rmolServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The Rmol service "
                                                    "has not been initialised");
    }
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;

    // Retrieve the bom root
    stdair::STDAIR_Service& lSTDAIR_Service =
      lRMOL_ServiceContext.getSTDAIR_Service();
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getBomRoot();
    
    // Retrieve the date from the RM event
    const stdair::Date_T lDate = iRMEventTime.date();

    double lMaxBPVariation = 1.0;
    short lIterationCounter = 0;
    // Iterate until the variation is under the wanted level or the maximal number of iterations is reached.
    // Every iteration corresponds to the optimisation of the whole network. Bid prices are communicated
    // between partners at the end of each iteration.
    while (lMaxBPVariation > 0.01 && lIterationCounter < 50) {
      lMaxBPVariation = 0.0;
      lIterationCounter++;

      const stdair::InventoryList_T& lInvList =
        stdair::BomManager::getList<stdair::Inventory> (lBomRoot);
      for (stdair::InventoryList_T::const_iterator itInv = lInvList.begin();
           itInv != lInvList.end(); ++itInv) {
        stdair::Inventory* lCurrentInv_ptr = *itInv;
        assert (lCurrentInv_ptr != NULL);
        const stdair::FlightDateList_T& lFlightDateList =
          stdair::BomManager::getList<stdair::FlightDate> (*lCurrentInv_ptr);
        for (stdair::FlightDateList_T::const_iterator itFlightDate =
               lFlightDateList.begin();
             itFlightDate != lFlightDateList.end(); ++itFlightDate) {
          stdair::FlightDate* lCurrentFlightDate_ptr = *itFlightDate;
          assert (lCurrentFlightDate_ptr != NULL);
          
          const stdair::Date_T& lCurrentDepartureDate = lCurrentFlightDate_ptr->getDepartureDate();
          stdair::DateOffset_T lDateOffset = lCurrentDepartureDate - lDate;
          stdair::DTD_T lDTD = short (lDateOffset.days());
          
          stdair::DCPList_T::const_iterator itDCP =
            std::find (stdair::DEFAULT_DCP_LIST.begin(), stdair::DEFAULT_DCP_LIST.end(), lDTD);
          if (itDCP != stdair::DEFAULT_DCP_LIST.end()) {
            const double lBPVariation = Optimiser::optimiseUsingOnDForecast (*lCurrentFlightDate_ptr);
            lMaxBPVariation = std::max(lMaxBPVariation, lBPVariation);
          }
        }
      }
      // At the end of each iteration, communicate bid prices and compute displacement adjusted yields.
      updateBidPrice (iRMEventTime);
      resetDemandInformation (iRMEventTime);
      projectOnDDemandOnLegCabinsUsingDYP (iRMEventTime);
    }    
  }

}
