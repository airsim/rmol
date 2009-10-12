// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/SegmentDateStructure.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/SegmentCabinList.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinList_T::
  SegmentCabinList_T (const SegmentDateStructure_T& iSegmentDateStructure)
    : _segmentDateStructure (iSegmentDateStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinList_T::
  SegmentCabinList_T (const SegmentCabinList_T& iSCList)
    : _segmentDateStructure (iSCList._segmentDateStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinList_T::~SegmentCabinList_T () {
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentCabinList_T::iterator SegmentCabinList_T::begin () const {
    return _segmentDateStructure.segmentCabinListBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentCabinList_T::iterator SegmentCabinList_T::end () const {
    return _segmentDateStructure.segmentCabinListEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentCabinList_T::reverse_iterator SegmentCabinList_T::rbegin () const {
    return _segmentDateStructure.segmentCabinListRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentCabinList_T::reverse_iterator SegmentCabinList_T::rend () const {
    return _segmentDateStructure.segmentCabinListREnd ();
  }

}

