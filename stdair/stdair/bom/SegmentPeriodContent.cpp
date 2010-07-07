// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/basic/BasConst_BookingClass.hpp>
#include <stdair/bom/SegmentPeriodContent.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentPeriodContent::SegmentPeriodContent (const Key_T& iKey)
    : _key (iKey) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentPeriodContent::~SegmentPeriodContent () {
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentPeriodContent::
  addCabinBookingClassList (const CabinCode_T& iCabinCode,
                            const ClassList_String_T& iClassCodeList) {
    const bool insert = _cabinBookingClassMap.
      insert (CabinBookingClassMap_T::value_type (iCabinCode, iClassCodeList)).second;
    assert (insert == true);                                                    
  }

}

