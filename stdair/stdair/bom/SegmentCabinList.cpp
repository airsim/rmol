// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomChildrenHolderImp.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/SegmentCabinList.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinList_T::
  SegmentCabinList_T (const SegmentCabinHolder_T& iSegmentCabinHolder)
    : _segmentCabinHolder (iSegmentCabinHolder) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinList_T::
  SegmentCabinList_T (const SegmentCabinList_T& iSCList)
    : _segmentCabinHolder (iSCList._segmentCabinHolder) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinList_T::~SegmentCabinList_T () {
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentCabinList_T::iterator SegmentCabinList_T::begin () const {
    return _segmentCabinHolder.listBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentCabinList_T::iterator SegmentCabinList_T::end () const {
    return _segmentCabinHolder.listEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentCabinList_T::reverse_iterator SegmentCabinList_T::rbegin () const {
    return _segmentCabinHolder.listRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentCabinList_T::reverse_iterator SegmentCabinList_T::rend () const {
    return _segmentCabinHolder.listREnd ();
  }

}

