#ifndef __RMOL_EMSRUTILS_HPP
#define __RMOL_EMSRUTILS_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/bom/BucketList.hpp>
#include <rmol/bom/BucketHolder.hpp>

namespace RMOL {

  /** Utility methods for the Monte-Carlo algorithms. */
  class EmsrUtils {
  public:
    
    /** 
	Calculate the optimal protections for the set of buckets/classes
	given in input, and update those buckets accordingly.
	
	<br>The cabin capacity is used to a double to allow for some
	overbooking.
     */
    static void heuristicOptimisationByEmsrA (const double iCabCapacity,
                                              BucketHolder& iBucketHolder);
  };
}
#endif
