#ifndef __RMOL_COMMAND_QFORECASTING_HPP
#define __RMOL_COMMAND_QFORECASTING_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_inventory_types.hpp>
// RMOL
#include <rmol/RMOL_Types.hpp>

// Forward declarations
namespace stdair {
  class SegmentCabin;
  class SegmentSnapshotTable;
}

namespace RMOL {
  // Forward declarations
  struct HistoricalBookingHolder;
  
  /** Class wrapping the optimisation algorithms. */
  class QForecasting {    
  public:
    /**
     * Forecast demand for a flight-date.
     *
     * @param const stdair::Date_T& Current Date
     * @param const stdair::NbOfSegments_T& Number of usable historical segments
    */
    static bool forecast (stdair::SegmentCabin&,
                          const stdair::Date_T&, const stdair::DTD_T&,
                          const stdair::UnconstrainingMethod&,
                          const stdair::NbOfSegments_T&);
    
    /**
     * Prepare the historical price-oriented booking figures for a given cabin
     *
     * @param const stdair::DCP_T& DCP range start
     * @param const stdair::DCP_T& DCP range end
     * @param const stdair::NbOfSegments_T& Segment range start index
     * @param const stdair::NbOfSegments_T& Segment range end index 
     */
    static void preparePriceOrientedHistoricalBooking
    (const stdair::SegmentCabin&, const stdair::SegmentSnapshotTable&,
     HistoricalBookingHolder&, const stdair::DCP_T&, const stdair::DCP_T&,
     const stdair::NbOfSegments_T&, const stdair::NbOfSegments_T&,
     const stdair::BookingClassSellUpCurveMap_T&);
  };
}
#endif // __RMOL_COMMAND_QFORECASTING_HPP
