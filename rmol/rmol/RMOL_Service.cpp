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
#include <rmol/factory/FacSupervisor.hpp>
#include <rmol/factory/FacDemand.hpp>
#include <rmol/factory/FacBucket.hpp>
#include <rmol/factory/FacBucketHolder.hpp>
#include <rmol/command/FileMgr.hpp>
#include <rmol/command/Optimiser.hpp>
#include <rmol/RMOL_Service.hpp>

namespace RMOL {

  // //////////// RMOL_Service_Context ///////////

  // //////////////////////////////////////////////////////////////////////
  RMOL_Service_Context::
  RMOL_Service_Context (const ResourceCapacity_T iResourceCapacity) :
    _bucketHolder (NULL), _capacity (iResourceCapacity) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  RMOL_Service_Context::RMOL_Service_Context () : 
    _bucketHolder (NULL), _capacity (DEFAULT_RMOL_SERVICE_CAPACITY) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  RMOL_Service_Context::RMOL_Service_Context (const RMOL_Service_Context&) :
    _bucketHolder (NULL), _capacity (DEFAULT_RMOL_SERVICE_CAPACITY) {
  }

  // //////////////////////////////////////////////////////////////////////
  RMOL_Service_Context::~RMOL_Service_Context() {
    // Clean operations
    FacSupervisor::cleanFactory();
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service_Context::addBucket (const double iYieldRange, 
					const double iDemandMean,
                                        const double iDemandStandardDev) {
    const FldYieldRange aYieldRange (iYieldRange);
    const FldDistributionParameters aDistribParams (iDemandMean, 
						    iDemandStandardDev);
    const Demand& aDemand = 
      FacDemand::instance().create (aDistribParams, aYieldRange);
    Bucket& aBucket = FacBucket::instance().create (aYieldRange, aDemand);

    assert (_bucketHolder != NULL);
    FacBucketHolder::instance().addBucket (*_bucketHolder, aBucket);
  }

  // //////////// RMOL_Service ///////////

  // //////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service () {
  }

  // //////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service (const RMOL_Service& iService) {
  }

  // //////////////////////////////////////////////////////////////////////
  RMOL_Service::RMOL_Service (const double iResourceCapacity) :
    _context (iResourceCapacity) {
    BucketHolder& aBucketHolder = 
      FacBucketHolder::instance().create (iResourceCapacity);
    _context.setBucketHolder (&aBucketHolder);
  }

  // //////////////////////////////////////////////////////////////////////
  RMOL_Service::~RMOL_Service () {
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::addBucket (const double iYieldRange, 
				const double iDemandMean,
                                const double iDemandStandardDev) {
    _context.addBucket (iYieldRange, iDemandMean, iDemandStandardDev);
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::readFromInputFile (const std::string& iInputFileName) {
    BucketHolder* ioBucketHolder_ptr = _context.getBucketHolder();

    assert (ioBucketHolder_ptr != NULL);
    FileMgr::readAndProcessInputFile (iInputFileName, *ioBucketHolder_ptr);
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_Service::
  optimalOptimisationByMCIntegration (const int K) {
    
    const double iCapacity = _context.getCapacity();
    BucketHolder* ioBucketHolder_ptr = _context.getBucketHolder();
    assert (ioBucketHolder_ptr != NULL);

    Optimiser::optimalOptimisationByMCIntegration (K, iCapacity, 
						   *ioBucketHolder_ptr);

    // Display
    ioBucketHolder_ptr->display();
  }
  
}
