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
  /** Class wrapping the optimisation algorithms. */
  class Forecaster {    
  public:
    /**
     * Forecast demand for  a flight-date.
    */
    static bool forecast (stdair::FlightDate&, const stdair::DateTime_T&);

  private:
    /**
     * Build the list of remaining DCP's for the segment-date.
     */
    static stdair::DCPList_T buildRemainingDCPList (const stdair::DTD_T&);

    /**
     * Forecast demand for a segment-cabin.
     */
    static bool forecast (stdair::SegmentCabin&, const stdair::DCPList_T&,
                          const stdair::Date_T&);

    /**
     * Forecast product-oriented and price-oriented demand given the
     * unconstrained demand of historical segments.
     */
    static void forecast (stdair::SegmentCabin&,
                          const BookingClassUnconstrainedDemandMap_T&,
                          const UnconstrainedDemandVector_T&, const double&);

    /**
     * Set the remaining demand forecast to zero for departed segment.
     */
    static void setRemainingDemandForecastToZero (const stdair::SegmentCabin&);

    /**
     * Retrieve the number of departed similar segments.
     */
    static stdair::NbOfSegments_T getNbOfDepartedSimilarSegments (const stdair::SegmentCabin&, const stdair::Date_T&);
  };
}
#endif // __RMOL_COMMAND_FORECASTER_HPP
