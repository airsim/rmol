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
  class RMOL {
  public:
    /** Constructor. */
    RMOL (const ResourceCapacity_T iResourceCapacity);
    /** Destructor. */
    ~RMOL();

    /** Add a bucket to the context. */
    void addBucket (const double iYieldRange, const double iDemandMean,
                    const double iDemandStandardDev);

    /** Read the input data from a file. */
    void readFromInputFile (const std::string& iInputFileName);

    /** */
    void optimalOptimisationByMCIntegration (const int K);

    /** */
    void optimalOptimisationByDP ();

    /** */
    void heuristicOptimisationByEmsr ();
    
    /** */
    void heuristicOptimisationByEmsrA ();
    
    /** */
    void heuristicOptimisationByEmsrB ();

  private:
    /** Default Constructors. */
    RMOL ();
    RMOL (const RMOL&);

    /** Initialiser. */
    void initContext (const ResourceCapacity_T iResourceCapacity);
    
    /** Service Context. */
    ServiceContext* _context;
  };
}
#endif // __RMOL_SVC_RMOL_SERVICE_HPP
