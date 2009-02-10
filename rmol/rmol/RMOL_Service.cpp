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
#include <rmol/factory/FacServiceContext.hpp>
#include <rmol/command/Optimiser.hpp>
#include <rmol/service/ServiceContext.hpp>
#include <rmol/RMOL_Service.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service () :
    _context (NULL) {
  }

  // //////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service (const RMOL_Service& iService) :
    _context (NULL) {
  }

  // //////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service (const ResourceCapacity_T iResourceCapacity) {
    // Initialise the context
    initContext (iResourceCapacity);
  }

  // //////////////////////////////////////////////////////////////////////
  RMOL_Service::~RMOL_Service () {
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::initContext (const ResourceCapacity_T iResourceCapacity) {
    _context = &FacServiceContext::instance().create (iResourceCapacity);
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::addBucket (const double iYieldRange, 
                                const double iDemandMean,
                                const double iDemandStandardDev) {
    assert (_context != NULL);
    _context->addBucket (iYieldRange, iDemandMean, iDemandStandardDev);
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::readFromInputFile (const std::string& iInputFileName) {
    assert (_context != NULL);
    _context->readFromInputFile (iInputFileName);
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  optimalOptimisationByMCIntegration (const int K) {
    
    assert (_context != NULL);
    const double iCapacity = _context->getCapacity();
    BucketHolder* ioBucketHolder_ptr = _context->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);

    Optimiser::optimalOptimisationByMCIntegration (K, iCapacity, 
                                                   *ioBucketHolder_ptr);

    // Display
    ioBucketHolder_ptr->display();
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  optimalOptimisationByMCIntegration (const int K,
                                      BookingLimitVector_T& ioBookingLimitVector) {
    
    assert (_context != NULL);
    const double iCapacity = _context->getCapacity();
    BucketHolder* ioBucketHolder_ptr = _context->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);

    Optimiser::optimalOptimisationByMCIntegration (K, iCapacity, 
                                                   *ioBucketHolder_ptr);

    // Fill up booking vector
    ioBucketHolder_ptr->fillup(ioBookingLimitVector);
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  optimalOptimisationByDP () {
    
    assert (_context != NULL);
    const double iCapacity = _context->getCapacity();
    BucketHolder* ioBucketHolder_ptr = _context->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);

    Optimiser::optimalOptimisationByDP (iCapacity, *ioBucketHolder_ptr);

    // Display
    ioBucketHolder_ptr->display();
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  optimalOptimisationByDP (BookingLimitVector_T& ioBookingLimitVector) {
    
    assert (_context != NULL);
    const double iCapacity = _context->getCapacity();
    BucketHolder* ioBucketHolder_ptr = _context->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);

    Optimiser::optimalOptimisationByDP (iCapacity, *ioBucketHolder_ptr);

    // Fill up booking vector
    ioBucketHolder_ptr->fillup(ioBookingLimitVector);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::heuristicOptimisationByEmsr () {
    assert (_context != NULL);
    const double iCapacity = _context->getCapacity();
    BucketHolder* ioBucketHolder_ptr = _context->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);
    BidPriceVector_T lBidPriceVector;

    Optimiser::heuristicOptimisationByEmsr (iCapacity, *ioBucketHolder_ptr,
                                            lBidPriceVector);

    // Display
    ioBucketHolder_ptr->display();
    
    std::cout << "BVP: ";
    unsigned int size = lBidPriceVector.size();

    for (unsigned int i = 0; i < size; ++i) {
      const double bidPrice = lBidPriceVector.at(i);
      std::cout << std::fixed << std::setprecision (2) << bidPrice << " ";
    }
    std::cout << std::endl;
    
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  heuristicOptimisationByEmsr (BidPriceVector_T& ioBidPriceVector) {
    assert (_context != NULL);
    const double iCapacity = _context->getCapacity();
    BucketHolder* ioBucketHolder_ptr = _context->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);

    Optimiser::heuristicOptimisationByEmsr (iCapacity, *ioBucketHolder_ptr,
                                            ioBidPriceVector);
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::heuristicOptimisationByEmsrA () {
    assert (_context != NULL);
    const double iCapacity = _context->getCapacity();
    BucketHolder* ioBucketHolder_ptr = _context->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);

    Optimiser::heuristicOptimisationByEmsrA (iCapacity, *ioBucketHolder_ptr);

    // Display
    ioBucketHolder_ptr->display();
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  heuristicOptimisationByEmsrA (BookingLimitVector_T& ioBookingLimitVector) {
    assert (_context != NULL);
    const double iCapacity = _context->getCapacity();
    BucketHolder* ioBucketHolder_ptr = _context->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);

    Optimiser::heuristicOptimisationByEmsrA (iCapacity, *ioBucketHolder_ptr);

    // Fill up booking vector
    ioBucketHolder_ptr->fillup(ioBookingLimitVector);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::heuristicOptimisationByEmsrB () {
    assert (_context != NULL);
    const double iCapacity = _context->getCapacity();
    BucketHolder* ioBucketHolder_ptr = _context->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);

    Optimiser::heuristicOptimisationByEmsrB (iCapacity, *ioBucketHolder_ptr);

    // Display
    ioBucketHolder_ptr->display();
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  heuristicOptimisationByEmsrB (BookingLimitVector_T& ioBookingLimitVector) {
    assert (_context != NULL);
    const double iCapacity = _context->getCapacity();
    BucketHolder* ioBucketHolder_ptr = _context->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);

    Optimiser::heuristicOptimisationByEmsrB (iCapacity, *ioBucketHolder_ptr);

    // Fill up booking vector
    ioBucketHolder_ptr->fillup(ioBookingLimitVector);
  }
  
}
