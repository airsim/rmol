#ifndef __LATUS_COM_BOM_LEGCABINLIST_HPP
#define __LATUS_COM_BOM_LEGCABINLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <map>
// LATUS Common
#include <latus/com/bom/BomAbstract.hpp>


namespace LATUS {

  namespace COM {

    /** Forward declarations. */
    class LegCabin;

    /** Define list of Leg-Cabin objects. */
    typedef std::map<std::string, LegCabin*> LegCabinList_T;

  }
}
#endif // __LATUS_COM_BOM_LEGCABINLIST_HPP
