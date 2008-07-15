#ifndef __RMOL_BAS_BASCONST_GENERAL_HPP
#define __RMOL_BAS_BASCONST_GENERAL_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

namespace RMOL {

  /** Default value for the number of draws within the Monte-Carlo
      Integration algorithm. */
  extern const int DEFAULT_NUMBER_OF_DRAWS_FOR_MC_SIMULATION;

  /** Default value for the precision of the integral computation in
      the Dynamic Programming algorithm. */
  extern const int DEFAULT_PRECISION;

  /** Default value for the lower bound of the integral (theorically
      -infinite) in DP. */
  extern const double DEFAULT_LOWER_BOUND;

  /** Default value for the upper bound of the integral (theorically
      +infinite) in DP. */
  extern const double DEFAULT_UPPER_BOUND;
      
  
}
#endif // __RMOL_BAS_BASCONST_GENERAL_HPP
