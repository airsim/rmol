#ifndef __RMOL_BOM_QEQUIVQLENTBOOKINGCALCULATOR_HPP
#define __RMOL_BOM_QEQUIVQLENTBOOKINGCALCULATOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL Bom
#include <rmol/bom/BomAbstract.hpp>
#include <rmol/RMOL_Types.hpp>

namespace RMOL {

  // Forward declaration
  struct HistoricalBookingHolderHolder;

  /** Accessary Class for Sellup considered forecast methods. */
  class QEquivalentBookingCalculator : public BomAbstract {

  public:

    /** Calculate Q-equivalent bookings probability for given sell-up 
        probabilities.<br> 
        The formular was proposed by Belobaba and Hopperstad:
        Algorithms for Revenue Management in Unrestricted Fare Markets, 
        AGIFORS, Auckland, New Zealand, Jan 2004    */
    static void calculateQEquivalentBooking 
    (HistoricalBookingHolderHolder&, 
     SellupProbabilityVector_T&, 
     HolderOfQEquivalentBookingsPerSimilarFlight_T&);
  };

}
#endif // __RMOL_BOM_QEQUIVQLENTBOOKINGCALCULATOR_HPP
