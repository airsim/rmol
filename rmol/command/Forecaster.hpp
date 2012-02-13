#ifndef __RMOL_COMMAND_FORECASTER_HPP
#define __RMOL_COMMAND_FORECASTER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
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
    static bool forecastUsingAddPkUp (stdair::FlightDate&,
                                      const stdair::DateTime_T&);

  private:
    /**
     * Forecast demand for a segment-cabin using addtive pick-up method.
     */
    static bool forecastUsingAddPkUp (stdair::SegmentCabin&,
                                      const stdair::Date_T&);

    /**
     * Distribute the unconstrained Q-equivalent demand into the classes.
     */
    static void distributeQEquiUncDemToClasses (stdair::UncDemCurveHolder_T&,
                                                stdair::BookingClassUncDemCurveHolderMap_T&,
                                                const stdair::BookingClassList_T&);

  
    
    /**
     * Precompute the sell-up factors for each class and each DCP.
     */
    static stdair::BookingClassSellUpCurveMap_T computeSellUpFactorCurves (const stdair::SellUpCurve_T&, const stdair::BookingClassList_T&);
    
    /**
     * Set the achievable demand forecast to zero for departed segment.
     */
    static void setAchievableDemandForecastToZero (const stdair::SegmentCabin&);
  };
}
#endif // __RMOL_COMMAND_FORECASTER_HPP
