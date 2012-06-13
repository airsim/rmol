#ifndef __RMOL_COMMAND_PREOPTIMISER_HPP
#define __RMOL_COMMAND_PREOPTIMISER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
// RMOL
#include <rmol/RMOL_Types.hpp>

// Forward declarations
namespace stdair {
  class FlightDate;
  class SegmentCabin;
}

namespace RMOL {
  /** Class wrapping the pre-optimisation algorithms. */
  class PreOptimiser {    
  public:
    /**
     * Prepare the demand input for the optimser.
    */
    static bool preOptimise (stdair::FlightDate&, 
                             const stdair::PreOptimisationMethod&);

  private:
    /**
     * Prepare the demand input for the optimser.
     */
    static bool preOptimise (stdair::SegmentCabin&, 
                             const stdair::PreOptimisationMethod&);
    
    /**
     * Set the demand forecasts to zero.
     */
    //static void setDemandForecastsToZero (const stdair::SegmentCabin&);

  };
}
#endif // __RMOL_COMMAND_PREOPTIMISER_HPP
