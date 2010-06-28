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
  const Duration_T SegmentDateContent::getTimeOffset() const {
    // TimeOffset = (OffTime - BoardingTime) + (OffDate - BoardingDate) * 24
    //              - ElapsedTime
    Duration_T oTimeOffset = (_offTime - _boardingTime);
    const DateOffset_T& lDateOffset = getDateOffset();
    const Duration_T lDateOffsetInHours (lDateOffset.days() * 24, 0, 0);
    oTimeOffset += lDateOffsetInHours - _elapsedTime;
    return oTimeOffset;
  }

}

