#ifndef __LATUS_TSP_BOM_AIRPORTLIST_HPP
#define __LATUS_TSP_BOM_AIRPORTLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <set>
#include <vector>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>

namespace LATUS {

  namespace TSP {

    /** Define lists of Airport Codes. */
    typedef std::set<COM::AirportCode_T> AirportList_T;
    typedef std::vector<COM::AirportCode_T> AirportOrderedList_T;

  }
}
#endif // __LATUS_TSP_BOM_AIRPORTLIST_HPP
