#ifndef __RMOL_MCUTILS_HPP
#define __RMOL_MCUTILS_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
#include "VariateList.hpp"
#include "PartialSumList.hpp"

namespace RMOL {

  /** Utility methods for the Monte-Carlo algorithms. */
  class MCUtils {
  public:
    
    /** Calculate the partial sums:
        S(j,k) = d(1,k) + d(2,k) + ... + d(j,k),
        for j=1 to n-1 and the current k.
        Note that n-1 corresponds to the size of the parameter list,
        i.e., n corresponds to the number of classes/buckets. */
    static void calculatePartialSum (const VariateList_T&, PartialSumList_T&);

    /** Preparation of the demand simulation "vectors" (one per draw). */
    static void initialiseDemandSimulation (const double iNbOfDraws,
                                            DemandSimulation_T&);
    
    /** Preparation of the partial sums of demand (for all the classes).
        Initialse with 0 values, so that the lists/vectors have
        the correct size. */
    static void initialisePartialSums (const double iNbOfClasses,
                                       const double iNbOfDraws,
                                       DemandSimulationPartialSum_T&);
  };
}
#endif
