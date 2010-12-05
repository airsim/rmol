#ifndef __RMOL_SVC_RMOL_SERVICE_HPP
#define __RMOL_SVC_RMOL_SERVICE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/basic/BasLogParams.hpp>
// RMOL
#include <rmol/RMOL_Types.hpp>
#include <rmol/RMOL_FORECASTER_Types.hpp>
#include <rmol/RMOL_UNCONSTRAINER_Types.hpp>
#include <rmol/RMOL_UTILITY_Types.hpp>

namespace RMOL {

  /** Forward declaration. */
  class RMOL_ServiceContext;

  /** Interface for the RMOL Services. */
  class RMOL_Service {
  public:
    // /////////// Business Methods /////////////
    /** Single resource optimization using the Monte Carlo algorithm. */
    void optimalOptimisationByMCIntegration (const int K);

    /** Single resource optimization that uses Monte-Carlo algorithm and
        returns a vector of cumulated booking limits. */
    void optimalOptimisationByMCIntegration (const int K,
                                             ProtectionLevelVector_T&,
                                             BidPriceVector_T&,
                                             BookingLimitVector_T&);

    /** Single resource optimization using dynamic programming. */
    void optimalOptimisationByDP ();

    /** Single resource optimization that uses dynamic programming and
        returns a vector of cumulated booking limits. */
    void optimalOptimisationByDP(ProtectionLevelVector_T&,BookingLimitVector_T&);

    /** Single resource optimization using EMSR heuristic. */
    void heuristicOptimisationByEmsr ();

    /** Single resource optimization that uses EMSR heuristic and
        returns a bid-price vector and a vector of cumulated booking limits. */
    void heuristicOptimisationByEmsr (BidPriceVector_T&, 
                                      ProtectionLevelVector_T&,
                                      BookingLimitVector_T&);
    
    /** Single resource optimization using EMSR-a heuristic. */
    void heuristicOptimisationByEmsrA ();

    /** Single resource optimization that uses EMSR-a heuristic and
        returns a vector of cumulated booking limits. */
    void heuristicOptimisationByEmsrA (BidPriceVector_T&, 
                                       ProtectionLevelVector_T&,
                                       BookingLimitVector_T&);

    /** Single resource optimization with sellup using EMSR-a heuristic. */
    void heuristicOptimisationByEmsrAwithSellup (SellupProbabilityVector_T&);

    /** Single resource optimization with sellup that uses EMSR-a heuristic and
        returns a vector of cumulated booking limits. */
    void heuristicOptimisationByEmsrAwithSellup (SellupProbabilityVector_T&,
                                                 ProtectionLevelVector_T&,
                                                 BidPriceVector_T&, 
                                                 BookingLimitVector_T&);
    
    /** Single resource optimization using EMSR-b heuristic. */
    void heuristicOptimisationByEmsrB ();

    /** Single resource optimization that uses EMSR-b heuristic and
        returns a vector of cumulated booking limits. */
    void heuristicOptimisationByEmsrB (BidPriceVector_T&, 
                                       ProtectionLevelVector_T&,
                                       BookingLimitVector_T&);

    /** Leg optimisation using Monte-Carlo Integration as a step in
        network optimisation. */
    void legOptimisationByMC ();
    
    /** Leg optimisation using Monte-Carlo Integration as a step in
        network optimisation. */
    void legOptimisationByMC (BidPriceVector_T&, 
                              ProtectionLevelVector_T&,
                              BookingLimitVector_T&);

    /** Data unconstraining by Expectation Maximization */
    void dataUnconstrainingByExpectationMaximization 
                      (ConstrainedDataHolder_T& ioConstrainedDataHolder, 
                       UnconstrainedDataHolder_T& iUnconstrainedDataHolder, 
                       StoppingCriterion_T& iStoppingCriterion);

    /** Demand forecast using Q-Forecasting */
    void demandForecastByQForecasting (ForecastedDemandParameterList_T&, 
                                       HistoricalDataHolderHolder_T&, 
                                       PriceHolder_T&,
                                       SellupFactorHolder_T&);

    
    // ////////// Constructors and destructors //////////
    /** Constructor.
        <br>The init() method is called; see the corresponding documentation
        for more details.
        <br>Moreover, a reference on an output stream is given, so
        that log outputs can be directed onto that stream.       
        @param const stdair::BasLogParams& Parameters for the output log
               stream.
        @param AirlineCode_T& Code of the owner airline. */
    RMOL_Service (const stdair::BasLogParams&, const stdair::AirlineCode_T&);

    /** Constructor.
        <br>The init() method is called; see the corresponding documentation
        for more details.
        <br>Moreover, as no reference on any output stream is given,
        it is assumed that the StdAir log service has already been
        initialised with the proper log output stream by some other
        methods in the calling chain (for instance, when the RMOL_Service
        is itself being initialised by another library service such as
        AIRINV_Service).
        @param AirlineCode_T& Code of the owner airline. */
    RMOL_Service (const stdair::AirlineCode_T&);

    /** Constructor.
        <br>The init() method is called; see the corresponding documentation
        for more details.
        <br>Moreover, a reference on an output stream is given, so
        that log outputs can be directed onto that stream.       
        @param const stdair::BasLogParams& Parameters for the output log stream.
        @param AirlineCode_T& Code of the owner airline.
        @param const ResourceCapacity_T Capacity of the resource to optimise. */
    RMOL_Service (const stdair::BasLogParams&, const stdair::AirlineCode_T&,
                  const ResourceCapacity_T);
    
    /** Constructor.
        <br>The init() method is called; see the corresponding documentation
        for more details.
        <br>Moreover, as no reference on any output stream is given,
        it is assumed that the StdAir log service has already been
        initialised with the proper log output stream by some other
        methods in the calling chain (for instance, when the RMOL_Service
        is itself being initialised by another library service such as
        AIRINV_Service).
        @param AirlineCode_T& Code of the owner airline.
        @param const ResourceCapacity_T Capacity of the resource to optimise. */
    RMOL_Service (const stdair::AirlineCode_T&, const ResourceCapacity_T);
    
    /** Destructor. */
    ~RMOL_Service();

    
    // //////// Initialisation support methods ///////////
    /** Set up the StudyStatManager. */
    void setUpStudyStatManager ();

    /** Set the cabin availability. */
    void setResourceCapacity (const ResourceCapacity_T iResourceCapacity);

    /** Add a bucket to the context. */
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

    
  private:
    // /////// Construction and Destruction helper methods ///////
    /** Default constructor. */
    RMOL_Service ();
    /** Default copy constructor. */
    RMOL_Service (const RMOL_Service&);

    /** Initialise the (RMOL) service context (i.e., the
        RMOL_ServiceContext object).
        @param AirlineCode_T& Code of the owner airline. */
    void initServiceContext (const stdair::AirlineCode_T&);

    /** Initialise the (RMOL) service context (i.e., the
        RMOL_ServiceContext object).
        @param AirlineCode_T& Code of the owner airline.
        @param const ResourceCapacity_T Capacity of the resource to optimise. */
    void initServiceContext (const stdair::AirlineCode_T&,
                             const ResourceCapacity_T);
    
    /** Initialise the STDAIR service (including the log service). */
    void initStdAirService (const stdair::BasLogParams&);
    
    /** Initialise.
        @param AirlineCode_T& Code of the owner airline. */
    void init (const stdair::AirlineCode_T&);

    /** Initialise.
        @param AirlineCode_T& Code of the owner airline.
        @param const ResourceCapacity_T Capacity of the resource to optimise. */
    void init (const stdair::AirlineCode_T&, const ResourceCapacity_T);
    
    /** Finaliser. */
    void finalise ();

  private:
    // ////////// Service Context //////////
    /** Service Context. */
    RMOL_ServiceContext* _rmolServiceContext;
  };
}
#endif // __RMOL_SVC_RMOL_SERVICE_HPP
