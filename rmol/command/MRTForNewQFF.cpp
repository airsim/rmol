// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <cmath>
#include <sstream>
// StdAir
#include <stdair/stdair_maths_types.hpp>
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/FareFamily.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/BookingClassTypes.hpp>
#include <stdair/bom/PolicyStruct.hpp>
#include <stdair/bom/PolicyTypes.hpp>
#include <stdair/bom/SimpleNestingStruct.hpp>
// RMOL
#include <rmol/basic/BasConst_Curves.hpp>
#include <rmol/bom/Utilities.hpp>
#include <rmol/bom/PolicyHelper.hpp>
#include <rmol/command/MRTForNewQFF.hpp>

namespace RMOL {

  // ////////////////////////////////////////////////////////////////////
  void MRTForNewQFF::initForOptimiser (stdair::FlightDate& ioFlightDate) {
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

        // Create the nesting structure for the optimiser
        initForOptimiser (*lLC_ptr);
      }
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void MRTForNewQFF::initForOptimiser (stdair::LegCabin& ioLegCabin) {
    // Retrieve the segment-cabin
    const stdair::SegmentCabinList_T& lSegmentCabinList =
      stdair::BomManager::getList<stdair::SegmentCabin> (ioLegCabin);
    stdair::SegmentCabinList_T::const_iterator itSC = lSegmentCabinList.begin();
    assert (itSC != lSegmentCabinList.end());
    stdair::SegmentCabin* lSegmentCabin_ptr = *itSC;
    assert (lSegmentCabin_ptr != NULL);
    
    // Retrieve the fare family list
    const stdair::FareFamilyList_T& lFareFamilyList =
      stdair::BomManager::getList<stdair::FareFamily> (*lSegmentCabin_ptr);  
        
    // Retrieve the forecasted demand for each Booking Class
    const bool isCumulated = true;
    const BookingClassMeanStdDevPairMap_T& lBookingClassMeanStdDevPairMap = 
      Utilities::createBookingClassMeanStdDevPairMap(lFareFamilyList, 
                                                     isCumulated);
    // Create the policies
    const stdair::PolicyList_T& lPolicies = 
      createPolicies(lFareFamilyList, lBookingClassMeanStdDevPairMap);

    // Create the convex hull
    const stdair::PolicyList_T& lHull = createConvexHull(lPolicies);
    lSegmentCabin_ptr->setConvexHull(lHull);

    // Create the nesting structure for the optimiser
    const unsigned int& lHullSize = lHull.size();
    if (lHullSize > 1) {
      lSegmentCabin_ptr->clearNestingStruct();
      stdair::PolicyList_T::const_iterator itHullNextPolicy = lHull.begin();
      ++itHullNextPolicy;
      for (stdair::PolicyList_T::const_iterator itHullPolicy = lHull.begin();
            itHullNextPolicy != lHull.end(); ++itHullPolicy, ++itHullNextPolicy) {
          const stdair::PolicyStruct& lPolicy = *itHullPolicy;
          const stdair::PolicyStruct& lNextPolicy = *itHullNextPolicy;
          stdair::BookingClassList_T lBCList = 
            PolicyHelper::diffBetweenTwoPolicies(lNextPolicy, lPolicy);
          for (stdair::BookingClassList_T::iterator itBC = lBCList.begin();
               itBC != lBCList.end();) {
            stdair::BookingClass* lBC_ptr = *itBC;
            assert(lBC_ptr != NULL);
            const stdair::BookingClassKey& lBCKey = lBC_ptr->getKey();
            const stdair::ClassCode_T& lCodeClass = lBCKey.getClassCode();
            if (lSegmentCabin_ptr->alreadyInNestingStruct(lCodeClass)) {
              itBC = lBCList.erase(itBC);
            } else {
              ++itBC;
            }
          }
          const stdair::Yield_T& lYield = lNextPolicy.getYield();
          const bool insertionSucceeded = 
            lSegmentCabin_ptr->insertBookingClassListInNestingStruct(
              lYield, lBCList);
          assert(insertionSucceeded == true);
      }
      lSegmentCabin_ptr->fillNestingStruct();
    }
    
  }

  // ////////////////////////////////////////////////////////////////////
  const stdair::PolicyList_T MRTForNewQFF::
  createPolicies(const stdair::FareFamilyList_T& iFareFamilyList,
                 const BookingClassMeanStdDevPairMap_T& iBCMSDPMap) {
    // Initialise the policy list, the next policy (booking class list, 
    // demand, revenue, yield, standard deviation) and the current fare family
    stdair::PolicyList_T lPolicies;
    stdair::BookingClassList_T lBookingClassList;
    stdair::NbOfBookings_T lDemand = 0.0;
    stdair::Revenue_T lRevenue = 0.0;
    stdair::StdDevValue_T lStdDev = 0.0;
    stdair::FareFamilyList_T::const_iterator itFF = iFareFamilyList.begin();
    createPolicies (lPolicies, 
                    iFareFamilyList, 
                    lBookingClassList,
                    lDemand,
                    lRevenue,
                    lStdDev,
                    itFF, 
                    iBCMSDPMap,
                    100000.0);
    
    return lPolicies;
  }

  // ////////////////////////////////////////////////////////////////////
  void MRTForNewQFF::
  createPolicies (stdair::PolicyList_T& ioPolicies,
                  const stdair::FareFamilyList_T& iFareFamilyList,
                  const stdair::BookingClassList_T& iBookingClassList,
                  const stdair::NbOfBookings_T& iDemand,
                  const stdair::Revenue_T& iRevenue,
                  const stdair::StdDevValue_T& iStdDev,
                  const stdair::FareFamilyList_T::const_iterator& itFF,
                  const BookingClassMeanStdDevPairMap_T& iBCMSDPMap,
                  const stdair::Yield_T& iPreviousYield) {
    // If we have browsed all the fare families, we create the new policy 
    // and add it to the list
    if (itFF == iFareFamilyList.end()) {
      stdair::Yield_T lYield = 0.0;
      if (iDemand != 0.0) {
        lYield = iRevenue / iDemand;
      }
      stdair::PolicyStruct lPolicy 
        (iBookingClassList, iDemand, lYield, iStdDev);
      ioPolicies.push_back(lPolicy);

    } else {
      // We add a booking class of the next Fare Family if it is cheapest than 
      // the previous booking class in the policy. 
      // Assumption: the fare family list is sorted according to their fares:
      // Fare_1 > Fare_2 > ... > Fare_n
      const stdair::FareFamily* lFF_ptr = *itFF;
      //Retrieve the booking class list of the current fare family
      const stdair::BookingClassList_T& lBookingClassList =
        stdair::BomManager::getList<stdair::BookingClass> (*lFF_ptr);
      stdair::BookingClassList_T::const_iterator itBC = lBookingClassList.begin();
      stdair::FareFamilyList_T::const_iterator lItFF = itFF;
      lItFF++;
      // Browse the booking class list
      for (; itBC != lBookingClassList.end(); ++itBC) {
        stdair::BookingClass* lBC_ptr = *itBC;
        assert(lBC_ptr != NULL);
        const stdair::Yield_T& lCurrentYield = lBC_ptr->getYield();
        if (lCurrentYield >= iPreviousYield) {
          continue;
        }
        assert(lCurrentYield < iPreviousYield);
        // Add the current booking class to the list, update the current policy
        // and call the same method for the next fare family
        stdair::BookingClassList_T lBookingClassList (iBookingClassList);
        lBookingClassList.push_back(lBC_ptr);
        BookingClassMeanStdDevPairMap_T::const_iterator itBCMSDPMap =
          iBCMSDPMap.find(lBC_ptr);
        assert(itBCMSDPMap != iBCMSDPMap.end());
        const stdair::MeanStdDevPair_T& lMeanStdDevPair = (*itBCMSDPMap).second;
        const stdair::MeanValue_T& lNewDemand = lMeanStdDevPair.first;
        const stdair::StdDevValue_T& lNewStdDev = lMeanStdDevPair.second;
        const stdair::NbOfBookings_T lDemand = iDemand + lNewDemand;
        const stdair::Revenue_T lRevenue = 
          iRevenue + lCurrentYield * lNewDemand;
        const stdair::StdDevValue_T lStdDev = 
          sqrt(iStdDev * iStdDev + lNewStdDev * lNewStdDev);
     
        createPolicies (ioPolicies,
                        iFareFamilyList,
                        lBookingClassList,
                        lDemand,
                        lRevenue,
                        lStdDev,
                        lItFF, 
                        iBCMSDPMap,
                        lCurrentYield);
      }
      // Call the same method for the next fare family 
      // (without adding a booking class to the list: 
      // no booking class of the current fare family in this policy)
      createPolicies (ioPolicies,
                      iFareFamilyList,
                      iBookingClassList,
                      iDemand,
                      iRevenue,
                      iStdDev,
                      lItFF, 
                      iBCMSDPMap,
                      0.0);
    }
  }

  
  // ////////////////////////////////////////////////////////////////////
  const stdair::PolicyList_T MRTForNewQFF::createConvexHull(
  const stdair::PolicyList_T& iPolicies) {
    stdair::PolicyList_T lConvexHull;
    stdair::BookingClassList_T lBCList;
    stdair::PolicyStruct lMaxPolicy (lBCList, 0.0, 0.0, 0.0);
    lConvexHull.push_back(lMaxPolicy);
    stdair::Yield_T lMaxYield = 1.0;
    stdair::Revenue_T lMaxRevenue = 0.0;
    stdair::NbOfRequests_T lDemand = 0.0;
    stdair::Revenue_T lTotalRevenue = 0.0;
    stdair::StdDevValue_T lStdDev = 0.0;
    // While there is a profitable policy
    while (lMaxYield > 0.0){
      lMaxYield = 0.0;
      // Browse the policy list to find the next point on the hull
      for (stdair::PolicyList_T::const_iterator itP = iPolicies.begin();
           itP != iPolicies.end(); ++itP) {
        const stdair::PolicyStruct& lCurrentPolicy = *itP; 
        const stdair::NbOfRequests_T& lCurrentDemand = lCurrentPolicy.getDemand();
        const stdair::Revenue_T& lCurrentRevenue = lCurrentPolicy.getRevenue();
        if (lCurrentDemand > lDemand) {
          const stdair::Yield_T lYield = (lCurrentRevenue - lTotalRevenue) /
                                         (lCurrentDemand - lDemand);
          // Save the point with the greatest gradient
          if (lYield > lMaxYield) {
            lMaxPolicy = lCurrentPolicy;
            lMaxYield = lYield;
            lMaxRevenue = lCurrentRevenue;
          } else if (lYield == lMaxYield && lCurrentRevenue > lMaxRevenue) {
            lMaxPolicy = lCurrentPolicy;
            lMaxYield = lYield;
            lMaxRevenue = lCurrentRevenue;
          }
        }
      }
      // If the point is profitable, we add it to the convex hull and
      // search a new point from the current point
      if (lMaxYield > 0.0) {
        const stdair::StdDevValue_T& lMaxPolicyStdDev = lMaxPolicy.getStdDev();
        if (lMaxPolicyStdDev < lStdDev) {
          std::ostringstream ostr;
          ostr << "The standard deviation of a policy "
                  "of the convex hull is greatest than the "
                  "standard deviation of the next policy.";
          STDAIR_LOG_DEBUG(ostr.str());
          throw ConvexHullException(ostr.str());
        }
        assert(lMaxPolicyStdDev >= lStdDev);
        const stdair::BookingClassList_T lMaxPolicyBCList = 
          lMaxPolicy.getBookingClasses();
        const stdair::NbOfRequests_T& lMaxPolicyDemand = lMaxPolicy.getDemand();
        const stdair::Revenue_T& lMaxPolicyRevenue = lMaxPolicy.getRevenue();
        const stdair::StdDevValue_T lHullStdDev = 
          sqrt(lMaxPolicyStdDev * lMaxPolicyStdDev - 
               lStdDev * lStdDev);
        stdair::PolicyStruct lHullPolicy (lMaxPolicyBCList,
                                          lMaxPolicyDemand - lDemand,
                                          lMaxYield,
                                          lHullStdDev);
        lConvexHull.push_back(lHullPolicy);
        lDemand = lMaxPolicyDemand;
        lTotalRevenue = lMaxPolicyRevenue;
        lStdDev = lMaxPolicyStdDev;
      } 
    } 
    return lConvexHull;
  }
}
