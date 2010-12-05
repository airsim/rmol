#ifndef __RMOL_COMMAND_FORECASTER_HPP
#define __RMOL_COMMAND_FORECASTER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/RMOL_Types.hpp>
#include <rmol/RMOL_FORECASTER_Types.hpp>

namespace RMOL {

  /** Forward declarations. */
  // // class BucketHolder;
  // // struct HistoricalBookingHolderHolder;

  /** Class wrapping the principal forecasting algorithms and 
      some accessory algorithms for demand forecasting. */
  class Forecaster {
  public:
    
  //   Calculate Q-equivalent demands for the given group of 
  //   classes/buckets/fare points using the given 
  //   sell-up factors.

  //   Q-equivalent demands are, by definition, 
    
  //      SUM_{buckets} histBooking_{bucket i} / ProbSellup_{bucket i} 
  //           where 
  //        ProbSellup_{bucket i} = 
  //        EXP(-sellupfactor*(yield_{bucket i}/lowest yield_{buckets}))

  //   static void qEquivalentDemandCalculation
  //                               (SellupFactorHolder_T&,
  //                                HistoricalDataHolderHolder&,
  //                                HolderOfQEquivalentDemandsPerSimilarFlight_T&);
  //   */

    /** A forecasting method developed by Belobaba and Hopperstad:
        Algorithms for Revenue Management in Unrestricted Fare Markets, 
        AGIFORS, Auckland, New Zealand, Jan 2004
          NOTES: Inputs are supposed to be appropriately ordered so that 
          i-th element of the PriceHolder is the price associated to the 
          i-th element of the HistoricalDataHolderHolder.   */
    static void demandForecastByQForecasting (ForecastedDemandParameterList_T&, 
                                              HistoricalDataHolderHolder_T&,
                                              PriceHolder_T&,
                                              SellupFactorHolder_T&);
  };
}
#endif // __RMOL_COMMAND_FORECASTER_HPP
