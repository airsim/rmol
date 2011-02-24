#ifndef __RMOL_EMSR_HPP
#define __RMOL_EMSR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/RMOL_Types.hpp>

/** Forward declarations. */
namespace stdair {
  class LegCabin;
}

namespace RMOL {

  /** Class Implementing the EMSR algorithm for Bid-Price Vector computing. */
  class Emsr {
  public:
    /**
    Compute the Bid-Price Vector using the EMSR algorithm. Then
    compute the protection levels and booking limits by using the BPV.

    <br>For each class/bucket j with yield pj and demand Dj, compute
    pj*Pr(Dj>=x) with x the capacity index. This value is called the
    EMSR (Expected Marginal Seat Revenue) of the class/bucket j with
    the remaining capacity of x. Thus, we have for each class/bucket
    a list of EMSR values. We merge all these lists and sort the values
    from high to low in order to obtain the BPV.
    */
    static void heuristicOptimisationByEmsr (stdair::LegCabin&);

    /** 
	Calculate the optimal protections for the set of buckets/classes
	given in input, and update those buckets accordingly.
    */
    static void heuristicOptimisationByEmsrA (stdair::LegCabin&);

    /**
    Complute the protection levels and booking limites by using
    the EMSR-b algorithm.
    */
    static void heuristicOptimisationByEmsrB (stdair::LegCabin&);

  };
}
#endif // __RMOL_EMSR_HPP
