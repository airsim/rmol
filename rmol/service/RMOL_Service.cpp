// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/basic/BasFileMgr.hpp>
#include <stdair/basic/BasChronometer.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/command/CmdBomManager.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/STDAIR_Service.hpp>
// RMOL
#include <rmol/basic/BasConst_RMOL_Service.hpp>
#include <rmol/factory/FacSupervisor.hpp>
#include <rmol/factory/FacRmolServiceContext.hpp>
#include <rmol/command/Optimiser.hpp>
#include <rmol/command/Unconstrainer.hpp>
#include <rmol/command/Forecaster.hpp>
#include <rmol/service/RMOL_ServiceContext.hpp>
#include <rmol/RMOL_Service.hpp>

namespace RMOL {

  // ////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service () : _rmolServiceContext (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service (const RMOL_Service& iService) :
    _rmolServiceContext (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service (const stdair::BasLogParams& iLogParams,
                              const stdair::CabinCapacity_T& iCabinCapacity) :
    _rmolServiceContext (NULL) {

    // Initialise the service context
    initServiceContext ();

    // Initialise the STDAIR service handler
    initStdAirService (iLogParams);

    // Build a dummy inventory with a leg-cabin which has the given capacity.
    buildInventorySample (iCabinCapacity);
    
  }

  // ////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service (const stdair::BasLogParams& iLogParams) :
    _rmolServiceContext (NULL) {

    // Initialise the service context
    initServiceContext ();

    // Initialise the STDAIR service handler
    initStdAirService (iLogParams);    
  }

  // ////////////////////////////////////////////////////////////////////
  RMOL_Service:: RMOL_Service (stdair::STDAIR_ServicePtr_T ioSTDAIRServicePtr)
    : _rmolServiceContext (NULL) {
    
    // Initialise the context
    initServiceContext ();
    
    // Add the StdAir service context to the RMOL service context
    addStdAirService (ioSTDAIRServicePtr);
  }

  // ////////////////////////////////////////////////////////////////////
  RMOL_Service::~RMOL_Service () {
    // Clean all the RMOL-scoped objects
    FacSupervisor::cleanFactory();
  }

  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::initServiceContext () {
    // Initialise the service context
    RMOL_ServiceContext& lRMOL_ServiceContext = 
      FacRmolServiceContext::instance().create ();
    _rmolServiceContext = &lRMOL_ServiceContext;
  }

  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  initStdAirService (const stdair::BasLogParams& iLogParams) {
    assert (_rmolServiceContext != NULL);
    
    // Initialise the STDAIR service handler
    // Note that the track on the object memory is kept thanks to the Boost
    // Smart Pointers component.
    STDAIR_ServicePtr_T lSTDAIR_Service = 
      STDAIR_ServicePtr_T (new stdair::STDAIR_Service (iLogParams));

    // Store the STDAIR service object within the (RMOL) service context
    addStdAirService (lSTDAIR_Service);
  }

  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  addStdAirService (stdair::STDAIR_ServicePtr_T ioSTDAIR_Service_ptr) {

    // Retrieve the RMOL service context
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext =
      *_rmolServiceContext;

    // Store the STDAIR service object within the (AIRINV) service context
    lRMOL_ServiceContext.setSTDAIR_Service (ioSTDAIR_Service_ptr);
  }

  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  buildInventorySample (const stdair::CabinCapacity_T& iCabinCapacity) {
    // Retrieve the BomRoot.
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;
    stdair::STDAIR_Service& lSTDAIR_Service =
      lRMOL_ServiceContext.getSTDAIR_Service ();
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getBomRoot ();

    stdair::CmdBomManager::buildSampleBomForRMOL (lBomRoot, iCabinCapacity);
  }

  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::readFromInputFile (const std::string& iInputFileName) {
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;
    lRMOL_ServiceContext.readFromInputFile (iInputFileName);
  }

  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::reset () {
    // Retrieve the RMOL service context
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;

    lRMOL_ServiceContext.reset();
  }
  
  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  optimalOptimisationByMCIntegration (const int K) {
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;

    stdair::LegCabin& lLegCabin = lRMOL_ServiceContext.getLegCabinSample();

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
  void RMOL_Service::
  optimalOptimisationByDP () {
    
  }
  
  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::heuristicOptimisationByEmsr () {
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;

    stdair::LegCabin& lLegCabin = lRMOL_ServiceContext.getLegCabinSample();

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
  void RMOL_Service::heuristicOptimisationByEmsrA () {
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;

    stdair::LegCabin& lLegCabin = lRMOL_ServiceContext.getLegCabinSample();    

    Optimiser::heuristicOptimisationByEmsrA (lLegCabin);

    // DEBUG
    STDAIR_LOG_DEBUG ("Result: " << lLegCabin.displayVirtualClassList());
    
  }

  // ////////////////////////////////////////////////////////////////////
  void RMOL_Service::heuristicOptimisationByEmsrB () {
    assert (_rmolServiceContext != NULL);
    RMOL_ServiceContext& lRMOL_ServiceContext = *_rmolServiceContext;

    stdair::LegCabin& lLegCabin = lRMOL_ServiceContext.getLegCabinSample();    

    Optimiser::heuristicOptimisationByEmsrB (lLegCabin);

    // DEBUG
    STDAIR_LOG_DEBUG ("Result: " << lLegCabin.displayVirtualClassList());
  }

}
