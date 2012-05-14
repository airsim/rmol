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
  struct PolicyStruct;
  class FareFamily;
  class BookingClass;
}

namespace RMOL {

  /** 
   * Class holding helper methods. 
   */
  class PolicyHelper {
  public:
    
    /** 
     * Find the booking class list representing the difference 
     * between two Policies 
     */
    static const stdair::BookingClassList_T 
    diffBetweenTwoPolicies (const stdair::PolicyStruct&,
                            const stdair::PolicyStruct&);
  
  private:

    /** 
     * Find the intersection (e.g. a Booking Class) between the booking class
     * list and the policy. Return false if the intersection is empty 
     */
    static const bool 
    intersectionBetweenPolicyAndBookingClassList (const stdair::BookingClassList_T&,
                                                  const stdair::PolicyStruct&,
                                                  stdair::ClassCode_T&);

    /** 
     * Find the booking class list between two booking class in a fare family 
     */
    static const stdair::BookingClassList_T 
    diffBetweenBookingClassAndPolicy (const stdair::FareFamily&,
                                      const stdair::ClassCode_T&,
                                      const stdair::PolicyStruct&);

  };

}

#endif // __RMOL_BOM_POLICYHELPER_HPP
