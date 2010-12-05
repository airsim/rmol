#ifndef __RMOL_EMSR_HPP
#define __RMOL_EMSR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/RMOL_Types.hpp>

namespace RMOL {

  /** Forward declarations. */
  // class Resource;
  class BucketHolder;
  class Bucket;

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
    static void heuristicOptimisationByEmsr (const ResourceCapacity_T,
                                             BucketHolder&,
                                             BidPriceVector_T&);

    /** 
	Calculate the optimal protections for the set of buckets/classes
	given in input, and update those buckets accordingly.
	
	<br>The cabin capacity is used to a double to allow for some
	overbooking.
     */
    static void heuristicOptimisationByEmsrA (const ResourceCapacity_T,
                                              BucketHolder&);

    /**
     Compute the optimal booking limits & protection limits for a set of 
     buckets/classes
     */
    static void heuristicOptimisationByEmsrAwithSellup 
    (const ResourceCapacity_T, BucketHolder&, SellupProbabilityVector_T&);

    /**
    Complute the protection levels and booking limites by using
    the EMSR-b algorithm.

    <br>The cabin capacity is used to a double to allow for some
	overbooking.
    */
    static void heuristicOptimisationByEmsrB (const ResourceCapacity_T,
                                              BucketHolder&,
                                              Bucket&);

  };
}
#endif // __RMOL_EMSR_HPP
