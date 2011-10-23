#ifndef __RMOL_BAS_BASCONST_GENERAL_HPP
#define __RMOL_BAS_BASCONST_GENERAL_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_types.hpp>

namespace RMOL {

  /** Default value for the number of draws within the Monte-Carlo
      Integration algorithm. */
  extern const int DEFAULT_NUMBER_OF_DRAWS_FOR_MC_SIMULATION;

  /** Default value for the precision of the integral computation in
      the Dynamic Programming algorithm. */
  extern const int DEFAULT_PRECISION;  

  /** Default epsilon value to qualify a denominator */
  extern const double DEFAULT_EPSILON;

  /** Default stopping value for an iterative algorithm. */
  extern const double DEFAULT_STOPPING_CRITERION;

  /** Default negative value used to initialze a double variable. */
  extern const double DEFAULT_INITIALIZER_DOUBLE_NEGATIVE;
  
  /** Defaut data collection point list. */
  extern const stdair::DCPList_T DEFAULT_DCP_LIST;
  struct DefaultDCPList { static stdair::DCPList_T init(); };
}
#endif // __RMOL_BAS_BASCONST_GENERAL_HPP
