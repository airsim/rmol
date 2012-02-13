// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/SegmentSnapshotTable.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/bom/SegmentSnapshotTableHelper.hpp>
#include <rmol/bom/HistoricalBookingHolder.hpp>
#include <rmol/bom/HistoricalBooking.hpp>
#include <rmol/bom/EMDetruncator.hpp>
#include <rmol/command/Detruncator.hpp>

namespace RMOL {
  // ////////////////////////////////////////////////////////////////////
  void Detruncator::
  unconstrainUsingAddPkUp (const stdair::SegmentCabin& iSegmentCabin,
                           stdair::BookingClassUncDemVectorMap_T& ioBkgClassUncDemMap,
                           stdair::UncDemVector_T& ioQEquivalentDemandVector,
                           const stdair::DCP_T& iDCPBegin,
                           const stdair::DCP_T& iDCPEnd,
                           const stdair::Date_T& iCurrentDate) {

    // Retrieve the guillotine block.
    const stdair::SegmentSnapshotTable& lSegmentSnapshotTable =
      iSegmentCabin.getSegmentSnapshotTable();

    // Build the historical booking holders for the product-oriented bookings
    // of the casses and the Q-equivalent (price-oriented) bookings of the cabin
    const stdair::NbOfSegments_T lNbOfUsableSegments =
      SegmentSnapshotTableHelper::
      getNbOfSegmentAlreadyPassedThisDTD (lSegmentSnapshotTable, iDCPEnd,
                                          iCurrentDate);

    // Parse the booking class list and unconstrain historical bookings.
    for (stdair::BookingClassUncDemVectorMap_T::iterator itBCUDV =
           ioBkgClassUncDemMap.begin(); itBCUDV != ioBkgClassUncDemMap.end();
         ++itBCUDV) {
      stdair::BookingClass* lBC_ptr = itBCUDV->first;
      assert (lBC_ptr != NULL);
      const stdair::MapKey_T& lBCKey = lBC_ptr->describeKey();
      const stdair::ClassIndex_T& lClassIdx =
        lSegmentSnapshotTable.getClassIndex (lBCKey);
      stdair::UncDemVector_T& lUncDemVector = itBCUDV->second;

      // STDAIR_LOG_DEBUG ("Unconstrain product-oriented bookings for " << lBCKey);
      // STDAIR_LOG_NOTIFICATION (lBCKey << ";" << iDCPBegin
      //                          << ";" << iDCPEnd);
      unconstrainUsingAddPkUp (lSegmentSnapshotTable, lUncDemVector,
                               iDCPBegin, iDCPEnd,
                               lNbOfUsableSegments, lClassIdx);
    }

    // Unconstrain the Q-equivalent bookings.
    // Retrieve the block index of the segment-cabin.
    std::ostringstream lSCMapKey;
    lSCMapKey << stdair::DEFAULT_SEGMENT_CABIN_VALUE_TYPE
              << iSegmentCabin.describeKey();    
    const stdair::ClassIndex_T& lCabinIdx =
      lSegmentSnapshotTable.getClassIndex (lSCMapKey.str());

    //STDAIR_LOG_DEBUG ("Unconstrain price-oriented bookings");
    //STDAIR_LOG_NOTIFICATION (iDCPBegin << ";" << iDCPEnd);
    unconstrainUsingAddPkUp (lSegmentSnapshotTable, ioQEquivalentDemandVector,
                                    iDCPBegin, iDCPEnd, lNbOfUsableSegments,
                                    lCabinIdx, iSegmentCabin, iCurrentDate);
  }

  // ////////////////////////////////////////////////////////////////////
  void Detruncator::unconstrainUsingAddPkUp
  (const stdair::SegmentSnapshotTable& iSegmentSnapshotTable,
   stdair::UncDemVector_T& ioUncDemVector,
   const stdair::DCP_T& iDCPBegin, const stdair::DCP_T& iDCPEnd,
   const stdair::NbOfSegments_T& iNbOfUsableSegments,
   const stdair::ClassIndex_T& iClassIdx) {/*
    // TODO:
    stdair::NbOfSegments_T lSegBegin = 0;
    if (iNbOfUsableSegments > 52) lSegBegin = iNbOfUsableSegments - 52;
    // Retrieve the gross daily booking and availability snapshots.
    stdair::ConstSegmentCabinDTDRangeSnapshotView_T lBookingView =
      iSegmentSnapshotTable.getConstSegmentCabinDTDRangeProductAndPriceOrientedBookingSnapshotView (lSegBegin, iNbOfUsableSegments -1, iDCPEnd, iDCPBegin);
    stdair::ConstSegmentCabinDTDRangeSnapshotView_T lAvlView =
      iSegmentSnapshotTable.getConstSegmentCabinDTDRangeAvailabilitySnapshotView (lSegBegin, iNbOfUsableSegments -1, iDCPEnd, iDCPBegin);
    
    // Browse the list of segments and build the historical booking holder.
    const stdair::ClassIndexMap_T& lVTIdxMap =
      iSegmentSnapshotTable.getClassIndexMap();
    const unsigned int lNbOfClasses = lVTIdxMap.size();
    HistoricalBookingHolder lHBHolder;
    for (short i = 0; i < iNbOfUsableSegments-lSegBegin; ++i) {
      stdair::Flag_T lCensorshipFlag = false;
      stdair::NbOfBookings_T lNbOfHistoricalBkgs = 0.0;
      const short lNbOfDTDs = iDCPBegin - iDCPEnd + 1;
      
      // Parse the DTDs during the period
      for (short j = 0; j < lNbOfDTDs; ++j) {
        // Check if the data has been censored during this day.
        // STDAIR_LOG_DEBUG ("i: " << i << ", NbOfClasses: " << lNbOfClasses
        //                   << ", ClassIdx: " << iClassIdx << ", j: " << j);
        if (lCensorshipFlag == false) {
          if (lAvlView[i*lNbOfClasses + iClassIdx][j] < 1.0) {
            lCensorshipFlag = true;
          }
        }
        
        // Get the bookings of the day.
        //STDAIR_LOG_DEBUG ("Bookings of the day: " << lBookingView[i*lNbOfClasses + iClassIdx][j]);
        lNbOfHistoricalBkgs += lBookingView[i*lNbOfClasses + iClassIdx][j];
      }
      
      HistoricalBooking lHistoricalBkg (lNbOfHistoricalBkgs, lCensorshipFlag);
      lHBHolder.addHistoricalBooking (lHistoricalBkg);

      // DEBUG
      //STDAIR_LOG_DEBUG ("Historical bkgs: " << lNbOfHistoricalBkgs
      //                  << ", censored: " << lCensorshipFlag);
      // STDAIR_LOG_NOTIFICATION (lNbOfHistoricalBkgs
      //                          << ";" << lCensorshipFlag);
    }

    // DEBUG
    // STDAIR_LOG_DEBUG ("Unconstrain by EM");
    
    // Unconstrain the booking figures
    EMDetruncator::unconstrainUsingEMMethod (lHBHolder);

    // Add the unconstrained demand of the period to the unconstrained demand
    // vector.    
    short idx = 0;
    for (UncDemVector_T::iterator itUD = ioUncDemVector.begin();
         itUD != ioUncDemVector.end(); ++itUD, ++idx) {
      *itUD += lHBHolder.getUnconstrainedDemand (idx);
      //STDAIR_LOG_NOTIFICATION (lHBHolder.getUnconstrainedDemand (idx));
      }*/
  }

  // ////////////////////////////////////////////////////////////////////
  void Detruncator::unconstrainUsingAddPkUp
  (const stdair::SegmentSnapshotTable& iSegmentSnapshotTable,
   stdair::UncDemVector_T& ioUncDemVector,
   const stdair::DCP_T& iDCPBegin, const stdair::DCP_T& iDCPEnd,
   const stdair::NbOfSegments_T& iNbOfUsableSegments,
   const stdair::ClassIndex_T& iClassIdx,
   const stdair::SegmentCabin& iSegmentCabin,
   const stdair::Date_T& iCurrentDate) {/*
    // TODO
    stdair::NbOfSegments_T lSegBegin = 0;
    if (iNbOfUsableSegments > 52) lSegBegin = iNbOfUsableSegments - 52;
    // Retrieve the gross daily booking and availability snapshots.
    stdair::ConstSegmentCabinDTDRangeSnapshotView_T lBookingView =
      iSegmentSnapshotTable.getConstSegmentCabinDTDRangeProductAndPriceOrientedBookingSnapshotView (lSegBegin, iNbOfUsableSegments -1, iDCPEnd, iDCPBegin);
    stdair::ConstSegmentCabinDTDRangeSnapshotView_T lAvlView =
      iSegmentSnapshotTable.getConstSegmentCabinDTDRangeAvailabilitySnapshotView (lSegBegin, iNbOfUsableSegments -1, iDCPEnd, iDCPBegin);
    
    // Browse the list of segments and build the historical booking holder.
    const stdair::ClassIndexMap_T& lVTIdxMap =
      iSegmentSnapshotTable.getClassIndexMap();
    const unsigned int lNbOfClasses = lVTIdxMap.size();
    HistoricalBookingHolder lHBHolder;
    for (short i = 0; i < iNbOfUsableSegments-lSegBegin; ++i) {
      stdair::Flag_T lCensorshipFlag = false;
      stdair::NbOfBookings_T lNbOfHistoricalBkgs = 0.0;
      const short lNbOfDTDs = iDCPBegin - iDCPEnd + 1;
      
      // Parse the DTDs during the period
      for (short j = 0; j < lNbOfDTDs; ++j) {
        // Check if the data has been censored during this day.
        // STDAIR_LOG_DEBUG ("i: " << i << ", NbOfClasses: " << lNbOfClasses
        //                   << ", ClassIdx: " << iClassIdx << ", j: " << j);
        if (lCensorshipFlag == false) {
          if (lAvlView[i*lNbOfClasses + iClassIdx][j] < 1.0) {
            lCensorshipFlag = true;
          }
        }
        
        // Get the bookings of the day.
        //STDAIR_LOG_DEBUG ("Bookings of the day: " << lBookingView[i*lNbOfClasses + iClassIdx][j]);
        lNbOfHistoricalBkgs += lBookingView[i*lNbOfClasses + iClassIdx][j];
      }
      
      HistoricalBooking lHistoricalBkg (lNbOfHistoricalBkgs, lCensorshipFlag);
      lHBHolder.addHistoricalBooking (lHistoricalBkg);

      // DEBUG
      // STDAIR_LOG_DEBUG ("Historical bkgs: " << lNbOfHistoricalBkgs
      //                  << ", censored: " << lCensorshipFlag);
      // STDAIR_LOG_NOTIFICATION (lNbOfHistoricalBkgs
      //                          << ";" << lCensorshipFlag);
    }

    // DEBUG
    // STDAIR_LOG_DEBUG ("Unconstrain by EM");
    
    // Unconstrain the booking figures
    EMDetruncator::unconstrainUsingEMMethod (lHBHolder);

    // Add the unconstrained demand of the period to the unconstrained demand
    // vector.
    // LOG
    const stdair::SegmentDate& lSegmentDate = stdair::BomManager::
      getParent<stdair::SegmentDate, stdair::SegmentCabin> (iSegmentCabin);
    const stdair::FlightDate& lFlightDate = stdair::BomManager::
      getParent<stdair::FlightDate, stdair::SegmentDate> (lSegmentDate);
    const stdair::Date_T& lDepDate = lFlightDate.getDepartureDate();
    const boost::gregorian::date_duration lDD = lDepDate - iCurrentDate;
    const long lDTD = lDD.days();
    stdair::Date_T lRefDate (2012, boost::gregorian::Jan, 01);
    
    short idx = 0;
    for (UncDemVector_T::iterator itUD = ioUncDemVector.begin();
         itUD != ioUncDemVector.end(); ++itUD, ++idx) {
      *itUD += lHBHolder.getUnconstrainedDemand (idx);
      if (lDepDate > lRefDate) {
        const stdair::DateOffset_T lDateOffset (7 *(52 - idx) + 420);
        const stdair::Date_T lHDate = lDepDate - lDateOffset;
        STDAIR_LOG_NOTIFICATION (boost::gregorian::to_iso_string(lDepDate)
                                 << ";" << lDTD << ";" << iDCPBegin << ";"
                                 << iDCPEnd << ";"
                                 << boost::gregorian::to_iso_string (lHDate)
                                 <<";"<<lHBHolder.getUnconstrainedDemand (idx));
        
        STDAIR_LOG_NOTIFICATION (boost::gregorian::to_iso_string(lDepDate)
                                 << ";" << lDTD << ";" << iDCPBegin << ";"
                                 << iDCPEnd << ";"
                                 << boost::gregorian::to_iso_string (lHDate)
                                 <<";"<<lHBHolder.getHistoricalBooking (idx));
      }
    }*/
  }

}
  
