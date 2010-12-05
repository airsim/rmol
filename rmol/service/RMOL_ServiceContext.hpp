#ifndef __RMOL_SVC_RMOL_SERVICE_CONTEXT_HPP
#define __RMOL_SVC_RMOL_SERVICE_CONTEXT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// RMOL
#include <rmol/RMOL_Types.hpp>
#include <rmol/service/ServiceAbstract.hpp>

namespace RMOL {

  /** Forward declaration. */
  class BucketHolder;
  class StudyStatManager;

  /** Inner class holding the context for the RMOL Service object. */
  class RMOL_ServiceContext : public ServiceAbstract {
    /** The RMOL_Service class should be the sole class to get access to
        ServiceContext content: general users do not want to bother
        with a context interface. */
    friend class RMOL_Service;
    friend class FacRmolServiceContext;

  private:
    /** Constructors. */
    RMOL_ServiceContext ();
    RMOL_ServiceContext (const RMOL_ServiceContext&);
    RMOL_ServiceContext (const ResourceCapacity_T iResourceCapacity);
    void init (const ResourceCapacity_T iResourceCapacity);
    /** Initialise the StudyStatManager. */
    void initStudyStatManager ();
    /** Destructor. */
    ~RMOL_ServiceContext();

    /** Set the cabin availability. */
    void setResourceCapacity (const ResourceCapacity_T iResourceCapacity);
    
    /** Set the BucketHolder. */
    void setBucketHolder (BucketHolder* ioBucketHolderPtr) {
      _bucketHolder = ioBucketHolderPtr;
    }

    /** Add a bucket to the BucketHolder. */
    void addBucket (const double iYieldRange, const double iDemandMean,
                    const double iDemandStandardDev);

    /** Add a bucket to the context. */
    void addBucket (const double iYieldRange, const double iDemandMean,
                    const double iDemandStandardDev,
                    GeneratedDemandVector_T* ioGeneratedDemandVector);

    /** Generate demand for a given (Gaussian) distribution. */
    GeneratedDemandVector_T* generateDemand (const int K,
                                             const double& iMean,
                                             const double& iDeviation);

    /** Sum the two generated demand vectors . */
    GeneratedDemandVector_T* generateDemand (GeneratedDemandVector_T*,
                                             GeneratedDemandVector_T*);
    
    /** Read the input data from a file. */
    void readFromInputFile (const std::string& iInputFileName);

    /** Build the context with the generated demand for Monte-Carlo
       Integration algorithm. */
    void buildContextForMC (const int K);

    /** Clear the context (cabin capacity, bucket holder). */
    void reset ();
    
    /** Get the internal BucketHolder. */
    BucketHolder* getBucketHolder() const {
      return _bucketHolder;
    }

    /** Get the StudyStatManager. */
    StudyStatManager* getStudyStatManager () const {
      return _studyStatManager;
    }

    /** Get the capacity. */
    ResourceCapacity_T getCapacity() const {
      return _capacity;
    }

  public:
    /** Set up the StudyStatManager. */
    void setUpStudyStatManager ();
    
  private:
    /** Internal pointer on BucketHolder. */
    BucketHolder* _bucketHolder;

    /** Resource Capacity. */
    ResourceCapacity_T _capacity;

    /** Statistic Manager. */
    StudyStatManager* _studyStatManager;

    /** Holder of the generated demand vectors. */
    GeneratedDemandVectorHolder_T _generatedDemandVectorHolder;
  };

}
#endif // __RMOL_SVC_RMOL_SERVICE_CONTEXT_HPP
