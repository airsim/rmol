#ifndef __RMOL_BAS_BASCONST_CURVES_HPP
#define __RMOL_BAS_BASCONST_CURVES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/RMOL_Types.hpp>

namespace RMOL {

  /** Default FRAT5 curve for forecasting and optimisation. */
  extern const stdair::FRAT5Curve_T DEFAULT_FRAT5_CURVE;

  /** Default FRAT5 curve. */
  struct DefaultMap {
    static stdair::FRAT5Curve_T createFRAT5Curve();
  };
}
#endif // __RMOL_BAS_BASCONST_CURVES_HPP
