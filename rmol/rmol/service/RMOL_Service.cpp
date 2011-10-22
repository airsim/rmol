// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iomanip>
#include <sstream>
#include <iostream>
// RMOL
#include <rmol/basic/BasConst_RMOL_Service.hpp>
#include <rmol/field/FldYieldRange.hpp>
#include <rmol/field/FldDistributionParameters.hpp>
#include <rmol/bom/Demand.hpp>
#include <rmol/bom/Bucket.hpp>
#include <rmol/bom/BucketHolder.hpp>
#include <rmol/bom/StudyStatManager.hpp>
#include <rmol/factory/FacRmolServiceContext.hpp>
#include <rmol/command/Optimiser.hpp>
#include <rmol/service/RMOL_ServiceContext.hpp>
#include <rmol/service/Logger.hpp>
#include <rmol/RMOL_Service.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service () :
    _rmolServiceContext (NULL) {
  }

  // //////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service (const RMOL_Service& iService) :
    _rmolServiceContext (iService._rmolServiceContext) {
  }

  // //////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service (std::ostream& ioLogStream,
                              const ResourceCapacity_T iResourceCapacity) {
    // Initialise the context
    init (ioLogStream, iResourceCapacity);
  }

  // //////////////////////////////////////////////////////////////////////
  RMOL_Service::~RMOL_Service () {
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::init (std::ostream& ioLogStream,
                           const ResourceCapacity_T iResourceCapacity) {
    // Set the log file
    logInit (LOG::DEBUG, ioLogStream);

    // Initialise the context
    RMOL_ServiceContext& lRMOL_ServiceContext = 
      FacRmolServiceContext::instance().create (iResourceCapacity);
    _rmolServiceContext = &lRMOL_ServiceContext;
  }
  
  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::logInit (const LOG::EN_LogLevel iLogLevel,
                              std::ostream& ioLogOutputFile) {
    Logger::instance().setLogParameters (iLogLevel, ioLogOutputFile);
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
    // DEBUG
    RMOL_LOG_DEBUG (oBucketHolder_ptr->display());

    std::ostringstream logStream;
    logStream << "Bid-Price Vector (BPV): ";
    unsigned int size = lBidPriceVector.size();
    
    for (unsigned int i = 0; i < size; ++i) {
      const double bidPrice = lBidPriceVector.at(i);
      logStream << std::fixed << std::setprecision (2) << bidPrice << " ";
    }
    RMOL_LOG_DEBUG (logStream.str());

    if (lStudyStatManager_ptr != NULL) {
      RMOL_LOG_DEBUG (lStudyStatManager_ptr->describe());
    }
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  optimalOptimisationByMCIntegration(const int K,
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
    oBucketHolder_ptr->fillup (ioBookingLimitVector);
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
    RMOL_LOG_DEBUG (oBucketHolder_ptr->display());
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  optimalOptimisationByDP (BookingLimitVector_T& ioBookingLimitVector) {
    
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* oBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (oBucketHolder_ptr != NULL);

    Optimiser::optimalOptimisationByDP (iCapacity, *oBucketHolder_ptr);

    // Fill up booking vector
    oBucketHolder_ptr->fillup (ioBookingLimitVector);
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
    RMOL_LOG_DEBUG (oBucketHolder_ptr->display());
    std::ostringstream logStream;
    logStream << "Bid-Price Vector (BPV): ";
    unsigned int size = lBidPriceVector.size();
    
    for (unsigned int i = 0; i < size; ++i) {
      const double bidPrice = lBidPriceVector.at(i);
      logStream << std::fixed << std::setprecision (2) << bidPrice << " ";
    }
    RMOL_LOG_DEBUG (logStream.str());

    if (lStudyStatManager_ptr != NULL) {
      RMOL_LOG_DEBUG (lStudyStatManager_ptr->describe());
    }
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  heuristicOptimisationByEmsr (BidPriceVector_T& ioBidPriceVector,
                               BookingLimitVector_T& ioBookingLimitVector) {
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* oBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (oBucketHolder_ptr != NULL);

    Optimiser::heuristicOptimisationByEmsr (iCapacity, *oBucketHolder_ptr,
                                            ioBidPriceVector);

    // Update the booking limit vector.
    for (oBucketHolder_ptr->begin(); oBucketHolder_ptr->hasNotReachedEnd();
         oBucketHolder_ptr->iterate()) {
      Bucket& currentBucket = oBucketHolder_ptr->getCurrentBucket();
      const double lBookingLimit = currentBucket.getCumulatedBookingLimit();
      ioBookingLimitVector.push_back (lBookingLimit);
    }
    
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::heuristicOptimisationByEmsrA () {
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* oBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (oBucketHolder_ptr != NULL);

    Optimiser::heuristicOptimisationByEmsrA (iCapacity, *oBucketHolder_ptr);

    // DEBUG
    RMOL_LOG_DEBUG (oBucketHolder_ptr->display());
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  heuristicOptimisationByEmsrA (BidPriceVector_T& ioBidPriceVector,
                                BookingLimitVector_T& ioBookingLimitVector) {
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* oBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (oBucketHolder_ptr != NULL);

    Optimiser::heuristicOptimisationByEmsrA (iCapacity, *oBucketHolder_ptr);

    // Fill up booking vector
    oBucketHolder_ptr->fillup (ioBookingLimitVector);
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
    RMOL_LOG_DEBUG (ioBucketHolder_ptr->display());
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::heuristicOptimisationByEmsrAwithSellup 
  (SellupProbabilityVector_T& iSellupProbabilityVector,
   BidPriceVector_T& ioBidPriceVector,
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
    ioBucketHolder_ptr->fillup (ioBookingLimitVector);
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::heuristicOptimisationByEmsrB () {
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* oBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (oBucketHolder_ptr != NULL);

    Optimiser::heuristicOptimisationByEmsrB (iCapacity, *oBucketHolder_ptr);

    // DEBUG
    RMOL_LOG_DEBUG (oBucketHolder_ptr->display());
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  heuristicOptimisationByEmsrB (BidPriceVector_T& ioBidPriceVector,
                                BookingLimitVector_T& ioBookingLimitVector) {
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* oBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (oBucketHolder_ptr != NULL);

    Optimiser::heuristicOptimisationByEmsrB (iCapacity, *oBucketHolder_ptr);

    // Fill up booking vector
    oBucketHolder_ptr->fillup (ioBookingLimitVector);
  }

  // ///////////////////////////////////////////////////////////////////////
  void RMOL_Service:: legOptimisationByMC () {
    assert (_rmolServiceContext != NULL);
    const ResourceCapacity_T iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* oBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (oBucketHolder_ptr != NULL);

    BidPriceVector_T lBidPriceVector;
    Optimiser::legOptimisationByMC (iCapacity, *oBucketHolder_ptr,
                                    lBidPriceVector);
    
    // DEBUG
    RMOL_LOG_DEBUG (oBucketHolder_ptr->display());
    std::ostringstream logStream;
    logStream << "Bid-Price Vector (BPV): ";
    unsigned int size = lBidPriceVector.size();
    
    for (unsigned int i = 0; i < size; ++i) {
      const double bidPrice = lBidPriceVector.at(i);
      logStream << std::fixed << std::setprecision (2) << bidPrice << " ";
    }
    RMOL_LOG_DEBUG (logStream.str());
  }

  // ///////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  legOptimisationByMC (BidPriceVector_T& ioBidPriceVector,
                       BookingLimitVector_T& ioBookingLimitVector) {
    assert (_rmolServiceContext != NULL);
    const ResourceCapacity_T iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* oBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (oBucketHolder_ptr != NULL);
    
    Optimiser::legOptimisationByMC (iCapacity, *oBucketHolder_ptr,
                                    ioBidPriceVector);

    // Fill up booking vector
    oBucketHolder_ptr->fillup (ioBookingLimitVector);
  }
  
}
