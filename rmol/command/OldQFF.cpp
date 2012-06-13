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
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/SegmentSnapshotTable.hpp>
#include <stdair/bom/FareFamily.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/Policy.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/bom/Utilities.hpp>
#include <rmol/bom/SegmentSnapshotTableHelper.hpp>
#include <rmol/bom/HistoricalBookingHolder.hpp>
#include <rmol/bom/HistoricalBooking.hpp>
#include <rmol/bom/EMDetruncator.hpp>
#include <rmol/command/OldQFF.hpp>
#include <rmol/command/Detruncator.hpp>

namespace RMOL {
  // ////////////////////////////////////////////////////////////////////
  bool OldQFF::
  forecast (stdair::SegmentCabin& ioSegmentCabin,
            const stdair::Date_T& iCurrentDate,
            const stdair::DTD_T& iCurrentDTD,
            const stdair::UnconstrainingMethod& iUnconstrainingMethod,
            const stdair::NbOfSegments_T& iNbOfDepartedSegments) {
    // Retrieve the snapshot table.
    const stdair::SegmentSnapshotTable& lSegmentSnapshotTable =
      ioSegmentCabin.getSegmentSnapshotTable();

    // Retrieve the FRAT5Curve.
    const stdair::FareFamilyList_T& lFFList =
      stdair::BomManager::getList<stdair::FareFamily>(ioSegmentCabin);
    stdair::FareFamilyList_T::const_reverse_iterator itFF = lFFList.rbegin();
    assert (itFF != lFFList.rend());
    stdair::FareFamily* lFF_ptr = *itFF;
    assert (lFF_ptr != NULL);
    const stdair::FRAT5Curve_T lFRAT5Curve = lFF_ptr->getFrat5Curve();

    // Retrieve the booking class list and compute the sell up curves
    // and the dispatching curves.
    const stdair::BookingClassList_T& lBCList =
      stdair::BomManager::getList<stdair::BookingClass>(ioSegmentCabin);
    const stdair::BookingClassSellUpCurveMap_T lBCSellUpCurveMap =
      Utilities::computeSellUpFactorCurves (lFRAT5Curve, lBCList);

    // Retrieve the list of all policies and reset the demand forecast
    // for each one.
    const stdair::PolicyList_T& lPolicyList =
      stdair::BomManager::getList<stdair::Policy> (ioSegmentCabin);
    for (stdair::PolicyList_T::const_iterator itPolicy = lPolicyList.begin();
         itPolicy != lPolicyList.end(); ++itPolicy) {
      stdair::Policy* lPolicy_ptr = *itPolicy;
      assert (lPolicy_ptr != NULL);
      lPolicy_ptr->resetDemandForecast();
    }

    // Browse all remaining DCP's and do unconstraining, forecasting
    // and dispatching.
    const stdair::DCPList_T lWholeDCPList = stdair::DEFAULT_DCP_LIST;
    stdair::DCPList_T::const_iterator itDCP = lWholeDCPList.begin();
    stdair::DCPList_T::const_iterator itNextDCP = itDCP; ++itNextDCP;
    for (; itNextDCP != lWholeDCPList.end(); ++itDCP, ++itNextDCP) {
      const stdair::DCP_T& lCurrentDCP = *itDCP;
      const stdair::DCP_T& lNextDCP = *itNextDCP;

      // The end of the interval is after the current DTD.
      if (lNextDCP < iCurrentDTD) {
        // Get the number of similar segments which has already passed the
        // (lNextDCP+1)
        const stdair::NbOfSegments_T& lNbOfUsableSegments =
          SegmentSnapshotTableHelper::
          getNbOfSegmentAlreadyPassedThisDTD (lSegmentSnapshotTable,
                                              lNextDCP+1,
                                              iCurrentDate);
        stdair::NbOfSegments_T lSegmentBegin = 0;
        const stdair::NbOfSegments_T lSegmentEnd = lNbOfUsableSegments-1;
        if (iNbOfDepartedSegments > 52) {
          lSegmentBegin = iNbOfDepartedSegments - 52;
        }
        
        // Retrieve the historical bookings and convert them to
        // Q-equivalent bookings.
        HistoricalBookingHolder lHBHolder;
        prepareHistoricalBooking (ioSegmentCabin, lSegmentSnapshotTable,
                                  lHBHolder, lCurrentDCP, lNextDCP,
                                  lSegmentBegin, lSegmentEnd,
                                  lBCSellUpCurveMap);

        // Unconstrain the historical bookings.
        Detruncator::unconstrain (lHBHolder, iUnconstrainingMethod);

        // Retrieve the historical unconstrained demand and perform the
        // forecasting.
        stdair::UncDemVector_T lUncDemVector;
        const short lNbOfHistoricalFlights = lHBHolder.getNbOfFlights();
        for (short i = 0; i < lNbOfHistoricalFlights; ++i) {
          const stdair::NbOfBookings_T& lUncDemand =
            lHBHolder.getUnconstrainedDemand (i);
          lUncDemVector.push_back (lUncDemand);
        }
        stdair::MeanValue_T lMean = 0.0;
        stdair::StdDevValue_T lStdDev = 0.0;
        Utilities::computeDistributionParameters (lUncDemVector,
                                                  lMean, lStdDev);

        // Add the demand forecast to the fare family.
        const stdair::MeanValue_T& lCurrentMean = lFF_ptr->getMean();
        const stdair::StdDevValue_T& lCurrentStdDev = lFF_ptr->getStdDev();

        const stdair::MeanValue_T lNewMean = lCurrentMean + lMean;
        const stdair::StdDevValue_T lNewStdDev = 
          std::sqrt (lCurrentStdDev * lCurrentStdDev + lStdDev * lStdDev);

        lFF_ptr->setMean (lNewMean);
        lFF_ptr->setStdDev (lNewStdDev);
 
        // Dispatch the demand forecast to the policies.
        dispatchDemandForecastToPolicies (lPolicyList, lCurrentDCP, lMean,
                                          lStdDev, lBCSellUpCurveMap);
      }
    }

    return true;
  }
  
  // ////////////////////////////////////////////////////////////////////
  void OldQFF::prepareHistoricalBooking
  (const stdair::SegmentCabin& iSegmentCabin,
   const stdair::SegmentSnapshotTable& iSegmentSnapshotTable,
   HistoricalBookingHolder& ioHBHolder,
   const stdair::DCP_T& iDCPBegin, const stdair::DCP_T& iDCPEnd,
   const stdair::NbOfSegments_T& iSegmentBegin,
   const stdair::NbOfSegments_T& iSegmentEnd,
   const stdair::BookingClassSellUpCurveMap_T& iBCSellUpCurveMap) {
    
    // Retrieve the segment-cabin index within the snapshot table
    std::ostringstream lSCMapKey;
    lSCMapKey << stdair::DEFAULT_SEGMENT_CABIN_VALUE_TYPE
              << iSegmentCabin.describeKey();    
    const stdair::ClassIndex_T& lCabinIdx =
      iSegmentSnapshotTable.getClassIndex (lSCMapKey.str());
    
    // Retrieve the gross daily booking and availability snapshots.
    const stdair::ConstSegmentCabinDTDRangeSnapshotView_T lPriceBookingView =
      iSegmentSnapshotTable.getConstSegmentCabinDTDRangePriceOrientedGrossBookingSnapshotView (iSegmentBegin, iSegmentEnd, iDCPEnd, iDCPBegin);
    const stdair::ConstSegmentCabinDTDRangeSnapshotView_T lProductBookingView =
      iSegmentSnapshotTable.getConstSegmentCabinDTDRangeProductOrientedGrossBookingSnapshotView (iSegmentBegin, iSegmentEnd, iDCPEnd, iDCPBegin);
    const stdair::ConstSegmentCabinDTDRangeSnapshotView_T lAvlView =
      iSegmentSnapshotTable.getConstSegmentCabinDTDRangeAvailabilitySnapshotView (iSegmentBegin, iSegmentEnd, iDCPEnd, iDCPBegin);
    
    // Browse the list of segments and build the historical booking holder.
    const stdair::ClassIndexMap_T& lVTIdxMap =
      iSegmentSnapshotTable.getClassIndexMap();
    const stdair::NbOfClasses_T lNbOfClasses = lVTIdxMap.size();

    for (short i = 0; i <= iSegmentEnd-iSegmentBegin; ++i) {
      stdair::Flag_T lCensorshipFlag = false;
      const short lNbOfDTDs = iDCPBegin - iDCPEnd + 1;
      const stdair::UnsignedIndex_T lAvlIdx = i*lNbOfClasses + lCabinIdx;

      // Parse the DTDs during the period and compute the censorship flag
      for (short j = 0; j < lNbOfDTDs; ++j) {
        // Check if the data has been censored during this day.
        // STDAIR_LOG_DEBUG ("i: " << i << ", NbOfClasses: " << lNbOfClasses
        //                   << ", ClassIdx: " << iClassIdx << ", j: " << j);
        if (lAvlView[lAvlIdx][j] < 1.0) {
          lCensorshipFlag = true;
          break;
        }
      }

      // Compute the Q-equivalent bookings
      stdair::NbOfBookings_T lNbOfHistoricalBkgs = 0.0;
      const stdair::BookingClassList_T& lBCList =
        stdair::BomManager::getList<stdair::BookingClass> (iSegmentCabin);
      for (short j = 0; j < lNbOfDTDs; ++j) {
        stdair::BookingClass* lLowestBC_ptr = NULL;
        stdair::NbOfBookings_T lNbOfBksOfTheDay = 0.0;
        for (stdair::BookingClassList_T::const_iterator itBC = lBCList.begin();
             itBC != lBCList.end(); ++itBC) {
          stdair::BookingClass* lBC_ptr = *itBC;
          assert (lBC_ptr != NULL);
          
          // Retrieve the number of bookings
          const stdair::ClassIndex_T& lClassIdx =
            iSegmentSnapshotTable.getClassIndex(lBC_ptr->describeKey());
          const stdair::UnsignedIndex_T lIdx = i*lNbOfClasses + lClassIdx;
          const stdair::NbOfBookings_T lNbOfBookings =
            lPriceBookingView[lIdx][j] + lProductBookingView[lIdx][j];
          lNbOfBksOfTheDay += lNbOfBookings;

          if (lAvlView[lIdx][j] >= 1.0) {
            lLowestBC_ptr = lBC_ptr;
          }
        }

        // Convert the number of bookings of the day to Q-equivalent
        // bookings using the sell-up probability of the lowest class
        // available of the day.
        if (lLowestBC_ptr != NULL) {
          stdair::BookingClassSellUpCurveMap_T::const_iterator itBCSUC =
             iBCSellUpCurveMap.find (lLowestBC_ptr);
          assert (itBCSUC != iBCSellUpCurveMap.end());
          const stdair::SellUpCurve_T& lSellUpCurve = itBCSUC->second;
          stdair::SellUpCurve_T::const_iterator itSellUp =
            lSellUpCurve.find (iDCPBegin);
          assert (itSellUp != lSellUpCurve.end());
          const stdair::SellupProbability_T& lSellUp = itSellUp->second;
          assert (lSellUp != 0);
          
          lNbOfHistoricalBkgs += lNbOfBksOfTheDay/lSellUp;          
        }
      }
      
      HistoricalBooking lHistoricalBkg (lNbOfHistoricalBkgs, lCensorshipFlag);
      ioHBHolder.addHistoricalBooking (lHistoricalBkg);
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void OldQFF::
  dispatchDemandForecastToPolicies (const stdair::PolicyList_T& iPolicyList,
                                    const stdair::DCP_T& iCurrentDCP,
                                    const stdair::MeanValue_T& iMean,
                                    const stdair::StdDevValue_T& iStdDev,
                                    const stdair::BookingClassSellUpCurveMap_T& iBCSellUpCurveMap) {
    for (stdair::PolicyList_T::const_iterator itPolicy = iPolicyList.begin();
         itPolicy != iPolicyList.end(); ++itPolicy) {
      stdair::Policy* lPolicy_ptr = *itPolicy;
      assert (lPolicy_ptr != NULL);
      dispatchDemandForecastToPolicy (*lPolicy_ptr,
                                      iCurrentDCP,
                                      iMean,
                                      iStdDev,
                                      iBCSellUpCurveMap);
    }
  }
 
  // ////////////////////////////////////////////////////////////////////
  void OldQFF::
  dispatchDemandForecastToPolicy (stdair::Policy& ioPolicy,
                                  const stdair::DCP_T& iCurrentDCP,
                                  const stdair::MeanValue_T& iMean,
                                  const stdair::StdDevValue_T& iStdDev,
                                  const stdair::BookingClassSellUpCurveMap_T& iBCSellUpCurveMap) {
    const stdair::MeanValue_T& lPolicyDemand = ioPolicy.getDemand();
    const stdair::StdDevValue_T& lPolicyStdDev = ioPolicy.getStdDev();

    // Browse the list of booking classes of the policy and use the
    // cumulative price-oriented demand forecast of each class.
    const bool hasAListOfBC = 
      stdair::BomManager::hasList<stdair::BookingClass> (ioPolicy);
    if (hasAListOfBC == true) { 
      const stdair::BookingClassList_T& lBCList =
        stdair::BomManager::getList<stdair::BookingClass> (ioPolicy);
      stdair::BookingClassList_T::const_reverse_iterator itCurrentBC =
        lBCList.rbegin();
      assert(itCurrentBC != lBCList.rend());
      stdair::BookingClass* lLowestBC_ptr = *itCurrentBC;
      assert (lLowestBC_ptr != NULL);
      const stdair::Yield_T& lLowestBCYield = lLowestBC_ptr->getYield();
      // Retrieve the sell-up factor for the lowest class.
      stdair::BookingClassSellUpCurveMap_T::const_iterator itBCSU =
        iBCSellUpCurveMap.find (lLowestBC_ptr);
      assert (itBCSU != iBCSellUpCurveMap.end());
      const stdair::SellUpCurve_T& lSellUpCurve = itBCSU->second;
      stdair::SellUpCurve_T::const_iterator itSellUpFactor =
        lSellUpCurve.find (iCurrentDCP);
      assert (itSellUpFactor != lSellUpCurve.end());
      const stdair::SellupProbability_T& lSUToLowestClass = itSellUpFactor->second;
      
      const stdair::MeanValue_T lAdditinalPolicyDemandMean = 
        iMean * lSUToLowestClass;
      const stdair::StdDevValue_T lAdditinalPolicyDemandStdDev = 
        iStdDev * std::sqrt (lSUToLowestClass);

      const stdair::MeanValue_T lNewPolicyDemandMean = 
        lPolicyDemand + lAdditinalPolicyDemandMean;
      const stdair::StdDevValue_T lNewPolicyDemandStdDev = 
        std::sqrt (lPolicyStdDev*lPolicyStdDev
        + lAdditinalPolicyDemandStdDev * lAdditinalPolicyDemandStdDev);
      //
      ioPolicy.setDemand (lNewPolicyDemandMean);
      ioPolicy.setStdDev (lNewPolicyDemandStdDev);

      ioPolicy.addYieldDemand (lLowestBCYield,
                               lAdditinalPolicyDemandMean);

      // Iterate other classes.
      stdair::BookingClassList_T::const_reverse_iterator itNextBC=itCurrentBC;
      ++itNextBC;
      for (; itNextBC != lBCList.rend(); ++itNextBC, ++itCurrentBC) {
        stdair::BookingClass* lCurrentBC_ptr = *itCurrentBC;
        assert (lCurrentBC_ptr != NULL);
        stdair::BookingClass* lNextBC_ptr = *itNextBC;
        assert (lNextBC_ptr != NULL);

        // Retrieve the disutility for the current policy to the next one.
        const stdair::FareFamily& lCurrentFF =
          stdair::BomManager::getParent<stdair::FareFamily> (*lCurrentBC_ptr);
        const stdair::FFDisutilityCurve_T& lDisutilityCurve =
          lCurrentFF.getDisutilityCurve();
        stdair::FFDisutilityCurve_T::const_iterator itDU =
          lDisutilityCurve.find (iCurrentDCP);
        assert (itDU != lDisutilityCurve.end());
        const double& lDU = itDU->second;
        
        // Retrieve the sell-up factor for the next class.
        stdair::BookingClassSellUpCurveMap_T::const_iterator itBCSUN =
          iBCSellUpCurveMap.find (lNextBC_ptr);
        assert (itBCSUN != iBCSellUpCurveMap.end());
        const stdair::SellUpCurve_T& lSellUpCurveN = itBCSUN->second;
        stdair::SellUpCurve_T::const_iterator itSellUpFactorN =
          lSellUpCurveN.find (iCurrentDCP);
        assert (itSellUpFactorN != lSellUpCurveN.end());
        const stdair::SellupProbability_T& lSUToNextClass = itSellUpFactorN->second;
        assert (lSUToNextClass > 0.0);
        assert(lSUToNextClass < lSUToLowestClass);

        // Retrieve the yields of the two classes
        const stdair::Yield_T& lCurrentYield = lCurrentBC_ptr->getYield();
        const stdair::Yield_T& lNextYield = lNextBC_ptr->getYield();
        const double lBuyUpFactor = exp ((lCurrentYield-lNextYield)*lDU);

        // Withdraw an amount demand forecast from the current class. This
        // amount of forecast will be added to the next class.
        const stdair::MeanValue_T lDemandForNextClass =
          iMean * lSUToNextClass * lBuyUpFactor;
        ioPolicy.addYieldDemand (lNextYield, lDemandForNextClass);
        ioPolicy.addYieldDemand (lCurrentYield, -lDemandForNextClass);
      }
    }
  }
}
