
// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <cmath>
// StdAir
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/PolicyStruct.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/FareFamily.hpp>
#include <stdair/bom/BomManager.hpp>

// RMOL
#include <rmol/bom/PolicyHelper.hpp>

namespace RMOL {
  // ////////////////////////////////////////////////////////////////////
  const stdair::BookingClassList_T PolicyHelper::
  diffBetweenTwoPolicies (const stdair::PolicyStruct& iFirstPolicy,
                          const stdair::PolicyStruct& iSecondPolicy) {
    stdair::BookingClassList_T lBookingClassList;
    // Retrieve the booking class list of the first policy
    const stdair::BookingClassList_T& lFirstBCList = 
      iFirstPolicy.getBookingClasses();

    // Browse the booking class list
    for (stdair::BookingClassList_T::const_iterator itBC = lFirstBCList.begin();
         itBC != lFirstBCList.end(); ++itBC){
      const stdair::BookingClass* iFirstPolicyBC_ptr = *itBC;
      const stdair::BookingClassKey& lFirstPolicyBCKey = 
        iFirstPolicyBC_ptr->getKey();
      const stdair::ClassCode_T& lFirstPolicyClassCode = 
        lFirstPolicyBCKey.getClassCode();
      // Retrieve the fare family of the booking class and the list of booking 
      // class of this fare family
      const stdair::FareFamily& lFareFamily = 
        stdair::BomManager::getParent<stdair::FareFamily> (*iFirstPolicyBC_ptr);
      
      // Retrieve the list of booking class between the both booking classes
      // and insert it in the global booking class list
      const stdair::BookingClassList_T& lCurrentBookingClassList = 
        diffBetweenBookingClassAndPolicy(lFareFamily, 
                                         lFirstPolicyClassCode, 
                                         iSecondPolicy);
      for (stdair::BookingClassList_T::const_iterator itBC = 
           lCurrentBookingClassList.begin(); 
           itBC != lCurrentBookingClassList.end(); ++itBC) {
        stdair::BookingClass* lBC_ptr = *itBC;
        assert (lBC_ptr != NULL);
        lBookingClassList.push_back(lBC_ptr);
      }
    }
    return lBookingClassList;
  }

  // ////////////////////////////////////////////////////////////////////
  const bool PolicyHelper::
  intersectionBetweenPolicyAndBookingClassList (const stdair::BookingClassList_T& iBCList,
                                            const stdair::PolicyStruct& iPolicy,
                                            stdair::ClassCode_T& oClassCode) {
    bool isInBookingClassList = false;

    // Retrieve the booking classes of the policy
    const stdair::BookingClassList_T& lPolicyBookingClassList = 
      iPolicy.getBookingClasses();

    // Browse the booking class list of the fare family
    stdair::BookingClassList_T::const_iterator itFFBC = iBCList.begin();
    for (; itFFBC != iBCList.end(); ++itFFBC) {
      stdair::BookingClass* lFFBC_ptr = *itFFBC;
      const stdair::BookingClassKey& lFFBCKey = lFFBC_ptr->getKey();
      const stdair::ClassCode_T& lFFClassCode = lFFBCKey.getClassCode();
      // Compare the booking class with booking classes of policy 
      stdair::BookingClassList_T::const_iterator itPolicyBC = 
        lPolicyBookingClassList.begin();
      for (; itPolicyBC != lPolicyBookingClassList.end(); ++itPolicyBC){
        const stdair::BookingClass* lPolicyBC_ptr = *itPolicyBC;
        const stdair::BookingClassKey& lPolicyBCKey = lPolicyBC_ptr->getKey();
        const stdair::ClassCode_T& lPolicyClassCode = 
          lPolicyBCKey.getClassCode();
        if (lPolicyClassCode == lFFClassCode) {
          oClassCode = lPolicyClassCode;
          isInBookingClassList = true;
          return isInBookingClassList;
        }
      }
    }
    // If the policy has not any booking class in the fare family,
    // return the end of the reverse iterator
    return isInBookingClassList;
  }

  // ////////////////////////////////////////////////////////////////////
  const stdair::BookingClassList_T PolicyHelper::
  diffBetweenBookingClassAndPolicy (const stdair::FareFamily& iFareFamily,
        const stdair::ClassCode_T& iFirstPolicyClassCode,
        const stdair::PolicyStruct& iSecondPolicy) {    
    const stdair::BookingClassList_T& lFFBCList = 
        stdair::BomManager::getList<stdair::BookingClass> (iFareFamily);
    const bool isEmptyBookingClassList = lFFBCList.empty();
    if (isEmptyBookingClassList == true) {
      std::ostringstream ostr;
      ostr << "The booking class list of the fare family " 
           << iFareFamily.describeKey() << " is empty.";
      STDAIR_LOG_DEBUG(ostr.str());
      throw EmptyBookingClassListException (ostr.str());
    }
    
    stdair::BookingClassList_T lBookingClassList;
    
    // Retrieve the reverse iterator for the first booking class   
    stdair::BookingClassList_T::const_reverse_iterator ritBC;   
    for (ritBC = lFFBCList.rbegin(); ritBC != lFFBCList.rend(); ++ritBC) {
      const stdair::BookingClass* lBC_ptr = *ritBC;
      assert (lBC_ptr != NULL);
      const stdair::BookingClassKey& lBookingClassKey = lBC_ptr->getKey();
      const stdair::ClassCode_T& lClassCode = lBookingClassKey.getClassCode();
      if (iFirstPolicyClassCode == lClassCode) {
        break;
      }   
    }
    if (ritBC == lFFBCList.rend()) {
      std::ostringstream ostr;
      ostr << "The booking class " << iFirstPolicyClassCode 
           << "is not in the Fare Family " << iFareFamily.describeKey();
      STDAIR_LOG_DEBUG(ostr.str());
      throw MissingBookingClassInFareFamilyException (ostr.str());
    }
    assert(ritBC != lFFBCList.rend());

    // Retrieve the booking class of the second policy in the same
    // fare family than the current booking class
    stdair::ClassCode_T lSecondPolicyClassCode;
    const bool hasABookingClassIn = 
      intersectionBetweenPolicyAndBookingClassList(lFFBCList,
                                                   iSecondPolicy,
                                                   lSecondPolicyClassCode);
    // Add booking class between the first booking class and 
    // the second booking class

    if (hasABookingClassIn == false) {
      for (; ritBC != lFFBCList.rend(); ++ritBC) {
        stdair::BookingClass* lBC_ptr = *ritBC;
        lBookingClassList.push_back(lBC_ptr);
      }
    } else {
      
      for (; ritBC != lFFBCList.rend(); ++ritBC) {
        stdair::BookingClass* lBC_ptr = *ritBC;
        assert (lBC_ptr != NULL);
        const stdair::BookingClassKey& lBookingClassKey = lBC_ptr->getKey();
        const stdair::ClassCode_T& lClassCode = lBookingClassKey.getClassCode();
        if (lSecondPolicyClassCode == lClassCode) {
          break;
        }
        lBookingClassList.push_back(lBC_ptr);
      }
      assert(ritBC != lFFBCList.rend());
    }
    
    return lBookingClassList;
  }
}
