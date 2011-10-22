// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
<<<<<<< HEAD
#include <math.h>
// RMOL
#include <rmol/bom/Bucket.hpp>
#include <rmol/bom/BucketHolder.hpp>
#include <rmol/bom/HistoricalBooking.hpp>
#include <rmol/bom/HistoricalBookingHolder.hpp>
#include <rmol/bom/HistoricalBookingHolderHolder.hpp>
#include <rmol/bom/SellupProbabilityCalculator.hpp>
#include <rmol/bom/QEquivalentBookingCalculator.hpp>
#include <rmol/command/Forecaster.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  void Forecaster::qEquivalentBookingCalculation 
       (BucketHolder& ioBucketHolder,
        SellupFactorHolder_T& iSellupFactorHolder,
        HistoricalBookingHolderHolder& iHistoricalBookingHolderHolder,
        HolderOfQEquivalentBookingsPerSimilarFlight_T& 
                                      oQEquivalentBookingsPerSimilarFlight){

    // Get the lowest yield of the given buckets
    const double qYield = ioBucketHolder.getLowestAverageYield ();

    // Initialize a vector for sell-up probabilities
    std::vector<double> lSellupProbabilityVector;

    // Compute sell-up probability for each bucket and store it in a vector
    SellupProbabilityCalculator::calculateSellupProbability
      (ioBucketHolder, qYield, iSellupFactorHolder, lSellupProbabilityVector);
    
    // Compute total Q-equivalent bookings
    QEquivalentBookingCalculator::calculateQEquivalentBooking 
      (iHistoricalBookingHolderHolder, 
       lSellupProbabilityVector, 
       oQEquivalentBookingsPerSimilarFlight);
  }

  // //////////////////////////////////////////////////////////////////////  
  void Forecaster::demandForecastByQForecasting 
       (ForecastedDemandParameterList_T oForecastedDemandParameterList,
        HistoricalDataHolderHolder_T& iHistoricalDataHolderHolder,
        PriceHolder_T& iPriceHolder) {
    // Run Q-Forecasting algorithm
    // 1. Obtain forecasted Q-eqivalent demand mean and s.d.(mu_Q, sigma_Q)
    // 2. Partition to each class
    //    E(alpha x Q)=alpha x mu_Q, S.D.(alpha x Q) = |alpha| X sigma_Q

    //qEquivalentDemandCalculation();

  }
=======
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
#include <rmol/bom/HistoricalBookingHolder.hpp>
#include <rmol/bom/HistoricalBooking.hpp>
#include <rmol/bom/EMDetruncator.hpp>
#include <rmol/command/Forecaster.hpp>
#include <rmol/command/Detruncator.hpp>

namespace RMOL {

  // ////////////////////////////////////////////////////////////////////
  bool Forecaster::
  forecastUsingAdditivePickUp (stdair::FlightDate& ioFlightDate,
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
      // TODO: treat the case where the segment departure is not the
      // same as the flight-date departure.
      const stdair::DCPList_T lDCPList =
        Utilities::buildRemainingDCPList (lSegmentDTD);
      
      //
      const stdair::SegmentCabinList_T& lSCList =
        stdair::BomManager::getList<stdair::SegmentCabin> (*lSD_ptr);
      for (stdair::SegmentCabinList_T::const_iterator itSC = lSCList.begin();
           itSC != lSCList.end(); ++itSC) {
        stdair::SegmentCabin* lSC_ptr = *itSC;
        assert (lSC_ptr != NULL);

        bool isForecasted = forecastUsingAdditivePickUp (*lSC_ptr, lDCPList,
                                                         lEventDate);
        if (isForecasted == false) {
          isSucceeded = false;
        }
      }
    }

    return isSucceeded;
  }

  // ////////////////////////////////////////////////////////////////////
  bool Forecaster::
  forecastUsingAdditivePickUp (stdair::SegmentCabin& ioSegmentCabin,
                               const stdair::DCPList_T& iDCPList,
                               const stdair::Date_T& iEventDate) {
    // Retrieve the number of departed similar segments.
    const stdair::NbOfSegments_T lNbOfDepartedSegments =
      Utilities::getNbOfDepartedSimilarSegments (ioSegmentCabin, iEventDate);

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
      BookingClassUnconstrainedDemandVectorMap_T lBkgClassUncDemMap;
      const stdair::BookingClassList_T& lBCList =
        stdair::BomManager::getList<stdair::BookingClass> (ioSegmentCabin);
      for (stdair::BookingClassList_T::const_iterator itBC = lBCList.begin();
           itBC != lBCList.end(); ++itBC) {
        stdair::BookingClass* lBC_ptr = *itBC;
        assert (lBC_ptr != NULL);
        std::vector<stdair::NbOfRequests_T> lUncDemandVector (lNbOfDepartedSegments, 0.0);
        bool insertionSucceeded = lBkgClassUncDemMap.insert
          (BookingClassUnconstrainedDemandVectorMap_T::
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
        STDAIR_LOG_DEBUG ("Unconstrain demand for "
                          << ioSegmentCabin.describeKey()
                          << " and the DCP's " << lCurrentDCP << ", "
                          << lNextDCP);
	Detruncator::unconstrainUsingAdditivePickUp (ioSegmentCabin,
                                                     lBkgClassUncDemMap,
                                                     lQEquivalentDemandVector,
                                                     lCurrentDCP-1, lNextDCP,
                                                     iEventDate);
        STDAIR_LOG_DEBUG ("Detrucation successful");
      }
      
      // Retrieve the FRAT5 coefficient and compute the sell-up coef.
      FRAT5Curve_T::const_iterator itFRAT5 =
        DEFAULT_CUMULATIVE_FRAT5_CURVE.lower_bound (lCurrentDTD);
      assert (itFRAT5 != DEFAULT_CUMULATIVE_FRAT5_CURVE.end());
      const double lFRAT5Coef = itFRAT5->second;
      const double lSellUpCoef = -log(0.5) / (lFRAT5Coef - 1); 
      
      forecastUsingAdditivePickUp (ioSegmentCabin, lBkgClassUncDemMap,
                                   lQEquivalentDemandVector, lSellUpCoef);
      return true;
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void Forecaster::
  forecastUsingAdditivePickUp (stdair::SegmentCabin& ioSegmentCabin,
                               const BookingClassUnconstrainedDemandVectorMap_T& iClassUncDemMap,
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
        BookingClassUnconstrainedDemandVectorMap_T::const_iterator itBCUD =
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
      BookingClassUnconstrainedDemandVectorMap_T::const_iterator itBCUD =
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
  bool Forecaster::
  forecastUsingMultiplicativePickUp (stdair::FlightDate& ioFlightDate,
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
      
      //
      const stdair::SegmentCabinList_T& lSCList =
        stdair::BomManager::getList<stdair::SegmentCabin> (*lSD_ptr);
      for (stdair::SegmentCabinList_T::const_iterator itSC = lSCList.begin();
           itSC != lSCList.end(); ++itSC) {
        stdair::SegmentCabin* lSC_ptr = *itSC;
        assert (lSC_ptr != NULL);

        bool isForecasted = forecastUsingMultiplicativePickUp (*lSC_ptr,
                                                               lEventDate,
                                                               lSegmentDTD);
        if (isForecasted == false) {
          isSucceeded = false;
        }
      }
    }
    return isSucceeded;
  }

  // ////////////////////////////////////////////////////////////////////
  bool Forecaster::
  forecastUsingMultiplicativePickUp (stdair::SegmentCabin& ioSegmentCabin,
                                     const stdair::Date_T& iEventDate,
                                     const stdair::DTD_T& iSegmentDTD) {
    // Retrieving the number of anterior similar segments.
    const stdair::GuillotineBlock& lGuillotineBlock =
      ioSegmentCabin.getGuillotineBlock();
    const stdair::NbOfSegments_T lNbOfAnteriorSimilarSegments =
      GuillotineBlockHelper::
      getNbOfSegmentAlreadyPassedThisDTD (lGuillotineBlock, iSegmentDTD,
                                          iEventDate) - 1;
      
    // DEBUG
    STDAIR_LOG_DEBUG ("Nb of anterior similar segments: "
                      << lNbOfAnteriorSimilarSegments);

    // If the iSegmentDTD is the last DCP or there is no anterior similar
    // segment, remaining demand for all classes will be set to zero
    stdair::DCPList_T::const_reverse_iterator itLastDCP =
      stdair::DEFAULT_DCP_LIST.rbegin();
    assert (itLastDCP != stdair::DEFAULT_DCP_LIST.rend());
    const stdair::DCP_T& lLastDCP = *itLastDCP;
    if (lNbOfAnteriorSimilarSegments < 1.0 || iSegmentDTD <= lLastDCP) {
      setRemainingDemandForecastToZero (ioSegmentCabin);
      return false;
    } else {
      // Retrieve the booking figures of the first DCP and consider them
      // as unconstrained demand figures.
      stdair::DCPList_T::const_iterator itDCP =stdair::DEFAULT_DCP_LIST.begin();
      assert (itDCP != stdair::DEFAULT_DCP_LIST.end());
      const stdair::DCP_T& lFirstDCP = *itDCP;
      
      // Initialise the unconstrained demand for classes.
      const stdair::NbOfSegments_T lNbOfUsableSegments =
        GuillotineBlockHelper::
        getNbOfSegmentAlreadyPassedThisDTD (lGuillotineBlock, lFirstDCP,
                                            iEventDate);
      
      STDAIR_LOG_DEBUG ("Nb of usable similar segments: "
                        << lNbOfUsableSegments);
        
      UnconstrainedDemandVector_T lQEquivalentDemandVector (lNbOfUsableSegments,
                                                            0.0);
      stdair::NbOfBookings_T lCurrentSegmentQEquivalentDemand = 0.0;
      BookingClassUnconstrainedDemandVectorMap_T lBkgClassUncDemVectorMap;
      BookingClassUnconstrainedDemandMap_T lCurrentSegmentBkgClassDemMap;
      const stdair::BookingClassList_T& lBCList =
        stdair::BomManager::getList<stdair::BookingClass> (ioSegmentCabin);
      for (stdair::BookingClassList_T::const_iterator itBC = lBCList.begin();
           itBC != lBCList.end(); ++itBC) {
        stdair::BookingClass* lBC_ptr = *itBC;
        assert (lBC_ptr != NULL);

        UnconstrainedDemandVector_T lUncDemandVector (lNbOfUsableSegments, 0.0);
        bool insertionSucceeded = lBkgClassUncDemVectorMap.
          insert (BookingClassUnconstrainedDemandVectorMap_T::
                  value_type (lBC_ptr, lUncDemandVector)).second;
        assert (insertionSucceeded == true);
        insertionSucceeded =
          lCurrentSegmentBkgClassDemMap.
          insert (BookingClassUnconstrainedDemandMap_T::
                  value_type (lBC_ptr, 0.0)).second;
        assert (insertionSucceeded == true);
      }
      Detruncator::
        retrieveUnconstrainedDemandForFirstDCP (ioSegmentCabin,
                                                lBkgClassUncDemVectorMap,
                                                lQEquivalentDemandVector,
                                                lFirstDCP, lNbOfUsableSegments);

      // Unconstrain the booking figures.
      stdair::DCPList_T::const_iterator itNextDCP = itDCP; ++itNextDCP;
      while (itNextDCP != stdair::DEFAULT_DCP_LIST.end()) {
        const stdair::DCP_T& lCurrentDCP = *itDCP;
        const stdair::DCP_T& lNextDCP = *itNextDCP;
        if (lCurrentDCP <= iSegmentDTD) {
          break;
        }
        Detruncator::
          unconstrainUsingMultiplicativePickUp (ioSegmentCabin,
                                                lBkgClassUncDemVectorMap,
                                                lQEquivalentDemandVector,
                                                lCurrentDCP-1, lNextDCP,
                                                iEventDate);
        ++itNextDCP; ++itDCP;
      }

      // Update the unconstrained demand for all the classes of the current
      // segment.
      lCurrentSegmentQEquivalentDemand =
        lQEquivalentDemandVector.at (lNbOfAnteriorSimilarSegments);
      BookingClassUnconstrainedDemandMap_T::iterator itBCUD =
        lCurrentSegmentBkgClassDemMap.begin();
      for (BookingClassUnconstrainedDemandVectorMap_T::iterator itBCUDV =
             lBkgClassUncDemVectorMap.begin();
           itBCUDV != lBkgClassUncDemVectorMap.end(); ++itBCUDV, ++itBCUD) {
        assert (itBCUD != lCurrentSegmentBkgClassDemMap.end());
        assert (itBCUD->first == itBCUDV->first);
        stdair::NbOfRequests_T& lUncDem = itBCUD->second;
        UnconstrainedDemandVector_T& lUncDemVector = itBCUDV->second;
        lUncDem = lUncDemVector.at (lNbOfAnteriorSimilarSegments);
      }

      // Forecast the remaining demand for all classes
      const stdair::DCP_T& lCurrentDTD = *itDCP;
      for (; itNextDCP != stdair::DEFAULT_DCP_LIST.end(); ++itNextDCP, ++itDCP){
        const stdair::DCP_T& lCurrentDCP = *itDCP;
        const stdair::DCP_T& lNextDCP = *itNextDCP;
        forecastUsingMultiplicativePickUp (ioSegmentCabin,
                                           lBkgClassUncDemVectorMap,
                                           lQEquivalentDemandVector,
                                           lCurrentDCP-1, lNextDCP, iEventDate,
                                           lNbOfAnteriorSimilarSegments);
      }

      // Update the remaining demand for all classes
      lCurrentSegmentQEquivalentDemand = 
        lQEquivalentDemandVector.at (lNbOfAnteriorSimilarSegments)
        - lCurrentSegmentQEquivalentDemand;
      itBCUD = lCurrentSegmentBkgClassDemMap.begin();
      for (BookingClassUnconstrainedDemandVectorMap_T::iterator itBCUDV =
             lBkgClassUncDemVectorMap.begin();
           itBCUDV != lBkgClassUncDemVectorMap.end(); ++itBCUDV, ++itBCUD) {
        assert (itBCUD != lCurrentSegmentBkgClassDemMap.end());
        assert (itBCUD->first == itBCUDV->first);
        stdair::NbOfRequests_T& lUncDem = itBCUD->second;
        UnconstrainedDemandVector_T& lUncDemVector = itBCUDV->second;
        lUncDem = lUncDemVector.at (lNbOfAnteriorSimilarSegments) - lUncDem;
      }     
      
      // Retrieve the FRAT5 coefficient and compute the sell-up coef.
      FRAT5Curve_T::const_iterator itFRAT5 =
        DEFAULT_CUMULATIVE_FRAT5_CURVE.lower_bound (lCurrentDTD);
      assert (itFRAT5 != DEFAULT_CUMULATIVE_FRAT5_CURVE.end());
      const double lFRAT5Coef = itFRAT5->second;
      const double lSellUpCoef = -log(0.5) / (lFRAT5Coef - 1); 
      
      return forecastUsingMultiplicativePickUp(ioSegmentCabin,
                                               lCurrentSegmentBkgClassDemMap,
                                               lCurrentSegmentQEquivalentDemand,
                                               lSellUpCoef);
      
    }
  }
  
  // ////////////////////////////////////////////////////////////////////
  void Forecaster::forecastUsingMultiplicativePickUp
  (const stdair::SegmentCabin& iSegmentCabin,
   BookingClassUnconstrainedDemandVectorMap_T& ioBkgClassUncDemMap,
   UnconstrainedDemandVector_T& ioQEquivalentDemandVector,
   const stdair::DCP_T& iDCPBegin, const stdair::DCP_T& iDCPEnd,
   const stdair::Date_T& iCurrentDate,
   const stdair::NbOfSegments_T& iNbOfAnteriorSimilarSegments) {

    // Retrieve the guillotine block.
    const stdair::GuillotineBlock& lGuillotineBlock =
      iSegmentCabin.getGuillotineBlock();

    // Build the historical booking holders for the product-oriented bookings
    // of the casses and the Q-equivalent (price-oriented) bookings of the cabin
    const stdair::NbOfSegments_T lNbOfUsableSegments = GuillotineBlockHelper::
      getNbOfSegmentAlreadyPassedThisDTD (lGuillotineBlock, iDCPEnd,
                                          iCurrentDate);
      
    STDAIR_LOG_DEBUG ("Nb of usable similar segments: "
                      << lNbOfUsableSegments);

    if (lNbOfUsableSegments > 0) {

      // Parse the booking class list and unconstrain historical bookings.
      for (BookingClassUnconstrainedDemandVectorMap_T::iterator itBCUDV =
             ioBkgClassUncDemMap.begin(); itBCUDV != ioBkgClassUncDemMap.end();
           ++itBCUDV) {
        stdair::BookingClass* lBC_ptr = itBCUDV->first;
        assert (lBC_ptr != NULL);
        const stdair::MapKey_T& lBCKey = lBC_ptr->describeKey();
        const stdair::BlockIndex_T& lBlockIdx =
          lGuillotineBlock.getBlockIndex (lBCKey);
        UnconstrainedDemandVector_T& lUncDemVector = itBCUDV->second;
        
        STDAIR_LOG_DEBUG ("Unconstrain product-oriented bookings for "<<lBCKey);
        forecastUsingMultiplicativePickUp (lGuillotineBlock, lUncDemVector,
                                           iDCPBegin, iDCPEnd,
                                           lNbOfUsableSegments, lBlockIdx,
                                           iNbOfAnteriorSimilarSegments);
      }
      
      // Unconstrain the Q-equivalent bookings.
      // Retrieve the block index of the segment-cabin.
      std::ostringstream lSCMapKey;
      lSCMapKey << stdair::DEFAULT_SEGMENT_CABIN_VALUE_TYPE
                << iSegmentCabin.describeKey();    
      const stdair::BlockIndex_T& lCabinIdx =
        lGuillotineBlock.getBlockIndex (lSCMapKey.str());
      
      STDAIR_LOG_DEBUG ("Unconstrain price-oriented bookings");
      forecastUsingMultiplicativePickUp (lGuillotineBlock,
                                         ioQEquivalentDemandVector,
                                         iDCPBegin, iDCPEnd,
                                         lNbOfUsableSegments, lCabinIdx,
                                         iNbOfAnteriorSimilarSegments);
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void Forecaster::forecastUsingMultiplicativePickUp
  (const stdair::GuillotineBlock& iGuillotineBlock,
   UnconstrainedDemandVector_T& ioUncDemVector,
   const stdair::DCP_T& iDCPBegin, const stdair::DCP_T& iDCPEnd,
   const stdair::NbOfSegments_T& iNbOfUsableSegments,
   const stdair::BlockIndex_T& iBlockIdx,
   const stdair::NbOfSegments_T& iNbOfAnteriorSimilarSegments) {
    // Retrieve the gross daily booking and availability snapshots.
    stdair::ConstSegmentCabinDTDRangeSnapshotView_T lBookingView =
      iGuillotineBlock.getConstSegmentCabinDTDRangeProductAndPriceOrientedBookingSnapshotView (0, iNbOfUsableSegments -1, iDCPEnd, iDCPBegin);
    stdair::ConstSegmentCabinDTDRangeSnapshotView_T lAvlView =
      iGuillotineBlock.getConstSegmentCabinDTDRangeAvailabilitySnapshotView (0, iNbOfUsableSegments -1, iDCPEnd, iDCPBegin);
    
    // Browse the list of segments and build the historical booking holder.
    const stdair::ValueTypeIndexMap_T& lVTIdxMap =
      iGuillotineBlock.getValueTypeIndexMap();
    const unsigned int lNbOfValueTypes = lVTIdxMap.size();
    HistoricalBookingHolder lHBHolder;
    std::vector<short> lDataIndexList;
    for (short i = 0; i < iNbOfUsableSegments; ++i) {
      stdair::Flag_T lCensorshipFlag = false;
      stdair::NbOfBookings_T lNbOfHistoricalBkgs = 0.0;
      const short lNbOfDTDs = iDCPBegin - iDCPEnd + 1;
      
      // Parse the DTDs during the period
      for (short j = 0; j < lNbOfDTDs; ++j) {
        // Check if the data has been censored during this day.
        // STDAIR_LOG_DEBUG ("i: " << i << ", NbOfValues: " << lNbOfValueTypes
        //                   << ", BlockIdx: " << iBlockIdx << ", j: " << j);
        if (lCensorshipFlag == false) {
          if (lAvlView[i*lNbOfValueTypes + iBlockIdx][j] < 1.0) {
            lCensorshipFlag = true;
          }
        }
        
        // Get the bookings of the day.
        // STDAIR_LOG_DEBUG ("Bookings of the day: " << lBookingView[i*lNbOfValueTypes + iBlockIdx][j]);
        lNbOfHistoricalBkgs += lBookingView[i*lNbOfValueTypes + iBlockIdx][j];
      }

      // If there is no booking till now for this class and for this segment,
      // there will be no unconstraining process.
      stdair::NbOfRequests_T& lUncDemand = ioUncDemVector.at (i);
      if (lUncDemand < 1.0) {
        lUncDemand += lNbOfHistoricalBkgs;
      } else {
        double lBkgDemandFactor = lNbOfHistoricalBkgs / lUncDemand;
        HistoricalBooking lHistoricalBkg (lBkgDemandFactor, lCensorshipFlag);
        lHBHolder.addHistoricalBooking (lHistoricalBkg);
        lDataIndexList.push_back (i);
      }
      
      // DEBUG
      STDAIR_LOG_DEBUG ("Historical bkgs: " << lNbOfHistoricalBkgs
                        << ", censored: " << lCensorshipFlag);
    }

    // DEBUG
    STDAIR_LOG_DEBUG ("Unconstrain by multiplicative pick-up using EM");
    
    // Unconstrain the booking figures
    EMDetruncator::unconstrainUsingEMMethod (lHBHolder);

    // Update the unconstrained demand vector.
    short i = 0;
    for (std::vector<short>::iterator itIdx = lDataIndexList.begin();
         itIdx != lDataIndexList.end(); ++itIdx, ++i) {
      short lIdx = *itIdx;
      stdair::NbOfRequests_T& lPastDemand = ioUncDemVector.at (lIdx);
      const stdair::NbOfRequests_T& lUncDemandFactorOfThisPeriod =
        lHBHolder.getUnconstrainedDemand (i);
      lPastDemand *= (1+lUncDemandFactorOfThisPeriod);
    }

    // Update the unconstrained demand for the current segment.
    if (lHBHolder.getNbOfFlights() > 0) {
      const stdair::NbOfRequests_T& lUncDemandFactorMean =
        lHBHolder.getDemandMean();
      stdair::NbOfRequests_T& lPastDemand =
        ioUncDemVector.at (iNbOfAnteriorSimilarSegments);
      lPastDemand *= (1+lUncDemandFactorMean);
    }
  }  

  // ////////////////////////////////////////////////////////////////////
  bool Forecaster::
  forecastUsingMultiplicativePickUp (stdair::SegmentCabin& ioSegmentCabin,
                                     const BookingClassUnconstrainedDemandMap_T& iClassUncDemMap,
                                     const stdair::NbOfRequests_T& iUncDem,
                                     const double& iSellUpFactor) {
    double lPriceOriMean = iUncDem;
    double lPriceOriStdDev = sqrt (iUncDem);
    
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
      if (lPriceOriMean > 0) {
        return true;
      } else {
        return false;
      }
    } else {
      bool isSucceeded = false;
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
        double lMean = itBCUD->second;
        double lStdDev = sqrt (lMean);
        
        // Compute the demand distribution for the current class;
        lMean += lPriceOriDemMeanFrac;
        lStdDev = sqrt (lStdDev * lStdDev +
                        lPriceOriDemStdDevFrac * lPriceOriDemStdDevFrac);
        lCurrentBC_ptr->setMean (lMean);
        lCurrentBC_ptr->setStdDev (lStdDev);

        if (lMean > 0) {
          isSucceeded = true;
        }
        
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
      double lMean = itBCUD->second;
      double lStdDev = sqrt (lMean);
      
      // Compute the demand distribution for the current class;
      lMean += lPriceOriMean;
      lStdDev = sqrt (lStdDev * lStdDev + lPriceOriStdDev * lPriceOriStdDev);
      lCurrentBC_ptr->setMean (lMean);
      lCurrentBC_ptr->setStdDev (lStdDev);
      
      if (lMean > 0) {
        isSucceeded = true;
      }

      // DEBUG
      STDAIR_LOG_DEBUG ("Class " << lCurrentBC_ptr->describeKey()
                        << ", mean = " << lMean
                        << ", stddev = " << lStdDev);
      return isSucceeded;
    }
  }

>>>>>>> 0.24
}
