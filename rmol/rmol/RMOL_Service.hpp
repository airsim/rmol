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

    /** Single resource optimization using the Monte Carlo algorithm. */
    void optimalOptimisationByMCIntegration (const int K);

    /** Single resource optimization that uses Monte-Carlo algorithm and
        returns a vector of cumulated booking limits. */
    void optimalOptimisationByMCIntegration (const int K,
                                             BookingLimitVector_T&);

    /** Single resource optimization using dynamic programming. */
    void optimalOptimisationByDP ();

    /** Single resource optimization that uses dynamic programming and
        returns a vector of cumulated booking limits. */
    void optimalOptimisationByDP (BookingLimitVector_T&);

    /** Single resource optimization using EMSR heuristic. */
    void heuristicOptimisationByEmsr ();

    /** Single resource optimization that uses EMSR heuristic and
        returns a vector of cumulated booking limits. */
    void heuristicOptimisationByEmsr (BookingLimitVector_T&);
    
    /** Single resource optimization using EMSR-a heuristic. */
    void heuristicOptimisationByEmsrA ();

    /** Single resource optimization that uses EMSR-a heuristic and
        returns a vector of cumulated booking limits. */
    void heuristicOptimisationByEmsrA (BookingLimitVector_T&);
    
    /** Single resource optimization using EMSR-b heuristic. */
    void heuristicOptimisationByEmsrB ();

    /** Single resource optimization that uses EMSR-b heuristic and
        returns a vector of cumulated booking limits. */
    void heuristicOptimisationByEmsrB (BookingLimitVector_T&);

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
