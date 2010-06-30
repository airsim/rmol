// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_SEGMENTPATHPERIODTYPES_HPP
#define __STDAIR_BOM_SEGMENTPATHPERIODTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <vector>
// STDAIR
#include <stdair/STDAIR_Types.hpp>

namespace stdair {

  // Forward declarations.
  template <typename CONTENT> class Structure;
  template <typename CONTENT> class BomChildrenHolderImp;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMultimap_T;
  class SegmentPathPeriod;
  
  /** Define the outbound path structure. */
  typedef Structure<SegmentPathPeriod> SegmentPathPeriodStructure_T;
  
  /** Define the outbound path holder. */
  typedef BomChildrenHolderImp<SegmentPathPeriod> SegmentPathPeriodHolder_T;

  /** Define the outbound path list. */
  typedef BomList_T<SegmentPathPeriod> SegmentPathPeriodList_T;

  /** Define the outbound path map. */
  typedef BomMultimap_T<SegmentPathPeriod> SegmentPathPeriodMultimap_T;

  typedef std::vector<const SegmentPathPeriod*> SegmentPathPeriodLightList_T;
  typedef std::vector<SegmentPathPeriodLightList_T>SegmentPathPeriodListList_T;

  /** Define the vector of boarding date offsets of the member segments of
      a segment path compare to the boarding date of the first segment. */
  typedef std::vector <DateOffset_T> DateOffsetList_T;
  
}
#endif // __STDAIR_BOM_SEGMENTPATHPERIODTYPES_HPP

