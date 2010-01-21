// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
#include <rmol/basic/BasConst_General.hpp>
#include <rmol/basic/BasConst_Overbooking.hpp>
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

  /** Default value for the load factor used for overbooking calculation. */
  const double DEFAULT_OVERBOOKING_LOAD_FACTOR = 0.0;

  /** Default value for the capacity used for overbooking calculation. */
  const unsigned int DEFAULT_OVERBOOKING_CAPACITY = 1;
  
  /** Default value for the net bookings used for overbooking calculation. */
  const unsigned int DEFAULT_OVERBOOKING_NET_BOOKINGS = 0;
  
  /** Default value for the overbooking used for overbooking calculation. */
  const double DEFAULT_OVERBOOKING_OVERBOOKING_PERCENTAGE = 0.0;

  /** Default value for the mean used for overbooking calculation. */
  const double DEFAULT_OVERBOOKING_MEAN = 0.0;

  /** Default value for the standard deviation used for overbooking
      calculation. */
  const double DEFAULT_OVERBOOKING_STANDARD_DEVIATION = 1.0;

  /** Default generated demand vector. */
  const GeneratedDemandVector_T DEFAULT_GENERATED_DEMAND_VECTOR = std::vector<double>();

  /** Default generated demand vector holder. */
  const GeneratedDemandVectorHolder_T DEFAULT_GENERATED_DEMAND_VECTOR_HOLDER = std::vector<GeneratedDemandVector_T>();

}
