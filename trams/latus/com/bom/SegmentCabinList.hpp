#ifndef __LATUS_COM_BOM_SEGMENTCABINLIST_HPP
#define __LATUS_COM_BOM_SEGMENTCABINLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <map>
#include <vector>

namespace LATUS {

  namespace COM {

    /** Forward declarations. */
    class SegmentCabin;

    /** Define lists of Segment-Cabin objects. */
    typedef std::map<std::string, SegmentCabin*> SegmentCabinList_T;
    typedef std::vector<SegmentCabin*> SegmentCabinOrderedList_T;

  }
}
#endif // __LATUS_COM_BOM_SEGMENTCABINLIST_HPP
