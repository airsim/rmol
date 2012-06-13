// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
#include <cmath>
// StdAir
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/SimpleNestingStructure.hpp>
#include <stdair/bom/NestingNode.hpp>
#include <stdair/bom/Policy.hpp>
#include <stdair/factory/FacBomManager.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/bom/PolicyHelper.hpp>
#include <rmol/bom/Utilities.hpp>
#include <rmol/command/MarginalRevenueTransformation.hpp>

namespace RMOL {

  // ////////////////////////////////////////////////////////////////////
  bool MarginalRevenueTransformation::
  prepareDemandInput (stdair::SegmentCabin& ioSegmentCabin) {
    // Build the convex hull, then adjust the yield and demand of all
    // classes based on the hull.
  
    buildNestedConvexHull (ioSegmentCabin);
    bool isSucceeded = adjustYieldAndDemand (ioSegmentCabin);

    return isSucceeded;
  }

  // ////////////////////////////////////////////////////////////////////
  void MarginalRevenueTransformation::
  buildConvexHull (stdair::SegmentCabin& ioSegmentCabin) {
    // Reset the convex hull of the segment.
    ioSegmentCabin.resetConvexHull();
    
    // The first (from the left side) point of the convex hull is the "empty"
    // policy, i.e. the one with all fare families closed.
    const stdair::PolicyList_T& lPolicyList =
      stdair::BomManager::getList<stdair::Policy> (ioSegmentCabin);

    // By construction, the empty policy is the first one on the list of
    // eligible policies.
    stdair::PolicyList_T::const_iterator itPolicy=lPolicyList.begin();
    stdair::Policy* lEmptyPolicy_ptr = *itPolicy;
    assert (lEmptyPolicy_ptr != NULL);
    ioSegmentCabin.addPolicy (*lEmptyPolicy_ptr);

    // Pointer on the current policy of the convex hull.
    stdair::Policy* lCurrentPolicy_ptr = lEmptyPolicy_ptr;
    bool lEndOfHull = false;

    // The end of hull is reached when from the current policy, we cannot
    // find an other one with greater demand and total revenue.
    while (lEndOfHull == false) {
      // Demand and total revenue of the current policy.
      const double& lCurrentDem = lCurrentPolicy_ptr->getDemand();
      const double lCurrentTR = lCurrentPolicy_ptr->getTotalRevenue();
      
      // Search for the next policy.
      double lGradient = 0.0;
      stdair::Policy* lNextPolicy_ptr = NULL;
      for (stdair::PolicyList_T::const_iterator itPol = lPolicyList.begin();
           itPol != lPolicyList.end(); ++itPol) {
        stdair::Policy* lPolicy_ptr = *itPol;
        assert (lPolicy_ptr != NULL);

        const double& lDem = lPolicy_ptr->getDemand();
        const double lTR = lPolicy_ptr->getTotalRevenue();
        if (lDem > lCurrentDem && lTR > lCurrentTR) {
          const double lNewGradient = (lTR-lCurrentTR)/(lDem-lCurrentDem);
          if (lNewGradient > lGradient) {
            lGradient = lNewGradient;
            lNextPolicy_ptr = lPolicy_ptr;
          }
        }
      }

      // Check if we have found the next policy
      if (lNextPolicy_ptr == NULL) {
        lEndOfHull = true;
      } else {
        ioSegmentCabin.addPolicy (*lNextPolicy_ptr);
        lCurrentPolicy_ptr = lNextPolicy_ptr;
      }
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void MarginalRevenueTransformation::
  buildNestedConvexHull (stdair::SegmentCabin& ioSegmentCabin) {
    // Reset the convex hull of the segment.
    ioSegmentCabin.resetConvexHull();
    
    // The first (from the left side) point of the convex hull is the "empty"
    // policy, i.e. the one with all fare families closed.
    const stdair::PolicyList_T& lPolicyList =
      stdair::BomManager::getList<stdair::Policy> (ioSegmentCabin);

    // By construction, the empty policy is the first one on the list of
    // eligible policies.
    stdair::PolicyList_T::const_iterator itPolicy=lPolicyList.begin();
    stdair::Policy* lEmptyPolicy_ptr = *itPolicy;
    assert (lEmptyPolicy_ptr != NULL);
    ioSegmentCabin.addPolicy (*lEmptyPolicy_ptr);

    // Pointer on the current policy of the convex hull.
    stdair::Policy* lCurrentPolicy_ptr = lEmptyPolicy_ptr;
    bool lEndOfHull = false;

    // The end of hull is reached when from the current policy, we cannot
    // find an other one with greater demand and total revenue.
    while (lEndOfHull == false) {
      // Demand and total revenue of the current policy.
      const double& lCurrentDem = lCurrentPolicy_ptr->getDemand();
      const double lCurrentTR = lCurrentPolicy_ptr->getTotalRevenue();

      // Search for the next policy.
      double lGradient = 0.0;
      stdair::Policy* lNextPolicy_ptr = NULL;
      for (stdair::PolicyList_T::const_iterator itPol = lPolicyList.begin();
           itPol != lPolicyList.end(); ++itPol) {
        stdair::Policy* lPolicy_ptr = *itPol;
        assert (lPolicy_ptr != NULL);

        const double& lDem = lPolicy_ptr->getDemand();
        const double lTR = lPolicy_ptr->getTotalRevenue();
        if (lDem > lCurrentDem && lTR > lCurrentTR
            && PolicyHelper::isNested (*lCurrentPolicy_ptr, *lPolicy_ptr)) {
          const double lNewGradient = (lTR-lCurrentTR)/(lDem-lCurrentDem);
          if (lNewGradient > lGradient) {
            lGradient = lNewGradient;
            lNextPolicy_ptr = lPolicy_ptr;
          }
        }
      }

      // Check if we have found the next policy
      if (lNextPolicy_ptr == NULL) {
        lEndOfHull = true;
      } else {
        ioSegmentCabin.addPolicy (*lNextPolicy_ptr);
        lCurrentPolicy_ptr = lNextPolicy_ptr;
      }
    }
  }

  // ////////////////////////////////////////////////////////////////////
  bool MarginalRevenueTransformation::
  adjustYieldAndDemand (stdair::SegmentCabin& ioSegmentCabin) {
    bool isSucceeded = false;
    stdair::NbOfClasses_T lBookingClassCounter = 0;
    // Browse the list of policies on the convex hull, compute the differences
    // between pairs of consecutive policies.
    const stdair::PolicyList_T& lConvexHull = ioSegmentCabin.getConvexHull();
    stdair::PolicyList_T::const_iterator itCurrentPolicy = lConvexHull.begin();
    assert (itCurrentPolicy != lConvexHull.end());
    stdair::PolicyList_T::const_iterator itNextPolicy = itCurrentPolicy;
    ++itNextPolicy;
    // If the nesting has only one element (the empty policy),
    // there is no optimisation and no pre-optimisation.
    if (itNextPolicy == lConvexHull.end()) {
      return isSucceeded;
    }

    // Reset the yield-based nesting structure
    stdair::FacBomManager::resetYieldBasedNestingStructure (ioSegmentCabin);

    // Retrieve the yield-based nesting structure.
    stdair::SimpleNestingStructure& lYieldBasedNS =
      stdair::BomManager::getObject<stdair::SimpleNestingStructure> (ioSegmentCabin, stdair::YIELD_BASED_NESTING_STRUCTURE_CODE);
    const stdair::NestingNodeList_T& lNodeList =
      stdair::BomManager::getList<stdair::NestingNode> (lYieldBasedNS);
    stdair::NestingNodeList_T::const_iterator itNode = lNodeList.begin();

    for (; itNextPolicy != lConvexHull.end();
         ++itCurrentPolicy, ++itNextPolicy, ++itNode){
      const stdair::Policy* lCurrentPolicy_ptr = *itCurrentPolicy;
      assert (lCurrentPolicy_ptr != NULL);
      const stdair::Policy* lNextPolicy_ptr = *itNextPolicy;
      assert (lNextPolicy_ptr != NULL);

      // Retrieve the node. If there isn't any node left, create new one.
      stdair::NestingNode* lNode_ptr = NULL;
      if (itNode == lNodeList.end()) {
        // Create a nesting node
        stdair::NestingNodeCode_T lNodeCode ("XXX");
        stdair::NestingNodeKey lNodeKey (lNodeCode);
        stdair::NestingNode& lNestingNode =
          stdair::FacBom<stdair::NestingNode>::instance().create (lNodeKey);
        stdair::FacBomManager::addToList (lYieldBasedNS, lNestingNode);
        stdair::FacBomManager::linkWithParent (lYieldBasedNS, lNestingNode);
        lNode_ptr = &lNestingNode;
      } else {
        lNode_ptr = *itNode;
      }
      assert (lNode_ptr != NULL);
      PolicyHelper::diffBetweenTwoPolicies (*lNode_ptr, *lNextPolicy_ptr,
                                            *lCurrentPolicy_ptr);

      // Compute the adjusted yield, demand mean and demand standard deviation.
      // Note: because of the nature of the convex hull, in the adjusted
      // standard deviation computation, we can take the difference between
      // the squares of the standard deviations of the two policies instead of
      // the sum of the squares.
      const stdair::MeanValue_T lAdjustedDemMean =
        lNextPolicy_ptr->getDemand()-lCurrentPolicy_ptr->getDemand();
      assert (lAdjustedDemMean > 0.0);
      const stdair::StdDevValue_T& lCurrentStdDev = 
        lCurrentPolicy_ptr->getStdDev();
      const stdair::StdDevValue_T& lNextStdDev = lNextPolicy_ptr->getStdDev();
      assert (lNextStdDev > lCurrentStdDev);
      const stdair::StdDevValue_T lAdjustedDemStdDev =
        std::sqrt (lNextStdDev*lNextStdDev - lCurrentStdDev*lCurrentStdDev);
      const stdair::Yield_T lAdjustedYield =
        (lNextPolicy_ptr->getTotalRevenue()-lCurrentPolicy_ptr->getTotalRevenue())/(lAdjustedDemMean);
      assert (lAdjustedYield > 0.0);
      lNode_ptr->setYield (lAdjustedYield);

      // Browse the list of booking classes in the node. Set the adjusted yield
      // for each class. However, the adjusted demand forecast will be
      // distributed only to the first class of the list.
      const stdair::BookingClassList_T lBCList =
        stdair::BomManager::getList<stdair::BookingClass> (*lNode_ptr);
      stdair::BookingClassList_T::const_iterator itBC = lBCList.begin();
      assert (itBC != lBCList.end());
      stdair::BookingClass* lFirstClass = *itBC;
      assert (lFirstClass != NULL);
      lFirstClass->setMean (lAdjustedDemMean);
      lFirstClass->setStdDev (lAdjustedDemStdDev);
      for (; itBC != lBCList.end(); ++itBC) {
        stdair::BookingClass* lClass = *itBC;
        assert (lClass != NULL);
        lClass->setAdjustedYield (lAdjustedYield);
        ++lBookingClassCounter;
      }
    }

    const stdair::BookingClassList_T& lSCBookingClassList = 
       stdair::BomManager::getList<stdair::BookingClass> (ioSegmentCabin);
    const stdair::NbOfClasses_T lNbOfBookingClass = lSCBookingClassList.size();
    assert (lNbOfBookingClass >= lBookingClassCounter); 
    if (lBookingClassCounter < lNbOfBookingClass) {
      // At the last node. All the classes which haven't been added to the
      // nesting structure will be added to the next nesting node, with
      // an adjusted yield of zero.
      // Retrieve the node. If there isn't any node left, create new one.
      stdair::NestingNode* lLastNode_ptr = NULL;
      if (itNode == lNodeList.end()) {
        // Create a nesting node
        stdair::NestingNodeCode_T lNodeCode ("XXX");
        stdair::NestingNodeKey lNodeKey (lNodeCode);
        stdair::NestingNode& lNestingNode =
          stdair::FacBom<stdair::NestingNode>::instance().create (lNodeKey);
        stdair::FacBomManager::addToList (lYieldBasedNS, lNestingNode);
        stdair::FacBomManager::linkWithParent (lYieldBasedNS, lNestingNode);
        lLastNode_ptr = 
          stdair::BomManager::getObjectPtr<stdair::NestingNode>(lYieldBasedNS, 
                                                           lNodeKey.toString());
      } else {
        lLastNode_ptr = *itNode;
      }
      assert (lLastNode_ptr != NULL);
      const stdair::Policy* lLastPolicy_ptr = *itCurrentPolicy;
      assert (lLastPolicy_ptr != NULL);
      PolicyHelper::computeLastNode (*lLastNode_ptr, *lLastPolicy_ptr,
                                     ioSegmentCabin);
    }

    isSucceeded = true;
    return isSucceeded;
  }
  
}
