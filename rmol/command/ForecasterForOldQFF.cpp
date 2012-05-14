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
#include <stdair/bom/FareFamily.hpp>
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
#include <rmol/command/ForecasterForOldQFF.hpp>
#include <rmol/command/DetruncatorForOldQFF.hpp>

namespace RMOL {

 
  // ////////////////////////////////////////////////////////////////////
  bool ForecasterForOldQFF::
  forecast (stdair::FlightDate& ioFlightDate,
            const stdair::DateTime_T& iEventTime) {
    // Build the offset dates.
    const stdair::Date_T& lEventDate = iEventTime.date();

    // Browse the segment date
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
      
      // Browse the segment cabin
      const stdair::SegmentCabinList_T& lSCList =
        stdair::BomManager::getList<stdair::SegmentCabin> (*lSD_ptr);
      for (stdair::SegmentCabinList_T::const_iterator itSC = lSCList.begin();
           itSC != lSCList.end(); ++itSC) {
        stdair::SegmentCabin* lSC_ptr = *itSC;
        assert (lSC_ptr != NULL);

        //
        // STDAIR_LOG_NOTIFICATION (ioFlightDate.getDepartureDate()
        //                          << ";" << lSegmentDTD);
        bool isForecasted = forecast (*lSC_ptr, lEventDate, *lSD_ptr);
        if (isForecasted == false) {
          isSucceeded = false;
        }
      }
    }
    return isSucceeded;
  }

  // ////////////////////////////////////////////////////////////////////
  bool ForecasterForOldQFF::
  forecast (stdair::SegmentCabin& ioSegmentCabin,
            const stdair::Date_T& iEventDate,
            const stdair::SegmentDate& iSegmentDate) {
    // Retrieve the number of departed similar segments.
    stdair::NbOfSegments_T lNbOfDepartedSegments =
      Utilities::getNbOfDepartedSimilarSegments (ioSegmentCabin, iEventDate);
    if (lNbOfDepartedSegments > 52) {
      lNbOfDepartedSegments = 52; 
    }
    const stdair::Date_T& lBoardingDate = iSegmentDate.getBoardingDate();
    stdair::DateOffset_T lDateOffset = lBoardingDate - iEventDate;
    const stdair::DTD_T lDaysBeforeDeparture = lDateOffset.days() + 1;

    // DEBUG
    // STDAIR_LOG_DEBUG ("Nb of similar departed segments: "
    //                   << lNbOfDepartedSegments);
    
    // If the number of departed segments are less than two, remaining
    // demand for all classes will be set to zero.
    if (lNbOfDepartedSegments < 2) {
      setAchievableDemandForecastToZero (ioSegmentCabin);
      return false;
    } else {      

      // Initialise the demand vector
        stdair::MeanStdDevPairVector_T lMeanStdDev 
          (stdair::DEFAULT_DCP_LIST.size() - 1, stdair::MeanStdDevPair_T(0.0, 0.0));  

      // Retrieve the nesting structure
      ioSegmentCabin.initNestingStruct();
      const stdair::SimpleNestingStruct& lNestingStruct = ioSegmentCabin.getNestingStruct();
      
      // Build the DCP intervals and unconstrain censored booking figures for
      // each interval.
      const stdair::DCPList_T lWholeDCPList = stdair::DEFAULT_DCP_LIST;
      stdair::DCPList_T::const_iterator itDCP = lWholeDCPList.begin();
      stdair::DCPList_T::const_iterator itNextDCP = itDCP; ++itNextDCP;
      for (unsigned short int idx = 0; itNextDCP != lWholeDCPList.end();
           ++itDCP, ++itNextDCP, ++idx) {
        const stdair::DCP_T& lCurrentDCP = *itDCP;
        const stdair::DCP_T& lNextDCP = *itNextDCP;

        // DEBUG
        // STDAIR_LOG_DEBUG ("Unconstrain demand for "
        //                   << ioSegmentCabin.describeKey()
        //                   << " and the DCP's " << lCurrentDCP << ", "
        //                   << lNextDCP);

          if (lNextDCP < lDaysBeforeDeparture) {
    	      DetruncatorForOldQFF::unconstrain (ioSegmentCabin,
                                               lNestingStruct,
                                               lCurrentDCP-1, lNextDCP,
                                               iEventDate, lMeanStdDev, idx);
          //STDAIR_LOG_DEBUG ("Detruncation successful");
        }
      }
      // Update the forecasted demand of booking classes
      // Browse the nesting structure
      // For each node, for each DCP interval, 
      // calculate the Probability of Sell Up and forecast the demand for 
      // each booking class of the current node
      const stdair::FRAT5Curve_T& lFRAT5Curve = DEFAULT_FRAT5_CURVE;
      // Retrieve yield of the cheapest booking class to calculate the probability of sell up
      const stdair::NestingNodeMap_T& lNestingNodeMap = 
        lNestingStruct.getNestingNodeMap();
      stdair::NestingNodeMap_T::const_iterator itNestingNode = lNestingNodeMap.begin();
      assert (itNestingNode != lNestingNodeMap.end());
      const stdair::NestingNode_T& lCheapestNestingNode = *itNestingNode;
      const stdair::Yield_T& lcheapestYield = lCheapestNestingNode.first;
      for (; itNestingNode != lNestingNodeMap.end(); ++itNestingNode) {
        const stdair::NestingNode_T& lNestingNode = *itNestingNode;
        const stdair::Yield_T& lYield = lNestingNode.first;
        itDCP = lWholeDCPList.begin();
        itNextDCP = itDCP; 
        ++itNextDCP;
        stdair::NbOfBookings_T lMean = 0.0;
        stdair::NbOfBookings_T lStdDev = 0.0;
        for (unsigned short int idx = 0; itNextDCP != lWholeDCPList.end();
              ++itDCP, ++itNextDCP, ++idx) {
          const stdair::DCP_T& lCurrentDCP = *itDCP;
          double lPSUp = 1.0;
          stdair::FRAT5Curve_T::const_iterator itFRAT5CURV = lFRAT5Curve.find(lCurrentDCP);
          assert(itFRAT5CURV != lFRAT5Curve.end());
          const double lFRAT5 = itFRAT5CURV->second;
          assert(lFRAT5 > 1.0);
          // Calculate the probability of sell up
          if (lYield != lcheapestYield){
            assert(lYield > lcheapestYield);
            const double lSellUpConstant = -log(0.5)/(lFRAT5 - 1);
            lPSUp = exp(-(lYield/lcheapestYield-1) * lSellUpConstant);
          }
          const stdair::NbOfBookings_T& lQEquivalentMean = lMeanStdDev[idx].first;
          const stdair::NbOfBookings_T& lQEquivalentStdDev = lMeanStdDev[idx].second;
          lMean += lQEquivalentMean * lPSUp;
          lStdDev = sqrt(lStdDev*lStdDev + lQEquivalentStdDev*lQEquivalentStdDev * lPSUp);
        }
        const stdair::BookingClassList_T& lBCList = lNestingNode.second;
        for (stdair::BookingClassList_T::const_iterator itBC = lBCList.begin();
             itBC != lBCList.end(); ++itBC) {
          stdair::BookingClass* lBC_ptr = *itBC;
          assert (lBC_ptr != NULL);
          lBC_ptr->setMean(lMean);
          lBC_ptr->setStdDev(lStdDev);
          // DEBUG
          // STDAIR_LOG_DEBUG("Forecasted demand for BC "
          //                  << lBC_ptr->describeKey() 
          //                  << ": " << lMean << ", " << lStdDev);
        }
      }
      return true;
    }
  }
  
    // ////////////////////////////////////////////////////////////////////
  void ForecasterForOldQFF::
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
