#ifndef __RMOL_SVC_RMOL_SERVICE_HPP
#define __RMOL_SVC_RMOL_SERVICE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// RMOL
#include <rmol/RMOL_Types.hpp>
#include <rmol/RMOL_FORECASTER_Types.hpp>

namespace RMOL {

  /** Forward declaration. */
  class RMOL_ServiceContext;

  /** Interface for the RMOL Services. */
  class RMOL_Service {
  public:
    /** Constructor. */
    RMOL_Service (std::ostream& ioLogStream);

    RMOL_Service (std::ostream& ioLogStream,
                  const ResourceCapacity_T iResourceCapacity);
    /** Destructor. */
    ~RMOL_Service();

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

    /** Single resource optimization using the Monte Carlo algorithm. */
    void optimalOptimisationByMCIntegration (const int K);

    /** Single resource optimization that uses Monte-Carlo algorithm and
        returns a vector of cumulated booking limits. */
    void optimalOptimisationByMCIntegration (const int K,
                                             BidPriceVector_T&,
                                             BookingLimitVector_T&);

    /** Single resource optimization using dynamic programming. */
    void optimalOptimisationByDP ();

    /** Single resource optimization that uses dynamic programming and
        returns a vector of cumulated booking limits. */
    void optimalOptimisationByDP (BookingLimitVector_T&);

    /** Single resource optimization using EMSR heuristic. */
    void heuristicOptimisationByEmsr ();

    /** Single resource optimization that uses EMSR heuristic and
        returns a bid-price vector and a vector of cumulated booking limits. */
    void heuristicOptimisationByEmsr (BidPriceVector_T&, BookingLimitVector_T&);
    
    /** Single resource optimization using EMSR-a heuristic. */
    void heuristicOptimisationByEmsrA ();

    /** Single resource optimization that uses EMSR-a heuristic and
        returns a vector of cumulated booking limits. */
    void heuristicOptimisationByEmsrA (BidPriceVector_T&, BookingLimitVector_T&);

    /** Single resource optimization with sellup using EMSR-a heuristic. */
    void heuristicOptimisationByEmsrAwithSellup (SellupProbabilityVector_T&);

    /** Single resource optimization with sellup that uses EMSR-a heuristic and
        returns a vector of cumulated booking limits. */
    void heuristicOptimisationByEmsrAwithSellup (SellupProbabilityVector_T&,
                                                 BidPriceVector_T&, 
                                                 BookingLimitVector_T&);
    
    /** Single resource optimization using EMSR-b heuristic. */
    void heuristicOptimisationByEmsrB ();

    /** Single resource optimization that uses EMSR-b heuristic and
        returns a vector of cumulated booking limits. */
    void heuristicOptimisationByEmsrB (BidPriceVector_T&, BookingLimitVector_T&);

    /** Leg optimisation using Monte-Carlo Integration as a step in
        network optimisation. */
    void legOptimisationByMC ();
    
    /** Leg optimisation using Monte-Carlo Integration as a step in
        network optimisation. */
    void legOptimisationByMC (BidPriceVector_T&, BookingLimitVector_T&);

    /** Demand unconstraining by Expectation Maximization */
    void demandUnconstrainingByExpectationMaximization ();

    /** Demand forecast using Q-Forecasting [used in unit tests] */
    void demandForecastByQForecasting (HistoricalDataHolderHolder_T&, 
                                       PriceHolder_T&);

    /** Demand forecast using Q-Forecasting */
    void demandForecastByQForecasting (ForecastedDemandParameterList_T, 
                                       HistoricalDataHolderHolder_T&, 
                                       PriceHolder_T&,
                                       SellupFactorHolder_T&);

  private:
    /** Default Constructors. */
    RMOL_Service ();
    RMOL_Service (const RMOL_Service&);

    /** Initialise. */
    void init (std::ostream& ioLogStream);

    void init (std::ostream& ioLogStream,
               const ResourceCapacity_T iResourceCapacity);
    
    /** Initilise the log. */
    void logInit (const LOG::EN_LogLevel iLogLevel, std::ostream& ioLogStream);

    /** Finaliser. */
    void finalise ();

  private:
    // ////////// Service Context //////////
    /** Service Context. */
    RMOL_ServiceContext* _rmolServiceContext;
  };
}
#endif // __RMOL_SVC_RMOL_SERVICE_HPP
