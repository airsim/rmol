// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
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
#include <rmol/RMOL.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  RMOL::RMOL () :
    _context (NULL) {
  }

  // //////////////////////////////////////////////////////////////////////
  RMOL::RMOL (const RMOL& iService) :
    _context (NULL) {
  }

  // //////////////////////////////////////////////////////////////////////
  RMOL::RMOL (const ResourceCapacity_T iResourceCapacity) {
    // Initialise the context
    initContext (iResourceCapacity);
  }

  // //////////////////////////////////////////////////////////////////////
  RMOL::~RMOL () {
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL::initContext (const ResourceCapacity_T iResourceCapacity) {
    _context = &FacServiceContext::instance().create (iResourceCapacity);
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL::addBucket (const double iYieldRange, 
                                const double iDemandMean,
                                const double iDemandStandardDev) {
    assert (_context != NULL);
    _context->addBucket (iYieldRange, iDemandMean, iDemandStandardDev);
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL::readFromInputFile (const std::string& iInputFileName) {
    assert (_context != NULL);
    _context->readFromInputFile (iInputFileName);
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL::
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
  void RMOL::
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
  void RMOL::
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
  void RMOL::
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
  void RMOL::heuristicOptimisationByEmsr () {
    assert (_context != NULL);
    const double iCapacity = _context->getCapacity();
    BucketHolder* ioBucketHolder_ptr = _context->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);

    Optimiser::heuristicOptimisationByEmsr (iCapacity, *ioBucketHolder_ptr);

    // Display
    ioBucketHolder_ptr->display();
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL::heuristicOptimisationByEmsr (BookingLimitVector_T& ioBookingLimitVector) {
    assert (_context != NULL);
    const double iCapacity = _context->getCapacity();
    BucketHolder* ioBucketHolder_ptr = _context->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);

    Optimiser::heuristicOptimisationByEmsr (iCapacity, *ioBucketHolder_ptr);

    // Fill up booking vector
    ioBucketHolder_ptr->fillup(ioBookingLimitVector);
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL::heuristicOptimisationByEmsrA () {
    assert (_context != NULL);
    const double iCapacity = _context->getCapacity();
    BucketHolder* ioBucketHolder_ptr = _context->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);

    Optimiser::heuristicOptimisationByEmsrA (iCapacity, *ioBucketHolder_ptr);

    // Display
    ioBucketHolder_ptr->display();
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL::heuristicOptimisationByEmsrA (BookingLimitVector_T& ioBookingLimitVector) {
    assert (_context != NULL);
    const double iCapacity = _context->getCapacity();
    BucketHolder* ioBucketHolder_ptr = _context->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);

    Optimiser::heuristicOptimisationByEmsrA (iCapacity, *ioBucketHolder_ptr);

    // Fill up booking vector
    ioBucketHolder_ptr->fillup(ioBookingLimitVector);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void RMOL::heuristicOptimisationByEmsrB () {
    assert (_context != NULL);
    const double iCapacity = _context->getCapacity();
    BucketHolder* ioBucketHolder_ptr = _context->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);

    Optimiser::heuristicOptimisationByEmsrB (iCapacity, *ioBucketHolder_ptr);

    // Display
    ioBucketHolder_ptr->display();
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL::heuristicOptimisationByEmsrB (BookingLimitVector_T& ioBookingLimitVector) {
    assert (_context != NULL);
    const double iCapacity = _context->getCapacity();
    BucketHolder* ioBucketHolder_ptr = _context->getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);

    Optimiser::heuristicOptimisationByEmsrB (iCapacity, *ioBucketHolder_ptr);

    // Fill up booking vector
    ioBucketHolder_ptr->fillup(ioBookingLimitVector);
  }
  
}
