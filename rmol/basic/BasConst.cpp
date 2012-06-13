// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
#include <rmol/basic/BasConst_General.hpp>
#include <rmol/basic/BasConst_RMOL_Service.hpp>

namespace RMOL {

  /** Default airline code for the RMOL_Service. */
  const stdair::AirlineCode_T DEFAULT_RMOL_SERVICE_AIRLINE_CODE = "BA";

  /** Default capacity for the RMOL_Service. */
  const double DEFAULT_RMOL_SERVICE_CAPACITY = 1.0;
  
  /** Default value for the number of draws within the Monte-Carlo
      Integration algorithm. */
  const int DEFAULT_NUMBER_OF_DRAWS_FOR_MC_SIMULATION = 10000;

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
}
