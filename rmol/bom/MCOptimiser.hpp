#ifndef __RMOL_BOM_MCUTILS_HPP
#define __RMOL_BOM_MCUTILS_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/RMOL_Types.hpp>
#include <stdair/stdair_maths_types.hpp>
#include <stdair/stdair_rm_types.hpp>

// Forward declarations.
namespace stdair {
  class LegCabin;
}

namespace RMOL {
  /** Utility methods for the Monte-Carlo algorithms. */
  class MCOptimiser {
  public:
    
    /** 
	Calculate the optimal protections for the set of buckets/classes
	given in input, and update those buckets accordingly.
	<br>The Monte Carlo Integration algorithm (see The Theory and 
	Practice of Revenue Management, by Kalyan T. Talluri and 
	Garret J. van Ryzin, Kluwer Academic Publishers, for the details) 
	is used.
     */
    static void optimalOptimisationByMCIntegration (stdair::LegCabin&);

    /**
     * Monte-Carlo
     */
    static stdair::GeneratedDemandVector_T
    generateDemandVector (const stdair::MeanValue_T&,
                          const stdair::StdDevValue_T&, 
                          const stdair::NbOfSamples_T&);
    
    static void optimisationByMCIntegration (stdair::LegCabin&);
    
  };
}
#endif // __RMOL_BOM_MCUTILS_HPP
