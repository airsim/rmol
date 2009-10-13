// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomChildrenHolderImp.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/BookingClassList.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  BookingClassList_T::
  BookingClassList_T (const BookingClassHolder_T& iBookingClassHolder)
    : _bookingClassHolder (iBookingClassHolder) {
  }

  // ////////////////////////////////////////////////////////////////////
  BookingClassList_T::
  BookingClassList_T (const BookingClassList_T& iBCList)
    : _bookingClassHolder (iBCList._bookingClassHolder) {
  }

  // ////////////////////////////////////////////////////////////////////
  BookingClassList_T::~BookingClassList_T () {
  }

  // //////////////////////////////////////////////////////////////////////
  BookingClassList_T::iterator BookingClassList_T::begin () const {
    return _bookingClassHolder.listBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  BookingClassList_T::iterator BookingClassList_T::end () const {
    return _bookingClassHolder.listEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  BookingClassList_T::reverse_iterator BookingClassList_T::rbegin () const {
    return _bookingClassHolder.listRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  BookingClassList_T::reverse_iterator BookingClassList_T::rend () const {
    return _bookingClassHolder.listREnd ();
  }

}

