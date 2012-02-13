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
#include <stdair/basic/RandomGeneration.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/SegmentSnapshotTable.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/basic/BasConst_Curves.hpp>
#include <rmol/bom/Utilities.hpp>
#include <rmol/bom/SegmentSnapshotTableHelper.hpp>
#include <rmol/bom/HistoricalBookingHolder.hpp>
#include <rmol/bom/HistoricalBooking.hpp>
#include <rmol/bom/EMDetruncator.hpp>
#include <rmol/command/Forecaster.hpp>
#include <rmol/command/Detruncator.hpp>

namespace RMOL {

  // ////////////////////////////////////////////////////////////////////
  bool Forecaster::
  forecastUsingAddPkUp (stdair::FlightDate& ioFlightDate,
                        const stdair::DateTime_T& iEventTime) {
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
        bool isForecasted = forecastUsingAddPkUp (*lSC_ptr, lEventDate);
        if (isForecasted == false) {
          isSucceeded = false;
        }
      }
    }

    return isSucceeded;
  }

  // ////////////////////////////////////////////////////////////////////
  bool Forecaster::
  forecastUsingAddPkUp (stdair::SegmentCabin& ioSegmentCabin,
                        const stdair::Date_T& iEventDate) {
    // Retrieve the number of departed similar segments.
    stdair::NbOfSegments_T lNbOfDepartedSegments =
      Utilities::getNbOfDepartedSimilarSegments (ioSegmentCabin, iEventDate);
    // TODO
    if (lNbOfDepartedSegments > 52) lNbOfDepartedSegments = 52; 

    // DEBUG
    // STDAIR_LOG_DEBUG ("Nb of similar departed segments: "
    //                   << lNbOfDepartedSegments);
    
    // If the number of departed segments are less than two, remaining
    // demand for all classes will be set to zero.
    if (lNbOfDepartedSegments < 2) {
      setAchievableDemandForecastToZero (ioSegmentCabin);
      return false;
    } else {      
      // Initialise the holders for the unconstrained demand.
      // There are a list of cumulative unconstrained demand at DCP's for
      // each departed segment.
      stdair::UncDemCurveHolder_T lUncQDemCurveHolder (lNbOfDepartedSegments);
      stdair::BookingClassUncDemCurveHolderMap_T lBCUncDemCurveHolderMap;

      stdair::UncDemVector_T lQEquivalentDemandVector (lNbOfDepartedSegments, 0.0);
      stdair::BookingClassUncDemVectorMap_T lBkgClassUncDemMap;
      const stdair::BookingClassList_T& lBCList =
        stdair::BomManager::getList<stdair::BookingClass> (ioSegmentCabin);
      for (stdair::BookingClassList_T::const_iterator itBC = lBCList.begin();
           itBC != lBCList.end(); ++itBC) {
        stdair::BookingClass* lBC_ptr = *itBC;
        assert (lBC_ptr != NULL);
        stdair::UncDemVector_T lUncDemandVector (lNbOfDepartedSegments, 0.0);
        bool insertionSucceeded = lBkgClassUncDemMap.insert
          (stdair::BookingClassUncDemVectorMap_T::
           value_type (lBC_ptr, lUncDemandVector)).second;
        assert (insertionSucceeded == true);
        
        stdair::UncDemCurveHolder_T lUncDemCurveHolder (lNbOfDepartedSegments);
        insertionSucceeded = lBCUncDemCurveHolderMap.insert
          (stdair::BookingClassUncDemCurveHolderMap_T::
           value_type (lBC_ptr, lUncDemCurveHolder)).second;
        assert (insertionSucceeded == true);
      }
      
      // Build the DCP intervals and unconstrain censored booking figures for
      // each interval.
      const stdair::DCPList_T lWholeDCPList = stdair::DEFAULT_DCP_LIST;
      stdair::DCPList_T::const_iterator itDCP = lWholeDCPList.begin();
      stdair::DCPList_T::const_iterator itNextDCP = itDCP; ++itNextDCP;
      for (; itNextDCP != lWholeDCPList.end(); ++itDCP, ++itNextDCP) {
        const stdair::DCP_T& lCurrentDCP = *itDCP;
	const stdair::DCP_T& lNextDCP = *itNextDCP;

        // DEBUG
        // STDAIR_LOG_DEBUG ("Unconstrain demand for "
        //                   << ioSegmentCabin.describeKey()
        //                   << " and the DCP's " << lCurrentDCP << ", "
        //                   << lNextDCP);
	Detruncator::unconstrainUsingAddPkUp (ioSegmentCabin,
                                              lBkgClassUncDemMap,
                                              lQEquivalentDemandVector,
                                              lCurrentDCP-1, lNextDCP,
                                              iEventDate);
        //STDAIR_LOG_DEBUG ("Detruncation successful");

        // Added the new unconstrained demand values to the curve holders.
        for (int i = 0; i < lNbOfDepartedSegments; ++i) {
          // The Q-equivalent demand
          stdair::UncDemCurve_T& lUncQDemCurve = lUncQDemCurveHolder.at(i);
          stdair::NbOfRequests_T& lUncQDem = lQEquivalentDemandVector.at(i);
          lUncQDemCurve.push_back (lUncQDem);

          // The product-oriented demand
          for (stdair::BookingClassUncDemCurveHolderMap_T::iterator itBCUDCH =
                 lBCUncDemCurveHolderMap.begin();
               itBCUDCH != lBCUncDemCurveHolderMap.end(); ++itBCUDCH) {
            stdair::BookingClass* lBC_ptr = itBCUDCH->first;
            stdair::UncDemCurveHolder_T lClassUncDemCurveHolder =
              itBCUDCH->second;
            stdair::BookingClassUncDemVectorMap_T::iterator itBCUDV =
              lBkgClassUncDemMap.find (lBC_ptr);
            assert (itBCUDV != lBkgClassUncDemMap.end());
            stdair::UncDemVector_T& lClassUncDemVector = itBCUDV->second;

            stdair::UncDemCurve_T& lClassUncDemCurve =
              lClassUncDemCurveHolder.at(i);
            stdair::NbOfRequests_T& lClassUncDem = lClassUncDemVector.at(i);
            lClassUncDemCurve.push_back (lClassUncDem);
          }
        }
      }
      
      distributeQEquiUncDemToClasses (lUncQDemCurveHolder,
                                      lBCUncDemCurveHolderMap, lBCList);
      //forecastUsingAddPkUp (ioSegmentCabin, lBCUncDemCurveHolderMap);
      return true;
    }
  }

  // ////////////////////////////////////////////////////////////////////
  stdair::BookingClassSellUpCurveMap_T Forecaster::
  computeSellUpFactorCurves (const stdair::SellUpCurve_T& iSellUpCoefVector,
                             const stdair::BookingClassList_T& iBCList) {
    stdair::BookingClassSellUpCurveMap_T oBCSellUpFactorMap;

    // Initialise a sell-up factor curve of 1.0 values
    stdair::SellUpCurve_T lBasedSellUpCurve (iSellUpCoefVector.size(), 1.0);
    
    // Retrieve the classes from low to high and compute the distributions of
    // product-oriented and price-oriented demand.
    // Retrieve the lowest class.
    stdair::BookingClassList_T::const_reverse_iterator itCurrentClass =
      iBCList.rbegin();
    assert (itCurrentClass != iBCList.rend());
    stdair::BookingClassList_T::const_reverse_iterator itNextClass =
      itCurrentClass;
    ++itNextClass;
    // If there is only one class in the cabin, all the sell-up factors
    // will be 1.
    stdair::BookingClass* lLowestBC_ptr = *itCurrentClass;
    assert (lLowestBC_ptr != NULL);
    const stdair::Yield_T& lLowestYield = lLowestBC_ptr->getYield();
    if (itNextClass == iBCList.rend()) {
      bool insert = oBCSellUpFactorMap.
        insert (stdair::BookingClassSellUpCurveMap_T::
               value_type(lLowestBC_ptr, lBasedSellUpCurve)).second;
      assert (insert == true);
    } else {
      // Compute the demand for higher class using the formula
      // Pro_sell_up_from_Q_to_F = e ^ ((y_F/y_Q - 1) * ln (0.5) / (FRAT5 - 1))
      for (; itNextClass != iBCList.rend(); ++itCurrentClass, ++itNextClass) {
        stdair::BookingClass* lCurrentBC_ptr = *itCurrentClass;
        stdair::BookingClass* lNextBC_ptr = *itNextClass;
        assert (lNextBC_ptr != NULL);
        const stdair::Yield_T& lNextYield = lNextBC_ptr->getYield();

        // Compute the sell-up factor curve for the current class.
        stdair::SellUpCurve_T lCurrentSellUpCurve;
        for (unsigned int i = 0; i < iSellUpCoefVector.size(); ++i) {
          const double& lSellUpCoef = iSellUpCoefVector.at(i);
          double lSellUpFactor = 
            exp ((1.0 - lNextYield/lLowestYield) * lSellUpCoef);
          double& lBasedFactor = lBasedSellUpCurve.at(i);
          lCurrentSellUpCurve.push_back (lBasedFactor - lSellUpFactor);
          lBasedFactor = lSellUpFactor;
        }
        bool insert = oBCSellUpFactorMap.
          insert (stdair::BookingClassSellUpCurveMap_T::
                 value_type(lCurrentBC_ptr, lCurrentSellUpCurve)).second;
        assert (insert == true);
      }

      // Compute the sell-up factor curve for the highest class (which is the
      // "current class")
      stdair::BookingClass* lCurrentBC_ptr = *itCurrentClass;
      bool insert = oBCSellUpFactorMap.
        insert (stdair::BookingClassSellUpCurveMap_T::
               value_type(lCurrentBC_ptr, lBasedSellUpCurve)).second;
      assert (insert == true);
    }
    return oBCSellUpFactorMap;
  }

  // ////////////////////////////////////////////////////////////////////
  void Forecaster::
  distributeQEquiUncDemToClasses (stdair::UncDemCurveHolder_T& iUncQDemCurveHolder,
                                  stdair::BookingClassUncDemCurveHolderMap_T& iBCUncDemCurveHolderMap,
                                  const stdair::BookingClassList_T& iBCList) {

    // Precompute the sell-up coefficient based on FRAT5 curve
    std::vector<double> lSellUpCoefVector;
    for (stdair::FRAT5Curve_T::const_reverse_iterator itFRAT5 =
           DEFAULT_FRAT5_CURVE.rbegin();
         itFRAT5 != DEFAULT_FRAT5_CURVE.rend(); ++itFRAT5) {
      const double lFRAT5Coef = itFRAT5->second;
      const double lSellUpCoef = -log(0.5) / (lFRAT5Coef - 1);
      lSellUpCoefVector.push_back (lSellUpCoef);      
    }

    // Precompute the sell-up factors for each class and each DCP.
    stdair::BookingClassSellUpCurveMap_T lBCSellUpFactorMap =
      computeSellUpFactorCurves (lSellUpCoefVector, iBCList);

    // Browse the holder of Q-Equivalent demand (by segment-date) then
    // browse the Q-Equivalent demand curve (by DCP) and make the distribution.

    // Browse by segment-date
    for (unsigned int i = 0; i < iUncQDemCurveHolder.size(); ++i) {
      //const UncDemCurve_T& lCurrentQDemandCurve = iUncQDemCurveHolder.at(i);
    }

  }
  
  // ////////////////////////////////////////////////////////////////////
  void Forecaster::
  setAchievableDemandForecastToZero(const stdair::SegmentCabin& iSegmentCabin) {
    // Set the demand forecast for all classes to zero.
    const stdair::BookingClassList_T& lBCList =
      stdair::BomManager::getList<stdair::BookingClass> (iSegmentCabin);
    for (stdair::BookingClassList_T::const_iterator itBC = lBCList.begin();
         itBC != lBCList.end(); ++itBC) {
      stdair::BookingClass* lBC_ptr = *itBC;
      assert (lBC_ptr != NULL);
      lBC_ptr->setMean (0.0);
    }
  }
}
