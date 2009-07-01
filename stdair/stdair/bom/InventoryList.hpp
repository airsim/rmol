#ifndef __STDAIR_BOM_INVENTORYLIST_HPP
#define __STDAIR_BOM_INVENTORYLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <map>
#include <vector>
#include <list>

namespace stdair {

  /** Forward declarations. */
  class Inventory;

  /** Define lists of Inventory objects. */
  typedef std::map<std::string, Inventory*> InventoryList_T;
  typedef std::vector<Inventory*> InventoryOrderedList_T;
  typedef std::list<const Inventory*> InventoryLightList_T;

}
#endif // __STDAIR_BOM_INVENTORYLIST_HPP
