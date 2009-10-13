// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomChildrenHolderImp.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/SegmentDateList.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentDateList_T::
  SegmentDateList_T (const SegmentDateHolder_T& iSegmentDateHolder)
    : _segmentDateHolder (iSegmentDateHolder) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDateList_T::
  SegmentDateList_T (const SegmentDateList_T& iSDList)
    : _segmentDateHolder (iSDList._segmentDateHolder) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDateList_T::~SegmentDateList_T () {
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentDateList_T::iterator SegmentDateList_T::begin () const {
    return _segmentDateHolder.listBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentDateList_T::iterator SegmentDateList_T::end () const {
    return _segmentDateHolder.listEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentDateList_T::reverse_iterator SegmentDateList_T::rbegin () const {
    return _segmentDateHolder.listRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentDateList_T::reverse_iterator SegmentDateList_T::rend () const {
    return _segmentDateHolder.listREnd ();
  }

}

