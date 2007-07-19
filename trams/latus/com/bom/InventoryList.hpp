#ifndef __LATUS_COM_BOM_INVENTORYLIST_HPP
#define __LATUS_COM_BOM_INVENTORYLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <map>

namespace LATUS {
  
  namespace COM {

    /** Forward declarations. */
    class Inventory;

    typedef std::map<std::string, Inventory*> InventoryList_T;
  }
}
#endif // __LATUS_COM_BOM_INVENTORYLIST_HPP
