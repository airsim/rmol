#ifndef __RMOL_COMMAND_FORECASTERFOROLDQFF_HPP
#define __RMOL_COMMAND_FORECASTERFOROLDQFF_HPP

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
  /** Class wrapping the forecasting algorithms. */
  class ForecasterForOldQFF {    
  public:
    /**
     * Forecast demand for a flight-date using old Q-FF method.
      */
    static bool forecast (stdair::FlightDate&,
                                      const stdair::DateTime_T&);

  private:
    /**
     * Forecast demand for a segment-cabin using old Q-FF method.
     */
    static bool forecast (stdair::SegmentCabin&,
                                      const stdair::Date_T&,
                                      const stdair::SegmentDate&);

    /**
     * Set the achievable demand forecast to zero for departed segment.
     */
    static void setAchievableDemandForecastToZero (const stdair::SegmentCabin&);

  };
}
#endif // __RMOL_COMMAND_FORECASTERFOROLDQFF_HPP
