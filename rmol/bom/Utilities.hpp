#ifndef __RMOL_BOM_UTILITIES_HPP
#define __RMOL_BOM_UTILITIES_HPP
// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/RMOL_Types.hpp>

namespace RMOL {

  /** Class holding helper methods. */
  class Utilities {
  public:
    /** Compute the mean and the standard deviation from a set of samples. */
    static void computeDistributionParameters (const UnconstrainedDemandVector_T&, double&, double&);

  };

}

#endif // __RMOL_BOM_UTILITIES_HPP
