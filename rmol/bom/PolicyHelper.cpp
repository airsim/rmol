
// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <cmath>
// StdAir
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/basic/BasConst_Yield.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/Policy.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/FareFamily.hpp>
#include <stdair/bom/NestingNode.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/factory/FacBomManager.hpp>
// RMOL
#include <rmol/bom/PolicyHelper.hpp>

namespace RMOL {
  // ////////////////////////////////////////////////////////////////////
  void PolicyHelper::
  diffBetweenTwoPolicies (stdair::NestingNode& ioNode,
                          const stdair::Policy& iFirstPolicy,
                          const stdair::Policy& iSecondPolicy) {

    // Retrieve the booking class list of the first policy
    const stdair::BookingClassList_T& lFirstBCList = 
          stdair::BomManager::getList<stdair::BookingClass> (iFirstPolicy);

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
      diffBetweenBookingClassAndPolicy (ioNode, lFareFamily, 
                                        lFirstPolicyClassCode, 
                                        iSecondPolicy);
    }
  }

  // ////////////////////////////////////////////////////////////////////
  const bool PolicyHelper::
  intersectionBetweenPolicyAndBookingClassList (const stdair::BookingClassList_T& iBCList,
                                            const stdair::Policy& iPolicy,
                                            stdair::ClassCode_T& oClassCode) {
    bool isInBookingClassList = false;

    // Retrieve the booking classes of the policy
    const bool hasAListOfBC = 
      stdair::BomManager::hasList<stdair::BookingClass> (iPolicy);
    if (hasAListOfBC == false) {
      return isInBookingClassList;
    } 
    const stdair::BookingClassList_T& lPolicyBookingClassList =
      stdair::BomManager::getList<stdair::BookingClass> (iPolicy);

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
    // return false
    return isInBookingClassList;
  }

  // ////////////////////////////////////////////////////////////////////
  void PolicyHelper::
  diffBetweenBookingClassAndPolicy (stdair::NestingNode& ioNode,
                                    const stdair::FareFamily& iFareFamily,
                                    const stdair::ClassCode_T& iFirstPolicyClassCode,
                                    const stdair::Policy& iSecondPolicy) {    
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
        stdair::FacBomManager::addToList (ioNode, *lBC_ptr);
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
        stdair::FacBomManager::addToList (ioNode, *lBC_ptr);
      }
      assert(ritBC != lFFBCList.rend());
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void PolicyHelper::
  computeLastNode (stdair::NestingNode& ioNode,
                   const stdair::Policy& iPolicy,
                   const stdair::SegmentCabin& iSegmentCabin) {
    // Compare the number of booking classes in the policy and the number
    // of fare families of the segment-cabin.
    ioNode.setYield(stdair::DEFAULT_YIELD_VALUE);
    const stdair::BookingClassList_T& lBCList =
      stdair::BomManager::getList<stdair::BookingClass> (iPolicy);
    const stdair::NbOfClasses_T lNbOfClasses = lBCList.size();
    const stdair::FareFamilyList_T& lFFList =
      stdair::BomManager::getList<stdair::FareFamily> (iSegmentCabin);
    const stdair::NbOfFareFamilies_T lNbOfFFs = lFFList.size();
    assert (lNbOfFFs >= lNbOfClasses);

    // Number of closed fare families in the policy.
    const stdair::NbOfFareFamilies_T lNbOfClosedFFs = lNbOfFFs - lNbOfClasses;
    stdair::FareFamilyList_T::const_reverse_iterator itFF = lFFList.rbegin();
    for (unsigned i=0; i<lNbOfClosedFFs; ++i, ++itFF) {
      const stdair::FareFamily* lFF_ptr = *itFF;
      assert (lFF_ptr != NULL);
      const stdair::BookingClassList_T& lCurrentBCList =
        stdair::BomManager::getList<stdair::BookingClass> (*lFF_ptr);
      for (stdair::BookingClassList_T::const_reverse_iterator itCurrentBC =
             lCurrentBCList.rbegin(); itCurrentBC != lCurrentBCList.rend();
           ++itCurrentBC) {
        stdair::BookingClass* lCurrentBC_ptr = *itCurrentBC;
        assert (lCurrentBC_ptr != NULL);
        stdair::FacBomManager::addToList (ioNode, *lCurrentBC_ptr);
      }
    }

    //
    for (stdair::BookingClassList_T::const_reverse_iterator itBC =
           lBCList.rbegin(); itBC != lBCList.rend(); ++itBC) {
      const stdair::BookingClass* lBC_ptr = *itBC;
      assert (lBC_ptr != NULL);
      const stdair::FareFamily& lFF =
        stdair::BomManager::getParent<stdair::FareFamily> (*lBC_ptr);

      const stdair::BookingClassList_T& lCurrentBCList =
        stdair::BomManager::getList<stdair::BookingClass> (lFF);
      for (stdair::BookingClassList_T::const_reverse_iterator itCurrentBC =
             lCurrentBCList.rbegin(); itCurrentBC != lCurrentBCList.rend();
           ++itCurrentBC) {
        stdair::BookingClass* lCurrentBC_ptr = *itCurrentBC;
        assert (lCurrentBC_ptr != NULL);
        if (lCurrentBC_ptr->describeKey() != lBC_ptr->describeKey()) {
          stdair::FacBomManager::addToList (ioNode, *lCurrentBC_ptr);
        } else {
          break;
        }
      }      
    }
  }

  // ////////////////////////////////////////////////////////////////////
  bool PolicyHelper::isNested (const stdair::Policy& iFirstPolicy,
                               const stdair::Policy& iSecondPolicy) {
    bool isNested = false;
    // The number of classes in the first policy should be smaller or equal
    // to the number of classes in the second one.
    const bool hasAListOfBCFirstPolicy = 
      stdair::BomManager::hasList<stdair::BookingClass> (iFirstPolicy);
    // All policies are nested with the empty policy
    if (hasAListOfBCFirstPolicy == false) {
      isNested = true;
      return isNested;
    } 
    const stdair::BookingClassList_T& lFirstBCList =
      stdair::BomManager::getList<stdair::BookingClass> (iFirstPolicy);
    const bool hasAListOfBCSecondPolicy = 
      stdair::BomManager::hasList<stdair::BookingClass> (iSecondPolicy);
    // The empty policy is not nested
    if (hasAListOfBCSecondPolicy == false) {
      return isNested;
    } 
    const stdair::BookingClassList_T& lSecondBCList =
      stdair::BomManager::getList<stdair::BookingClass> (iSecondPolicy);
    if (lFirstBCList.size() > lSecondBCList.size()) {
      return isNested;
    }

    // Browse the two lists of booking classes and verify if the pairs
    // of classes are in order.
    stdair::BookingClassList_T::const_iterator itFirstBC = lFirstBCList.begin();
    for (stdair::BookingClassList_T::const_iterator itSecondBC =
           lSecondBCList.begin(); itFirstBC != lFirstBCList.end();
         ++itFirstBC, ++itSecondBC) {
      const stdair::BookingClass* lFirstBC_ptr = *itFirstBC;
      assert (lFirstBC_ptr != NULL);
      const std::string lFirstKey = lFirstBC_ptr->describeKey();
      const stdair::BookingClass* lSecondBC_ptr = *itSecondBC;
      assert (lSecondBC_ptr != NULL);
      const std::string lSecondKey = lSecondBC_ptr->describeKey();
      if (lFirstKey == lSecondKey) {
        break;
      }
      
      // Retrieve the parent FF and its booking class list.
      const stdair::FareFamily& lFF =
        stdair::BomManager::getParent<stdair::FareFamily> (*lFirstBC_ptr);
      const stdair::BookingClassList_T& lBCList =
        stdair::BomManager::getList<stdair::BookingClass> (lFF);
      for (stdair::BookingClassList_T::const_iterator itBC = lBCList.begin();
           itBC != lBCList.end(); ++itBC) {
        const stdair::BookingClass* lBC_ptr = *itBC;
        assert (lBC_ptr != NULL);
        const std::string lKey = lBC_ptr->describeKey();
        if (lFirstKey == lKey) {
          break;
        } else if (lSecondKey == lKey) {
          return isNested;
        }
      }
    }

    isNested = true;
    return isNested;
  }
}
