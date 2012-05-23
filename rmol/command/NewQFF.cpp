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
#include <rmol/command/NewQFF.hpp>
#include <rmol/command/Detruncator.hpp>

namespace RMOL {
  // ////////////////////////////////////////////////////////////////////
  bool NewQFF::
  forecast (stdair::SegmentCabin& ioSegmentCabin,
            const stdair::Date_T& iCurrentDate,
            const stdair::DTD_T& iCurrentDTD,
            const stdair::UnconstrainingMethod::EN_UnconstrainingMethod& iUnconstrainingMethod,
            const stdair::NbOfSegments_T& iNbOfDepartedSegments) {
    // Retrieve the snapshot table.
    const stdair::SegmentSnapshotTable& lSegmentSnapshotTable =
      ioSegmentCabin.getSegmentSnapshotTable();

    // Browse the list of fare families and execute "Q-forecasting" within
    // each fare family.
    const stdair::FareFamilyList_T& lFFList =
      stdair::BomManager::getList<stdair::FareFamily>(ioSegmentCabin);
    for (stdair::FareFamilyList_T::const_iterator itFF = lFFList.begin();
         itFF != lFFList.end(); ++itFF) {
      stdair::FareFamily* lFF_ptr = *itFF;
      assert (lFF_ptr != NULL);

      // Retrieve the FRAT5Curve.
      const stdair::FRAT5Curve_T lFRAT5Curve = lFF_ptr->getFrat5Curve();

      // Retrieve the booking class list and compute the sell up curves
      // and the dispatching curves.
      const stdair::BookingClassList_T& lBCList =
        stdair::BomManager::getList<stdair::BookingClass>(*lFF_ptr);
      stdair::BookingClassSellUpCurveMap_T lBCSellUpCurveMap =
        Utilities::computeSellUpFactorCurves (lFRAT5Curve, lBCList);
      stdair::BookingClassDispatchingCurveMap_T lBCDispatchingCurveMap =
        Utilities::computeDispatchingFactorCurves (lFRAT5Curve, lBCList);
      
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
          preparePriceOrientedHistoricalBooking (*lFF_ptr,
                                                 lSegmentSnapshotTable,
                                                 lHBHolder,
                                                 lCurrentDCP, lNextDCP,
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
          double lMean, lStdDev;
          Utilities::computeDistributionParameters (lUncDemVector,
                                                    lMean, lStdDev);

          // Dispatch the forecast to all the classes.
          Utilities::dispatchDemandForecast (lBCDispatchingCurveMap,
                                             lMean, lStdDev, lCurrentDCP);

          // Dispatch the forecast to all classes for Fare Adjustment or MRT.
          // The sell-up probability will be used in this case.
          Utilities::dispatchDemandForecastForFA (lBCDispatchingCurveMap,
                                                  lMean, lStdDev, lCurrentDCP);

          // Add the demand forecast to the fare family.
          const double& lCurrentMean = lFF_ptr->getMean();
          const double& lCurrentStdDev = lFF_ptr->getStdDev();

          const double lNewMean = lCurrentMean + lMean;
          const double lNewStdDev = sqrt (lCurrentStdDev * lCurrentStdDev
                                          + lStdDev * lStdDev);

          lFF_ptr->setMean (lNewMean);
          lFF_ptr->setStdDev (lNewStdDev);
        }
      }
    }
 
    // Dispatch the demand forecast to the policies.
    dispatchDemandForecastToPolicies (ioSegmentCabin);

    return true;
  }
  
  // ////////////////////////////////////////////////////////////////////
  void NewQFF::preparePriceOrientedHistoricalBooking
    (const stdair::FareFamily& iFareFamily,
     const stdair::SegmentSnapshotTable& iSegmentSnapshotTable,
     HistoricalBookingHolder& ioHBHolder,
     const stdair::DCP_T& iDCPBegin, const stdair::DCP_T& iDCPEnd,
     const stdair::NbOfSegments_T& iSegmentBegin,
     const stdair::NbOfSegments_T& iSegmentEnd,
     const stdair::BookingClassSellUpCurveMap_T& iBCSellUpCurveMap) {

    // Retrieve the gross daily booking and availability snapshots.
    stdair::ConstSegmentCabinDTDRangeSnapshotView_T lPriceBookingView =
      iSegmentSnapshotTable.getConstSegmentCabinDTDRangePriceOrientedGrossBookingSnapshotView (iSegmentBegin, iSegmentEnd, iDCPEnd, iDCPBegin);
    stdair::ConstSegmentCabinDTDRangeSnapshotView_T lProductBookingView =
      iSegmentSnapshotTable.getConstSegmentCabinDTDRangeProductOrientedGrossBookingSnapshotView (iSegmentBegin, iSegmentEnd, iDCPEnd, iDCPBegin);
    stdair::ConstSegmentCabinDTDRangeSnapshotView_T lAvlView =
      iSegmentSnapshotTable.getConstSegmentCabinDTDRangeAvailabilitySnapshotView (iSegmentBegin, iSegmentEnd, iDCPEnd, iDCPBegin);
    
    // Browse the list of segments and build the historical booking holder.
    const stdair::ClassIndexMap_T& lVTIdxMap =
      iSegmentSnapshotTable.getClassIndexMap();
    const unsigned int lNbOfClasses = lVTIdxMap.size();
    
    for (short i = 0; i <= iSegmentEnd-iSegmentBegin; ++i) {
      stdair::Flag_T lCensorshipFlag = false;
      const short lNbOfDTDs = iDCPBegin - iDCPEnd + 1;
      
      // Parse the DTDs during the period and compute the censorship flag
      for (short j = 0; j < lNbOfDTDs; ++j) {
        // Check if the data has been censored during this day.
        // STDAIR_LOG_DEBUG ("i: " << i << ", NbOfClasses: " << lNbOfClasses
        //                   << ", ClassIdx: " << iClassIdx << ", j: " << j);
        bool tempCensorship = true;
        for (stdair::BookingClassSellUpCurveMap_T::const_iterator itBCSUC =
             iBCSellUpCurveMap.begin();
           itBCSUC != iBCSellUpCurveMap.end(); ++itBCSUC) {
          const stdair::BookingClass* lBookingClass_ptr = itBCSUC->first;
          assert (lBookingClass_ptr != NULL);
          const stdair::ClassIndex_T& lClassIdx =
            iSegmentSnapshotTable.getClassIndex(lBookingClass_ptr->describeKey());
      
          if (lAvlView[i*lNbOfClasses + lClassIdx][j] >= 1.0) {
            tempCensorship = false;
            break;
          }
        }
        if (tempCensorship == true) {
          lCensorshipFlag = true;
          break;
        }
      }

      // Compute the Q-equivalent bookings
      stdair::NbOfBookings_T lNbOfHistoricalBkgs = 0.0;
      for (stdair::BookingClassSellUpCurveMap_T::const_iterator itBCSUC =
             iBCSellUpCurveMap.begin();
           itBCSUC != iBCSellUpCurveMap.end(); ++itBCSUC) {
        const stdair::BookingClass* lBookingClass_ptr = itBCSUC->first;
        assert (lBookingClass_ptr != NULL);
        const stdair::SellUpCurve_T& lSellUpCurve = itBCSUC->second;
        stdair::SellUpCurve_T::const_iterator itSellUp =
          lSellUpCurve.find (iDCPBegin);
        assert (itSellUp != lSellUpCurve.end());
        const double& lSellUp = itSellUp->second;
        assert (lSellUp != 0);

        // Retrieve the number of bookings
        const stdair::ClassIndex_T& lClassIdx =
          iSegmentSnapshotTable.getClassIndex(lBookingClass_ptr->describeKey());
        const stdair::NbOfBookings_T lNbOfBookings =
          lPriceBookingView[i*lNbOfClasses + lClassIdx][iDCPBegin-iDCPEnd]
          - lPriceBookingView[i*lNbOfClasses + lClassIdx][0]
          + lProductBookingView[i*lNbOfClasses + lClassIdx][iDCPBegin-iDCPEnd]
          - lProductBookingView[i*lNbOfClasses + lClassIdx][0];
        const stdair::NbOfBookings_T lNbOfQEquivalentBkgs=lNbOfBookings/lSellUp;

        lNbOfHistoricalBkgs += lNbOfQEquivalentBkgs;
      }

      HistoricalBooking lHistoricalBkg (lNbOfHistoricalBkgs, lCensorshipFlag);
      ioHBHolder.addHistoricalBooking (lHistoricalBkg);
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void NewQFF::
  dispatchDemandForecastToPolicies (const stdair::SegmentCabin& iSegmentCabin){
    // Retrieve the list of policies.
    const stdair::PolicyList_T& lPolicyList =
      stdair::BomManager::getList<stdair::Policy> (iSegmentCabin);

    for (stdair::PolicyList_T::const_iterator itPolicy = lPolicyList.begin();
         itPolicy != lPolicyList.end(); ++itPolicy) {
      stdair::Policy* lPolicy_ptr = *itPolicy;
      assert (lPolicy_ptr != NULL);

      // Reset the demand forecast of the policy
      lPolicy_ptr->resetDemandForecast();

      double lPolicyDemand = lPolicy_ptr->getDemand();
      double lPolicyStdDev = lPolicy_ptr->getStdDev();

      // Browse the list of booking classes of the policy and use the
      // cumulative price-oriented demand forecast of each class.
      const stdair::BookingClassList_T& lBCList =
        stdair::BomManager::getList<stdair::BookingClass> (*lPolicy_ptr);
      for (stdair::BookingClassList_T::const_iterator itBC = lBCList.begin();
           itBC != lBCList.end(); ++itBC) {
        const stdair::BookingClass* lBC_ptr = *itBC;
        assert (lBC_ptr != NULL);
        const stdair::Yield_T& lYield = lBC_ptr->getYield();
        const double& lDemand = lBC_ptr->getCumuPriceDemMean();
        const double& lStdDev = lBC_ptr->getCumuPriceDemStdDev();

        lPolicy_ptr->addYieldDemand (lYield, lDemand);
        lPolicyDemand += lDemand;
        lPolicyStdDev = sqrt (lPolicyStdDev*lPolicyStdDev + lStdDev*lStdDev);
      }
    }
  }
  
}
