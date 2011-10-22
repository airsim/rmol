// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/GuillotineBlock.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/bom/GuillotineBlockHelper.hpp>
#include <rmol/bom/HistoricalBookingHolder.hpp>
#include <rmol/bom/HistoricalBooking.hpp>
#include <rmol/bom/EMDetruncator.hpp>
#include <rmol/command/Detruncator.hpp>

namespace RMOL {
  // ////////////////////////////////////////////////////////////////////
  void Detruncator::
  unconstrainUsingAdditivePickUp (const stdair::SegmentCabin& iSegmentCabin,
	       BookingClassUnconstrainedDemandVectorMap_T& ioBkgClassUncDemMap,
               UnconstrainedDemandVector_T& ioQEquivalentDemandVector,
	       const stdair::DCP_T& iDCPBegin, const stdair::DCP_T& iDCPEnd,
               const stdair::Date_T& iCurrentDate) {

    // Retrieve the guillotine block.
    const stdair::GuillotineBlock& lGuillotineBlock =
      iSegmentCabin.getGuillotineBlock();

    // Build the historical booking holders for the product-oriented bookings
    // of the casses and the Q-equivalent (price-oriented) bookings of the cabin
    const stdair::NbOfSegments_T lNbOfUsableSegments = GuillotineBlockHelper::
      getNbOfSegmentAlreadyPassedThisDTD (lGuillotineBlock, iDCPEnd,
                                          iCurrentDate);

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

      STDAIR_LOG_DEBUG ("Unconstrain product-oriented bookings for " << lBCKey);
      unconstrainUsingAdditivePickUp (lGuillotineBlock, lUncDemVector,
                                      iDCPBegin, iDCPEnd,
                                      lNbOfUsableSegments, lBlockIdx);
    }

    // Unconstrain the Q-equivalent bookings.
    // Retrieve the block index of the segment-cabin.
    std::ostringstream lSCMapKey;
    lSCMapKey << stdair::DEFAULT_SEGMENT_CABIN_VALUE_TYPE
              << iSegmentCabin.describeKey();    
    const stdair::BlockIndex_T& lCabinIdx =
      lGuillotineBlock.getBlockIndex (lSCMapKey.str());

    STDAIR_LOG_DEBUG ("Unconstrain price-oriented bookings");
    unconstrainUsingAdditivePickUp (lGuillotineBlock, ioQEquivalentDemandVector,
                                    iDCPBegin, iDCPEnd, lNbOfUsableSegments,
                                    lCabinIdx);
  }

  // ////////////////////////////////////////////////////////////////////
  void Detruncator::unconstrainUsingAdditivePickUp
  (const stdair::GuillotineBlock& iGuillotineBlock,
   UnconstrainedDemandVector_T& ioUncDemVector,
   const stdair::DCP_T& iDCPBegin, const stdair::DCP_T& iDCPEnd,
   const stdair::NbOfSegments_T& iNbOfUsableSegments,
   const stdair::BlockIndex_T& iBlockIdx) {
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
        //STDAIR_LOG_DEBUG ("Bookings of the day: " << lBookingView[i*lNbOfValueTypes + iBlockIdx][j]);
        lNbOfHistoricalBkgs += lBookingView[i*lNbOfValueTypes + iBlockIdx][j];
      }
      
      HistoricalBooking lHistoricalBkg (lNbOfHistoricalBkgs, lCensorshipFlag);
      lHBHolder.addHistoricalBooking (lHistoricalBkg);

      // DEBUG
      STDAIR_LOG_DEBUG ("Historical bkgs: " << lNbOfHistoricalBkgs
                        << ", censored: " << lCensorshipFlag);
    }

    // DEBUG
    STDAIR_LOG_DEBUG ("Unconstrain by EM");
    
    // Unconstrain the booking figures
    EMDetruncator::unconstrainUsingEMMethod (lHBHolder);

    // Add the unconstrained demand of the period to the unconstrained demand
    // vector.
    short idx = 0;
    for (UnconstrainedDemandVector_T::iterator itUD = ioUncDemVector.begin();
         itUD != ioUncDemVector.end(); ++itUD, ++idx) {
      *itUD += lHBHolder.getUnconstrainedDemand (idx);
    }
  }
  
  // ////////////////////////////////////////////////////////////////////
  void Detruncator::retrieveUnconstrainedDemandForFirstDCP
  (const stdair::SegmentCabin& iSegmentCabin,
   BookingClassUnconstrainedDemandVectorMap_T& ioBkgClassUncDemVectorMap,
   UnconstrainedDemandVector_T& ioQEquivalentDemandVector,
   const stdair::DCP_T& iFirstDCP, const stdair::NbOfSegments_T& iNbOfSegments){

    // Retrieve the guillotine block.
    const stdair::GuillotineBlock& lGuillotineBlock =
      iSegmentCabin.getGuillotineBlock();

    // Parse the booking class list and unconstrain historical bookings.
    for (BookingClassUnconstrainedDemandVectorMap_T::iterator itBCUDV =
           ioBkgClassUncDemVectorMap.begin();
         itBCUDV != ioBkgClassUncDemVectorMap.end(); ++itBCUDV) {
      stdair::BookingClass* lBC_ptr = itBCUDV->first;
      assert (lBC_ptr != NULL);
      const stdair::MapKey_T& lBCKey = lBC_ptr->describeKey();
      const stdair::BlockIndex_T& lBlockIdx =
        lGuillotineBlock.getBlockIndex (lBCKey);
      UnconstrainedDemandVector_T& lUncDemVector = itBCUDV->second;

      STDAIR_LOG_DEBUG("Retrieve the unconstrained product-oriented demand for "
                       << lBCKey);
      retrieveUnconstrainedDemandForFirstDCP (lGuillotineBlock, lUncDemVector,
                                              iFirstDCP, lBlockIdx,
                                              iNbOfSegments);
    }

    // Unconstrain the Q-equivalent bookings.
    // Retrieve the block index of the segment-cabin.
    std::ostringstream lSCMapKey;
    lSCMapKey << stdair::DEFAULT_SEGMENT_CABIN_VALUE_TYPE
              << iSegmentCabin.describeKey();    
    const stdair::BlockIndex_T& lCabinValueIdx =
      lGuillotineBlock.getBlockIndex (lSCMapKey.str());
    
    STDAIR_LOG_DEBUG ("Retrieve the unconstrained price-oriented demand");
    retrieveUnconstrainedDemandForFirstDCP (lGuillotineBlock,
                                            ioQEquivalentDemandVector,iFirstDCP,
                                            lCabinValueIdx, iNbOfSegments);
  }
  
  // ////////////////////////////////////////////////////////////////////
  void Detruncator::retrieveUnconstrainedDemandForFirstDCP
  (const stdair::GuillotineBlock& iGuillotineBlock,
   UnconstrainedDemandVector_T& ioUnconstrainedDemandVector,
   const stdair::DCP_T& iFirstDCP, const stdair::BlockIndex_T& iValueIdx,
   const stdair::NbOfSegments_T& iNbOfSegments) {
    
    // Retrieve the snapshots of the corresponding booking value from the
    // first DTD (usually 365) till the given iFirstDCP.
    stdair::ConstSegmentCabinDTDRangeSnapshotView_T lRangeBookingView =
      iGuillotineBlock.getConstSegmentCabinDTDRangeProductAndPriceOrientedBookingSnapshotView (0, iNbOfSegments -1, iFirstDCP, stdair::DEFAULT_MAX_DTD);
    
    // Sum the bookings from the first day till the given iFirstDCP in order to
    // get the supposing unconstrained demand for this period.
    for (int itSegment = 0; itSegment < iNbOfSegments; ++itSegment) {
      for (int i = iFirstDCP; i <= stdair::DEFAULT_MAX_DTD; ++i) {
        stdair::NbOfRequests_T& lUncDemand =
          ioUnconstrainedDemandVector.at(itSegment);
        lUncDemand += lRangeBookingView[iValueIdx][i-iFirstDCP];
      }
    }
  }
  
  // ////////////////////////////////////////////////////////////////////
  void Detruncator::unconstrainUsingMultiplicativePickUp
  (const stdair::SegmentCabin& iSegmentCabin,
   BookingClassUnconstrainedDemandVectorMap_T& ioBkgClassUncDemMap,
   UnconstrainedDemandVector_T& ioQEquivalentDemandVector,
   const stdair::DCP_T& iDCPBegin, const stdair::DCP_T& iDCPEnd,
   const stdair::Date_T& iCurrentDate) {

    // Retrieve the guillotine block.
    const stdair::GuillotineBlock& lGuillotineBlock =
      iSegmentCabin.getGuillotineBlock();

    // Build the historical booking holders for the product-oriented bookings
    // of the casses and the Q-equivalent (price-oriented) bookings of the cabin
    const stdair::NbOfSegments_T lNbOfUsableSegments = GuillotineBlockHelper::
      getNbOfSegmentAlreadyPassedThisDTD (lGuillotineBlock, iDCPEnd,
                                          iCurrentDate);

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

      STDAIR_LOG_DEBUG ("Unconstrain product-oriented bookings for " << lBCKey);
      unconstrainUsingMultiplicativePickUp (lGuillotineBlock, lUncDemVector,
                                            iDCPBegin, iDCPEnd,
                                            lNbOfUsableSegments, lBlockIdx);
    }

    // Unconstrain the Q-equivalent bookings.
    // Retrieve the block index of the segment-cabin.
    std::ostringstream lSCMapKey;
    lSCMapKey << stdair::DEFAULT_SEGMENT_CABIN_VALUE_TYPE
              << iSegmentCabin.describeKey();    
    const stdair::BlockIndex_T& lCabinIdx =
      lGuillotineBlock.getBlockIndex (lSCMapKey.str());

    STDAIR_LOG_DEBUG ("Unconstrain price-oriented bookings");
    unconstrainUsingMultiplicativePickUp (lGuillotineBlock,
                                          ioQEquivalentDemandVector,
                                          iDCPBegin, iDCPEnd,
                                          lNbOfUsableSegments, lCabinIdx);
  }

  // ////////////////////////////////////////////////////////////////////
  void Detruncator::unconstrainUsingMultiplicativePickUp
  (const stdair::GuillotineBlock& iGuillotineBlock,
   UnconstrainedDemandVector_T& ioUncDemVector,
   const stdair::DCP_T& iDCPBegin, const stdair::DCP_T& iDCPEnd,
   const stdair::NbOfSegments_T& iNbOfUsableSegments,
   const stdair::BlockIndex_T& iBlockIdx) {
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
        //STDAIR_LOG_DEBUG ("Bookings of the day: " << lBookingView[i*lNbOfValueTypes + iBlockIdx][j]);
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
  }  
}
  
