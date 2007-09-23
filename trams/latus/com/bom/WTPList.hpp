#ifndef __LATUS_COM_BOM_WTPLIST_HPP
#define __LATUS_COM_BOM_WTPLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>

namespace LATUS {
  
  namespace COM {

    /** Forward declarations. */
    class WTP;

    // TODO: use a comparator for the floats (as they are not comparable as is)
    /** List of WTP objects (for each CityPairDate object). */
    typedef std::map<PriceValue_T, WTP*> WTPList_T;
  }

}
#endif // __LATUS_COM_BOM_WTPLIST_HPP
