#ifndef __RMOL_COMMAND_OPTIMISER_HPP
#define __RMOL_COMMAND_OPTIMISER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/basic/OptimisationMethod.hpp>
// RMOL
#include <rmol/RMOL_Types.hpp>

// Forward declarations
namespace stdair {
  class FlightDate;
  class LegCabin;
}

namespace RMOL {
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
    static void optimalOptimisationByMCIntegration (const stdair::NbOfSamples_T&, 
                                                    stdair::LegCabin&);
    
    /**
       Dynamic Programming.
     */
    static void optimalOptimisationByDP (stdair::LegCabin&);
    
    /**
       EMRS algorithm.
     */
    static void heuristicOptimisationByEmsr (stdair::LegCabin&);

    /**
       EMRS-a algorithm.
     */
    static void heuristicOptimisationByEmsrA (stdair::LegCabin&);

    /**
       EMRS-b algorithm.
     */
    static void heuristicOptimisationByEmsrB (stdair::LegCabin&);

    /**
       Optimise a flight-date using leg-based Monte Carlo Integration.
    */
    static bool optimise (stdair::FlightDate&,
                          const stdair::OptimisationMethod&);

    /**
     * Build the virtual class list for the given leg-cabin.
     */
    static bool buildVirtualClassListForLegBasedOptimisation(stdair::LegCabin&);

    /** Optimiser */
    static double optimiseUsingOnDForecast (stdair::FlightDate&,
                                            const bool& iReduceFluctuations = false);

  private:
    /**
       Optimise a leg-date using leg-based Monte Carlo Integration.
    */
    static bool optimise (stdair::LegDate&,
                          const stdair::OptimisationMethod&);
    /**
       Optimise a leg-cabin using leg-based Monte Carlo Integration.
    */
    static bool optimise (stdair::LegCabin&,
                          const stdair::OptimisationMethod&);


  };
}
#endif // __RMOL_COMMAND_OPTIMISER_HPP
