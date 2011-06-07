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
#include <stdair/bom/GuillotineBlock.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/basic/BasConst_Curves.hpp>
#include <rmol/bom/Utilities.hpp>
#include <rmol/bom/GuillotineBlockHelper.hpp>
#include <rmol/command/Forecaster.hpp>
#include <rmol/command/Detruncator.hpp>

namespace RMOL {

  // ////////////////////////////////////////////////////////////////////
  bool Forecaster::forecast (stdair::FlightDate& ioFlightDate,
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

      const stdair::Date_T& lBoardingDate = lSD_ptr->getBoardingDate();
      const stdair::DateOffset_T lSegmentDateOffset =
        lBoardingDate - lEventDate;
      const stdair::DTD_T lSegmentDTD = lSegmentDateOffset.days();

      // Build remaining DCP's for the segment-date.
      const stdair::DCPList_T lDCPList =
        buildRemainingDCPList (lSegmentDTD);
      
      //
      const stdair::SegmentCabinList_T& lSCList =
        stdair::BomManager::getList<stdair::SegmentCabin> (*lSD_ptr);
      for (stdair::SegmentCabinList_T::const_iterator itSC = lSCList.begin();
           itSC != lSCList.end(); ++itSC) {
        stdair::SegmentCabin* lSC_ptr = *itSC;
        assert (lSC_ptr != NULL);

        bool isForecasted = forecast (*lSC_ptr, lDCPList, lEventDate);
        if (isForecasted == false) {
          isSucceeded = false;
        }
      }
    }

    return isSucceeded;
  }

  // ////////////////////////////////////////////////////////////////////
  stdair::DCPList_T Forecaster::
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
  bool Forecaster::forecast (stdair::SegmentCabin& ioSegmentCabin,
                             const stdair::DCPList_T& iDCPList,
                             const stdair::Date_T& iEventDate) {
    // Retrieve the number of departed similar segments.
    const stdair::NbOfSegments_T lNbOfDepartedSegments =
      getNbOfDepartedSimilarSegments (ioSegmentCabin, iEventDate);

    // DEBUG
    STDAIR_LOG_DEBUG ("Nb of similar departed segments: "
                      << lNbOfDepartedSegments);
    
    // If the DCP list includes only DTD0 or the number of departed
    // segments are less than two, remaining demand for all classes
    // will be set to zero.
    stdair::DCPList_T::const_iterator itDCP = iDCPList.begin();
    assert (itDCP != iDCPList.end());
    const stdair::DCP_T& lCurrentDTD = *itDCP;
    if (iDCPList.size() == 1 || lNbOfDepartedSegments < 2) {
      setRemainingDemandForecastToZero (ioSegmentCabin);
      return false;
    } else {      
      // Initialise a holder for the unconstrained demand.
      UnconstrainedDemandVector_T lQEquivalentDemandVector (lNbOfDepartedSegments, 0.0);
      BookingClassUnconstrainedDemandMap_T lBkgClassUncDemMap;
      const stdair::BookingClassList_T& lBCList =
        stdair::BomManager::getList<stdair::BookingClass> (ioSegmentCabin);
      for (stdair::BookingClassList_T::const_iterator itBC = lBCList.begin();
           itBC != lBCList.end(); ++itBC) {
        stdair::BookingClass* lBC_ptr = *itBC;
        assert (lBC_ptr != NULL);
        std::vector<stdair::NbOfRequests_T> lUncDemandVector (lNbOfDepartedSegments, 0.0);
        bool insertionSucceeded = lBkgClassUncDemMap.insert
          (BookingClassUnconstrainedDemandMap_T::
           value_type (lBC_ptr, lUncDemandVector)).second;
        assert (insertionSucceeded == true);
      }
      
      // Build the DCP intervals and unconstrain censored booking figures for
      // each interval.
      stdair::DCPList_T::const_iterator itNextDCP = itDCP; ++itNextDCP;
      for (; itNextDCP != iDCPList.end(); ++itDCP, ++itNextDCP) {
        const stdair::DCP_T& lCurrentDCP = *itDCP;
	const stdair::DCP_T& lNextDCP = *itNextDCP;

        // DEBUG
        // STDAIR_LOG_DEBUG ("Unconstrain demand for "
        //                   << ioSegmentCabin.describeKey()
        //                   << " and the DCP's " << lCurrentDCP << ", "
        //                   << lNextDCP);
	Detruncator::unconstrain (ioSegmentCabin, lBkgClassUncDemMap,
                                  lQEquivalentDemandVector,
                                  lCurrentDCP, lNextDCP+1, iEventDate);
        // STDAIR_LOG_DEBUG ("Detrucation successful");
      }
      
      // Retrieve the FRAT5 coefficient and compute the sell-up coef.
      FRAT5Curve_T::const_iterator itFRAT5 =
        DEFAULT_CUMULATIVE_FRAT5_CURVE.lower_bound (lCurrentDTD);
      assert (itFRAT5 != DEFAULT_CUMULATIVE_FRAT5_CURVE.end());
      const double lFRAT5Coef = itFRAT5->second;
      const double lSellUpCoef = -log(0.5) / (lFRAT5Coef - 1); 
      
      forecast (ioSegmentCabin, lBkgClassUncDemMap, lQEquivalentDemandVector,
                lSellUpCoef);
      return true;
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void Forecaster::
  forecast (stdair::SegmentCabin& ioSegmentCabin,
            const BookingClassUnconstrainedDemandMap_T& iClassUncDemMap,
            const UnconstrainedDemandVector_T& iUncDemVector,
            const double& iSellUpFactor) {
    double lPriceOriMean; double lPriceOriStdDev;
    Utilities::computeDistributionParameters (iUncDemVector, lPriceOriMean,
                                              lPriceOriStdDev);

    // DEBUG
    STDAIR_LOG_DEBUG ("Price-oriented demand: mean = " << lPriceOriMean
                      << ", stddev = " << lPriceOriStdDev);
    
    // Retrieve the classes from low to high and compute the distributions of
    // product-oriented and price-oriented demand.
    // Retrieve the lowest class.
    const stdair::BookingClassList_T& lBCList =
      stdair::BomManager::getList<stdair::BookingClass> (ioSegmentCabin);
    stdair::BookingClassList_T::const_reverse_iterator itCurrentClass =
      lBCList.rbegin();
    assert (itCurrentClass != lBCList.rend());    
    stdair::BookingClassList_T::const_reverse_iterator itNextClass =
      itCurrentClass;
    ++itNextClass;
    // If there is only one class in the cabin, the demand distribution of this
    // class is equal to the price-oriented demand distribution of the cabin.
    if (itNextClass == lBCList.rend()) {
      stdair::BookingClass* lLowestBC_ptr = *itCurrentClass;
      lLowestBC_ptr->setMean (lPriceOriMean);
      lLowestBC_ptr->setStdDev (lPriceOriStdDev);
    } else {
      // Compute the demand for higher class using the formula
      // Pro_sell_up_from_Q_to_F = e ^ ((y_F/y_Q - 1) * ln (0.5) / (FRAT5 - 1))
      for (; itNextClass != lBCList.rend(); ++itCurrentClass, ++itNextClass) {
        stdair::BookingClass* lCurrentBC_ptr = *itCurrentClass;
        assert (lCurrentBC_ptr != NULL);
        const stdair::Yield_T& lCurrentYield = lCurrentBC_ptr->getYield();
        stdair::BookingClass* lNextBC_ptr = *itNextClass;
        assert (lNextBC_ptr != NULL);
        const stdair::Yield_T& lNextYield = lNextBC_ptr->getYield();

        // Compute the part of price-oriented demand distributed to the
        // current class.
        const double lSellUp =
          exp ((1.0 - lNextYield/lCurrentYield) * iSellUpFactor);
        const double lPriceOriDemMeanFrac = lPriceOriMean * (1.0 - lSellUp);
        const double lPriceOriDemStdDevFrac = lPriceOriStdDev * (1.0 - lSellUp);

        // Compute the product-oriented demand distribution for the
        // current class.
        BookingClassUnconstrainedDemandMap_T::const_iterator itBCUD =
          iClassUncDemMap.find (lCurrentBC_ptr);
        assert (itBCUD != iClassUncDemMap.end());
        const UnconstrainedDemandVector_T& lDemandVector = itBCUD->second;
        double lMean; double lStdDev;
        Utilities::computeDistributionParameters(lDemandVector, lMean, lStdDev);
        
        // Compute the demand distribution for the current class;
        lMean += lPriceOriDemMeanFrac;
        lStdDev = sqrt (lStdDev * lStdDev +
                        lPriceOriDemStdDevFrac * lPriceOriDemStdDevFrac);
        lCurrentBC_ptr->setMean (lMean);
        lCurrentBC_ptr->setStdDev (lStdDev);
        
        // DEBUG
        STDAIR_LOG_DEBUG ("Class " << lCurrentBC_ptr->describeKey()
                          << ", mean = " << lMean
                          << ", stddev = " << lStdDev);

        // Update the price-oriented demand
        lPriceOriMean *= lSellUp;
        lPriceOriStdDev *= lSellUp;
      }

      // Compute the demand distribution for the highest class (which is the
      // "current class")
      stdair::BookingClass* lCurrentBC_ptr = *itCurrentClass;
      assert (lCurrentBC_ptr != NULL);
      BookingClassUnconstrainedDemandMap_T::const_iterator itBCUD =
        iClassUncDemMap.find (lCurrentBC_ptr);
      assert (itBCUD != iClassUncDemMap.end());
      const UnconstrainedDemandVector_T& lDemandVector = itBCUD->second;
      double lMean; double lStdDev;
      Utilities::computeDistributionParameters(lDemandVector, lMean, lStdDev);
        
      // Compute the demand distribution for the current class;
      lMean += lPriceOriMean;
      lStdDev = sqrt (lStdDev * lStdDev + lPriceOriStdDev * lPriceOriStdDev);
      lCurrentBC_ptr->setMean (lMean);
      lCurrentBC_ptr->setStdDev (lStdDev);

      // DEBUG
      STDAIR_LOG_DEBUG ("Class " << lCurrentBC_ptr->describeKey()
                        << ", mean = " << lMean
                        << ", stddev = " << lStdDev);
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void Forecaster::
  setRemainingDemandForecastToZero (const stdair::SegmentCabin& iSegmentCabin) {
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

  // ////////////////////////////////////////////////////////////////////
  stdair::NbOfSegments_T Forecaster::
  getNbOfDepartedSimilarSegments (const stdair::SegmentCabin& iSegmentCabin,
                                  const stdair::Date_T& iEventDate) {
    stdair::DTD_T lDTD = 0;
    // Retrieve the guillotine block.
    const stdair::GuillotineBlock& lGuillotineBlock =
      iSegmentCabin.getGuillotineBlock();
    return GuillotineBlockHelper::
      getNbOfSegmentAlreadyPassedThisDTD (lGuillotineBlock, lDTD, iEventDate);
  }
}
