// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_YIELDSTORETYPES_HPP
#define __STDAIR_BOM_YIELDSTORETYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <list>
// StdAir
#include <stdair/bom/key_types.hpp>

namespace stdair {

  // Forward declarations.
  class YieldStore;

  /** Define the Inventory list. */
  typedef std::list<YieldStore*> YieldStoreList_T;
  
  /** Define the Inventory map. */
  typedef std::map<const MapKey_T, YieldStore*> YieldStoreMap_T;
  
}
#endif // __STDAIR_BOM_YIELDSTORETYPES_HPP

