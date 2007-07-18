#ifndef __LATUS_COM_BOM_CITYPAIRLIST_HPP
#define __LATUS_COM_BOM_CITYPAIRLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <map>

namespace LATUS {
  
  namespace COM {

    /** Forward declarations. */
    class CityPair;

    typedef std::map<std::string, CityPair*> CityPairList_T;
  }
}
#endif // __LATUS_COM_BOM_CITYPAIRLIST_HPP
