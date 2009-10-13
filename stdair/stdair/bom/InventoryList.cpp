// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomChildrenHolderImp.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/InventoryList.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  InventoryList_T::
  InventoryList_T (const InventoryHolder_T& iInventoryHolder)
    : _inventoryHolder (iInventoryHolder) {
  }

  // ////////////////////////////////////////////////////////////////////
  InventoryList_T::
  InventoryList_T (const InventoryList_T& iINVList)
    : _inventoryHolder (iINVList._inventoryHolder) {
  }

  // ////////////////////////////////////////////////////////////////////
  InventoryList_T::~InventoryList_T () {
  }

  // //////////////////////////////////////////////////////////////////////
  InventoryList_T::iterator InventoryList_T::begin () const {
    return _inventoryHolder.listBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  InventoryList_T::iterator InventoryList_T::end () const {
    return _inventoryHolder.listEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  InventoryList_T::reverse_iterator InventoryList_T::rbegin () const {
    return _inventoryHolder.listRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  InventoryList_T::reverse_iterator InventoryList_T::rend () const {
    return _inventoryHolder.listREnd ();
  }

}

