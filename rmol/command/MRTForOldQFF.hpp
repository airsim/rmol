#ifndef __RMOL_COMMAND_MRTFOROLDQFF_HPP
#define __RMOL_COMMAND_MRTFOROLDQFF_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/RMOL_Types.hpp>
//STDAIR
#include <stdair/bom/PolicyTypes.hpp>
#include <stdair/bom/FareFamilyTypes.hpp>
#include <stdair/stdair_rm_types.hpp>

// Forward declarations
namespace stdair {
  class FlightDate;
  class LegCabin;
}

namespace RMOL {
  /** Class wrapping the marginal revenue transformation algorithms. */
  class MRTForOldQFF {
  public:
 
    /**
     * Initialise the nesting structure for a flight date
     */
    static void initForOptimiser (stdair::FlightDate&);

  private:
    /**
     * Initialise the nesting structure for a leg cabin
     */
    static void initForOptimiser (stdair::LegCabin&);

    /**
     * Create policies from a fare family list
     */
    static const stdair::PolicyList_T 
      createPolicies(const stdair::FareFamilyList_T&,
                     const stdair::SimpleNestingStruct&);

    /**
     * Recursive method which create the set of policies
     */
    static void createPolicies (stdair::PolicyList_T&,
                                const stdair::FareFamilyList_T&,
                                const stdair::BookingClassList_T&,
                                const stdair::FareFamilyList_T::const_iterator&,
                                const stdair::SimpleNestingStruct&,
                                const stdair::Yield_T&);

    /**
     * Create the convex hull from a set of policies
     */
    static const stdair::PolicyList_T createConvexHull(const stdair::PolicyList_T&);
  };
}
#endif // __RMOL_COMMAND_MRTFOROLDQFF_HPP
