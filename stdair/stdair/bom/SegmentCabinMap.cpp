// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomChildrenHolderImp.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/SegmentCabinMap.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinMap_T::
  SegmentCabinMap_T (const SegmentCabinHolder_T& iSegmentCabinHolder)
    : _segmentCabinHolder (iSegmentCabinHolder) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinMap_T::
  SegmentCabinMap_T (const SegmentCabinMap_T& iSCMap)
    : _segmentCabinHolder (iSCMap._segmentCabinHolder) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinMap_T::~SegmentCabinMap_T () {
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentCabinMap_T::iterator SegmentCabinMap_T::begin () const {
    return _segmentCabinHolder.mapBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentCabinMap_T::iterator SegmentCabinMap_T::end () const {
    return _segmentCabinHolder.mapEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentCabinMap_T::reverse_iterator SegmentCabinMap_T::rbegin () const {
    return _segmentCabinHolder.mapRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentCabinMap_T::reverse_iterator SegmentCabinMap_T::rend () const {
    return _segmentCabinHolder.mapREnd ();
  }

}

