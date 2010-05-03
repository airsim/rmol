// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/basic/BasConst_BookingClass.hpp>
#include <stdair/bom/SegmentDateContent.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentDateContent::SegmentDateContent (const Key_T& iKey)
    : _key (iKey) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDateContent::~SegmentDateContent () {
  }

  // ////////////////////////////////////////////////////////////////////
  const Duration_T SegmentDateContent::getTimeOffSet() const {
    // TimeOffSet = (OffTime - BoardingTime) + (OffDate - BoardingDate) * 24
    //              - ElapsedTime
    Duration_T oTimeOffSet = (_offTime - _boardingTime);
    const DateOffSet_T& lDateOffSet = getDateOffSet();
    const Duration_T lDateOffSetInHours (lDateOffSet.days() * 24, 0, 0);
    oTimeOffSet += lDateOffSetInHours - _elapsedTime;
    return oTimeOffSet;
  }

}

