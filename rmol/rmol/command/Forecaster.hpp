#ifndef __RMOL_COMMAND_FORECASTER_HPP
#define __RMOL_COMMAND_FORECASTER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/RMOL_Types.hpp>
#include <rmol/bom/HistoricalBookingHolderHolder.hpp>
namespace RMOL {

  /** Forward declarations. */
  class BucketHolder;
  struct HistoricalBookingHolderHolder;
  //  class StudyStatManager;

  /** Class wrapping the principal forecasting algorithms and 
      some accessory algorithms for demand forecasting. */
  class Forecaster {
  public:
    
    /** 
    An accessory algorithm for demand forecasting.

    Calculate Q-equivalent bookings for the given group of 
    classes/buckets/fare points using the given 
    sell-up factors.

    Q-equivalent bookings are, by definition, 
    
       SUM_{buckets} histBooking_{bucket i} / ProbSellup_{bucket i} 
            where 
         ProbSellup_{bucket i} = 
         EXP(-sellupfactor*(yield_{bucket i}/lowest yield_{buckets}))
     */
    static void qEquivalentBookingCalculation
                                (BucketHolder&, 
                                 SellupFactorHolder_T&,
                                 HistoricalBookingHolderHolder&,
                                 HolderOfQEquivalentBookingsPerSimilarFlight_T&);
  };
}
#endif // __RMOL_COMMAND_FORECASTER_HPP
