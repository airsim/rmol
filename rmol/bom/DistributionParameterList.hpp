#ifndef __RMOL_DISTRIBUTIONPARAMETERLIST_HPP
#define __RMOL_DISTRIBUTIONPARAMETERLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <list>
// RMOL
#include <rmol/field/FldDistributionParameters.hpp>

namespace RMOL {

  /** Define the set of parameters, each of one wrapping a pair of
      distribution parameters (i.e., mean and standard deviation). */
  typedef std::list<FldDistributionParameters> DistributionParameterList_T;
  
}
#endif // __RMOL_DISTRIBUTIONPARAMETERLIST_HPP
