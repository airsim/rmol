#ifndef __LATUS_COM_BOM_SEGMENTDATELIST_HPP
#define __LATUS_COM_BOM_SEGMENTDATELIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <map>

namespace LATUS {

  namespace COM {

    /** Forward declarations. */
    class SegmentDate;

    /** Define list of Segment-Date objects. */
    typedef std::map<std::string, SegmentDate*> SegmentDateList_T;
  }
}
#endif // __LATUS_COM_BOM_SEGMENTDATELIST_HPP
