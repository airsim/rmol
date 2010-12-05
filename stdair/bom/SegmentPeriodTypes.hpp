// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_SEGMENTPERIODTYPES_HPP
#define __STDAIR_BOM_SEGMENTPERIODTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <list>
// StdAir
#include <stdair/bom/key_types.hpp>

namespace stdair {

  // Forward declarations.
  class SegmentPeriod;
  
  /** Define the segment-period list. */
  typedef std::list<SegmentPeriod*> SegmentPeriodList_T;

  /** Define the segment-period map. */
  typedef std::map<const MapKey_T, SegmentPeriod*> SegmentPeriodMap_T;

  /** Define the list of pair<MapKey_T, SegmentPeriod>. */
  typedef std::pair<MapKey_T, SegmentPeriod*> SegmentPeriodWithKey_T;
  typedef std::list<SegmentPeriodWithKey_T> SegmentPeriodDetailedList_T;
}
#endif // __STDAIR_BOM_SEGMENTPERIODTYPES_HPP

