#ifndef __RMOL_COMMAND_MARGINALREVENUETRANSFORMATION_HPP
#define __RMOL_COMMAND_MARGINALREVENUETRANSFORMATION_HPP

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
  class MarginalRevenueTransformation {    
  public:
    /**
     * Prepare the demand input for the optimser.
     */
    static bool prepareDemandInput (stdair::SegmentCabin&);
    
  private:
    /**
     * Build the nested convex hull
     */
    static void buildNestedConvexHull (stdair::SegmentCabin&);
    
    /**
     * Build the convex hull
     */
    static void buildConvexHull (stdair::SegmentCabin&);
    
    /**
     * Adjust yield and demand of all classes.
     */
    static bool adjustYieldAndDemand (stdair::SegmentCabin&);  
  };
}
#endif // __RMOL_COMMAND_MARGINALREVENUETRANSFORMATION_HPP
