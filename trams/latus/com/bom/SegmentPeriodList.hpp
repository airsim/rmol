#ifndef __LATUS_COM_BOM_SEGMENTPERIODLIST_HPP
#define __LATUS_COM_BOM_SEGMENTPERIODLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <map>

namespace LATUS {

  namespace COM {

    /** Forward declarations. */
    class SegmentPeriod;

    /** Define list of Segment-Period objects. */
    typedef std::map<std::string, SegmentPeriod*> SegmentPeriodList_T;
  }
}
#endif // __LATUS_COM_BOM_SEGMENTPERIODLIST_HPP
