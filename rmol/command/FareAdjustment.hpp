#ifndef __RMOL_COMMAND_FAREADJUSTMENT_HPP
#define __RMOL_COMMAND_FAREADJUSTMENT_HPP

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
  class FareAdjustment {    
  public:
    /**
     * Prepare the demand input for the optimser.
     */
    static bool adjustYield (const stdair::SegmentCabin&);  
  };
}
#endif // __RMOL_COMMAND_FAREADJUSTMENT_HPP
