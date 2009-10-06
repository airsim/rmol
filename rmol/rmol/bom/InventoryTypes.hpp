// //////////////////////////////////////////////////////////////////////
#ifndef __RMOL_BOM_INVENTORYTYPES_HPP
#define __RMOL_BOM_INVENTORYTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

// Forward declarations.
namespace stdair {
  template <typename BOM_CONTENT> class Inventory;
  template <typename BOM_CONTENT> class InventoryKey;
}

namespace RMOL {

  // Forward declarations.
  class Inventory;
  
  /** Define the Inventory structure. */
  typedef stdair::Inventory<Inventory> InventoryStructure_T;
  
  /** Define the Inventory key. */
  typedef stdair::InventoryKey<Inventory> InventoryKey_T;

  /** Define the flight-date structure list. */
  typedef std::vector<InventoryStructure_T*> InventoryStructureList_T;

  /** Define the flight-date structure map. */
  typedef std::map<const std::string, InventoryStructure_T*> InventoryStructureMap_T;
  
}
#endif // __RMOL_BOM_INVENTORYTYPES_HPP

