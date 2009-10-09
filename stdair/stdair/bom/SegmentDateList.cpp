// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/FlightDateStructure.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/SegmentDateList.hpp>
#include <stdair/bom/LegDate.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentDateList_T::
  SegmentDateList_T (const FlightDateStructure_T& iFlightDateStructure)
    : _flightDateStructure (iFlightDateStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDateList_T::
  SegmentDateList_T (const SegmentDateList_T& iSDList)
    : _flightDateStructure (iSDList._flightDateStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDateList_T::~SegmentDateList_T () {
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentDateList_T::iterator SegmentDateList_T::begin () const {
    return _flightDateStructure.segmentDateListBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentDateList_T::iterator SegmentDateList_T::end () const {
    return _flightDateStructure.segmentDateListEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentDateList_T::reverse_iterator SegmentDateList_T::rbegin () const {
    return _flightDateStructure.segmentDateListRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentDateList_T::reverse_iterator SegmentDateList_T::rend () const {
    return _flightDateStructure.segmentDateListREnd ();
  }

}

