// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iomanip>
// RMOL
#include <rmol/basic/BasConst_RMOL_Service.hpp>
#include <rmol/field/FldYieldRange.hpp>
#include <rmol/field/FldDistributionParameters.hpp>
#include <rmol/bom/Demand.hpp>
#include <rmol/bom/Bucket.hpp>
#include <rmol/bom/BucketHolder.hpp>
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
  void RMOL_Service::addBucket (const double iYieldRange, 
                                const double iDemandMean,
                                const double iDemandStandardDev) {
    assert (_rmolServiceContext != NULL);
    _rmolServiceContext->addBucket (iYieldRange, iDemandMean,
                                    iDemandStandardDev);
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::readFromInputFile (const std::string& iInputFileName) {
    assert (_rmolServiceContext != NULL);
    _rmolServiceContext->readFromInputFile (iInputFileName);
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  optimalOptimisationByMCIntegration (const int K) {
    
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* ioBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);
    BidPriceVector_T lBidPriceVector;

    Optimiser::optimalOptimisationByMCIntegration (K, iCapacity, 
                                                   *ioBucketHolder_ptr,
                                                   lBidPriceVector);

    // DEBUG
    RMOL_LOG_DEBUG (ioBucketHolder_ptr->display());
    /*
    std::cout << "Bid-Price Vector (BPV): ";
    unsigned int size = lBidPriceVector.size();
    
    for (unsigned int i = 0; i < size; ++i) {
      const double bidPrice = lBidPriceVector.at(i);
      std::cout << std::fixed << std::setprecision (2) << bidPrice << " ";
    }
    std::cout << std::endl;
    */
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  optimalOptimisationByMCIntegration(const int K,
                                     BidPriceVector_T& ioBidPriceVector,
                                     BookingLimitVector_T& ioBookingLimitVector){
    
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* ioBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);

    Optimiser::optimalOptimisationByMCIntegration (K, iCapacity, 
                                                   *ioBucketHolder_ptr,
                                                   ioBidPriceVector);

    // Fill up booking vector
    ioBucketHolder_ptr->fillup (ioBookingLimitVector);
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  optimalOptimisationByDP () {
    
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* ioBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);

    Optimiser::optimalOptimisationByDP (iCapacity, *ioBucketHolder_ptr);

    // DEBUG
    RMOL_LOG_DEBUG (ioBucketHolder_ptr->display());
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  optimalOptimisationByDP (BookingLimitVector_T& ioBookingLimitVector) {
    
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* ioBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);

    Optimiser::optimalOptimisationByDP (iCapacity, *ioBucketHolder_ptr);

    // Fill up booking vector
    ioBucketHolder_ptr->fillup (ioBookingLimitVector);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::heuristicOptimisationByEmsr () {
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* ioBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);
    BidPriceVector_T lBidPriceVector;

    Optimiser::heuristicOptimisationByEmsr (iCapacity, *ioBucketHolder_ptr,
                                            lBidPriceVector);

    // DEBUG
    RMOL_LOG_DEBUG (ioBucketHolder_ptr->display());
    
    // std::cout << "Bid-Price Vector (BPV): ";
    // unsigned int size = lBidPriceVector.size();

    // for (unsigned int i = 0; i < size; ++i) {
      // const double bidPrice = lBidPriceVector.at(i);
      // std::cout << std::fixed << std::setprecision (2) << bidPrice << " ";
    // }
    // std::cout << std::endl;
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  heuristicOptimisationByEmsr (BidPriceVector_T& ioBidPriceVector,
                               BookingLimitVector_T& ioBookingLimitVector) {
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* ioBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);

    Optimiser::heuristicOptimisationByEmsr (iCapacity, *ioBucketHolder_ptr,
                                            ioBidPriceVector);

    // Update the booking limit vector.
    for (ioBucketHolder_ptr->begin(); ioBucketHolder_ptr->hasNotReachedEnd();
         ioBucketHolder_ptr->iterate()) {
      Bucket& currentBucket = ioBucketHolder_ptr->getCurrentBucket();
      const double lBookingLimit = currentBucket.getCumulatedBookingLimit();
      ioBookingLimitVector.push_back (lBookingLimit);
    }
    
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::heuristicOptimisationByEmsrA () {
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* ioBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);

    Optimiser::heuristicOptimisationByEmsrA (iCapacity, *ioBucketHolder_ptr);

    // DEBUG
    RMOL_LOG_DEBUG (ioBucketHolder_ptr->display());
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  heuristicOptimisationByEmsrA (BidPriceVector_T& ioBidPriceVector,
                                BookingLimitVector_T& ioBookingLimitVector) {
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* ioBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);

    Optimiser::heuristicOptimisationByEmsrA (iCapacity, *ioBucketHolder_ptr);

    // Fill up booking vector
    ioBucketHolder_ptr->fillup (ioBookingLimitVector);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::heuristicOptimisationByEmsrB () {
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* ioBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);

    Optimiser::heuristicOptimisationByEmsrB (iCapacity, *ioBucketHolder_ptr);

    // DEBUG
    RMOL_LOG_DEBUG (ioBucketHolder_ptr->display());
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  heuristicOptimisationByEmsrB (BidPriceVector_T& ioBidPriceVector,
                                BookingLimitVector_T& ioBookingLimitVector) {
    assert (_rmolServiceContext != NULL);
    const double iCapacity = _rmolServiceContext->getCapacity();
    BucketHolder* ioBucketHolder_ptr = _rmolServiceContext->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);

    Optimiser::heuristicOptimisationByEmsrB (iCapacity, *ioBucketHolder_ptr);

    // Fill up booking vector
    ioBucketHolder_ptr->fillup (ioBookingLimitVector);
  }
  
}
