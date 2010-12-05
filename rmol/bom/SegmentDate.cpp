// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// RMOL
#include <rmol/bom/SegmentDate.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  void SegmentDate::updateCensorshipFlag () {
    updateCensorshipFlag (*self);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void SegmentDate::updateCensorshipFlag (SegmentDate& ioSegmentDate) {
    bool censorshipFlag = false;

    const BookingClassDateList_T& lBookingClassDateList =
      ioSegmentDate.getBookingClassList();
    for (BookingClassDateList_T::const_iterator itBookingClassDateList =
           lBookingClassDateList.begin();
         itBookingClassDateList != lBookingClassDateList.end();
         ++itBookingClassDateList) {
      BookingClassDate& lBookingClassDate = *itBookingClassDateList;

      const bool lCensorshipFlagOfAClass= lBookingClassDate.getCensorshipFlag();
      if (lCensorshipFlagOfAClass == true) {
        censorshipFlag = true;
        break;
      }
    }
    
    // Store the result within the object
    ioSegmentDate.setCensorshipFlag (censorshipFlag);
  }

}
