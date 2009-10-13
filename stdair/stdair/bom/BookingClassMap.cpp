// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomChildrenHolderImp.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/BookingClassMap.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  BookingClassMap_T::
  BookingClassMap_T (const BookingClassHolder_T& iBookingClassHolder)
    : _bookingClassHolder (iBookingClassHolder) {
  }

  // ////////////////////////////////////////////////////////////////////
  BookingClassMap_T::
  BookingClassMap_T (const BookingClassMap_T& iBCMap)
    : _bookingClassHolder (iBCMap._bookingClassHolder) {
  }

  // ////////////////////////////////////////////////////////////////////
  BookingClassMap_T::~BookingClassMap_T () {
  }

  // //////////////////////////////////////////////////////////////////////
  BookingClassMap_T::iterator BookingClassMap_T::begin () const {
    return _bookingClassHolder.mapBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  BookingClassMap_T::iterator BookingClassMap_T::end () const {
    return _bookingClassHolder.mapEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  BookingClassMap_T::reverse_iterator BookingClassMap_T::rbegin () const {
    return _bookingClassHolder.mapRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  BookingClassMap_T::reverse_iterator BookingClassMap_T::rend () const {
    return _bookingClassHolder.mapREnd ();
  }

}

