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
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class SegmentDate;
  
  /** Define the SegmentDate structure. */
  typedef SegmentDateStructure<SegmentDate> SegmentDateStructure_T;
  
  /** Define the segment-date structure list. */
  typedef std::vector<SegmentDateStructure_T*> SegmentDateStructureList_T;

  /** Define the segment-date structure map. */
  typedef std::map<const std::string, SegmentDateStructure_T*> SegmentDateStructureMap_T;
  
 /** Define the segment-date list. */
  typedef BomList_T<SegmentDate> SegmentDateList_T;

  /** Define the segment-date map. */
  typedef BomMap_T<SegmentDate> SegmentDateMap_T;
}
#endif // __STDAIR_BOM_SEGMENTDATETYPES_HPP

