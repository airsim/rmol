#ifndef __RMOL_SVC_RMOL_SERVICE_HPP
#define __RMOL_SVC_RMOL_SERVICE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// RMOL
#include <rmol/RmolTypes.hpp>

namespace RMOL {

  /** Forward declaration. */
  class ServiceContext;

  /** Interface for the RMOL Services. */
  class RMOL_Service {
  public:
    /** Constructor. */
    RMOL_Service (const ResourceCapacity_T iResourceCapacity);
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

    /** Initialiser. */
    void initContext (const ResourceCapacity_T iResourceCapacity);
    
    /** Service Context. */
    ServiceContext* _context;
  };
}
#endif // __RMOL_SVC_RMOL_SERVICE_HPP
