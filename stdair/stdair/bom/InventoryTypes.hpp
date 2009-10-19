// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_INVENTORYTYPES_HPP
#define __STDAIR_BOM_INVENTORYTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <vector>

namespace stdair {

  // Forward declarations.
  template <typename BOM_CONTENT> class InventoryStructure;
  template <typename BOM_CONTENT> class InventoryKey;
  class Inventory;
  
  /** Define the Inventory structure. */
  typedef InventoryStructure<Inventory> InventoryStructure_T;
  
  /** Define the Inventory key. */
  typedef InventoryKey<Inventory> InventoryKey_T;

  /** Define the Inventory structure list. */
  typedef std::vector<InventoryStructure_T*> InventoryStructureList_T;

  /** Define the Inventory structure map. */
  typedef std::map<const std::string, InventoryStructure_T*> InventoryStructureMap_T;
  
}
#endif // __STDAIR_BOM_INVENTORYTYPES_HPP

