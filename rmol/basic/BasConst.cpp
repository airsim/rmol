// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
#include <rmol/basic/BasConst_General.hpp>
#include <rmol/basic/BasConst_Curves.hpp>
#include <rmol/basic/BasConst_RMOL_Service.hpp>

namespace RMOL {

  /** Default airline code for the RMOL_Service. */
  const stdair::AirlineCode_T DEFAULT_RMOL_SERVICE_AIRLINE_CODE = "BA";

  /** Default capacity for the RMOL_Service. */
  const double DEFAULT_RMOL_SERVICE_CAPACITY = 1.0;
  
  /** Default value for the number of draws within the Monte-Carlo
      Integration algorithm. */
  const int DEFAULT_NUMBER_OF_DRAWS_FOR_MC_SIMULATION = 100000;

  /** Default value for the precision of the integral computation in
      the Dynamic Programming algorithm (100 means that the precision
      will be 0.01). */
  const int DEFAULT_PRECISION = 10;

  /** Default epsilon value to qualify a denominator */
  const double DEFAULT_EPSILON = 0.0001;

  /** Default stopping value for an iterative algorithm. */
  const double DEFAULT_STOPPING_CRITERION = 0.01;
  
  /** Default negative value used to initialze a double variable. */
  const double DEFAULT_INITIALIZER_DOUBLE_NEGATIVE = -10.0;

  /** Default cumulative[for the remaining period] FRAT5 curve for
      forecasting and optimisation. */
  const FRAT5Curve_T DEFAULT_CUMULATIVE_FRAT5_CURVE =
    DefaultMap::createCumulativeFRAT5Curve();
  FRAT5Curve_T DefaultMap::createCumulativeFRAT5Curve() {
    FRAT5Curve_T oCurve;
    oCurve[63] = 1.4;  oCurve[56] = 1.45; oCurve[49] = 1.5;
    oCurve[42] = 1.55; oCurve[35] = 1.6;  oCurve[31] = 1.7;
    oCurve[28] = 1.8;  oCurve[24] = 2.0;  oCurve[21] = 2.3;
    oCurve[17] = 2.6;  oCurve[14] = 3.0;  oCurve[10] = 3.3;
    oCurve[7]  = 3.4;  oCurve[5]  = 3.44; oCurve[3] = 3.47;
    oCurve[1]  = 3.5;
    return oCurve;
  };

}
