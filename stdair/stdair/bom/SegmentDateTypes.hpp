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
  template <typename BOM_CONTENT> class SegmentDateStructure;
  class SegmentDate;
  
  /** Define the SegmentDate structure. */
  typedef SegmentDateStructure<SegmentDate> SegmentDateStructure_T;
  
  /** Define the segment-date structure list. */
  typedef std::vector<SegmentDateStructure_T*> SegmentDateStructureList_T;

  /** Define the segment-date structure map. */
  typedef std::map<const std::string, SegmentDateStructure_T*> SegmentDateStructureMap_T;

}
#endif // __STDAIR_BOM_SEGMENTDATETYPES_HPP

