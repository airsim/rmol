#ifndef __RMOL_COMMAND_OPTIMISERFORQFF_HPP
#define __RMOL_COMMAND_OPTIMISERFORQFF_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/RMOL_Types.hpp>

// Forward declarations
namespace stdair {
  class FlightDate;
  class LegCabin;
}

namespace RMOL {
  /** Class wrapping the optimisation algorithms. */
  class OptimiserForQFF {
  public:
    
    /**
     * Optimise the bid price vector using Monte Carlo integration 
     */
    static void optimiseUsingMC (stdair::FlightDate&);

    /**
     * Optimise the authorization level using EMSRb 
     */
    static void optimiseUsingEMSRb (stdair::FlightDate&);

    /**
     * Optimisation thanks to Monte Carlo integration 
     */
    static void heuristicOptimisationByMCIntegration (stdair::LegCabin&);
    
    /**
     * Optimise the authorization level thanks to EMSRb  
     */
    static void heuristicOptimisationByEMSRb (stdair::LegCabin&);

  private:
  
    /**
     * Build the virtual class of a leg cabin for optimisation
     */
    static void buildVirtualClassList (stdair::LegCabin&);

     /**
     * Build the map of demand by yield of a leg cabin for optimisation
     */
    static void buildYieldLevelDemandMap (stdair::LegCabin&);

    /**
     * Update the authorization level of a leg cabin from its virtual classes
     */
    static void updateAuthorizationLevel (stdair::LegCabin&);

    /**
     * Set authorization level of all booking class of a leg cabin to zero
     */
    static void setAuthorizationLevelToZero (stdair::LegCabin&);

  };
}
#endif // __RMOL_COMMAND_OPTIMISERFORQFF_HPP
