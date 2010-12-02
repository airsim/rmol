// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_SEGMENTDATETYPES_HPP
#define __STDAIR_BOM_SEGMENTDATETYPES_HPP

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
  class SegmentDate;
  
  /** Define the segment-date list. */
  typedef std::list<SegmentDate*> SegmentDateList_T;

  /** Define the segment-date map. */
  typedef std::map<const MapKey_T, SegmentDate*> SegmentDateMap_T;
}

#endif // __STDAIR_BOM_SEGMENTDATETYPES_HPP

