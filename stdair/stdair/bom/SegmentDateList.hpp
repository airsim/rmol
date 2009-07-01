#ifndef __STDAIR_BOM_SEGMENTDATELIST_HPP
#define __STDAIR_BOM_SEGMENTDATELIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <map>
#include <vector>
#include <list>

namespace stdair {

  /** Forward declarations. */
  class SegmentDate;

  /** Define lists of Segment-Date objects. */
  typedef std::map<std::string, SegmentDate*> SegmentDateList_T;
  typedef std::vector<SegmentDate*> SegmentDateOrderedList_T;
  typedef std::list<const SegmentDate*> SegmentDateLightList_T;

}
#endif // __STDAIR_BOM_SEGMENTDATELIST_HPP
