#ifndef __RMOL_PARAMETERLIST_HPP
#define __RMOL_PARAMETERLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <list>
// RMOL
#include "FldDistributionParameters.hpp"

namespace RMOL {

  /** Define the set of parameters, each of one wrapping a pair of
      distribution parameters (i.e., mean and standard deviation). */
  typedef std::list<FldDistributionParameters> ParameterList_T;
  
}
#endif // __RMOL_PARAMETERLIST_HPP
