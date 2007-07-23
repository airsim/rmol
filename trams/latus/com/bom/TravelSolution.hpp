#ifndef __LATUS_COM_BOM_TRAVELSOLUTION_HPP
#define __LATUS_COM_BOM_TRAVELSOLUTION_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <vector>
// LATUS Common
#include <latus/com/bom/SegmentDateKey.hpp>

namespace LATUS {

  namespace COM {

    /** Define a Travel Solution (TS). */
    typedef std::vector<SegmentDateKey_T> TravelSolutionKey_T;

    /** Define a list of travel solutions. */
    typedef std::vector<TravelSolutionKey_T> TravelSolutionKeyList_T;

  }
}
#endif // __LATUS_COM_BOM_TRAVELSOLUTION_HPP
