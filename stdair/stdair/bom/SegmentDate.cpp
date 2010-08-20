// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/basic/BasConst_BookingClass.hpp>
#include <stdair/bom/SegmentDate.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentDate::SegmentDate (const Key_T& iKey)
    : _key (iKey) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDate::~SegmentDate () {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string SegmentDate::toString() const {
    std::ostringstream oStr;

    oStr << describeKey() << std::endl;
    
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const Duration_T SegmentDate::getTimeOffset() const {
    // TimeOffset = (OffTime - BoardingTime) + (OffDate - BoardingDate) * 24
    //              - ElapsedTime
    Duration_T oTimeOffset = (_offTime - _boardingTime);
    const DateOffset_T& lDateOffset = getDateOffset();
    const Duration_T lDateOffsetInHours (lDateOffset.days() * 24, 0, 0);
    oTimeOffset += lDateOffsetInHours - _elapsedTime;
    return oTimeOffset;
  }

}

