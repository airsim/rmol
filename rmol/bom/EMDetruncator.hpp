#ifndef __RMOL_BOM_EMDETRUNCATOR_HPP
#define __RMOL_BOM_EMDETRUNCATOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
namespace RMOL {
  // Forward declarations.
  struct HistoricalBookingHolder;

  /** Utility for the Expectation-Maximisation algorithm. */
  class EMDetruncator {
  public:
    /** Unconstrain the censored booking data using the Expection-Maximisation
        algorithm. */
    static void unconstrain (HistoricalBookingHolder&);
  };
}
#endif // __RMOL_BOM_EMDETRUNCATOR_HPP
