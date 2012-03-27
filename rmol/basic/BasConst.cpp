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
    oCurve[63] = 1.2; 
    oCurve[49] = 1.3;  oCurve[35] = 1.4;
    oCurve[23] = 1.7;  oCurve[16] = 2.0; 
    oCurve[10] = 2.3;  oCurve[5]  = 2.44;
    oCurve[1]  = 2.5; 
    // oCurve[63] = 1.4;  oCurve[56] = 1.45;
    // oCurve[49] = 1.5;  oCurve[42] = 1.55; oCurve[35] = 1.6;
    // oCurve[31] = 1.7;  oCurve[27] = 1.8;  oCurve[23] = 2.0;
    // oCurve[19] = 2.3;  oCurve[16] = 2.6;  oCurve[13] = 3.0;
    // oCurve[10] = 3.3;  oCurve[7]  = 3.4;  oCurve[5]  = 3.44;
    // oCurve[3] = 3.47;  oCurve[1]  = 3.5;
    // oCurve[63] = 1.1;   oCurve[56] = 1.11;
    // oCurve[49] = 1.17;  oCurve[42] = 1.27;
    // oCurve[35] = 1.28;  oCurve[31] = 1.28; oCurve[27] = 1.28;
    // oCurve[23] = 1.37;  oCurve[19] = 1.37;
    // oCurve[16] = 1.6;  oCurve[13] = 1.6;
    // oCurve[10] = 1.8;  oCurve[7]  = 1.8;
    // oCurve[5]  = 2.23; oCurve[3] = 2.23;
    // oCurve[1]  = 2.5; 
    // oCurve[63] = 1.05;  oCurve[56] = 1.07;
    // oCurve[49] = 1.09;  oCurve[42] = 1.11; oCurve[35] = 1.14;
    // oCurve[31] = 1.16;  oCurve[27] = 1.18;  oCurve[23] = 1.21;
    // oCurve[19] = 1.24;  oCurve[16] = 1.27;  oCurve[13] = 1.3;
    // oCurve[10] = 1.33;  oCurve[7]  = 1.37;  oCurve[5]  = 1.4;
    // oCurve[3] = 1.45;  oCurve[1]  = 1.5; 
    // oCurve[63] = 1.4; 
    // oCurve[49] = 1.5;  oCurve[35] = 1.6;
    // oCurve[23] = 2.0;  oCurve[16] = 2.6; 
    // oCurve[10] = 3.3;  oCurve[5]  = 3.44;
    // oCurve[1]  = 3.5;  
    return oCurve;
  };

  /** Defaut data collection point list. */
  const stdair::DCPList_T DEFAULT_DCP_LIST = DefaultDCPList::init();
  stdair::DCPList_T DefaultDCPList::init() {
    stdair::DCPList_T oDCPList;
    oDCPList.push_back (63); oDCPList.push_back (49);
    oDCPList.push_back (35); oDCPList.push_back (23); 
    oDCPList.push_back (16); oDCPList.push_back (10);
    oDCPList.push_back (5);  oDCPList.push_back (1);
    oDCPList.push_back (0);
    return oDCPList;
  }

}
