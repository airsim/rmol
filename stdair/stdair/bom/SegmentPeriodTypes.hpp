// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_SEGMENTPERIODTYPES_HPP
#define __STDAIR_BOM_SEGMENTPERIODTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <list>
// STDAIR
#include <stdair/STDAIR_Types.hpp>

namespace stdair {

  // Forward declarations.
  class SegmentPeriod;
  
  /** Define the segment-period list. */
  typedef std::list<SegmentPeriod*> SegmentPeriodList_T;

  /** Define the segment-period map. */
  typedef std::map<const MapKey_T&, SegmentPeriod*> SegmentPeriodMap_T;
}
#endif // __STDAIR_BOM_SEGMENTPERIODTYPES_HPP

