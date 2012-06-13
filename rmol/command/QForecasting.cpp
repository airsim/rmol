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
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/SegmentSnapshotTable.hpp>
#include <stdair/bom/FareFamily.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/bom/Utilities.hpp>
#include <rmol/bom/SegmentSnapshotTableHelper.hpp>
#include <rmol/bom/HistoricalBookingHolder.hpp>
#include <rmol/bom/HistoricalBooking.hpp>
#include <rmol/command/QForecasting.hpp>
#include <rmol/command/Detruncator.hpp>

namespace RMOL {
  // ////////////////////////////////////////////////////////////////////
  bool QForecasting::
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
    const stdair::BookingClassDispatchingCurveMap_T lBCDispatchingCurveMap =
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
        preparePriceOrientedHistoricalBooking (ioSegmentCabin,
                                               lSegmentSnapshotTable, lHBHolder,
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
        stdair::MeanValue_T lMean = 0.0;
        stdair::StdDevValue_T lStdDev = 0.0;
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
        const stdair::MeanValue_T& lCurrentMean = lFF_ptr->getMean();
        const stdair::StdDevValue_T& lCurrentStdDev = lFF_ptr->getStdDev();

        const stdair::MeanValue_T lNewMean = lCurrentMean + lMean;
        const stdair::StdDevValue_T lNewStdDev = 
          std::sqrt (lCurrentStdDev * lCurrentStdDev + lStdDev * lStdDev);

        lFF_ptr->setMean (lNewMean);
        lFF_ptr->setStdDev (lNewStdDev);       
      }
    }

    return true;
  }
  
  // ////////////////////////////////////////////////////////////////////
  void QForecasting::preparePriceOrientedHistoricalBooking
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
    const stdair::ConstSegmentCabinDTDRangeSnapshotView_T lBookingView =
      iSegmentSnapshotTable.getConstSegmentCabinDTDRangePriceOrientedGrossBookingSnapshotView (iSegmentBegin, iSegmentEnd, iDCPEnd, iDCPBegin);
    const stdair::ConstSegmentCabinDTDRangeSnapshotView_T lAvlView =
      iSegmentSnapshotTable.getConstSegmentCabinDTDRangeAvailabilitySnapshotView (iSegmentBegin, iSegmentEnd, iDCPEnd, iDCPBegin);
    
    // Browse the list of segments and build the historical booking holder.
    const stdair::ClassIndexMap_T& lVTIdxMap =
      iSegmentSnapshotTable.getClassIndexMap();
    const stdair::NbOfClasses_T lNbOfClasses = lVTIdxMap.size();

    for (short i = 0; i <= iSegmentEnd-iSegmentBegin; ++i) {
      stdair::Flag_T lCensorshipFlag = false;
      const short lNbOfDTDs = iDCPBegin - iDCPEnd + 1;
      const stdair::UnsignedIndex_T lIdx = i*lNbOfClasses + lCabinIdx;

      // Parse the DTDs during the period and compute the censorship flag
      for (short j = 0; j < lNbOfDTDs; ++j) {
        // Check if the data has been censored during this day.
        // STDAIR_LOG_DEBUG ("i: " << i << ", NbOfClasses: " << lNbOfClasses
        //                   << ", ClassIdx: " << iClassIdx << ", j: " << j);
        if (lAvlView[lIdx][j] < 1.0) {
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
        const stdair::SellupProbability_T& lSellUp = itSellUp->second;
        assert (lSellUp != 0);

        // Retrieve the number of bookings
        const stdair::ClassIndex_T& lClassIdx =
          iSegmentSnapshotTable.getClassIndex(lBookingClass_ptr->describeKey());
        stdair::NbOfBookings_T lNbOfBookings = 0.0;
        for (short j = 0; j < lNbOfDTDs; ++j) {
          lNbOfBookings += lBookingView[i*lNbOfClasses + lClassIdx][j];
        }

        const stdair::NbOfBookings_T lNbOfQEquivalentBkgs=lNbOfBookings/lSellUp;
        lNbOfHistoricalBkgs += lNbOfQEquivalentBkgs;
      }

      HistoricalBooking lHistoricalBkg (lNbOfHistoricalBkgs, lCensorshipFlag);
      ioHBHolder.addHistoricalBooking (lHistoricalBkg);
    }
  }
}
