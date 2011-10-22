#ifndef __RMOL_COMMAND_FORECASTER_HPP
#define __RMOL_COMMAND_FORECASTER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
<<<<<<< HEAD
// RMOL
#include <rmol/RMOL_Types.hpp>
#include <rmol/RMOL_FORECASTER_Types.hpp>

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

    /** 
    An accessory algorithm for demand forecasting.

    Calculate Q-equivalent demands for the given group of 
    classes/buckets/fare points using the given 
    sell-up factors.

    Q-equivalent demands are, by definition, 
    
       SUM_{buckets} histBooking_{bucket i} / ProbSellup_{bucket i} 
            where 
         ProbSellup_{bucket i} = 
         EXP(-sellupfactor*(yield_{bucket i}/lowest yield_{buckets}))
    static void qEquivalentBookingCalculation
                                (BucketHolder&, 
                                 SellupFactorHolder_T&,
                                 HistoricalBookingHolderHolder&,
                                 HolderOfQEquivalentDemandsPerSimilarFlight_T&);
     */

    /** A forecasting method developed by Belobaba and Hopperstad:
        Algorithms for Revenue Management in Unrestricted Fare Markets, 
        AGIFORS, Auckland, New Zealand, Jan 2004
     */
    static void demandForecastByQForecasting (ForecastedDemandParameterList_T, 
                                              HistoricalDataHolderHolder_T&,
                                              PriceHolder_T&);
=======
// STL
#include <map>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
// RMOL
#include <rmol/RMOL_Types.hpp>

// Forward declarations
namespace stdair {
  class FlightDate;
  class SegmentCabin;
  class GuillotineBlock;
}

namespace RMOL {
  /** Class wrapping the optimisation algorithms. */
  class Forecaster {    
  public:
    /**
     * Forecast demand for  a flight-date using additive pick-up method.
    */
    static bool forecastUsingAdditivePickUp (stdair::FlightDate&,
                                             const stdair::DateTime_T&);
    
    /**
     * Forecast demand for  a flight-date using multiplicative pick-up method.
    */
    static bool forecastUsingMultiplicativePickUp (stdair::FlightDate&,
                                                   const stdair::DateTime_T&);


  private:
    /**
     * Forecast demand for a segment-cabin using addtive pick-up method.
     */
    static bool forecastUsingAdditivePickUp (stdair::SegmentCabin&,
                                             const stdair::DCPList_T&,
                                             const stdair::Date_T&);

    /**
     * Forecast product-oriented and price-oriented demand given the
     * unconstrained demand of historical segments.
     */
    static void forecastUsingAdditivePickUp (stdair::SegmentCabin&,
                                             const BookingClassUnconstrainedDemandVectorMap_T&, const UnconstrainedDemandVector_T&, const double&);
    
    /**
     * Forecast demand for a segment-cabin using addtive pick-up method.
     */
    static bool forecastUsingMultiplicativePickUp (stdair::SegmentCabin&,
                                                   const stdair::Date_T&,
                                                   const stdair::DTD_T&);
    /**
     * Forecast demand between two DCP's.
     */
    static void forecastUsingMultiplicativePickUp(const stdair::SegmentCabin&,
                                                  BookingClassUnconstrainedDemandVectorMap_T&,
                                                  UnconstrainedDemandVector_T&,
                                                  const stdair::DCP_T&,
                                                  const stdair::DCP_T&,
                                                  const stdair::Date_T&,
                                                  const stdair::NbOfSegments_T&);
    
    /**
     * Forecast the product-oriented demand for a given class ou
     * Q-equivalent class. */
    static void forecastUsingMultiplicativePickUp(const stdair::GuillotineBlock&,
                                                  UnconstrainedDemandVector_T&,
                                                  const stdair::DCP_T&,
                                                  const stdair::DCP_T&,
                                                  const stdair::NbOfSegments_T&,
                                                  const stdair::BlockIndex_T&,
                                                  const stdair::NbOfSegments_T&);

    /**
     * Forecast product-oriented and price-oriented demand given the
     * unconstrained demand of historical segments.
     */
    static bool forecastUsingMultiplicativePickUp(stdair::SegmentCabin&,
                                                  const BookingClassUnconstrainedDemandMap_T&,
                                                  const stdair::NbOfRequests_T&,
                                                  const double&);

    /**
     * Set the remaining demand forecast to zero for departed segment.
     */
    static void setRemainingDemandForecastToZero (const stdair::SegmentCabin&);
>>>>>>> 0.24
  };
}
#endif // __RMOL_COMMAND_FORECASTER_HPP
