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
  template <typename CONTENT> class Structure;
  template <typename CONTENT> class BomChildrenHolderImp;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class Inventory;
  
  /** Define the Inventory structure. */
  typedef Structure<Inventory> InventoryStructure_T;

  /** Define the Inventory holder. */
  typedef BomChildrenHolderImp<Inventory> InventoryHolder_T;

  /** Define the Inventory list. */
  typedef BomList_T<Inventory> InventoryList_T;

  /** Define the Inventory map. */
  typedef BomMap_T<Inventory> InventoryMap_T;
  
}
#endif // __STDAIR_BOM_INVENTORYTYPES_HPP

