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
#include <stdair/bom/SegmentCabinMap.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinMap_T::
  SegmentCabinMap_T (const SegmentDateStructure_T& iSegmentDateStructure)
    : _segmentDateStructure (iSegmentDateStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinMap_T::
  SegmentCabinMap_T (const SegmentCabinMap_T& iSCMap)
    : _segmentDateStructure (iSCMap._segmentDateStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinMap_T::~SegmentCabinMap_T () {
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentCabinMap_T::iterator SegmentCabinMap_T::begin () const {
    return _segmentDateStructure.segmentCabinMapBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentCabinMap_T::iterator SegmentCabinMap_T::end () const {
    return _segmentDateStructure.segmentCabinMapEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentCabinMap_T::reverse_iterator SegmentCabinMap_T::rbegin () const {
    return _segmentDateStructure.segmentCabinMapRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentCabinMap_T::reverse_iterator SegmentCabinMap_T::rend () const {
    return _segmentDateStructure.segmentCabinMapREnd ();
  }

}

