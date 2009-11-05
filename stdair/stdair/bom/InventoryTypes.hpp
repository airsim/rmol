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
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class Inventory;
  
  /** Define the Inventory structure. */
  typedef InventoryStructure<Inventory> InventoryStructure_T;
  
  /** Define the Inventory structure list. */
  typedef std::vector<InventoryStructure_T*> InventoryStructureList_T;

  /** Define the Inventory structure map. */
  typedef std::map<const std::string, InventoryStructure_T*> InventoryStructureMap_T;

  /** Define the Inventory list. */
  typedef BomList_T<Inventory> InventoryList_T;

  /** Define the Inventory map. */
  typedef BomMap_T<Inventory> InventoryMap_T;
  
}
#endif // __STDAIR_BOM_INVENTORYTYPES_HPP

