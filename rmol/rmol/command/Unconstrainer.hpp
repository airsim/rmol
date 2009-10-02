#ifndef __RMOL_COMMAND_UNCONSTRAINER_HPP
#define __RMOL_COMMAND_UNCONSTRAINER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/RMOL_UNCONSTRAINER_Types.hpp>
#include <rmol/RMOL_UTILITY_Types.hpp>

namespace RMOL {

  /** Class wrapping the principal unconstraining algorithms and 
      some accessory algorithms. */
  class Unconstrainer {
  public:
    
    /** A sensored-demand unconstraining method based on 
        Expectation Maximization algorithm.<br>
        Reference: K.T. Talluri and G.Van Ryzin, 
        The Theory and Practice of Revenue Management. */
    static void dataUnconstrainByExpectationMaximization 
    (ConstrainedDataHolder_T&, UnconstrainedDataHolder_T&, 
     StoppingCriterion_T&);

  };
}
#endif // __RMOL_COMMAND_UNCONSTRAINER_HPP
