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
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/command/CmdBomManager.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/STDAIR_Service.hpp>
// RMOL
#include <rmol/basic/BasConst_RMOL_Service.hpp>
#include <rmol/factory/FacRmolServiceContext.hpp>
#include <rmol/command/InventoryParser.hpp>
#include <rmol/command/Optimiser.hpp>
#include <rmol/command/Forecaster.hpp>
#include <rmol/service/RMOL_ServiceContext.hpp>
#include <rmol/RMOL_Service.hpp>

namespace RMOL {

  // ////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service() : _rmolServiceContext (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service (const RMOL_Service& iService) :
    _rmolServiceContext (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service (const stdair::BasLogParams& iLogParams,
                              const stdair::BasDBParams& iDBParams,
                              const stdair::CabinCapacity_T& iCabinCapacity,
                              const stdair::Filename_T& iInputFileName) :
    _rmolServiceContext (NULL) {

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
    initRmolService (iCabinCapacity, iInputFileName);
  }

  // ////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service (const stdair::BasLogParams& iLogParams,
                              const stdair::CabinCapacity_T& iCabinCapacity,
                              const stdair::Filename_T& iInputFileName) :
    _rmolServiceContext (NULL) {

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
    initRmolService (iCabinCapacity, iInputFileName);
  }

  // ////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service (const stdair::BasLogParams& iLogParams,
                              const stdair::BasDBParams& iDBParams,
                              const stdair::CabinCapacity_T& iCabinCapacity) :
    _rmolServiceContext (NULL) {

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
    initRmolService (iCabinCapacity);
  }

  // ////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service (const stdair::BasLogParams& iLogParams,
                              const stdair::CabinCapacity_T& iCabinCapacity) :
    _rmolServiceContext (NULL) {

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
    initRmolService (iCabinCapacity);
  }

  // ////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service (stdair::STDAIR_ServicePtr_T ioSTDAIRServicePtr,
                              const stdair::CabinCapacity_T& iCabinCapacity,
                              const stdair::Filename_T& iInputFileName)
    : _rmolServiceContext (NULL) {
    
    // Initialise the context
    initServiceContext();
    
    // Add the StdAir service context to the RMOL service context.
    // \note RMOL does not own the STDAIR service resources here.
    const bool doesNotOwnStdairService = false;
    addStdAirService (ioSTDAIRServicePtr, doesNotOwnStdairService);

    // Initialise the (remaining of the) context
    initRmolService (iCabinCapacity, iInputFileName);
  }

  // ////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service (stdair::STDAIR_ServicePtr_T ioSTDAIRServicePtr)
    : _rmolServiceContext (NULL) {
    
    // Initialise the context
    initServiceContext();
    
    // Add the StdAir service context to the RMOL service context.
    // \note RMOL does not own the STDAIR service resources here.
    const bool doesNotOwnStdairService = false;
    addStdAirService (ioSTDAIRServicePtr, doesNotOwnStdairService);
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

  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::initRmolService() {
    // Do nothing at this stage. A sample BOM tree may be built by
    // calling the buildSampleBom() method
  }

  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  initRmolService (const stdair::CabinCapacity_T& iCabinCapacity) {
    // Build a dummy inventory with a leg-cabin which has the given capacity.
    // The StdAir-held BOM tree is altered correspondingly.
    buildSampleBom (iCabinCapacity);
  }

  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  initRmolService (const stdair::CabinCapacity_T& iCabinCapacity,
                   const stdair::Filename_T& iInputFileName) {

    // Build a dummy inventory with a leg-cabin which has the given capacity.
    // The StdAir-held BOM tree is altered correspondingly.
    buildSampleBom (iCabinCapacity);

    // Retrieve the BOM tree root
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;
    stdair::STDAIR_Service& lSTDAIR_Service =
      lRMOL_ServiceContext.getSTDAIR_Service();
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getBomRoot();

    // Complete the BOM tree with the optimisation problem specification
    InventoryParser::parseInputFileAndBuildBom (iInputFileName, lBomRoot);
  }
  
  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  buildSampleBom (const stdair::CabinCapacity_T& iCabinCapacity) {

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
     *    SimFQT)
     *
     * \note: Currently, no more things to do by RMOL at that stage,
     *        as there is no child
     */
  }

  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::optimalOptimisationByMCIntegration (const int K) {
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;

    // Retrieve the StdAir service
    stdair::STDAIR_Service& lSTDAIR_Service =
      lRMOL_ServiceContext.getSTDAIR_Service();
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getBomRoot();

    //
    stdair::LegCabin& lLegCabin = InventoryParser::getSampleLegCabin (lBomRoot);

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
    unsigned int size = lBidPriceVector.size();
    
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
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getBomRoot();

    //
    stdair::LegCabin& lLegCabin = InventoryParser::getSampleLegCabin (lBomRoot);

    stdair::BasChronometer lOptimisationChronometer;
    lOptimisationChronometer.start();
    
    Optimiser::heuristicOptimisationByEmsr (lLegCabin);
    
    const double lOptimisationMeasure = lOptimisationChronometer.elapsed();
    // DEBUG
    STDAIR_LOG_DEBUG ("Optimisation EMSR performed in "
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
  void RMOL_Service::heuristicOptimisationByEmsrA() {
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;

    // Retrieve the StdAir service
    stdair::STDAIR_Service& lSTDAIR_Service =
      lRMOL_ServiceContext.getSTDAIR_Service();
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getBomRoot();

    //
    stdair::LegCabin& lLegCabin = InventoryParser::getSampleLegCabin (lBomRoot);

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
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getBomRoot();

    //
    stdair::LegCabin& lLegCabin = InventoryParser::getSampleLegCabin (lBomRoot);

    Optimiser::heuristicOptimisationByEmsrB (lLegCabin);

    // DEBUG
    STDAIR_LOG_DEBUG ("Result: " << lLegCabin.displayVirtualClassList());
  }

  // ////////////////////////////////////////////////////////////////////
  bool RMOL_Service::optimise (stdair::FlightDate& ioFlightDate,
                               const stdair::DateTime_T& iRMEventTime,
                               const stdair::ForecastingMethod::EN_ForecastingMethod& iForecastingMethod) {    
    // Call the functions in the forecaster and the optimiser.
    // DEBUG
    STDAIR_LOG_DEBUG ("Forecast");
    bool isForecasted = false;
    switch (iForecastingMethod) {
    case stdair::ForecastingMethod::ADD_PK: isForecasted = Forecaster::forecastUsingAdditivePickUp (ioFlightDate, iRMEventTime); break;
    case stdair::ForecastingMethod::MUL_PK: isForecasted = Forecaster::forecastUsingMultiplicativePickUp (ioFlightDate, iRMEventTime); break;
    default: assert (false); break;
    }
                                 
    STDAIR_LOG_DEBUG ("Forecast successful: " << isForecasted);
    if (isForecasted == true) {
      STDAIR_LOG_DEBUG ("Optimise");
      Optimiser::optimise (ioFlightDate);
      return true;
    } else {
      return false;
    }
  }
}
