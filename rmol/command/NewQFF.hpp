#ifndef __RMOL_COMMAND_NEWQFF_HPP
#define __RMOL_COMMAND_NEWQFF_HPP

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
  class FareFamily;
  class SegmentSnapshotTable;
}

namespace RMOL {
  /** Class wrapping the forecasting algorithms. */
  class NewQFF {
  public:
    /**
     * Forecast demand for a segment-cabin.
     */
    static bool forecast (stdair::SegmentCabin&, const stdair::Date_T&,
                          const stdair::DTD_T&,
                          const stdair::UnconstrainingMethod&,
                          const stdair::NbOfSegments_T&);
    
  private:
    /**
     * Forecast demand for a fare family
     */
    static void forecast (stdair::FareFamily&,
                          const stdair::Date_T&,
                          const stdair::DTD_T&,
                          const stdair::UnconstrainingMethod&,
                          const stdair::NbOfSegments_T&,
                          const stdair::SegmentSnapshotTable&);

    /**
     * Prepare the historical price-oriented booking figures for a given cabin
     */
    static void preparePriceOrientedHistoricalBooking
    (const stdair::FareFamily&, const stdair::SegmentSnapshotTable&,
     HistoricalBookingHolder&, const stdair::DCP_T&, const stdair::DCP_T&,
     const stdair::NbOfSegments_T&, const stdair::NbOfSegments_T&,
     const stdair::BookingClassSellUpCurveMap_T&); 

    /**
     * Dispatch the demand forecast to the policies.
     */
    static void dispatchDemandForecastToPolicies (const stdair::SegmentCabin&);

    /**
     * Dispatch the demand forecast to the policy.
     */
    static void dispatchDemandForecastToPolicy (stdair::Policy&);
  };
}
#endif // __RMOL_COMMAND_NEWQFF_HPP
