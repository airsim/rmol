#ifndef __LATUS_COM_BOM_SEGMENTCABINLIST_HPP
#define __LATUS_COM_BOM_SEGMENTCABINLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <map>

namespace LATUS {

  namespace COM {

    /** Forward declarations. */
    class SegmentCabin;

    /** Define list of Segment-Cabin objects. */
    typedef std::map<std::string, SegmentCabin*> SegmentCabinList_T;

  }
}
#endif // __LATUS_COM_BOM_SEGMENTCABINLIST_HPP
