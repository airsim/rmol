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
#include <stdair/bom/BookingClassMap.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  BookingClassMap_T::
  BookingClassMap_T (const SegmentCabinStructure_T& iSegmentCabinStructure)
    : _segmentCabinStructure (iSegmentCabinStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  BookingClassMap_T::
  BookingClassMap_T (const BookingClassMap_T& iSCMap)
    : _segmentCabinStructure (iSCMap._segmentCabinStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  BookingClassMap_T::~BookingClassMap_T () {
  }

  // //////////////////////////////////////////////////////////////////////
  BookingClassMap_T::iterator BookingClassMap_T::begin () const {
    return _segmentCabinStructure.bookingClassMapBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  BookingClassMap_T::iterator BookingClassMap_T::end () const {
    return _segmentCabinStructure.bookingClassMapEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  BookingClassMap_T::reverse_iterator BookingClassMap_T::rbegin () const {
    return _segmentCabinStructure.bookingClassMapRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  BookingClassMap_T::reverse_iterator BookingClassMap_T::rend () const {
    return _segmentCabinStructure.bookingClassMapREnd ();
  }

}

