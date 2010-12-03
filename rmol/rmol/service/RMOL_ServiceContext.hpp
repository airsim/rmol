#ifndef __RMOL_SVC_RMOL_SERVICE_CONTEXT_HPP
#define __RMOL_SVC_RMOL_SERVICE_CONTEXT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// Boost
#include <boost/shared_ptr.hpp>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_maths_types.hpp>
// RMOL
#include <rmol/RMOL_Types.hpp>
#include <rmol/service/ServiceAbstract.hpp>

// Forward declarations
namespace stdair {
  class STDAIR_Service;
}

namespace RMOL {

  /** Forward declaration. */
  class BucketHolder;
  class StudyStatManager;

  /** Pointer on the STDAIR Service handler. */
  typedef boost::shared_ptr<stdair::STDAIR_Service> STDAIR_ServicePtr_T;
  

  /** Inner class holding the context for the RMOL Service object. */
  class RMOL_ServiceContext : public ServiceAbstract {
    /** The RMOL_Service class should be the sole class to get access to
        ServiceContext content: general users do not want to bother
        with a context interface. */
    friend class RMOL_Service;
    friend class FacRmolServiceContext;

  public:
    // ///////// Getters //////////
    /** Get the airline code. */
    const stdair::AirlineCode_T& getAirlineCode () const {
      return _airlineCode;
    }

    
    // ///////// Setters //////////
    /** Set the airline code. */
    void setAirlineCode (const stdair::AirlineCode_T& iAirlineCode) {
      _airlineCode = iAirlineCode;
    }

    
  public:
    /** Set up the StudyStatManager. */
    void setUpStudyStatManager ();

    
  private:
    // /////// Construction / initialisation ////////
    /** Constructors. */
    RMOL_ServiceContext ();
    RMOL_ServiceContext (const RMOL_ServiceContext&);
    RMOL_ServiceContext (const stdair::AirlineCode_T&);
    RMOL_ServiceContext (const stdair::AirlineCode_T&,
                         const ResourceCapacity_T);
    void init (const ResourceCapacity_T);
    
    /** Initialise the StudyStatManager. */
    void initStudyStatManager ();
    
    /** Destructor. */
    ~RMOL_ServiceContext();

  private:    
    /** Set the pointer on the STDAIR service handler. */
    void setSTDAIR_Service (STDAIR_ServicePtr_T ioSTDAIR_ServicePtr) {
      _stdairService = ioSTDAIR_ServicePtr;
    }

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
                                             const stdair::MeanValue_T&,
                                             const stdair::StdDevValue_T&);

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

    
  private:
    // ///////////// Children ////////////
    /** Standard Airline (StdAir) Service Handler. */
    STDAIR_ServicePtr_T _stdairService;

    
  private:
    // //////////// Attributes //////////////////
    /** Internal pointer on BucketHolder. */
    BucketHolder* _bucketHolder;

    /** Statistic Manager. */
    StudyStatManager* _studyStatManager;

    /** Code of the airline owner of the revenue management system. */
    stdair::AirlineCode_T _airlineCode;
    
    /** Resource Capacity. */
    ResourceCapacity_T _capacity;

    /** Holder of the generated demand vectors. */
    GeneratedDemandVectorHolder_T _generatedDemandVectorHolder;
  };

}
#endif // __RMOL_SVC_RMOL_SERVICE_CONTEXT_HPP
