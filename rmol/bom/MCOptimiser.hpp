#ifndef __RMOL_BOM_MCUTILS_HPP
#define __RMOL_BOM_MCUTILS_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/RMOL_Types.hpp>

// Forward declarations.
namespace stdair {
  class LegCabin;
}

namespace RMOL {

  /** Forward declarations. */
  class StudyStatManager;
  
  /** Utility methods for the Monte-Carlo algorithms. */
  class MCOptimiser {
  public:
    
    /** 
	Calculate the optimal protections for the set of buckets/classes
	given in input, and update those buckets accordingly.
	<br>The Monte Carlo Integration algorithm (see The Theory and 
	Practice of Revenue Management, by Kalyan T. Talluri and 
	Garret J. van Ryzin, Kluwer Academic Publishers, for the details) 
	is used. Hence, K is the number of random draws to perform.
	100 is a minimum for K, as statistics must be drawn from those
	random generations.
     */
    static void optimalOptimisationByMCIntegration (const int K,
                                                    stdair::LegCabin&);
    /**
       Monte Carlo algorithm with StudyStatManager.
     */
    static void optimalOptimisationByMCIntegration (const int K,
                                                    stdair::LegCabin&,
                                                    StudyStatManager&);
    
  };
}
#endif // __RMOL_BOM_MCUTILS_HPP
