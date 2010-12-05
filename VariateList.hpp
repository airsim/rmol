#ifndef __RMOL_VARIATELIST_HPP
#define __RMOL_VARIATELIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <list>

namespace RMOL {

  /** Define a vector (ordered list) of N variates, each of one
      corresponding to an observation of a random variable.
      <br>Hence, the vector (list) of variates corresponds to
      a given list of N random variables. */
  typedef std::list<double> VariateList_T;
  
  /** Define a list of K variate "vectors", hence representing
      a simulation run. Each variate vector represents one draw for
      N given random variables. The list of those vectors thus corresponds
      to K of those random draws.*/
  typedef std::list<VariateList_T> DemandSimulation_T;
  
}
#endif // __RMOL_VARIATELIST_HPP
