// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// Boost
#include <boost/make_shared.hpp>
// StdAir
#include <stdair/basic/BasChronometer.hpp>
#include <stdair/basic/BasFileMgr.hpp>
#include <stdair/bom/BomManager.hpp> 
#include <stdair/service/Logger.hpp>
#include <stdair/STDAIR_Service.hpp>
#include <stdair/bom/TravelSolutionStruct.hpp>
// Airrac
#include <airrac/basic/BasConst_AIRRAC_Service.hpp>
#include <airrac/factory/FacAirracServiceContext.hpp>
#include <airrac/command/YieldParser.hpp>
#include <airrac/command/YieldManager.hpp>
#include <airrac/service/AIRRAC_ServiceContext.hpp>
#include <airrac/AIRRAC_Service.hpp>

namespace AIRRAC {

  // //////////////////////////////////////////////////////////////////////
  AIRRAC_Service::AIRRAC_Service ()
    : _airracServiceContext (NULL) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  AIRRAC_Service::AIRRAC_Service (const AIRRAC_Service& iService) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  AIRRAC_Service::
  AIRRAC_Service (stdair::STDAIR_ServicePtr_T ioSTDAIR_ServicePtr,
                  const stdair::Filename_T& iYieldInputFilename)
    : _airracServiceContext (NULL) {

    // Initialise the service context
    initServiceContext ();
    
    // Retrieve the Airrac service context
    assert (_airracServiceContext != NULL);
    AIRRAC_ServiceContext& lAIRRAC_ServiceContext =
      *_airracServiceContext;
    
    // Store the STDAIR service object within the (AIRRAC) service context
    lAIRRAC_ServiceContext.setSTDAIR_Service (ioSTDAIR_ServicePtr);
    
    // Initialise the context
    init (iYieldInputFilename);
  }

  // ////////////////////////////////////////////////////////////////////
  AIRRAC_Service::
  AIRRAC_Service (const stdair::BasLogParams& iLogParams,
                  const stdair::BasDBParams& iDBParams,
                  const stdair::Filename_T& iYieldInputFilename) 
    : _airracServiceContext (NULL) {
    
    // Initialise the service context
    initServiceContext ();
    
    // Initialise the STDAIR service handler
    initStdAirService (iLogParams, iDBParams);
    
    // Initialise the (remaining of the) context
    init (iYieldInputFilename);
  }

  // ////////////////////////////////////////////////////////////////////
  AIRRAC_Service::
  AIRRAC_Service (const stdair::BasLogParams& iLogParams,
                  const stdair::Filename_T& iYieldInputFilename) 
    : _airracServiceContext (NULL) {
    
    // Initialise the service context
    initServiceContext ();
    
    // Initialise the STDAIR service handler
    initStdAirService (iLogParams);
    
    // Initialise the (remaining of the) context
    init (iYieldInputFilename);
  }


  // //////////////////////////////////////////////////////////////////////
  AIRRAC_Service::~AIRRAC_Service () {
    // Delete/Clean all the objects from memory
    finalise();
  }
  
  // //////////////////////////////////////////////////////////////////////
  void AIRRAC_Service::finalise () {
    assert (_airracServiceContext != NULL);
  }

  // //////////////////////////////////////////////////////////////////////
  void AIRRAC_Service::initServiceContext () {
    // Initialise the service context
    AIRRAC_ServiceContext& lAIRRAC_ServiceContext = 
      FacAirracServiceContext::instance().create ();
    _airracServiceContext = &lAIRRAC_ServiceContext;
  }

  // //////////////////////////////////////////////////////////////////////
  void AIRRAC_Service::
  initStdAirService (const stdair::BasLogParams& iLogParams,
                     const stdair::BasDBParams& iDBParams) {

    // Retrieve the Airrac service context
    assert (_airracServiceContext != NULL);
    AIRRAC_ServiceContext& lAIRRAC_ServiceContext =
      *_airracServiceContext;
    
    // Initialise the STDAIR service handler
    // Note that the track on the object memory is kept thanks to the Boost
    // Smart Pointers component.
    stdair::STDAIR_ServicePtr_T lSTDAIR_Service_ptr = 
      boost::make_shared<stdair::STDAIR_Service> (iLogParams, iDBParams);
    assert (lSTDAIR_Service_ptr != NULL);
    
    // Store the STDAIR service object within the (AIRRAC) service context
    lAIRRAC_ServiceContext.setSTDAIR_Service (lSTDAIR_Service_ptr);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void AIRRAC_Service::
  initStdAirService (const stdair::BasLogParams& iLogParams) {

    // Retrieve the Airrac service context
    assert (_airracServiceContext != NULL);
    AIRRAC_ServiceContext& lAIRRAC_ServiceContext =
      *_airracServiceContext;
    
    // Initialise the STDAIR service handler
    // Note that the track on the object memory is kept thanks to the Boost
    // Smart Pointers component.
    stdair::STDAIR_ServicePtr_T lSTDAIR_Service_ptr = 
      boost::make_shared<stdair::STDAIR_Service> (iLogParams);
    assert (lSTDAIR_Service_ptr != NULL);

    // Store the STDAIR service object within the (AIRRAC) service context
    lAIRRAC_ServiceContext.setSTDAIR_Service (lSTDAIR_Service_ptr);
  }
  
  // ////////////////////////////////////////////////////////////////////
  void AIRRAC_Service::
  init (const stdair::Filename_T& iYieldInputFilename) {

    // Check that the file path given as input corresponds to an actual file
    const bool doesExistAndIsReadable =
      stdair::BasFileMgr::doesExistAndIsReadable (iYieldInputFilename);
    if (doesExistAndIsReadable == false) {
      STDAIR_LOG_ERROR ("The yield input file, '" << iYieldInputFilename
                        << "', can not be retrieved on the file-system");
      throw YieldInputFileNotFoundException ("The demand file '"
                                             + iYieldInputFilename
                                             + "' does not exist or can not be read");
    }

    // Retrieve the Airrac service context
    assert (_airracServiceContext != NULL);
    AIRRAC_ServiceContext& lAIRRAC_ServiceContext =
      *_airracServiceContext;

    // Retrieve the StdAir service context
    stdair::STDAIR_ServicePtr_T lSTDAIR_Service_ptr =
      lAIRRAC_ServiceContext.getSTDAIR_Service();
    assert (lSTDAIR_Service_ptr != NULL);
    
    // Get the root of the BOM tree, on which all of the other BOM objects
    // will be attached
    stdair::BomRoot& lBomRoot = lSTDAIR_Service_ptr->getBomRoot();

    // Initialise the yield parser
    YieldParser::generateYieldStore  (iYieldInputFilename, lBomRoot);
  } 

  // ////////////////////////////////////////////////////////////////////
  void AIRRAC_Service::
  calculateYields (stdair::TravelSolutionList_T& ioTravelSolutionList) {
    
    // Retrieve the Airrac service context
    assert (_airracServiceContext != NULL);
    AIRRAC_ServiceContext& lAIRRAC_ServiceContext =
      *_airracServiceContext;

    // Retrieve the StdAir service context
    stdair::STDAIR_ServicePtr_T lSTDAIR_Service_ptr =
      lAIRRAC_ServiceContext.getSTDAIR_Service();
    assert (lSTDAIR_Service_ptr != NULL);
    
    // Get the root of the BOM tree, on which all of the other BOM objects
    // will be attached
    stdair::BomRoot& lBomRoot = lSTDAIR_Service_ptr->getBomRoot();

    // Initialise the yield parser 
    if (!ioTravelSolutionList.empty()) {
      for (stdair::TravelSolutionList_T::iterator itTravelSolution =
	     ioTravelSolutionList.begin();
	   itTravelSolution != ioTravelSolutionList.end(); ++itTravelSolution) {
	YieldManager::calculateYield (*itTravelSolution, lBomRoot);
      }
    }
  }
  
}
