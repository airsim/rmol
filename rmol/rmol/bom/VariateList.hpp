#ifndef __RMOL_VARIATELIST_HPP
#define __RMOL_VARIATELIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <list>

namespace RMOL {

  /** 
      Define a vector (ordered list) of K variates, each of one
      corresponding to a distinct observation of the same random variable.
  */
  typedef std::list<double> VariateList_T;
  
  /** 
      Define a list of N variate "vectors", hence representing
      a simulation run. Each variate vector represents K draws for
      a given random variable. The list of those vectors thus corresponds
      to all the draws for N classes/buckets.
  */
  typedef std::list<VariateList_T> DemandSimulation_T;
  
  // DEPRECATED
  /** Define a vector (ordered list) of N variates, each of one
      corresponding to an observation of a random variable.
      <br>Hence, the vector (list) of variates corresponds to
      a given list of N random variables. */
  
  /** Define a list of K variate "vectors", hence representing
      a simulation run. Each variate vector represents one draw for
      N given random variables. The list of those vectors thus corresponds
      to K of those random draws.*/
  // END OF DEPRECATED
  
}
#endif // __RMOL_VARIATELIST_HPP
