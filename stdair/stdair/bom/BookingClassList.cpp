// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/SegmentCabinStructure.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/BookingClassList.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  BookingClassList_T::
  BookingClassList_T (const SegmentCabinStructure_T& iSegmentCabinStructure)
    : _segmentCabinStructure (iSegmentCabinStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  BookingClassList_T::
  BookingClassList_T (const BookingClassList_T& iSCList)
    : _segmentCabinStructure (iSCList._segmentCabinStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  BookingClassList_T::~BookingClassList_T () {
  }

  // //////////////////////////////////////////////////////////////////////
  BookingClassList_T::iterator BookingClassList_T::begin () const {
    return _segmentCabinStructure.bookingClassListBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  BookingClassList_T::iterator BookingClassList_T::end () const {
    return _segmentCabinStructure.bookingClassListEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  BookingClassList_T::reverse_iterator BookingClassList_T::rbegin () const {
    return _segmentCabinStructure.bookingClassListRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  BookingClassList_T::reverse_iterator BookingClassList_T::rend () const {
    return _segmentCabinStructure.bookingClassListREnd ();
  }

}

