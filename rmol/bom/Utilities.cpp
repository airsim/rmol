
// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <string>
#include <numeric>
#include <algorithm>
#include <cmath>
// StdAir
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/FareFamily.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/BookingClassTypes.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/basic/BasConst_General.hpp>
#include <rmol/bom/Utilities.hpp>
#include <rmol/bom/SegmentSnapshotTableHelper.hpp>

namespace RMOL {
  // ////////////////////////////////////////////////////////////////////
  void Utilities::
  computeDistributionParameters (const stdair::UncDemVector_T& iVector,
                                 stdair::MeanValue_T& ioMean,
                                 stdair::StdDevValue_T& ioStdDev) {
    ioMean = 0.0; ioStdDev = 0.0;
    const stdair::NbOfSamples_T lNbOfSamples = iVector.size();
    assert (lNbOfSamples > 1);

    // Compute the mean
    for (stdair::UncDemVector_T::const_iterator itSample = iVector.begin();
         itSample != iVector.end(); ++itSample) {
      //STDAIR_LOG_NOTIFICATION (*itSample);
      ioMean += *itSample;
    }
    ioMean /= lNbOfSamples;

    // Compute the standard deviation
    for (stdair::UncDemVector_T::const_iterator itSample = iVector.begin();
         itSample != iVector.end(); ++itSample) {
      const stdair::MeanValue_T& lSample = *itSample;
      ioStdDev += ((lSample - ioMean) * (lSample - ioMean));
    }
    ioStdDev /= (lNbOfSamples - 1);
    ioStdDev = std::sqrt (ioStdDev);

    // Sanity check
    if (ioStdDev == 0) {
      ioStdDev = 0.1;
    }
  }

  // ////////////////////////////////////////////////////////////////////
  stdair::DCPList_T Utilities::
  buildRemainingDCPList (const stdair::DTD_T& iDTD) {
    stdair::DCPList_T oDCPList;

    const stdair::DCPList_T lWholeDCPList = stdair::DEFAULT_DCP_LIST;
    stdair::DCPList_T::const_iterator itDCP = lWholeDCPList.begin();
    while (itDCP != lWholeDCPList.end()) {
      const stdair::DCP_T& lDCP = *itDCP;
      if (iDTD >= lDCP) {
        break;
      }
      ++itDCP;
    }
    assert (itDCP != lWholeDCPList.end());

    oDCPList.push_back (iDTD);
    ++itDCP;
    for (; itDCP != lWholeDCPList.end(); ++itDCP) {
      oDCPList.push_back (*itDCP);
    }
    
    return oDCPList;
  }

  // ////////////////////////////////////////////////////////////////////
  stdair::DCPList_T Utilities::
  buildPastDCPList (const stdair::DTD_T& iDTD) {
    stdair::DCPList_T oDCPList;

    const stdair::DCPList_T lWholeDCPList = stdair::DEFAULT_DCP_LIST;
    stdair::DCPList_T::const_iterator itDCP = lWholeDCPList.begin();
    while (itDCP != lWholeDCPList.end()) {
      const stdair::DCP_T& lDCP = *itDCP;
      if (iDTD <= lDCP) {
        oDCPList.push_back (lDCP);
        ++itDCP;
      } else {
        break;
      }
    }
    
    return oDCPList;
  }
  
  // ////////////////////////////////////////////////////////////////////
  stdair::NbOfSegments_T Utilities::
  getNbOfDepartedSimilarSegments (const stdair::SegmentCabin& iSegmentCabin,
                                  const stdair::Date_T& iEventDate) {
    stdair::DTD_T lDTD = 0;
    // Retrieve the guillotine block.
    const stdair::SegmentSnapshotTable& lSegmentSnapshotTable =
      iSegmentCabin.getSegmentSnapshotTable();
    return SegmentSnapshotTableHelper::
      getNbOfSegmentAlreadyPassedThisDTD (lSegmentSnapshotTable, lDTD, iEventDate);
  }

  // ////////////////////////////////////////////////////////////////////
  stdair::BookingClassSellUpCurveMap_T Utilities::
  computeSellUpFactorCurves (const stdair::FRAT5Curve_T& iFRAT5Curve,
                             const stdair::BookingClassList_T& iBCList) {
    stdair::BookingClassSellUpCurveMap_T oBCSellUpFactorMap;

    // Initialise a sell-up factor curve of 1.0 values
    stdair::SellUpCurve_T lBasedSellUpCurve;
    for (stdair::FRAT5Curve_T::const_iterator itFRAT5 = iFRAT5Curve.begin();
         itFRAT5 != iFRAT5Curve.end(); ++itFRAT5) {
      const stdair::DTD_T& lDTD = itFRAT5->first;
      lBasedSellUpCurve.insert(stdair::SellUpCurve_T::value_type(lDTD, 1.0));
    }
    
    // Retrieve the classes from low to high and compute the distributions of
    // product-oriented and price-oriented demand.
    // Retrieve the lowest class.
    stdair::BookingClassList_T::const_reverse_iterator itCurrentClass =
      iBCList.rbegin();
    assert (itCurrentClass != iBCList.rend());
    
    // If there is only one class in the cabin, all the sell-up factors
    // will be 1.
    stdair::BookingClass* lLowestBC_ptr = *itCurrentClass;
    assert (lLowestBC_ptr != NULL);
    const stdair::Yield_T& lLowestYield = lLowestBC_ptr->getYield();
    bool insert = oBCSellUpFactorMap.
      insert (stdair::BookingClassSellUpCurveMap_T::
              value_type(lLowestBC_ptr, lBasedSellUpCurve)).second;
    assert (insert == true);
    ++itCurrentClass;
    
    // Compute the demand for higher class using the formula
    // Pro_sell_up_from_Q_to_F = e ^ ((y_F/y_Q - 1) * ln (0.5) / (FRAT5 - 1))
    for (; itCurrentClass != iBCList.rend(); ++itCurrentClass) {
      stdair::BookingClass* lCurrentBC_ptr = *itCurrentClass;
      assert (lCurrentBC_ptr != NULL);
      const stdair::Yield_T& lCurrentYield = lCurrentBC_ptr->getYield();

      // Compute the sell-up factor curve for the current class.
      stdair::SellUpCurve_T lCurrentSellUpCurve;
      for (stdair::FRAT5Curve_T::const_iterator itFRAT5 = iFRAT5Curve.begin();
           itFRAT5 != iFRAT5Curve.end(); ++itFRAT5) {
        const stdair::DTD_T& lDTD = itFRAT5->first;
        const stdair::FRAT5_T& lFRAT5 = itFRAT5->second;
        const double lSellUpCoef = log(0.5)/(lFRAT5-1);
        const stdair::SellupProbability_T lSellUpFactor = 
          exp ((lCurrentYield/lLowestYield - 1.0) * lSellUpCoef);
        const bool isInsertionSuccessful =
          lCurrentSellUpCurve.insert (stdair::SellUpCurve_T::value_type(lDTD, lSellUpFactor)).second;
        assert (isInsertionSuccessful == true);
      }
      const bool isInsertionSuccessful = oBCSellUpFactorMap.
        insert (stdair::BookingClassSellUpCurveMap_T::
                value_type(lCurrentBC_ptr, lCurrentSellUpCurve)).second;
      assert (isInsertionSuccessful == true);
    }
    return oBCSellUpFactorMap;
  }

  
  // ////////////////////////////////////////////////////////////////////
  stdair::BookingClassDispatchingCurveMap_T Utilities::
  computeDispatchingFactorCurves (const stdair::FRAT5Curve_T& iFRAT5Curve,
                                  const stdair::BookingClassList_T& iBCList) {
    stdair::BookingClassDispatchingCurveMap_T oBCDispatchingFactorMap;

    // Initialise a sell-up factor curve of 1.0 values
    stdair::DispatchingCurve_T lBasedDispatchingCurve;
    for (stdair::FRAT5Curve_T::const_iterator itFRAT5 = iFRAT5Curve.begin();
         itFRAT5 != iFRAT5Curve.end(); ++itFRAT5) {
      const stdair::DTD_T& lDTD = itFRAT5->first;
      lBasedDispatchingCurve.insert(stdair::DispatchingCurve_T::value_type(lDTD, 1.0));
    }
    
    // Retrieve the classes from low to high and compute the distributions of
    // product-oriented and price-oriented demand.
    // Retrieve the lowest class.
    stdair::BookingClassList_T::const_reverse_iterator itCurrentClass =
      iBCList.rbegin();
    assert (itCurrentClass != iBCList.rend());
    stdair::BookingClassList_T::const_reverse_iterator itNextClass =
      itCurrentClass; ++itNextClass;
    
    // If there is only one class in the cabin, all the sell-up factors
    // will be 1.
    stdair::BookingClass* lLowestBC_ptr = *itCurrentClass;
    assert (lLowestBC_ptr != NULL);
    const stdair::Yield_T& lLowestYield = lLowestBC_ptr->getYield();
    if (itNextClass == iBCList.rend()) {
      bool insert = oBCDispatchingFactorMap.
        insert (stdair::BookingClassDispatchingCurveMap_T::
               value_type(lLowestBC_ptr, lBasedDispatchingCurve)).second;
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
        stdair::DispatchingCurve_T lCurrentDispatchingCurve;
        for (stdair::FRAT5Curve_T::const_iterator itFRAT5 = iFRAT5Curve.begin();
         itFRAT5 != iFRAT5Curve.end(); ++itFRAT5) {
          const stdair::DTD_T& lDTD = itFRAT5->first;
          const stdair::FRAT5_T& lFRAT5 = itFRAT5->second;
          const double lDispatchingCoef = log(0.5)/(lFRAT5-1);
          double lDispatchingFactor = 
            exp ((lNextYield/lLowestYield - 1.0) * lDispatchingCoef);
          stdair::DispatchingCurve_T::iterator itBasedDispatching =
            lBasedDispatchingCurve.find (lDTD);
          assert (itBasedDispatching != lBasedDispatchingCurve.end());
          double& lBasedFactor = itBasedDispatching->second;
          bool insert = lCurrentDispatchingCurve.insert (stdair::DispatchingCurve_T::value_type(lDTD, lBasedFactor - lDispatchingFactor)).second;
          assert (insert == true);
          lBasedFactor = lDispatchingFactor;
        }
        bool insert = oBCDispatchingFactorMap.
          insert (stdair::BookingClassDispatchingCurveMap_T::
                 value_type(lCurrentBC_ptr, lCurrentDispatchingCurve)).second;
        assert (insert == true);
      }

      // Compute the sell-up factor curve for the highest class (which is the
      // "current class")
      stdair::BookingClass* lCurrentBC_ptr = *itCurrentClass;
      bool insert = oBCDispatchingFactorMap.
        insert (stdair::BookingClassDispatchingCurveMap_T::
               value_type(lCurrentBC_ptr, lBasedDispatchingCurve)).second;
      assert (insert == true);
    }
    return oBCDispatchingFactorMap;
  }

  // ////////////////////////////////////////////////////////////////////
  void Utilities::dispatchDemandForecast
  (const stdair::BookingClassDispatchingCurveMap_T& iBCDispatchingCurveMap,
   const stdair::MeanValue_T& iMean, 
   const stdair::StdDevValue_T& iStdDev,
   const stdair::DTD_T& iCurrentDCP) {
    for (stdair::BookingClassDispatchingCurveMap_T::const_iterator itBCDC =
           iBCDispatchingCurveMap.begin();
         itBCDC != iBCDispatchingCurveMap.end(); ++itBCDC) {
      stdair::BookingClass* lBC_ptr = itBCDC->first;
      assert (lBC_ptr != NULL);
      const stdair::DispatchingCurve_T& lDispatchingCurve = itBCDC->second;
      stdair::DispatchingCurve_T::const_iterator itDispatchingFactor =
        lDispatchingCurve.find (iCurrentDCP);
      assert (itDispatchingFactor != lDispatchingCurve.end());
      const double& lDF = itDispatchingFactor->second;

      const stdair::MeanValue_T& lCurrentMean = lBC_ptr->getPriceDemMean();
      const stdair::StdDevValue_T& lCurrentStdDev = lBC_ptr->getPriceDemStdDev();

      const stdair::MeanValue_T lAdditionalMean = iMean * lDF;
      const stdair::StdDevValue_T lAdditionalStdDev = iStdDev * std::sqrt (lDF);

      const stdair::MeanValue_T lNewMean = lCurrentMean + lAdditionalMean;
      const stdair::StdDevValue_T lNewStdDev = 
        std::sqrt (lCurrentStdDev * lCurrentStdDev
                   + lAdditionalStdDev * lAdditionalStdDev);

      lBC_ptr->setPriceDemMean (lNewMean);
      lBC_ptr->setPriceDemStdDev (lNewStdDev);
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void Utilities::dispatchDemandForecastForFA
  (const stdair::BookingClassSellUpCurveMap_T& iBCSellUpCurveMap,
   const stdair::MeanValue_T& iMean,
   const stdair::StdDevValue_T& iStdDev,
   const stdair::DTD_T& iCurrentDCP) {
    for (stdair::BookingClassSellUpCurveMap_T::const_iterator itBCSU =
           iBCSellUpCurveMap.begin();
         itBCSU != iBCSellUpCurveMap.end(); ++itBCSU) {
      stdair::BookingClass* lBC_ptr = itBCSU->first;
      assert (lBC_ptr != NULL);
      const stdair::SellUpCurve_T& lSellUpCurve = itBCSU->second;
      stdair::SellUpCurve_T::const_iterator itSellUpFactor =
        lSellUpCurve.find (iCurrentDCP);
      assert (itSellUpFactor != lSellUpCurve.end());
      const stdair::SellupProbability_T& lSU = itSellUpFactor->second;

      const stdair::MeanValue_T& lCurrentMean = lBC_ptr->getCumuPriceDemMean();
      const stdair::StdDevValue_T& lCurrentStdDev = 
        lBC_ptr->getCumuPriceDemStdDev();

      const stdair::MeanValue_T lAdditionalMean = iMean * lSU;
      const stdair::StdDevValue_T lAdditionalStdDev = iStdDev * std::sqrt (lSU);

      const stdair::MeanValue_T lNewMean = lCurrentMean + lAdditionalMean;
      const stdair::StdDevValue_T lNewStdDev = 
        std::sqrt (lCurrentStdDev * lCurrentStdDev
                   + lAdditionalStdDev * lAdditionalStdDev);

      lBC_ptr->setCumuPriceDemMean (lNewMean);
      lBC_ptr->setCumuPriceDemStdDev (lNewStdDev);
    }
  }
}
