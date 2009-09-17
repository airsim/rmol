#ifndef __RMOL_PARTIALSUMLIST_HPP
#define __RMOL_PARTIALSUMLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <list>
#include <vector>

namespace RMOL {

  /** 
      Define a vector (ordered list) of K values, each of one
      corresponding to the partial sum of N random variable observations.
      <br>
      <br>For instance, if d(j) defines an observation for the
      j-th random variable (out of N), S(j) is defined as:
      S(j) = d(1) + d(2) + ... + d(j), for j ranging from 1 to N.
      <br>
  */
  typedef std::vector<double> PartialSumList_T;
  
  /** 
      Define a list of N partial sum "vectors", hence representing
      the partial sums derived by a simulation run. Each partial sum vector
      represents K draws for the N given random variables.
  */
  typedef std::list<PartialSumList_T> DemandSimulationPartialSum_T;
  
}
#endif // __RMOL_PARTIALSUMLIST_HPP
