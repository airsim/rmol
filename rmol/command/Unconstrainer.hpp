#ifndef __RMOL_COMMAND_UNCONSTRAINER_HPP
#define __RMOL_COMMAND_UNCONSTRAINER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/RMOL_Types.hpp>

namespace RMOL {

  /** Forward declarations. */
  class BucketHolder;
  struct HistoricalBookingHolderHolder;

  /** Class wrapping the principal unconstraining algorithms and 
      some accessory algorithms. */
  class Unconstrainer {
  public:
    
    /** A sensored-demand unconstraining method based on 
        Expectation Maximization algorithm.<br>
        Reference: K.T. Talluri and G.Van Ryzin, 
        The Theory and Practice of Revenue Management. */
    static void demandUnconstrainByExpectationMaximization ();
  };
}
#endif // __RMOL_COMMAND_UNCONSTRAINER_HPP
