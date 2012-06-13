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
}

namespace RMOL {
  /** Class wrapping the forecasting algorithms. */
  class Forecaster {    
  public:
    /**
     * Forecast demand for a flight-date.
    */
    static bool forecast (stdair::FlightDate&, const stdair::DateTime_T&,
                          const stdair::UnconstrainingMethod&,
                          const stdair::ForecastingMethod&);

  private:
    /**
     * Forecast demand for a segment-cabin.
     */
    static bool forecast (stdair::SegmentCabin&, const stdair::Date_T&,
                          const stdair::UnconstrainingMethod&,
                          const stdair::ForecastingMethod&);

    /**
     * Set the demand forecasts to zero.
     */
    static void setDemandForecastsToZero (const stdair::SegmentCabin&);

  };
}
#endif // __RMOL_COMMAND_FORECASTER_HPP
