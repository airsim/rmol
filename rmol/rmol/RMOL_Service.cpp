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
  
}
