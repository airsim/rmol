// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/basic/BasConst_BookingClass.hpp>
#include <stdair/bom/SegmentPeriod.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentPeriod::SegmentPeriod (const Key_T& iKey)
    : _key (iKey), _parent (NULL),  _boardingDateOffset (0), _offDateOffset (0) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentPeriod::~SegmentPeriod () {
  }
  
  // ////////////////////////////////////////////////////////////////////
  std::string SegmentPeriod::toString() const {
    std::ostringstream oStr;
    oStr << describeKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentPeriod::
  addCabinBookingClassList (const CabinCode_T& iCabinCode,
                            const ClassList_String_T& iClassCodeList) {
    const bool insert = _cabinBookingClassMap.
      insert (CabinBookingClassMap_T::value_type (iCabinCode, 
						  iClassCodeList)).second;
    assert (insert == true);
  }

}
