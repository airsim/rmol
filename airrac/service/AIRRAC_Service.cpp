// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// Boost
#include <boost/make_shared.hpp>
// StdAir
#include <stdair/basic/BasChronometer.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/STDAIR_Service.hpp>
// Airrac
#include <airrac/basic/BasConst_AIRRAC_Service.hpp>
#include <airrac/factory/FacAirracServiceContext.hpp>
#include <airrac/command/YieldParser.hpp>
#include <airrac/command/YieldManager.hpp>
#include <airrac/service/AIRRAC_ServiceContext.hpp>
#include <airrac/AIRRAC_Service.hpp>

namespace AIRRAC {

  // //////////////////////////////////////////////////////////////////////
  AIRRAC_Service::AIRRAC_Service() : _airracServiceContext (NULL) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  AIRRAC_Service::AIRRAC_Service (const AIRRAC_Service& iService) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  AIRRAC_Service::AIRRAC_Service (const stdair::BasLogParams& iLogParams)
    : _airracServiceContext (NULL) {
    
    // Initialise the STDAIR service handler
    stdair::STDAIR_ServicePtr_T lSTDAIR_Service_ptr =
      initStdAirService (iLogParams);
    
    // Initialise the service context
    initServiceContext();

    // Add the StdAir service context to the AIRRAC service context
    // \note AIRRAC owns the STDAIR service resources here.
    const bool ownStdairService = true;
    addStdAirService (lSTDAIR_Service_ptr, ownStdairService);
    
    // Initialise the (remaining of the) context
    initAirracService();
  }

  // ////////////////////////////////////////////////////////////////////
  AIRRAC_Service::AIRRAC_Service (const stdair::BasLogParams& iLogParams,
                                  const stdair::BasDBParams& iDBParams)
    : _airracServiceContext (NULL) {
    
    // Initialise the STDAIR service handler
    stdair::STDAIR_ServicePtr_T lSTDAIR_Service_ptr =
      initStdAirService (iLogParams, iDBParams);
    
    // Initialise the service context
    initServiceContext();

    // Add the StdAir service context to the AIRRAC service context
    // \note AIRRAC owns the STDAIR service resources here.
    const bool ownStdairService = true;
    addStdAirService (lSTDAIR_Service_ptr, ownStdairService);
    
    // Initialise the (remaining of the) context
    initAirracService();
  }

  // ////////////////////////////////////////////////////////////////////
  AIRRAC_Service::
  AIRRAC_Service (stdair::STDAIR_ServicePtr_T ioSTDAIR_Service_ptr)
    : _airracServiceContext (NULL) {

    // Initialise the service context
    initServiceContext();

    // Store the STDAIR service object within the (AIRRAC) service context
    // \note Airrac does not own the STDAIR service resources here.
    const bool doesNotOwnStdairService = false;
    addStdAirService (ioSTDAIR_Service_ptr, doesNotOwnStdairService);
    
    // Initialise the context
    initAirracService();
  }

  // ////////////////////////////////////////////////////////////////////
  AIRRAC_Service::
  AIRRAC_Service (const stdair::BasLogParams& iLogParams,
                  const stdair::Filename_T& iYieldInputFilename) 
    : _airracServiceContext (NULL) {

    // Initialise the STDAIR service handler
    stdair::STDAIR_ServicePtr_T lSTDAIR_Service_ptr =
      initStdAirService (iLogParams);
    
    // Initialise the service context
    initServiceContext();

    // Add the StdAir service context to the AIRRAC service context
    // \note AIRRAC owns the STDAIR service resources here.
    const bool ownStdairService = true;
    addStdAirService (lSTDAIR_Service_ptr, ownStdairService);
    
    // Initialise the (remaining of the) context
    initAirracService (iYieldInputFilename);
  }

  // ////////////////////////////////////////////////////////////////////
  AIRRAC_Service::
  AIRRAC_Service (const stdair::BasLogParams& iLogParams,
                  const stdair::BasDBParams& iDBParams,
                  const stdair::Filename_T& iYieldInputFilename) 
    : _airracServiceContext (NULL) {

    // Initialise the STDAIR service handler
    stdair::STDAIR_ServicePtr_T lSTDAIR_Service_ptr =
      initStdAirService (iLogParams, iDBParams);
    
    // Initialise the service context
    initServiceContext();

    // Add the StdAir service context to the AIRRAC service context
    // \note AIRRAC owns the STDAIR service resources here.
    const bool ownStdairService = true;
    addStdAirService (lSTDAIR_Service_ptr, ownStdairService);

    // Initialise the (remaining of the) context
    initAirracService (iYieldInputFilename);
  }

  // ////////////////////////////////////////////////////////////////////
  AIRRAC_Service::
  AIRRAC_Service (stdair::STDAIR_ServicePtr_T ioSTDAIR_Service_ptr,
                  const stdair::Filename_T& iYieldInputFilename)
    : _airracServiceContext (NULL) {

    // Initialise the service context
    initServiceContext();

    // Store the STDAIR service object within the (AIRRAC) service context
    // \note Airrac does not own the STDAIR service resources here.
    const bool doesNotOwnStdairService = false;
    addStdAirService (ioSTDAIR_Service_ptr, doesNotOwnStdairService);
    
    // Initialise the context
    initAirracService (iYieldInputFilename);
  }

  // //////////////////////////////////////////////////////////////////////
  AIRRAC_Service::~AIRRAC_Service() {
    // Delete/Clean all the objects from memory
    finalise();
  }
  
  // //////////////////////////////////////////////////////////////////////
  void AIRRAC_Service::finalise() {
    assert (_airracServiceContext != NULL);
    // Reset the (Boost.)Smart pointer pointing on the STDAIR_Service object.
    _airracServiceContext->reset();
  }

  // //////////////////////////////////////////////////////////////////////
  void AIRRAC_Service::initServiceContext() {
    // Initialise the service context
    AIRRAC_ServiceContext& lAIRRAC_ServiceContext = 
      FacAirracServiceContext::instance().create();
    _airracServiceContext = &lAIRRAC_ServiceContext;
  }

  // //////////////////////////////////////////////////////////////////////
  stdair::STDAIR_ServicePtr_T AIRRAC_Service::
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
  
  // //////////////////////////////////////////////////////////////////////
  stdair::STDAIR_ServicePtr_T AIRRAC_Service::
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
  void AIRRAC_Service::
  addStdAirService (stdair::STDAIR_ServicePtr_T ioSTDAIR_Service_ptr,
                    const bool iOwnStdairService) {

    // Retrieve the Airrac service context
    assert (_airracServiceContext != NULL);
    AIRRAC_ServiceContext& lAIRRAC_ServiceContext = *_airracServiceContext;

    // Store the STDAIR service object within the (AIRRAC) service context
    lAIRRAC_ServiceContext.setSTDAIR_Service (ioSTDAIR_Service_ptr,
                                              iOwnStdairService);
  }
  
  // ////////////////////////////////////////////////////////////////////
  void AIRRAC_Service::initAirracService() {
    // Do nothing at this stage. A sample BOM tree may be built by
    // calling the buildSampleBom() method
  }
  
  // ////////////////////////////////////////////////////////////////////
  void AIRRAC_Service::
  initAirracService  (const stdair::Filename_T& iYieldInputFilename) {

    // Retrieve the AirRAC service context
    assert (_airracServiceContext != NULL);
    AIRRAC_ServiceContext& lAIRRAC_ServiceContext = *_airracServiceContext;

    // Retrieve the StdAir service context
    stdair::STDAIR_Service& lSTDAIR_Service =
      lAIRRAC_ServiceContext.getSTDAIR_Service();
    
    // Get the root of the BOM tree, on which all of the other BOM objects
    // will be attached
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getBomRoot();

    // Initialise the yield parser
    YieldParser::generateYieldStore  (iYieldInputFilename, lBomRoot);

    // Update the default yields to the booking classes.
    YieldManager::updateYields (lBomRoot);
  }

  // ////////////////////////////////////////////////////////////////////
  void AIRRAC_Service::
  parseAndLoad (const stdair::Filename_T& iYieldInputFilename) {
    initAirracService (iYieldInputFilename);
  }

  // ////////////////////////////////////////////////////////////////////
  void AIRRAC_Service::buildSampleBom() {

    // TODO: implement this within StdAir (where Yield objects should
    // be created)

    // Retrieve the AirRAC service context
    if (_airracServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The AirRAC service has not"
                                                    " been initialised");
    }
    assert (_airracServiceContext != NULL);

    // Retrieve the AirRAC service context
    AIRRAC_ServiceContext& lAIRRAC_ServiceContext = *_airracServiceContext;

    // Retrieve the STDAIR service object from the (AirRAC) service context
    stdair::STDAIR_Service& lSTDAIR_Service =
      lAIRRAC_ServiceContext.getSTDAIR_Service();

    // Delegate the BOM building to the dedicated service
    lSTDAIR_Service.buildSampleBomForAirRAC();
  }

  // //////////////////////////////////////////////////////////////////////
  void AIRRAC_Service::
  buildSampleTravelSolutions(stdair::TravelSolutionList_T& ioTravelSolutionList){

    // Retrieve the AIRRAC service context
    if (_airracServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The AirRAC service has not "
                                                    "been initialised");
    }
    assert (_airracServiceContext != NULL);

    AIRRAC_ServiceContext& lAIRRAC_ServiceContext = *_airracServiceContext;
  
    // Retrieve the STDAIR service object from the (AirRAC) service context
    stdair::STDAIR_Service& lSTDAIR_Service =
      lAIRRAC_ServiceContext.getSTDAIR_Service();

    // Delegate the BOM building to the dedicated service
    lSTDAIR_Service.buildSampleTravelSolutions (ioTravelSolutionList);
  }

  // //////////////////////////////////////////////////////////////////////
  std::string AIRRAC_Service::csvDisplay() const {

    // Retrieve the AirRAC service context
    if (_airracServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The AirRAC service has not"
                                                    " been initialised");
    }
    assert (_airracServiceContext != NULL);

    // Retrieve the AirRAC service context
    AIRRAC_ServiceContext& lAIRRAC_ServiceContext = *_airracServiceContext;
  
    // Retrieve the STDAIR service object from the (AirRAC) service context
    stdair::STDAIR_Service& lSTDAIR_Service =
      lAIRRAC_ServiceContext.getSTDAIR_Service();

    // Delegate the BOM building to the dedicated service
    return lSTDAIR_Service.csvDisplay();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string AIRRAC_Service::
  csvDisplay (const stdair::TravelSolutionList_T& ioTravelSolutionList) const {

    // Retrieve the AirRAC service context
    if (_airracServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The AirRAC service has not"
                                                    " been initialised");
    }
    assert (_airracServiceContext != NULL);

    // Retrieve the AirRAC service context
    AIRRAC_ServiceContext& lAIRRAC_ServiceContext = *_airracServiceContext;
  
    // Retrieve the STDAIR service object from the (AirRAC) service context
    stdair::STDAIR_Service& lSTDAIR_Service =
      lAIRRAC_ServiceContext.getSTDAIR_Service();

    // Delegate the BOM building to the dedicated service
    return lSTDAIR_Service.csvDisplay (ioTravelSolutionList);
  }

  // ////////////////////////////////////////////////////////////////////
  void AIRRAC_Service::
  calculateYields (stdair::TravelSolutionList_T& ioTravelSolutionList) {
    
    // Retrieve the Airrac service context
    if (_airracServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The AirRAC service has not"
                                                    " been initialised");
    }
    assert (_airracServiceContext != NULL);
    AIRRAC_ServiceContext& lAIRRAC_ServiceContext = *_airracServiceContext;

    // Retrieve the StdAir service context
    stdair::STDAIR_Service& lSTDAIR_Service =
      lAIRRAC_ServiceContext.getSTDAIR_Service();
    
    // Get the root of the BOM tree, on which all of the other BOM objects
    // will be attached
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getBomRoot();

    // Delegate the booking to the dedicated command: set the yields
    // for each travel solution of the given list
    stdair::BasChronometer lYieldChronometer;
    lYieldChronometer.start();
    YieldManager::calculateYield (ioTravelSolutionList, lBomRoot);
    const double lYieldMeasure = lYieldChronometer.elapsed();

    // DEBUG
    STDAIR_LOG_DEBUG ("Yield calculation: " << lYieldMeasure << " - "
                      << lAIRRAC_ServiceContext.display());
  }
  
}
