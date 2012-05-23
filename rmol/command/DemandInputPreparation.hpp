#ifndef __RMOL_COMMAND_DEMANDINPUTPREPARATION_HPP
#define __RMOL_COMMAND_DEMANDINPUTPREPARATION_HPP

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
  class SegmentCabin;
}

namespace RMOL {
  /** Class wrapping the pre-optimisation algorithms. */
  class DemandInputPreparation {    
  public:
    /**
     * Prepare the demand input for the optimser.
     */
    static bool prepareDemandInput (const stdair::SegmentCabin&);  
  };
}
#endif // __RMOL_COMMAND_DEMANDINPUTPREPARATION_HPP
