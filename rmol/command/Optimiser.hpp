#ifndef __RMOL_COMMAND_OPTIMISER_HPP
#define __RMOL_COMMAND_OPTIMISER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/RMOL_Types.hpp>

// Forward declarations
namespace stdair {
  class LegCabin;
}

namespace RMOL {
  /** Forward declarations. */
  class StudyStatManager;

  /** Class wrapping the optimisation algorithms. */
  class Optimiser {
  public:
    
    /** 
	Monte Carlo Integration algorithm.
	<br>Calculate the optimal protections for the set of buckets/classes
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
       Monte Carlo Integartion algorithm with StudyStatManager.
    */
    static void optimalOptimisationByMCIntegration (const int K, 
                                                    stdair::LegCabin&,
                                                    StudyStatManager&);
    
    /**
       Dynamic Programming.
     */
    static void optimalOptimisationByDP (stdair::LegCabin&);
    
    /**
       EMRS algorithm.
     */
    static void heuristicOptimisationByEmsr (stdair::LegCabin&);

    /**
       EMRS algorithm with StudyStatManager.
     */
    static void heuristicOptimisationByEmsr (stdair::LegCabin&,
                                             StudyStatManager&);

    /**
       EMRS-a algorithm.
     */
    static void heuristicOptimisationByEmsrA (stdair::LegCabin&);

    /**
       EMRS-b algorithm.
     */
    static void heuristicOptimisationByEmsrB (stdair::LegCabin&);

  };
}
#endif // __RMOL_COMMAND_OPTIMISER_HPP
