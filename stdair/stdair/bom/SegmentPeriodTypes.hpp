// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_SEGMENTPERIODTYPES_HPP
#define __STDAIR_BOM_SEGMENTPERIODTYPES_HPP

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
  class SegmentPeriod;
  
  /** Define the SegmentPeriod structure. */
  typedef Structure<SegmentPeriod> SegmentPeriodStructure_T;
  
  /** Define the SegmentPeriod holder. */
  typedef BomChildrenHolderImp<SegmentPeriod> SegmentPeriodHolder_T;

  /** Define the segment-period list. */
  typedef BomList_T<SegmentPeriod> SegmentPeriodList_T;

  /** Define the segment-period map. */
  typedef BomMap_T<SegmentPeriod> SegmentPeriodMap_T;
}
#endif // __STDAIR_BOM_SEGMENTPERIODTYPES_HPP

