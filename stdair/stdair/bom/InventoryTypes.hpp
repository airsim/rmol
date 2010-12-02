// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_INVENTORYTYPES_HPP
#define __STDAIR_BOM_INVENTORYTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <list>
// Stdair
#include <stdair/bom/key_types.hpp>

namespace stdair {

  // Forward declarations.
  class Inventory;

  /** Define the Inventory list. */
  typedef std::list<Inventory*> InventoryList_T;

  /** Define the Inventory map. */
  typedef std::map<const MapKey_T, Inventory*> InventoryMap_T;
  
}
#endif // __STDAIR_BOM_INVENTORYTYPES_HPP
