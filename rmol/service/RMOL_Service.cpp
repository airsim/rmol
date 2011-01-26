// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/basic/BasChronometer.hpp>
#include <stdair/basic/BasFileMgr.hpp>
#include <stdair/bom/BomManager.hpp> // for display()
#include <stdair/service/Logger.hpp>
#include <stdair/STDAIR_Service.hpp>
// RMOL
#include <rmol/basic/BasConst_RMOL_Service.hpp>
#include <rmol/field/FldYieldRange.hpp>
#include <rmol/field/FldDistributionParameters.hpp>
#include <rmol/bom/Demand.hpp>
#include <rmol/bom/Bucket.hpp>
#include <rmol/bom/BucketHolder.hpp>
#include <rmol/bom/StudyStatManager.hpp>
#include <rmol/factory/FacSupervisor.hpp>
#include <rmol/factory/FacRmolServiceContext.hpp>
#include <rmol/command/Optimiser.hpp>
#include <rmol/command/Unconstrainer.hpp>
#include <rmol/command/Forecaster.hpp>
#include <rmol/service/RMOL_ServiceContext.hpp>
#include <rmol/RMOL_Service.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service () : _rmolServiceContext (NULL) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service (const RMOL_Service& iService) :
    _rmolServiceContext (NULL) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service (const stdair::BasLogParams& iLogParams,
                              const stdair::AirlineCode_T& iAirlineCode) :
    _rmolServiceContext (NULL) {

    // Initialise the service context
    initServiceContext (iAirlineCode);

    // Initialise the STDAIR service handler
    initStdAirService (iLogParams);
    
    // Initialise the (remaining of the) context
    init (iAirlineCode);
  }

  // //////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service (const stdair::AirlineCode_T& iAirlineCode) :
    _rmolServiceContext (NULL) {
    
    // Initialise the context
    init (iAirlineCode);
  }

  // //////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service (const stdair::BasLogParams& iLogParams,
                              const stdair::AirlineCode_T& iAirlineCode,
                              const ResourceCapacity_T iResourceCapacity) :
    _rmolServiceContext (NULL) {
    
    // Initialise the service context
    initServiceContext (iAirlineCode, iResourceCapacity);
    
    // Initialise the STDAIR service handler
    initStdAirService (iLogParams);
    
    // Initialise the (remaining of the) context
    init (iAirlineCode, iResourceCapacity);
  }

  // //////////////////////////////////////////////////////////////////////
  RMOL_Service::~RMOL_Service () {
    // Clean all the RMOL-scoped objects
    FacSupervisor::cleanFactory();
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  initServiceContext (const stdair::AirlineCode_T& iAirlineCode) {
    // Initialise the service context
    RMOL_ServiceContext& lRMOL_ServiceContext = 
      FacRmolServiceContext::instance().create (iAirlineCode);
    _rmolServiceContext = &lRMOL_ServiceContext;
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  initServiceContext (const stdair::AirlineCode_T& iAirlineCode,
                      const ResourceCapacity_T iResourceCapacity) {
    // Initialise the service context
    RMOL_ServiceContext& lRMOL_ServiceContext = 
      FacRmolServiceContext::instance().create (iAirlineCode, iResourceCapacity);
    _rmolServiceContext = &lRMOL_ServiceContext;
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  initStdAirService (const stdair::BasLogParams& iLogParams) {
    assert (_rmolServiceContext != NULL);
    
    // Initialise the STDAIR service handler
    // Note that the track on the object memory is kept thanks to the Boost
    // Smart Pointers component.
    STDAIR_ServicePtr_T lSTDAIR_Service = 
      STDAIR_ServicePtr_T (new stdair::STDAIR_Service (iLogParams));

    // Store the STDAIR service object within the (RMOL) service context
    _rmolServiceContext->setSTDAIR_Service (lSTDAIR_Service);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::init (const stdair::AirlineCode_T& iAirlineCode) {
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::init (const stdair::AirlineCode_T& iAirlineCode,
                           const ResourceCapacity_T iResourceCapacity) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::setUpStudyStatManager () {
    assert (_rmolServiceContext != NULL);
    _rmolServiceContext->setUpStudyStatManager ();
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  setResourceCapacity (const ResourceCapacity_T iResourceCapacity) {
    assert (_rmolServiceContext != NULL);
    _rmolServiceContext->setResourceCapacity (iResourceCapacity);
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::addBucket (const double iYieldRange, 
                                const double iDemandMean,
                                const double iDemandStandardDev) {
    assert (_rmolServiceContext != NULL);
    _rmolServiceContext->addBucket (iYieldRange, iDemandMean,
                                    iDemandStandardDev);
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::addBucket(const double iYieldRange, 
                               const double iDemandMean,
                               const double iDemandStandardDev,
                               GeneratedDemandVector_T* ioGeneratedDemandVector){
    assert (_rmolServiceContext != NULL);
    _rmolServiceContext->addBucket (iYieldRange, iDemandMean,
                                    iDemandStandardDev, ioGeneratedDemandVector);
  }

  // //////////////////////////////////////////////////////////////////////
  GeneratedDemandVector_T* RMOL_Service::
  generateDemand (const int K, const double& iMean, const double& iDeviation) {
    return _rmolServiceContext->generateDemand (K, iMean, iDeviation);
  }

  // //////////////////////////////////////////////////////////////////////
  GeneratedDemandVector_T* RMOL_Service::
  generateDemand (GeneratedDemandVector_T* ioFirstVector,
                  GeneratedDemandVector_T* ioSecondVector) {
    return _rmolServiceContext->generateDemand (ioFirstVector, ioSecondVector);
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::readFromInputFile (const std::string& iInputFileName) {
    // Check that the file path given as input corresponds to an actual file
    const bool doesExistAndIsReadable =
      stdair::BasFileMgr::doesExistAndIsReadable (iInputFileName);
    if (doesExistAndIsReadable == false) {
      STDAIR_LOG_ERROR ("The input file, '" << iInputFileName
                        << "', can not be retrieved on the file-system");
      throw FileNotFoundException();
    }

    assert (_rmolServiceContext != NULL);
    _rmolServiceContext->readFromInputFile (iInputFileName);
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::buildContextForMC (const int K) {
    assert (_rmolServiceContext != NULL);
    _rmolServiceContext->buildContextForMC (K);
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::reset () {
    assert (_rmolServiceContext != NULL);
    _rmolServiceContext->reset ();
  }
  
  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  optimalOptimisationByMCIntegration (const int K) {
    
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* oBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (oBucketHolder_ptr != NULL);
    
    BidPriceVector_T lBidPriceVector;
    StudyStatManager* lStudyStatManager_ptr =
      _rmolServiceContext->getStudyStatManager();

    stdair::BasChronometer lOptimisationChronometer;
    lOptimisationChronometer.start();
    
    if (lStudyStatManager_ptr == NULL) {
      Optimiser::optimalOptimisationByMCIntegration (K, iCapacity, 
                                                     *oBucketHolder_ptr,
                                                     lBidPriceVector);
    } else {
      Optimiser::optimalOptimisationByMCIntegration (K, iCapacity, 
                                                     *oBucketHolder_ptr,
                                                     lBidPriceVector,
                                                     *lStudyStatManager_ptr);
    }

    const double lOptimisationMeasure = lOptimisationChronometer.elapsed();
    
    // DEBUG
    STDAIR_LOG_DEBUG ("Optimisation by Monte-Carlo performed in "
                      << lOptimisationMeasure);
    STDAIR_LOG_DEBUG ("Resulting buckets: " << oBucketHolder_ptr->display());

    std::ostringstream logStream;
    logStream << "Bid-Price Vector (BPV): ";
    unsigned int size = lBidPriceVector.size();
    
    for (unsigned int i = 0; i < size; ++i) {
      const double bidPrice = lBidPriceVector.at(i);
      logStream << std::fixed << std::setprecision (2) << bidPrice << ", ";
    }
    STDAIR_LOG_DEBUG (logStream.str());

    if (lStudyStatManager_ptr != NULL) {
      STDAIR_LOG_DEBUG (lStudyStatManager_ptr->describe());
    }
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::optimalOptimisationByMCIntegration
  (const int K, ProtectionLevelVector_T& ioProtectionLevelVector,
   BidPriceVector_T& ioBidPriceVector,
   BookingLimitVector_T& ioBookingLimitVector){
    
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* oBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (oBucketHolder_ptr != NULL);

    Optimiser::optimalOptimisationByMCIntegration (K, iCapacity, 
                                                   *oBucketHolder_ptr,
                                                   ioBidPriceVector);

    // Fill up booking vector
    oBucketHolder_ptr->fillup (ioProtectionLevelVector, ioBookingLimitVector);
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  optimalOptimisationByDP () {
    
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* oBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (oBucketHolder_ptr != NULL);

    Optimiser::optimalOptimisationByDP (iCapacity, *oBucketHolder_ptr);

    // DEBUG
    STDAIR_LOG_DEBUG (oBucketHolder_ptr->display());
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  optimalOptimisationByDP (ProtectionLevelVector_T& ioProtectionLevelVector,
                           BookingLimitVector_T& ioBookingLimitVector) {
    
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* oBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (oBucketHolder_ptr != NULL);

    Optimiser::optimalOptimisationByDP (iCapacity, *oBucketHolder_ptr);

    // Fill up booking vector
    oBucketHolder_ptr->fillup (ioProtectionLevelVector, ioBookingLimitVector);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::heuristicOptimisationByEmsr () {
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* oBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (oBucketHolder_ptr != NULL);
    BidPriceVector_T lBidPriceVector;
    
    StudyStatManager* lStudyStatManager_ptr =
      _rmolServiceContext->getStudyStatManager();
    
    if (lStudyStatManager_ptr == NULL) {
      Optimiser::heuristicOptimisationByEmsr (iCapacity, *oBucketHolder_ptr,
                                              lBidPriceVector);
    } else {      
      Optimiser::heuristicOptimisationByEmsr (iCapacity, *oBucketHolder_ptr,
                                              lBidPriceVector,
                                              *lStudyStatManager_ptr);
    }
    
    // DEBUG
    STDAIR_LOG_DEBUG (oBucketHolder_ptr->display());
    std::ostringstream logStream;
    logStream << "Bid-Price Vector (BPV): ";
    const unsigned int size = lBidPriceVector.size();
    
    for (unsigned int i = 0; i < size; ++i) {
      const double bidPrice = lBidPriceVector.at(i);
      logStream << std::fixed << std::setprecision (2) << bidPrice << ", ";
    }
    STDAIR_LOG_DEBUG (logStream.str());

    if (lStudyStatManager_ptr != NULL) {
      STDAIR_LOG_DEBUG (lStudyStatManager_ptr->describe());
    }
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  heuristicOptimisationByEmsr (BidPriceVector_T& ioBidPriceVector,
                               ProtectionLevelVector_T& ioProtectionLevelVector,
                               BookingLimitVector_T& ioBookingLimitVector) {
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* oBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (oBucketHolder_ptr != NULL);

    Optimiser::heuristicOptimisationByEmsr (iCapacity, *oBucketHolder_ptr,
                                            ioBidPriceVector);

    oBucketHolder_ptr->fillup (ioProtectionLevelVector, ioBookingLimitVector); 
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::heuristicOptimisationByEmsrA () {
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* oBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (oBucketHolder_ptr != NULL);

    Optimiser::heuristicOptimisationByEmsrA (iCapacity, *oBucketHolder_ptr);

    // DEBUG
    STDAIR_LOG_DEBUG (oBucketHolder_ptr->display());
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  heuristicOptimisationByEmsrA (BidPriceVector_T& ioBidPriceVector,
                                ProtectionLevelVector_T& ioProtectionLevelVector,
                                BookingLimitVector_T& ioBookingLimitVector) {
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* oBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (oBucketHolder_ptr != NULL);

    Optimiser::heuristicOptimisationByEmsrA (iCapacity, *oBucketHolder_ptr);

    // Fill up booking vector
    oBucketHolder_ptr->fillup (ioProtectionLevelVector, ioBookingLimitVector);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::heuristicOptimisationByEmsrAwithSellup 
  (SellupProbabilityVector_T& iSellupProbabilityVector) {

    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* ioBucketHolder_ptr = 
      _rmolServiceContext->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);

    Optimiser::
      heuristicOptimisationByEmsrAwithSellup (iCapacity, 
                                              *ioBucketHolder_ptr,
                                              iSellupProbabilityVector);

    // DEBUG
    STDAIR_LOG_DEBUG (ioBucketHolder_ptr->display());
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::heuristicOptimisationByEmsrAwithSellup 
  (SellupProbabilityVector_T& iSellupProbabilityVector,
   BidPriceVector_T& ioBidPriceVector,
   ProtectionLevelVector_T& ioProtectionLevelVector,
   BookingLimitVector_T& ioBookingLimitVector) {
    
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* ioBucketHolder_ptr = 
      _rmolServiceContext->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);

    Optimiser::
      heuristicOptimisationByEmsrAwithSellup (iCapacity, 
                                              *ioBucketHolder_ptr,
                                              iSellupProbabilityVector);

    // Fill up booking limit vector
    ioBucketHolder_ptr->fillup (ioProtectionLevelVector, ioBookingLimitVector);
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::heuristicOptimisationByEmsrB () {
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* oBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (oBucketHolder_ptr != NULL);

    Optimiser::heuristicOptimisationByEmsrB (iCapacity, *oBucketHolder_ptr);

    // DEBUG
    STDAIR_LOG_DEBUG (oBucketHolder_ptr->display());
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  heuristicOptimisationByEmsrB (BidPriceVector_T& ioBidPriceVector,
                                ProtectionLevelVector_T& ioProtectionLevelVector,
                                BookingLimitVector_T& ioBookingLimitVector) {
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* oBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (oBucketHolder_ptr != NULL);

    Optimiser::heuristicOptimisationByEmsrB (iCapacity, *oBucketHolder_ptr);

    // Fill up booking vector
    oBucketHolder_ptr->fillup (ioProtectionLevelVector, ioBookingLimitVector);
  }

  // ///////////////////////////////////////////////////////////////////////
  void RMOL_Service::legOptimisationByMC () {
    assert (_rmolServiceContext != NULL);
    const ResourceCapacity_T iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* oBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (oBucketHolder_ptr != NULL);

    BidPriceVector_T lBidPriceVector;
    Optimiser::legOptimisationByMC (iCapacity, *oBucketHolder_ptr,
                                    lBidPriceVector);
    
    // DEBUG
    STDAIR_LOG_DEBUG (oBucketHolder_ptr->display());
    std::ostringstream logStream;
    logStream << "Bid-Price Vector (BPV): ";
    unsigned int size = lBidPriceVector.size();
    
    for (unsigned int i = 0; i < size; ++i) {
      const double bidPrice = lBidPriceVector.at(i);
      logStream << std::fixed << std::setprecision (2) << bidPrice << ", ";
    }

    // DEBUG
    STDAIR_LOG_DEBUG (logStream.str());
  }

  // ///////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  legOptimisationByMC (BidPriceVector_T& ioBidPriceVector,
                       ProtectionLevelVector_T& ioProtectionLevelVector,
                       BookingLimitVector_T& ioBookingLimitVector) {
    assert (_rmolServiceContext != NULL);
    const ResourceCapacity_T iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* oBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (oBucketHolder_ptr != NULL);
    
    Optimiser::legOptimisationByMC (iCapacity, *oBucketHolder_ptr,
                                    ioBidPriceVector);

    // Fill up booking vector
    oBucketHolder_ptr->fillup (ioProtectionLevelVector, ioBookingLimitVector);
  }

  // ///////////////////////////////////////////////////////////////////////
  void RMOL_Service::dataUnconstrainingByExpectationMaximization 
                     (ConstrainedDataHolder_T& ioConstrainedDataHolder, 
                      UnconstrainedDataHolder_T& iUnconstrainedDataHolder, 
                      StoppingCriterion_T& iStoppingCriterion) {
    
    Unconstrainer::dataUnconstrainByExpectationMaximization 
    (ioConstrainedDataHolder, iUnconstrainedDataHolder, iStoppingCriterion);

  }

  // ///////////////////////////////////////////////////////////////////////
  void RMOL_Service::demandForecastByQForecasting 
         (ForecastedDemandParameterList_T& ioForecastedDemandParameterList, 
          HistoricalDataHolderHolder_T& iHistoricalDataHolderHolder, 
          PriceHolder_T& iPriceHolder,
          SellupFactorHolder_T& iSellupFactorHolder) {

    Forecaster::demandForecastByQForecasting (ioForecastedDemandParameterList,
                                              iHistoricalDataHolderHolder,
                                              iPriceHolder,
                                              iSellupFactorHolder);    

  }
  
}
