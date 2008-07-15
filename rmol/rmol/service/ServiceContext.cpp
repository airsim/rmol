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
#include <rmol/service/ServiceContext.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  ServiceContext::
  ServiceContext (const ResourceCapacity_T iResourceCapacity) :
    _bucketHolder (NULL), _capacity (iResourceCapacity) {
    init (iResourceCapacity);
  }
  
  // //////////////////////////////////////////////////////////////////////
  ServiceContext::ServiceContext () : 
    _bucketHolder (NULL), _capacity (DEFAULT_RMOL_SERVICE_CAPACITY) {
    init (DEFAULT_RMOL_SERVICE_CAPACITY);
  }
  
  // //////////////////////////////////////////////////////////////////////
  ServiceContext::ServiceContext (const ServiceContext&) :
    _bucketHolder (NULL), _capacity (DEFAULT_RMOL_SERVICE_CAPACITY) {
    init (DEFAULT_RMOL_SERVICE_CAPACITY);
  }

  // //////////////////////////////////////////////////////////////////////
  ServiceContext::~ServiceContext() {
  }

  // //////////////////////////////////////////////////////////////////////
  void ServiceContext::init (const ResourceCapacity_T iResourceCapacity) {
    _bucketHolder = &FacBucketHolder::instance().create (iResourceCapacity);
  }

  // //////////////////////////////////////////////////////////////////////
  void ServiceContext::addBucket (const double iYieldRange, 
                                  const double iDemandMean,
                                  const double iDemandStandardDev) {
    const FldYieldRange aYieldRange (iYieldRange);
    const FldDistributionParameters aDistribParams (iDemandMean, 
						    iDemandStandardDev);
    Demand& aDemand = 
      FacDemand::instance().create (aDistribParams, aYieldRange);
    Bucket& aBucket = FacBucket::instance().create (aYieldRange, aDemand);

    assert (_bucketHolder != NULL);
    FacBucketHolder::instance().addBucket (*_bucketHolder, aBucket);
  }

  // //////////////////////////////////////////////////////////////////////
  void ServiceContext::readFromInputFile (const std::string& iInputFileName) {
    assert (_bucketHolder != NULL);
    FileMgr::readAndProcessInputFile (iInputFileName, *_bucketHolder);
  }

}
