#ifndef __RMOL_BAS_BASCONST_CURVES_HPP
#define __RMOL_BAS_BASCONST_CURVES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/RMOL_Types.hpp>

namespace RMOL {

  /** Default cumulative (for the remaining period) FRAT5 curve for
      forecasting and optimisation. */
  extern const FRAT5Curve_T DEFAULT_CUMULATIVE_FRAT5_CURVE;

  /** Default PoS probability mass. */
  struct DefaultMap {
    static FRAT5Curve_T createCumulativeFRAT5Curve();
  };
}
#endif // __RMOL_BAS_BASCONST_CURVES_HPP
