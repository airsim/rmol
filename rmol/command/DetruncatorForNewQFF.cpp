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
#include <rmol/bom/Utilities.hpp>
#include <rmol/command/DetruncatorForNewQFF.hpp>
#include <rmol/basic/BasConst_Curves.hpp>

namespace RMOL {
  
  void DetruncatorForNewQFF::
  unconstrain (const stdair::SegmentCabin& iSegmentCabin,
               const stdair::SimpleNestingStruct& iNestingStructure,
               const stdair::DCP_T& iDCPBegin,
               const stdair::DCP_T& iDCPEnd,
               const stdair::Date_T& iCurrentDate,
               stdair::MeanStdDevPairVector_T& oMeanStdDev, 
               const unsigned int& iDCPIdx) {

    // Retrieve the guillotine block.
    const stdair::SegmentSnapshotTable& lSegmentSnapshotTable =
      iSegmentCabin.getSegmentSnapshotTable();
    
    // Retrieve the Nesting Node Map.
    const stdair::NestingNodeMap_T& lNestingNodeMap = 
      iNestingStructure.getNestingNodeMap();
  
    // Build the historical booking holders for the product-oriented bookings
    // of the casses and the Q-equivalent (price-oriented) bookings of the cabin
    const stdair::NbOfSegments_T& lNbOfUsableSegments =
      SegmentSnapshotTableHelper::
      getNbOfSegmentAlreadyPassedThisDTD (lSegmentSnapshotTable, iDCPEnd,
                                          iCurrentDate);
    // Retrieve yield of the cheapest booking class to calculate the probability of sell up
    stdair::NestingNodeMap_T::const_iterator itNestingNode = lNestingNodeMap.begin();
    const bool isEmptyNestingNodeMap = lNestingNodeMap.empty();
    if (isEmptyNestingNodeMap == true) {
      std::ostringstream ostr;
      ostr << "The nesting structure is empty and it should not.";
      STDAIR_LOG_DEBUG(ostr.str());
      throw EmptyNestingStructException(ostr.str());
    }
    assert (itNestingNode != lNestingNodeMap.end());
    const stdair::Yield_T& lcheapestYield = itNestingNode->first;
    const stdair::FRAT5Curve_T& lFRAT5Curve = DEFAULT_FRAT5_CURVE;
    const stdair::DCP_T lDCPBegin = iDCPBegin + 1;
    stdair::FRAT5Curve_T::const_iterator itFRAT5CURV = lFRAT5Curve.find(lDCPBegin);
    if (itFRAT5CURV == lFRAT5Curve.end()) {
      std::ostringstream ostr;
      ostr << "The DCP " << lDCPBegin << " is not in the FRAT5 curve.";
      STDAIR_LOG_DEBUG(ostr.str());
      throw MissingDCPException(ostr.str());
    }
    assert(itFRAT5CURV != lFRAT5Curve.end());
    const double lFRAT5 = itFRAT5CURV->second;
    assert(lFRAT5 > 1);
    stdair::UncDemVector_T lSumDemand;
    
    // Parse the booking class list and unconstrain historical bookings.
    for (; itNestingNode != lNestingNodeMap.end(); ++itNestingNode) {
      // Retrieve yield of the current node to calculate the probability of sell up
      const stdair::NestingNode_T& lNestingNode = *itNestingNode;
      const stdair::Yield_T& lYield = lNestingNode.first;
      double lPSUp = 1.0;
      
      // Calculate the probability of sell up
      if (lYield != lcheapestYield){
        assert(lYield > lcheapestYield);
        const double lSellUpConstant = -log(0.5)/(lFRAT5 - 1);
        lPSUp = exp((1 - lYield/lcheapestYield) * lSellUpConstant);
      }
      const stdair::BookingClassList_T& lBCList = lNestingNode.second;
      for (stdair::BookingClassList_T::const_iterator itBC = lBCList.begin();
           itBC != lBCList.end(); ++itBC) {
        stdair::BookingClass* lBC_ptr = *itBC;
        assert (lBC_ptr != NULL);
        stdair::UncDemVector_T lDemand;
        // Unconstrain the Q-equivalent bookings.
        // Retrieve the block index of the segment-cabin.
        std::ostringstream lSCMapKey;
        lSCMapKey << lBC_ptr->describeKey();    
        const stdair::ClassIndex_T& lCabinIdx =
          lSegmentSnapshotTable.getClassIndex (lSCMapKey.str());
        //STDAIR_LOG_DEBUG ("Unconstrain price-oriented bookings for " << lBCKey);
        //STDAIR_LOG_NOTIFICATION (iDCPBegin << ";" << iDCPEnd);
        unconstrain (lSegmentSnapshotTable, iDCPBegin, iDCPEnd, 
                     lNbOfUsableSegments, lCabinIdx, iSegmentCabin,
                     iCurrentDate, lPSUp, lDemand);
        // Created or update the demand vector
        const unsigned int& lSumDemandVectorSize = lSumDemand.size();
        const unsigned int& lDemandVectorSize = lDemand.size();
        if (lSumDemandVectorSize == 0) {
          for (unsigned int i = 0; i < lDemandVectorSize; i++){        
            lSumDemand.push_back(lDemand[i]);
          }
        } else {
          assert (lSumDemandVectorSize == lDemandVectorSize);
          for (unsigned int i = 0; i < lDemandVectorSize; i++){
            lSumDemand[i] += lDemand[i];
          }
        }
      }
    }
    // Retrieve the mean and the standard deviation of the demand
    stdair::NbOfBookings_T lMean;
    stdair::NbOfBookings_T lStdDev;
    Utilities::computeDistributionParameters(lSumDemand, lMean, lStdDev);
    const stdair::MeanStdDevPair_T lMeanStdDevPair (lMean, lStdDev);
    const unsigned int& lMeanStdDevVectorSize = oMeanStdDev.size();
    assert(iDCPIdx < lMeanStdDevVectorSize);
    oMeanStdDev[iDCPIdx] = lMeanStdDevPair;
  }
  

  // ////////////////////////////////////////////////////////////////////
  void DetruncatorForNewQFF::unconstrain
  (const stdair::SegmentSnapshotTable& iSegmentSnapshotTable,
   const stdair::DCP_T& iDCPBegin, const stdair::DCP_T& iDCPEnd,
   const stdair::NbOfSegments_T& iNbOfUsableSegments,
   const stdair::ClassIndex_T& iClassIdx,
   const stdair::SegmentCabin& iSegmentCabin,
   const stdair::Date_T& iCurrentDate,
   const stdair::SellupProbability_T& iPSUp,
   stdair::UncDemVector_T& oDemand) {

    stdair::NbOfSegments_T lSegBegin = 0;
    if (iNbOfUsableSegments > 52) {
      lSegBegin = iNbOfUsableSegments - 52;
    }
    const stdair::NbOfSegments_T lNbOfUsableSegments = iNbOfUsableSegments - 1;
    // Retrieve the gross daily booking and availability snapshots.
    //const stdair::ConstSegmentCabinDTDRangeSnapshotView_T& lCancellationsView = 
    //  iSegmentSnapshotTable.getConstSegmentCabinDTDRangeCancellationSnapshotView (lSegBegin, iNbOfUsableSegments -1, iDCPEnd, iDCPBegin);
    const stdair::ConstSegmentCabinDTDRangeSnapshotView_T& lBookingView =
      iSegmentSnapshotTable.getConstSegmentCabinDTDRangeBookingSnapshotView (lSegBegin,
                                                                             lNbOfUsableSegments,
                                                                             iDCPEnd,
                                                                             iDCPBegin);
    const stdair::ConstSegmentCabinDTDRangeSnapshotView_T& lAvlView =
      iSegmentSnapshotTable.getConstSegmentCabinDTDRangeAvailabilitySnapshotView (lSegBegin,
                                                                                  lNbOfUsableSegments,
                                                                                  iDCPEnd,
                                                                                  iDCPBegin);

    // Browse the list of segments and build the historical booking holder.
    const stdair::ClassIndexMap_T& lVTIdxMap =
      iSegmentSnapshotTable.getClassIndexMap();
    const unsigned int& lNbOfClasses = lVTIdxMap.size();
    HistoricalBookingHolder lHBHolder;
    for (short i = 0; i < iNbOfUsableSegments-lSegBegin; ++i) {
      const unsigned int lIndexInSnapshotView = i*lNbOfClasses + iClassIdx;
      stdair::Flag_T lCensorshipFlag = false;
      stdair::NbOfBookings_T lNbOfHistoricalBkgs = 0.0;
      const short lNbOfDTDs = iDCPBegin - iDCPEnd + 1;
     
      // Parse the DTDs during the period
      for (short j = 0; j < lNbOfDTDs; ++j) {
        // Check if the data has been censored during this day.
        // STDAIR_LOG_DEBUG ("i: " << i << ", NbOfClasses: " << lNbOfClasses
        //                   << ", ClassIdx: " << iClassIdx << ", j: " << j);
        if (lCensorshipFlag == false) {
          if (lAvlView[lIndexInSnapshotView][j] < 1.0) {
            lCensorshipFlag = true;
            break;
          }
        }
      }
      
      // Retrieve the booking of the DCP
      stdair::NbOfBookings_T lNbOfHistoricalBkgsYesterday = 0.0;
      lNbOfHistoricalBkgsYesterday = 
        lBookingView[lIndexInSnapshotView][lNbOfDTDs];
      lNbOfHistoricalBkgs += lBookingView[lIndexInSnapshotView][0] 
                             - lNbOfHistoricalBkgsYesterday;
      lNbOfHistoricalBkgs /= iPSUp;
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
    
    // Retrieve the demand
    const unsigned int& lHBHolderSize = lHBHolder.getNbOfFlights();
    for (unsigned int i = 0; i < lHBHolderSize; ++ i) {
      const stdair::NbOfRequests_T& lCurrentUnconstrainedDemand = 
        lHBHolder.getUnconstrainedDemand(i);
      oDemand.push_back(lCurrentUnconstrainedDemand);
    }
  }

}
  
