// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// RMOL
#include <rmol/basic/BasConst_RMOL_Service.hpp>
#include <rmol/field/FldYieldRange.hpp>
#include <rmol/field/FldDistributionParameters.hpp>
#include <rmol/bom/Demand.hpp>
#include <rmol/bom/Bucket.hpp>
#include <rmol/bom/BucketHolder.hpp>
#include <rmol/bom/StudyStatManager.hpp>
#include <rmol/bom/Gaussian.hpp>
#include <rmol/factory/FacSupervisor.hpp>
#include <rmol/factory/FacDemand.hpp>
#include <rmol/factory/FacBucket.hpp>
#include <rmol/factory/FacBucketHolder.hpp>
#include <rmol/factory/FacStudyStatManager.hpp>
#include <rmol/command/FileMgr.hpp>
#include <rmol/service/RMOL_ServiceContext.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  RMOL_ServiceContext::RMOL_ServiceContext () : 
    _bucketHolder (NULL), _studyStatManager (NULL) {
    assert (false);
  }
  
  // //////////////////////////////////////////////////////////////////////
  RMOL_ServiceContext::RMOL_ServiceContext (const RMOL_ServiceContext&) :
    _bucketHolder (NULL), _studyStatManager (NULL) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  RMOL_ServiceContext::
  RMOL_ServiceContext (const stdair::AirlineCode_T& iAirlineCode) : 
    _bucketHolder (NULL), _studyStatManager (NULL),
    _airlineCode (iAirlineCode), _capacity (DEFAULT_RMOL_SERVICE_CAPACITY),
    _generatedDemandVectorHolder (DEFAULT_GENERATED_DEMAND_VECTOR_HOLDER) {
    init (DEFAULT_RMOL_SERVICE_CAPACITY);
  }
  
  // //////////////////////////////////////////////////////////////////////
  RMOL_ServiceContext::
  RMOL_ServiceContext (const stdair::AirlineCode_T& iAirlineCode,
                       const ResourceCapacity_T iResourceCapacity) :
    _bucketHolder (NULL), _studyStatManager (NULL),
    _airlineCode (iAirlineCode), _capacity (iResourceCapacity),
    _generatedDemandVectorHolder (DEFAULT_GENERATED_DEMAND_VECTOR_HOLDER) {
    init (iResourceCapacity);
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
  void RMOL_ServiceContext::
  setResourceCapacity (const ResourceCapacity_T iResourceCapacity) {
    _capacity = iResourceCapacity;
    init (iResourceCapacity);
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
  addBucket (const double iYieldRange, 
             const double iDemandMean,
             const double iDemandStandardDev,
             GeneratedDemandVector_T* ioGeneratedDemandVector) {
    const FldYieldRange aYieldRange (iYieldRange);
    const FldDistributionParameters aDistribParams (iDemandMean, 
						    iDemandStandardDev);
    Demand& aDemand = 
      FacDemand::instance().create (aDistribParams, aYieldRange);
    Bucket& aBucket = FacBucket::instance().create (aYieldRange, aDemand);
    aBucket.setGeneratedDemandVector (ioGeneratedDemandVector);

    assert (_bucketHolder != NULL);
    FacBucketHolder::instance().addBucket (*_bucketHolder, aBucket);
  }
  
  // //////////////////////////////////////////////////////////////////////
  GeneratedDemandVector_T* RMOL_ServiceContext::
  generateDemand (const int K, const stdair::MeanValue_T& iMean,
                  const stdair::StdDevValue_T& iDeviation) {
    // Build a vector of K generated numbers from the given distribution
    // N(iMean, iDeviation) and add this vector to the
    // GeneratedDemandVector holder.
    _generatedDemandVectorHolder.push_back (DEFAULT_GENERATED_DEMAND_VECTOR);
    GeneratedDemandVectorHolder_T::reverse_iterator itLastVector =
      _generatedDemandVectorHolder.rbegin();
    GeneratedDemandVector_T& lDemandVector = *itLastVector;
    lDemandVector.reserve (K);
    const FldDistributionParameters aDistributionParam =
      FldDistributionParameters (iMean, iDeviation);
    Gaussian gaussianDemandGenerator (aDistributionParam);

    // Generate K numbers
    for (int i = 0; i < K; ++i) {
      const double lGeneratedDemand= gaussianDemandGenerator.generateVariate ();
      lDemandVector.push_back (lGeneratedDemand);
    }

    return &lDemandVector;
  }

  // //////////////////////////////////////////////////////////////////////
  GeneratedDemandVector_T* RMOL_ServiceContext::
  generateDemand (GeneratedDemandVector_T* ioFirstVector,
                  GeneratedDemandVector_T* ioSecondVector) {
    if (ioFirstVector == NULL || ioSecondVector == NULL) {
      return NULL;

    } else {
      assert (ioFirstVector != NULL);
      assert (ioSecondVector != NULL);
    
      const unsigned int K = ioFirstVector->size();
      assert (K == ioSecondVector->size());
      
      _generatedDemandVectorHolder.push_back (DEFAULT_GENERATED_DEMAND_VECTOR);
      GeneratedDemandVectorHolder_T::reverse_iterator itLastVector =
        _generatedDemandVectorHolder.rbegin();
      
      GeneratedDemandVector_T& lDemandVector = *itLastVector;
      lDemandVector.reserve (K);
      GeneratedDemandVector_T::const_iterator itFirst = ioFirstVector->begin();
      GeneratedDemandVector_T::const_iterator itSecond= ioSecondVector->begin();
      for ( ; itFirst != ioFirstVector->end(); ++itFirst, ++itSecond) {
        const double& lFirst = *itFirst;
        const double& lSecond = *itSecond;
        const double lGeneratedDemand = lFirst + lSecond;
        lDemandVector.push_back (lGeneratedDemand);
      }
      
      return &lDemandVector;
    }
  }
  
  // //////////////////////////////////////////////////////////////////////
  void RMOL_ServiceContext::
  readFromInputFile (const std::string& iInputFileName) {
    assert (_bucketHolder != NULL);
    FileMgr::readAndProcessInputFile (iInputFileName, *_bucketHolder);
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_ServiceContext::buildContextForMC (const int K) {
    assert (_bucketHolder != NULL);
    for (_bucketHolder->begin(); _bucketHolder->hasNotReachedEnd();
         _bucketHolder->iterate()) {
      Bucket& currentBucket = _bucketHolder->getCurrentBucket();
      const double mean = currentBucket.getMean();
      const double standardDeviation = currentBucket.getStandardDeviation();
      GeneratedDemandVector_T* lGeneratedDemandVector =
        generateDemand (K, mean, standardDeviation);
      currentBucket.setGeneratedDemandVector (lGeneratedDemandVector);
    }
  }

  // //////////////////////////////////////////////////////////////////////
  void RMOL_ServiceContext::reset () {
    _capacity = DEFAULT_RMOL_SERVICE_CAPACITY;
    _bucketHolder = NULL;
  }

}
