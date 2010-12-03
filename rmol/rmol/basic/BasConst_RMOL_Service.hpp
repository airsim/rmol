#ifndef __RMOL_BAS_BASCONST_RMOL_SERVICE_HPP
#define __RMOL_BAS_BASCONST_RMOL_SERVICE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <vector>
// StdAir
#include <stdair/stdair_basic_types.hpp>
// RMOL
#include <rmol/RMOL_Types.hpp>

namespace RMOL {

  /** Default airline code for the RMOL_Service. */
  extern const stdair::AirlineCode_T DEFAULT_RMOL_SERVICE_AIRLINE_CODE;

  /** Default capacity for the RMOL_Service. */
  extern const double DEFAULT_RMOL_SERVICE_CAPACITY;

  /** Default generated demand vector. */
  extern const GeneratedDemandVector_T DEFAULT_GENERATED_DEMAND_VECTOR;

  /** Default generated demand vector holder. */
  extern const GeneratedDemandVectorHolder_T DEFAULT_GENERATED_DEMAND_VECTOR_HOLDER;
  
}
#endif // __RMOL_BAS_BASCONST_RMOL_SERVICE_HPP
