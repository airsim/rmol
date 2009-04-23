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
#include <rmol/bom/StudyStatManager.hpp>
#include <rmol/factory/FacSupervisor.hpp>
#include <rmol/factory/FacDemand.hpp>
#include <rmol/factory/FacBucket.hpp>
#include <rmol/factory/FacBucketHolder.hpp>
#include <rmol/factory/FacStudyStatManager.hpp>
#include <rmol/command/FileMgr.hpp>
#include <rmol/service/RMOL_ServiceContext.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  RMOL_ServiceContext::
  RMOL_ServiceContext (const ResourceCapacity_T iResourceCapacity) :
    _bucketHolder (NULL), _capacity (iResourceCapacity),
    _studyStatManager (NULL) {
    init (iResourceCapacity);
  }
  
  // //////////////////////////////////////////////////////////////////////
  RMOL_ServiceContext::RMOL_ServiceContext () : 
    _bucketHolder (NULL), _capacity (DEFAULT_RMOL_SERVICE_CAPACITY),
    _studyStatManager (NULL) {
    init (DEFAULT_RMOL_SERVICE_CAPACITY);
  }
  
  // //////////////////////////////////////////////////////////////////////
  RMOL_ServiceContext::RMOL_ServiceContext (const RMOL_ServiceContext&) :
    _bucketHolder (NULL), _capacity (DEFAULT_RMOL_SERVICE_CAPACITY),
    _studyStatManager (NULL) {
    init (DEFAULT_RMOL_SERVICE_CAPACITY);
  }

  // //////////////////////////////////////////////////////////////////////
  RMOL_ServiceContext::~RMOL_ServiceContext() {
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_ServiceContext::init (const ResourceCapacity_T iResourceCapacity) {
    _bucketHolder = &FacBucketHolder::instance().create (iResourceCapacity);
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_ServiceContext::setUpStudyStatManager () {
    _studyStatManager = &FacStudyStatManager::instance().create();
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_ServiceContext::addBucket (const double iYieldRange, 
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
  void RMOL_ServiceContext::
  readFromInputFile (const std::string& iInputFileName) {
    assert (_bucketHolder != NULL);
    FileMgr::readAndProcessInputFile (iInputFileName, *_bucketHolder);
  }

}
