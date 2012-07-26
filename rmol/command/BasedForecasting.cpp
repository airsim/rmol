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
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/SegmentSnapshotTable.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/bom/Utilities.hpp>
#include <rmol/bom/SegmentSnapshotTableHelper.hpp>
#include <rmol/bom/HistoricalBookingHolder.hpp>
#include <rmol/bom/HistoricalBooking.hpp>
#include <rmol/command/BasedForecasting.hpp>
#include <rmol/command/Detruncator.hpp>

namespace RMOL {
  // ////////////////////////////////////////////////////////////////////
  bool BasedForecasting::
  forecast (stdair::SegmentCabin& ioSegmentCabin,
            const stdair::Date_T& iCurrentDate,
            const stdair::DTD_T& iCurrentDTD,
            const stdair::UnconstrainingMethod& iUnconstrainingMethod,
            const stdair::NbOfSegments_T& iNbOfDepartedSegments) {

    // Retrieve the snapshot table.
    const stdair::SegmentSnapshotTable& lSegmentSnapshotTable =
      ioSegmentCabin.getSegmentSnapshotTable();

    // Retrieve the booking class list.
    const stdair::BookingClassList_T& lBCList =
      stdair::BomManager::getList<stdair::BookingClass>(ioSegmentCabin);      

    // Browse all remaining DCP's and do unconstraining and forecasting for
    // all demand.
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

        // Browse the list of booking classes and forecast the product-oriented
        // demand for each class.
        for (stdair::BookingClassList_T::const_iterator itBC = lBCList.begin();
             itBC != lBCList.end(); ++itBC) {
          stdair::BookingClass* lBC_ptr = *itBC;
          assert (lBC_ptr != NULL);
          
          // Retrieve the historical product-oriented bookings for the
          // given class.
          HistoricalBookingHolder lHBHolder;
          prepareHistoricalBooking (ioSegmentCabin, *lBC_ptr,
                                    lSegmentSnapshotTable,
                                    lHBHolder,
                                    lCurrentDCP, lNextDCP,
                                    lSegmentBegin, lSegmentEnd);
          
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

          // Add the demand forecast to the booking class.
          const stdair::MeanValue_T& lCurrentMean = lBC_ptr->getProductDemMean();
          const stdair::StdDevValue_T& lCurrentStdDev = 
            lBC_ptr->getProductDemStdDev();

          const stdair::MeanValue_T lNewMean = lCurrentMean + lMean;
          const stdair::StdDevValue_T lNewStdDev = 
            std::sqrt (lCurrentStdDev * lCurrentStdDev + lStdDev * lStdDev);

          lBC_ptr->setProductDemMean (lNewMean);
          lBC_ptr->setProductDemStdDev (lNewStdDev);
        }
      }
    }
    return true;
  }
  
  // ////////////////////////////////////////////////////////////////////
  void BasedForecasting::prepareHistoricalBooking
    (const stdair::SegmentCabin& iSegmentCabin,
     const stdair::BookingClass& iBookingClass,
     const stdair::SegmentSnapshotTable& iSegmentSnapshotTable,
     HistoricalBookingHolder& ioHBHolder,
     const stdair::DCP_T& iDCPBegin, const stdair::DCP_T& iDCPEnd,
     const stdair::NbOfSegments_T& iSegmentBegin,
     const stdair::NbOfSegments_T& iSegmentEnd) {

    // Retrieve the booking class index within the snapshot table
    const stdair::ClassIndex_T& lClassIdx = 
      iSegmentSnapshotTable.getClassIndex (iBookingClass.describeKey());

    // Retrieve the gross daily booking and availability snapshots.
    const stdair::ConstSegmentCabinDTDRangeSnapshotView_T lPriceBookingView =
      iSegmentSnapshotTable.getConstSegmentCabinDTDRangePriceOrientedGrossBookingSnapshotView (iSegmentBegin, iSegmentEnd, iDCPEnd, iDCPBegin);
    const stdair::ConstSegmentCabinDTDRangeSnapshotView_T lProductBookingView =
      iSegmentSnapshotTable.getConstSegmentCabinDTDRangeProductOrientedGrossBookingSnapshotView (iSegmentBegin, iSegmentEnd, iDCPEnd, iDCPBegin);
    const stdair::ConstSegmentCabinDTDRangeSnapshotView_T lAvlView =
      iSegmentSnapshotTable.getConstSegmentCabinDTDRangeAvailabilitySnapshotView (iSegmentBegin, iSegmentEnd, iDCPEnd, iDCPBegin);
    
    // Browse the list of segments and build the historical booking holder.
    const stdair::ClassIndexMap_T& lVTIdxMap =
      iSegmentSnapshotTable.getClassIndexMap();
    const stdair::NbOfClasses_T lNbOfClasses = lVTIdxMap.size();

    for (short i = 0; i <= iSegmentEnd-iSegmentBegin; ++i) {
      stdair::Flag_T lCensorshipFlag = false;
      const short lNbOfDTDs = iDCPBegin - iDCPEnd + 1;
      const stdair::UnsignedIndex_T lIdx = i*lNbOfClasses + lClassIdx;

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

      // Retrieve the historical bookings
      stdair::NbOfBookings_T lNbOfHistoricalBkgs = 0.0;
      for (short j = 0; j < lNbOfDTDs; ++j) {
        lNbOfHistoricalBkgs += 
          lPriceBookingView[lIdx][j] + lProductBookingView[lIdx][j];
      }              
      HistoricalBooking lHistoricalBkg (lNbOfHistoricalBkgs, lCensorshipFlag);
      ioHBHolder.addHistoricalBooking (lHistoricalBkg);
    }
  }
  
}
