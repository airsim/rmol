// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/SegmentSnapshotTable.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/bom/SegmentSnapshotTableHelper.hpp>

namespace RMOL {
  // ////////////////////////////////////////////////////////////////////
  stdair::NbOfSegments_T SegmentSnapshotTableHelper::
  getNbOfSegmentAlreadyPassedThisDTD (const stdair::SegmentSnapshotTable& iGB,
                                      const stdair::DTD_T& iDTD,
                                      const stdair::Date_T& iCurrentDate) {
    stdair::NbOfSegments_T oNbOfSegments = 0;

    // Browse the list of segments and check if it has passed the given DTD.
    const stdair::SegmentCabinIndexMap_T& lSCMap=iGB.getSegmentCabinIndexMap();
    for (stdair::SegmentCabinIndexMap_T::const_iterator itSC = lSCMap.begin();
         itSC != lSCMap.end(); ++itSC) {
      const stdair::SegmentCabin* lSC_ptr = itSC->first;
      assert (lSC_ptr != NULL);

      if (hasPassedThisDTD (*lSC_ptr, iDTD, iCurrentDate) == true) {
        ++oNbOfSegments;
      }
    }
    
    return oNbOfSegments;
  }
  
  // ////////////////////////////////////////////////////////////////////
  bool SegmentSnapshotTableHelper::
  hasPassedThisDTD (const stdair::SegmentCabin& iSegmentCabin,
                    const stdair::DTD_T& iDTD,
                    const stdair::Date_T& iCurrentDate) {
    // Retrieve the boarding date.
    const stdair::SegmentDate& lSegmentDate =
      stdair::BomManager::getParent<stdair::SegmentDate> (iSegmentCabin);
    const stdair::Date_T& lBoardingDate = lSegmentDate.getBoardingDate();

    // Compare the date offset between the boarding date and the current date
    // to the DTD.
    stdair::DateOffset_T lDateOffset = lBoardingDate - iCurrentDate;
    stdair::DTD_T lDateOffsetInDays = lDateOffset.days();
    if (iDTD > lDateOffsetInDays) {
      return true;
    } else {
      return false;
    }
  }
}
