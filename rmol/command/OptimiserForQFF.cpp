// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/basic/RandomGeneration.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/FareFamily.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/PolicyStruct.hpp>
#include <stdair/bom/PolicyTypes.hpp>
#include <stdair/bom/VirtualClassStruct.hpp>
#include <stdair/bom/VirtualClassTypes.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/bom/PolicyHelper.hpp>
#include <rmol/bom/Emsr.hpp>
#include <rmol/bom/MCOptimiser.hpp>
#include <rmol/command/OptimiserForQFF.hpp>
#include <rmol/command/MRTForNewQFF.hpp>

namespace RMOL {

  // ////////////////////////////////////////////////////////////////////
  void OptimiserForQFF::optimiseUsingMC (stdair::FlightDate& ioFlightDate) {

    // Browse the leg-cabin list.
    const stdair::LegDateList_T& lLDList =
      stdair::BomManager::getList<stdair::LegDate> (ioFlightDate);
    for (stdair::LegDateList_T::const_iterator itLD = lLDList.begin();
         itLD != lLDList.end(); ++itLD) {
      stdair::LegDate* lLD_ptr = *itLD;
      assert (lLD_ptr != NULL);

      
      const stdair::LegCabinList_T& lLCList =
        stdair::BomManager::getList<stdair::LegCabin> (*lLD_ptr);
      for (stdair::LegCabinList_T::const_iterator itLC = lLCList.begin();
           itLC != lLCList.end(); ++itLC) {
        stdair::LegCabin* lLC_ptr = *itLC;
        assert (lLC_ptr != NULL);

        //Build the virtual classes
        buildVirtualClassList (*lLC_ptr);
        stdair::VirtualClassList_T& lVirtualClassList = 
          lLC_ptr->getVirtualClassList();

        // Optimise using Monte Carlo integration
        if (lVirtualClassList.size() > 0) {
          buildYieldLevelDemandMap(*lLC_ptr);
          MCOptimiser::optimisationByMCIntegration(*lLC_ptr);
        }
      }
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void OptimiserForQFF::optimiseUsingEMSRb (stdair::FlightDate& ioFlightDate) {

    MRTForNewQFF::initForOptimiser(ioFlightDate);
    // Browse the leg-cabin list.
    const stdair::LegDateList_T& lLDList =
      stdair::BomManager::getList<stdair::LegDate> (ioFlightDate);
    for (stdair::LegDateList_T::const_iterator itLD = lLDList.begin();
         itLD != lLDList.end(); ++itLD) {
      stdair::LegDate* lLD_ptr = *itLD;
      assert (lLD_ptr != NULL);

      
      const stdair::LegCabinList_T& lLCList =
        stdair::BomManager::getList<stdair::LegCabin> (*lLD_ptr);
      for (stdair::LegCabinList_T::const_iterator itLC = lLCList.begin();
           itLC != lLCList.end(); ++itLC) {
        stdair::LegCabin* lLC_ptr = *itLC;
        assert (lLC_ptr != NULL);

        //Build the virtual classes
        buildVirtualClassList (*lLC_ptr);
        stdair::VirtualClassList_T& lVirtualClassList = 
          lLC_ptr->getVirtualClassList();

        // Optimise using EmsrB method.
        if (lVirtualClassList.size() > 0) {
          Emsr::heuristicOptimisationByEmsrB(*lLC_ptr);
          updateAuthorizationLevel(*lLC_ptr);
        }
      }
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void OptimiserForQFF::buildVirtualClassList (stdair::LegCabin& ioLegCabin) {

    stdair::VirtualClassList_T lVirtualClassList;

    // Retrieve the segment-cabin
    const stdair::SegmentCabinList_T& lSegmentCabinList =
      stdair::BomManager::getList<stdair::SegmentCabin> (ioLegCabin);
    stdair::SegmentCabinList_T::const_iterator itSC = lSegmentCabinList.begin();
    assert (itSC != lSegmentCabinList.end());
    const stdair::SegmentCabin* lSegmentCabin_ptr = *itSC;
    assert (lSegmentCabin_ptr != NULL);

    // Retrieve the convex hull
    const stdair::PolicyList_T& lConvexHull = lSegmentCabin_ptr->getConvexHull(); 
 
    // Browse the convex hull
    stdair::PolicyList_T::const_iterator itPolicy = lConvexHull.begin();
    if (lConvexHull.empty() == true) {
      throw EmptyConvexHullException("The convex hull is empty and "
                                     "it should not be.");
    }
    assert (itPolicy != lConvexHull.end());
    const stdair::PolicyStruct& lFirstPolicy = *itPolicy;
    const stdair::BookingClassList_T& lFirstPolicyBCList = 
      lFirstPolicy.getBookingClasses();
    if (lFirstPolicyBCList.empty() == false) {
      throw FirstPolicyNotNullException("The first element of the convex hull"
                                        " is not the null policy.");
    }
    assert(lFirstPolicyBCList.empty() == true);
    stdair::PolicyList_T::const_iterator itNextPolicy = itPolicy;
    ++itNextPolicy;

    for (; itNextPolicy != lConvexHull.end(); ++itNextPolicy, ++itPolicy) {
      assert(itPolicy != lConvexHull.end());
      const stdair::PolicyStruct& lPolicy = *itPolicy;
      assert(itNextPolicy != lConvexHull.end());
      const stdair::PolicyStruct& lNextPolicy = *itNextPolicy;
      const stdair::BookingClassList_T& lBookingClassList = 
        PolicyHelper::diffBetweenTwoPolicies(lNextPolicy, lPolicy);
      const stdair::MeanValue_T& lNextPolicyDemand = lNextPolicy.getDemand();
      const stdair::StdDevValue_T& lNextPolicyStdDev = lNextPolicy.getStdDev();
      const stdair::Yield_T& lNextPolicyYield = lNextPolicy.getYield();
      // Create the virtual class structure representing the difference 
      // between two adjacent policies of the convex hull
      stdair::VirtualClassStruct lVirtualClass (lBookingClassList);
      lVirtualClass.setMean(lNextPolicyDemand);
      lVirtualClass.setStdDev(lNextPolicyStdDev);
      lVirtualClass.setYield(lNextPolicyYield);
      lVirtualClassList.push_back(lVirtualClass);
    }
    // Build the virtual classes of the leg cabin
    // Empty the current virtual class list and add the new virtual classes
    ioLegCabin.emptyVirtualClassList();
    for (stdair::VirtualClassList_T::const_iterator itVC = 
      lVirtualClassList.begin(); itVC != lVirtualClassList.end(); ++itVC)  {
      const stdair::VirtualClassStruct& lVC = *itVC;
      ioLegCabin.addVirtualClass (lVC);
    }

  }

  // ////////////////////////////////////////////////////////////////////
  void OptimiserForQFF::buildYieldLevelDemandMap (stdair::LegCabin& ioLegCabin) {
    // Empty the old map
    ioLegCabin.emptyYieldLevelDemandMap();
    // Browse the virtual class list and add the tuple yield, mean and
    // standard deviation to the new map
    const stdair::VirtualClassList_T& lVirtualClassList = 
      ioLegCabin.getVirtualClassList();
    for (stdair::VirtualClassList_T::const_iterator itVC = 
         lVirtualClassList.begin(); itVC != lVirtualClassList.end(); ++itVC) {
      const stdair::VirtualClassStruct& lVirtualClass = *itVC;
      const int lYieldLevel =
        static_cast<int> (std::floor (lVirtualClass.getYield() + 0.5));
      if (lYieldLevel >= 1) {
        ioLegCabin.addDemandInformation(lVirtualClass.getYield(),
                                        lVirtualClass.getMean(),
                                        lVirtualClass.getStdDev());
      }
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void OptimiserForQFF::updateAuthorizationLevel (stdair::LegCabin& ioLegCabin) {

    // Set the authorization level to zero
    setAuthorizationLevelToZero(ioLegCabin);
    
    // Browse the virtual class
    const stdair::VirtualClassList_T& lVirtualClassList = 
      ioLegCabin.getVirtualClassList();
    for (stdair::VirtualClassList_T::const_iterator itVC = 
         lVirtualClassList.begin(); itVC != lVirtualClassList.end(); ++itVC) {
      const stdair::VirtualClassStruct& lVirtualClass = *itVC;
      const stdair::BookingLimit_T& lBookingLimit = 
        lVirtualClass.getCumulatedBookingLimit();
      const stdair::BookingClassList_T lBookingClassList = 
        lVirtualClass.getBookingClassList();
      // Browse the booking class list of the virtual class to set the
      // authorization level of each booking class
      for (stdair::BookingClassList_T::const_iterator itBC = 
           lBookingClassList.begin(); itBC != lBookingClassList.end(); ++itBC) {
        stdair::BookingClass* lBC_ptr = *itBC;
        assert (lBC_ptr != NULL);
        lBC_ptr->setAuthorizationLevel(lBookingLimit);
      }
    }

  }

  // ////////////////////////////////////////////////////////////////////
  void OptimiserForQFF::
  setAuthorizationLevelToZero (stdair::LegCabin& ioLegCabin) {
    // Retrieve the segment-cabin
    const stdair::SegmentCabinList_T& lSegmentCabinList =
      stdair::BomManager::getList<stdair::SegmentCabin> (ioLegCabin);
    stdair::SegmentCabinList_T::const_iterator itSC = lSegmentCabinList.begin();
    assert (itSC != lSegmentCabinList.end());
    const stdair::SegmentCabin* lSegmentCabin_ptr = *itSC;
    assert (lSegmentCabin_ptr != NULL);

    // Retrieve the booking class list
    const stdair::BookingClassList_T& lBookingClassList =
      stdair::BomManager::getList<stdair::BookingClass> (*lSegmentCabin_ptr);

    // Browse the booking class list
    for (stdair::BookingClassList_T::const_iterator itBC = 
         lBookingClassList.begin(); itBC !=  lBookingClassList.end(); ++itBC) {
      // Set the authorization level to zero
      stdair::BookingClass* lBC_ptr = *itBC;
      assert(lBC_ptr != NULL);
      lBC_ptr->setAuthorizationLevel(0.0);
    } 

  }

  // ////////////////////////////////////////////////////////////////////
  void OptimiserForQFF::
  heuristicOptimisationByMCIntegration (stdair::LegCabin& ioLegCabin) {
    const stdair::VirtualClassList_T& lVirtualClassList = 
      ioLegCabin.getVirtualClassList();

    const stdair::CabinCapacity_T& lCabinCapacity =
                ioLegCabin.getPhysicalCapacity();
    ioLegCabin.emptyBidPriceVector();
    stdair::BidPriceVector_T& lBPV = ioLegCabin.getBidPriceVector();

    for (stdair::CabinCapacity_T k = 0; k != lCabinCapacity; k++) {
      lBPV.push_back (400);
    }

    ioLegCabin.setPreviousBidPrice (lBPV.back());
    ioLegCabin.setCurrentBidPrice (lBPV.back());
    // Optimise using Monte Carlo integration
    const unsigned int lVirtualClassListSize = lVirtualClassList.size();
    if (lVirtualClassListSize > 0) {
      buildYieldLevelDemandMap(ioLegCabin);
      MCOptimiser::optimisationByMCIntegration(ioLegCabin);
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void OptimiserForQFF::
  heuristicOptimisationByEMSRb (stdair::LegCabin& ioLegCabin) {
    stdair::VirtualClassList_T& lVirtualClassList = 
      ioLegCabin.getVirtualClassList();

    // Optimise using EmsrB method.
    const unsigned int lVirtualClassListSize = lVirtualClassList.size();
    if (lVirtualClassListSize > 0) {
      Emsr::heuristicOptimisationByEmsrB(ioLegCabin);
      updateAuthorizationLevel(ioLegCabin);
    }

  }
  

}
