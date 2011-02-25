#ifndef __RMOL_SVC_RMOL_SERVICE_HPP
#define __RMOL_SVC_RMOL_SERVICE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/stdair_service_types.hpp>
// RMOL
#include <rmol/RMOL_FORECASTER_Types.hpp>
#include <rmol/RMOL_UNCONSTRAINER_Types.hpp>
#include <rmol/RMOL_UTILITY_Types.hpp>

// Forward declaration
namespace stdair {
  struct BasLogParams;
}

namespace RMOL {

  /** Forward declaration. */
  class RMOL_ServiceContext;

  /** Interface for the RMOL Services. */
  class RMOL_Service {
  public:
    // /////////// Business Methods /////////////
    /** Single resource optimization using the Monte Carlo algorithm. */
    void optimalOptimisationByMCIntegration (const int K);

    /** Single resource optimization using dynamic programming. */
    void optimalOptimisationByDP ();

    /** Single resource optimization using EMSR heuristic. */
    void heuristicOptimisationByEmsr ();
    
    /** Single resource optimization using EMSR-a heuristic. */
    void heuristicOptimisationByEmsrA ();

    /** Single resource optimization using EMSR-b heuristic. */
    void heuristicOptimisationByEmsrB ();

    // ////////// Constructors and destructors //////////
    /** Constructor.
        <br>The init() method is called; see the corresponding documentation
        for more details.
        <br>Moreover, a reference on an output stream is given, so
        that log outputs can be directed onto that stream.       
        @param const stdair::BasLogParams& Parameters for the output log
               stream.
        @param stdair::CabinCapacity& Capacity of the cabin. */
    RMOL_Service (const stdair::BasLogParams&, const stdair::CabinCapacity_T&);

    /** Constructor.
        <br>The init() method is called; see the corresponding documentation
        for more details.
        <br>Moreover, a reference on an output stream is given, so
        that log outputs can be directed onto that stream.       
        @param const stdair::BasLogParams& Parameters for the output log
               stream. */
    RMOL_Service (const stdair::BasLogParams&);

    /** Constructor.
        <br>The init() method is called; see the corresponding documentation
        for more details.
        <br>Moreover, as no reference on any output stream is given,
        it is assumed that the StdAir log service has already been
        initialised with the proper log output stream by some other
        methods in the calling chain (for instance, when the RMOL_Service
        is itself being initialised by another library service such as
        AIRINV_Service).
        @param STDAIR_ServicePtr_T the shared pointer of stdair service. */
    RMOL_Service (stdair::STDAIR_ServicePtr_T);
        
    /** Destructor. */
    ~RMOL_Service();

    // //////// Initialisation support methods ///////////
    /** Set up the StudyStatManager. */
    void setUpStudyStatManager ();
    
    /** Read the input data from a file. */
    void readFromInputFile (const std::string& iInputFileName);

    /** Clear the context (cabin capacity, bucket holder). */
    void reset ();

    
  private:
    // /////// Construction and Destruction helper methods ///////
    /** Default constructor. */
    RMOL_Service ();
    /** Default copy constructor. */
    RMOL_Service (const RMOL_Service&);

    /** Initialise the (RMOL) service context (i.e., the
        RMOL_ServiceContext object). */
    void initServiceContext ();
    
    /** Initialise the STDAIR service (including the log service). */
    void initStdAirService (const stdair::BasLogParams&);

    /** Attach the STDAIR service (holding the log and database services) to
        the RMOL_Service.
        @param stdair::STDAIR_ServicePtr_T Reference on the STDAIR service. */
    void addStdAirService (stdair::STDAIR_ServicePtr_T);

    /** Build a dummy inventory with one leg-cabin which has the given capacity.
        For optimisation demo. */
    void buildInventorySample (const stdair::CabinCapacity_T&);
    
    /** Finaliser. */
    void finalise ();

  private:
    // ////////// Service Context //////////
    /** Service Context. */
    RMOL_ServiceContext* _rmolServiceContext;
  };
}
#endif // __RMOL_SVC_RMOL_SERVICE_HPP
