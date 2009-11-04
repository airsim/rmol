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
  SegmentDateContent::SegmentDateContent (const BomKey_T& iKey)
    : _key (iKey),
      _bookingCounter (DEFAULT_CLASS_NB_OF_BOOKINGS),
      _segmentRevenue (DEFAULT_REVENUE_VALUE),
      _segmentAverageFare (DEFAULT_CLASS_FARE_VALUE),
      _segmentUnitRevenue (DEFAULT_REVENUE_VALUE),
      _segmentRPK (DEFAULT_DISTANCE_VALUE) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDateContent::~SegmentDateContent () {
  }

  // //////////////////////////////////////////////////////////////////////
  const Duration_T SegmentDateContent::getTimeOffSet() const {
    // TimeOffSet = (OffTime - BoardTime) + (OffDate - BoardDate) * 24
    //              - ElapsedTime
    Duration_T oTimeOffSet = (_offTime - _boardTime);
    const DateOffSet_T& lDateOffSet = getDateOffSet();
    const Duration_T lDateOffSetInHours (lDateOffSet.days() * 24, 0, 0);
    oTimeOffSet += lDateOffSetInHours - _elapsedTime;
    return oTimeOffSet;
  }

}

