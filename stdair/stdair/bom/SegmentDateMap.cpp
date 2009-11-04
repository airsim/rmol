// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomChildrenHolderImp.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/SegmentDateMap.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentDateMap_T::
  SegmentDateMap_T (const SegmentDateHolder_T& iSegmentDateHolder)
    : _segmentDateHolder (iSegmentDateHolder) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDateMap_T::
  SegmentDateMap_T (const SegmentDateMap_T& iSDMap)
    : _segmentDateHolder (iSDMap._segmentDateHolder) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDateMap_T::~SegmentDateMap_T () {
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentDateMap_T::iterator SegmentDateMap_T::begin () const {
    return _segmentDateHolder.mapBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentDateMap_T::iterator SegmentDateMap_T::end () const {
    return _segmentDateHolder.mapEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentDateMap_T::reverse_iterator SegmentDateMap_T::rbegin () const {
    return _segmentDateHolder.mapRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentDateMap_T::reverse_iterator SegmentDateMap_T::rend () const {
    return _segmentDateHolder.mapREnd ();
  }
  
  // //////////////////////////////////////////////////////////////////////
  SegmentDateMap_T::
  iterator SegmentDateMap_T::find (const MapKey_T& iKey) const {
    return _segmentDateHolder.find (iKey);
  }

}

