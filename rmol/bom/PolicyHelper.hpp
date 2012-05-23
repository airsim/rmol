#ifndef __RMOL_BOM_POLICYHELPER_HPP
#define __RMOL_BOM_POLICYHELPER_HPP
// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/PolicyTypes.hpp>
#include <stdair/bom/BookingClassTypes.hpp>
#include <stdair/bom/FareFamilyTypes.hpp>
// RMOL
#include <rmol/RMOL_Types.hpp>

// Forward declarations
namespace stdair {
  class SegmentCabin;
  class Policy;
  class FareFamily;
  class BookingClass;
  class NestingNode;
}

namespace RMOL {

  /** 
   * Class holding helper methods. 
   */
  class PolicyHelper {
  public:
    
    /** 
     * Find the booking class list representing the difference 
     * between two Policies (first minus second)
     */
    static void
    diffBetweenTwoPolicies (stdair::NestingNode&, const stdair::Policy&,
                            const stdair::Policy&);

    /**
     * Compute the list of the booking class which is not in the node.
     */
    static void
    computeLastNode (stdair::NestingNode&, const stdair::Policy&,
                     const stdair::SegmentCabin&);

    /**
     * Check if the first policy is nested under the second policy.
     */
    static bool isNested (const stdair::Policy&, const stdair::Policy&);
    
  
  private:

    /** 
     * Find the intersection (e.g. a Booking Class) between the booking class
     * list and the policy. Return false if the intersection is empty 
     */
    static const bool 
    intersectionBetweenPolicyAndBookingClassList (const stdair::BookingClassList_T&,
                                                  const stdair::Policy&,
                                                  stdair::ClassCode_T&);

    /** 
     * Find the booking class list between two booking class in a fare family 
     */
    static void
    diffBetweenBookingClassAndPolicy (stdair::NestingNode&,
                                      const stdair::FareFamily&,
                                      const stdair::ClassCode_T&,
                                      const stdair::Policy&);

  };

}

#endif // __RMOL_BOM_POLICYHELPER_HPP
