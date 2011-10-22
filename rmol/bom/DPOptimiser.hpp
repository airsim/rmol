#ifndef __RMOL_BOM_DPOPTIMISER_HPP
#define __RMOL_BOM_DPOPTIMISER_HPP

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
  /** Utility methods for the Dynamic Programming algorithms. */
  class DPOptimiser {
  public:
    
    /** 
	Dynamic Programming to compute the cumulative protection levels
	and booking limits (described in the book Revenue Management -
	Talluri & Van Ryzin, p.41-42).
     */
    static void optimalOptimisationByDP (stdair::LegCabin&);

    /**
     Compute the cdf_Q of a gaussian.
     */
    static double cdfGaussianQ (const double, const double);
  };
}
#endif // __RMOL_BOM_DPOPTIMISER_HPP
