#ifndef __RMOL_COMMAND_QFORECASTING_HPP
#define __RMOL_COMMAND_QFORECASTING_HPP

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
    */
    static bool forecast (stdair::SegmentCabin&,
                          const stdair::Date_T&, const stdair::DTD_T&,
                          const stdair::UnconstrainingMethod::EN_UnconstrainingMethod&,
                          const stdair::NbOfSegments_T&);
    
    /**
     * Prepare the historical price-oriented booking figures for a given cabin
     */
    static void preparePriceOrientedHistoricalBooking
    (const stdair::SegmentCabin&, const stdair::SegmentSnapshotTable&,
     HistoricalBookingHolder&, const stdair::DCP_T&, const stdair::DCP_T&,
     const stdair::NbOfSegments_T&, const stdair::NbOfSegments_T&,
     const stdair::BookingClassSellUpCurveMap_T&);
  };
}
#endif // __RMOL_COMMAND_QFORECASTING_HPP
