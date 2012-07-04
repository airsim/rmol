#ifndef __RMOL_COMMAND_OLDQFF_HPP
#define __RMOL_COMMAND_OLDQFF_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/PolicyTypes.hpp>
// RMOL
#include <rmol/RMOL_Types.hpp>

// Forward declarations
namespace stdair {
  class SegmentCabin;
  class SegmentSnapshotTable;
}

namespace RMOL {
  /** Class wrapping the forecasting algorithms. */
  class OldQFF {    
  public: 
    /**
     * Forecast demand for a segment cabin.
     *
     * @param stdair::SegmentCabin& Current Segment Cabin
     * @param const stdair::Date_T& Current Date
     * @param const stdair::DTD_T& Current DTD 
     * @param const stdair::UnconstrainingMethod& Method used for the unconstraining
     * @param const stdair::NbOfSegments_T& Number of usable historical segments
    */
    static bool forecast (stdair::SegmentCabin&, const stdair::Date_T&,
                          const stdair::DTD_T&,
                          const stdair::UnconstrainingMethod&,
                          const stdair::NbOfSegments_T&);

  private:
    /**
     * Prepare the historical price-oriented booking figures for a given cabin
     *
     * @param const stdair::DCP_T& DCP range start
     * @param const stdair::DCP_T& DCP range end
     * @param const stdair::NbOfSegments_T& Segment range start index
     * @param const stdair::NbOfSegments_T& Segment range end index 
     */
    static void prepareHistoricalBooking (const stdair::SegmentCabin&,
                                          const stdair::SegmentSnapshotTable&,
                                          HistoricalBookingHolder&,
                                          const stdair::DCP_T&,
                                          const stdair::DCP_T&,
                                          const stdair::NbOfSegments_T&,
                                          const stdair::NbOfSegments_T&,
                                          const stdair::BookingClassSellUpCurveMap_T&);

    /**
     * Dispatch the demand forecast to the policies.
     */
    static void 
    dispatchDemandForecastToPolicies (const stdair::PolicyList_T&,
                                      const stdair::DCP_T&,
                                      const stdair::MeanValue_T&, 
                                      const stdair::StdDevValue_T&,
                                      const stdair::BookingClassSellUpCurveMap_T&);

    /**
     * Dispatch the demand forecast to the policy.
     */
    static void 
    dispatchDemandForecastToPolicy (stdair::Policy&,
                                    const stdair::DCP_T&,
                                    const stdair::MeanValue_T&,
                                    const stdair::StdDevValue_T&,
                                    const stdair::BookingClassSellUpCurveMap_T&);
  };
}
#endif // __RMOL_COMMAND_OLDQFF_HPP
