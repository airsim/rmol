#ifndef __RMOL_SVC_RMOL_SERVICE_HPP
#define __RMOL_SVC_RMOL_SERVICE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>

namespace RMOL {

  /** Forward declaration. */
  class BucketHolder;

  class RMOL_Service_Context {
    friend class RMOL_Service;

  private:
    /** Constructors. */
    RMOL_Service_Context ();
    RMOL_Service_Context (const RMOL_Service_Context&);
    RMOL_Service_Context (const double iResourceCapacity);
    /** Destructor. */
    ~RMOL_Service_Context();

    /** Set the BucketHolder. */
    void setBucketHolder (BucketHolder* ioBucketHolderPtr) {
      _bucketHolder = ioBucketHolderPtr;
    }

    /** Add a bucket to the BucketHolder. */
    void addBucket (const double iYieldRange, const double iDemandMean,
                    const double iDemandStandardDev);
  private:
    /** Get the internal BucketHolder. */
    BucketHolder* getBucketHolder() const {
      return _bucketHolder;
    }

    /** Get the capacity. */
    double getCapacity() const {
      return _capacity;
    }

  private:
    /** Internal pointer on BucketHolder. */
    BucketHolder* _bucketHolder;

    /** Resource Capacity. */
    double _capacity;
  };

  /** Interface for the RMOL Services. */
  class RMOL_Service {
  public:
    /** Constructor. */
    RMOL_Service (const double iResourceCapacity);
    /** Destructor. */
    ~RMOL_Service();

    /** Add a bucket to the context. */
    void addBucket (const double iYieldRange, const double iDemandMean,
                    const double iDemandStandardDev);

    /** Read the input data from a file. */
    void readFromInputFile (const std::string& iInputFileName);

    /** */
    void optimalOptimisationByMCIntegration (const int K);

  private:
    /** Default Constructors. */
    RMOL_Service ();
    RMOL_Service (const RMOL_Service&);

    /** Service Context. */
    RMOL_Service_Context _context;
  };
}
#endif
