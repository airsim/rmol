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
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
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
#include <rmol/command/BasedForecasting.hpp>
#include <rmol/command/Forecaster.hpp>
#include <rmol/command/QForecasting.hpp>
#include <rmol/command/HybridForecasting.hpp>
#include <rmol/command/OldQFF.hpp>
#include <rmol/command/NewQFF.hpp>

namespace RMOL {

  // ////////////////////////////////////////////////////////////////////
  bool Forecaster::
  forecast (stdair::FlightDate& ioFlightDate,
            const stdair::DateTime_T& iEventTime,
            const stdair::UnconstrainingMethod& iUnconstrainingMethod,
            const stdair::ForecastingMethod& iForecastingMethod) {
    // Build the offset dates.
    const stdair::Date_T& lEventDate = iEventTime.date();
    
    // 
    bool isSucceeded = true;
    const stdair::SegmentDateList_T& lSDList =
      stdair::BomManager::getList<stdair::SegmentDate> (ioFlightDate);
    for (stdair::SegmentDateList_T::const_iterator itSD = lSDList.begin();
         itSD != lSDList.end(); ++itSD) {
      stdair::SegmentDate* lSD_ptr = *itSD;
      assert (lSD_ptr != NULL);

      // TODO: Take into account the case where the segment departure date
      // is not the same as the flight departure date.
      // const stdair::Date_T& lBoardingDate = lSD_ptr->getBoardingDate();
      // const stdair::DateOffset_T lSegmentDateOffset =
      //   lBoardingDate - lEventDate;
      // const stdair::DTD_T lSegmentDTD = lSegmentDateOffset.days();
      
      //
      const stdair::SegmentCabinList_T& lSCList =
        stdair::BomManager::getList<stdair::SegmentCabin> (*lSD_ptr);
      for (stdair::SegmentCabinList_T::const_iterator itSC = lSCList.begin();
           itSC != lSCList.end(); ++itSC) {
        stdair::SegmentCabin* lSC_ptr = *itSC;
        assert (lSC_ptr != NULL);

        //
        // STDAIR_LOG_NOTIFICATION (ioFlightDate.getDepartureDate()
        //                          << ";" << lSegmentDTD);
        bool isForecasted = forecast (*lSC_ptr, lEventDate,
                                      iUnconstrainingMethod,
                                      iForecastingMethod);
        if (isForecasted == false) {
          isSucceeded = false;
        }
      }
    }

    return isSucceeded;
  }

  // ////////////////////////////////////////////////////////////////////
  bool Forecaster::
  forecast (stdair::SegmentCabin& ioSegmentCabin,
            const stdair::Date_T& iEventDate,
            const stdair::UnconstrainingMethod& iUnconstrainingMethod,
            const stdair::ForecastingMethod& iForecastingMethod) {
    // Retrieve the number of departed similar segments.
    stdair::NbOfSegments_T lNbOfDepartedSegments =
      Utilities::getNbOfDepartedSimilarSegments (ioSegmentCabin, iEventDate);

    // DEBUG
    // STDAIR_LOG_DEBUG ("Nb of similar departed segments: "
    //                   << lNbOfDepartedSegments);
    
    // If the number of departed segments are less than two, there
    // will be no forecast, and thus no optimisation.
    if (lNbOfDepartedSegments < 2) {
      return false;
    } else {
      setDemandForecastsToZero (ioSegmentCabin);
      const stdair::SegmentDate& lSegmentDate =
        stdair::BomManager::getParent<stdair::SegmentDate> (ioSegmentCabin);
      const stdair::Date_T& lBoardingDate = lSegmentDate.getBoardingDate();
      const stdair::DateOffset_T lDateOffset = lBoardingDate - iEventDate;
      const stdair::DTD_T& lDaysBeforeDeparture = lDateOffset.days();
      
      // If the forecasting method is QFF (old or new), but there are
      // not more than two fare families in the cabin, hybrid
      // forecasting will be used.
      const stdair::ForecastingMethod::EN_ForecastingMethod lForecastingMethod =
        iForecastingMethod.getMethod();
      switch (lForecastingMethod) {
      case stdair::ForecastingMethod::Q_FORECASTING: {
        return QForecasting::forecast (ioSegmentCabin, iEventDate,
                                       lDaysBeforeDeparture,
                                       iUnconstrainingMethod,
                                       lNbOfDepartedSegments);
      }
      case stdair::ForecastingMethod::HYBRID_FORECASTING: {
        return HybridForecasting::forecast (ioSegmentCabin, iEventDate,
                                            lDaysBeforeDeparture,
                                            iUnconstrainingMethod,
                                            lNbOfDepartedSegments);
      }
      case stdair::ForecastingMethod::NEW_QFF: {
        if (ioSegmentCabin.getFareFamilyStatus()==false) {
          
          return HybridForecasting::forecast (ioSegmentCabin, iEventDate,
                                              lDaysBeforeDeparture,
                                              iUnconstrainingMethod,
                                              lNbOfDepartedSegments);
        } else {
          return NewQFF::forecast (ioSegmentCabin, iEventDate,
                                   lDaysBeforeDeparture, iUnconstrainingMethod,
                                   lNbOfDepartedSegments);
        }
      }
      case stdair::ForecastingMethod::OLD_QFF: {
        if (ioSegmentCabin.getFareFamilyStatus()==false) {
          
          return HybridForecasting::forecast (ioSegmentCabin, iEventDate,
                                              lDaysBeforeDeparture,
                                              iUnconstrainingMethod,
                                              lNbOfDepartedSegments);
        } else {
          return OldQFF::forecast (ioSegmentCabin, iEventDate,
                                   lDaysBeforeDeparture, iUnconstrainingMethod,
                                   lNbOfDepartedSegments);
        }
      }
      case stdair::ForecastingMethod::BASED_FORECASTING: {
        return BasedForecasting::forecast (ioSegmentCabin, iEventDate,
                                            lDaysBeforeDeparture,
                                            iUnconstrainingMethod,
                                            lNbOfDepartedSegments);
      }
      default:{
        assert (false);
        break;
      }
      }
      return false;
    }
  }
  
  // ////////////////////////////////////////////////////////////////////
  void Forecaster::
  setDemandForecastsToZero(const stdair::SegmentCabin& iSegmentCabin) {
    // Set the demand forecast for all classes and fare families to zero.
    const stdair::FareFamilyList_T& lFFList =
      stdair::BomManager::getList<stdair::FareFamily> (iSegmentCabin);
    for (stdair::FareFamilyList_T::const_iterator itFF = lFFList.begin();
         itFF != lFFList.end(); ++itFF) {
      stdair::FareFamily* lFF_ptr = *itFF;
      assert (lFF_ptr != NULL);
      lFF_ptr->setMean (0.0);
      lFF_ptr->setStdDev (0.0);
      
      const stdair::BookingClassList_T& lBCList =
        stdair::BomManager::getList<stdair::BookingClass> (*lFF_ptr);
      for (stdair::BookingClassList_T::const_iterator itBC = lBCList.begin();
           itBC != lBCList.end(); ++itBC) {
        stdair::BookingClass* lBC_ptr = *itBC;
        assert (lBC_ptr != NULL);
        lBC_ptr->setMean (0.0);
        lBC_ptr->setStdDev (0.0);
        lBC_ptr->setPriceDemMean (0.0);
        lBC_ptr->setPriceDemStdDev (0.0);
        lBC_ptr->setProductDemMean (0.0);
        lBC_ptr->setProductDemStdDev (0.0);
        lBC_ptr->setCumuPriceDemMean (0.0);
        lBC_ptr->setCumuPriceDemStdDev (0.0);
      }
    }
  }
}
