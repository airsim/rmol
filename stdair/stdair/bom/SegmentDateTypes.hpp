// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_SEGMENTDATETYPES_HPP
#define __STDAIR_BOM_SEGMENTDATETYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <vector>

namespace stdair {

  // Forward declarations.
  template <typename CONTENT> class Structure;
  template <typename CONTENT> class BomChildrenHolderImp;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class SegmentDate;
  
  /** Define the SegmentDate structure. */
  typedef Structure<SegmentDate> SegmentDateStructure_T;
  
  /** Define the SegmentDate holder. */
  typedef BomChildrenHolderImp<SegmentDate> SegmentDateHolder_T;
  
 /** Define the segment-date list. */
  typedef BomList_T<SegmentDate> SegmentDateList_T;

  /** Define the segment-date map. */
  typedef BomMap_T<SegmentDate> SegmentDateMap_T;
}

#endif // __STDAIR_BOM_SEGMENTDATETYPES_HPP

