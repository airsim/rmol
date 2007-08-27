#ifndef __LATUS_COM_BOM_LEGCABINLIST_HPP
#define __LATUS_COM_BOM_LEGCABINLIST_HPP

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
    class LegCabin;

    /** Define lists of Leg-Cabin objects. */
    typedef std::map<std::string, LegCabin*> LegCabinList_T;
    typedef std::vector<LegCabin*> LegCabinOrderedList_T;

  }
}
#endif // __LATUS_COM_BOM_LEGCABINLIST_HPP
