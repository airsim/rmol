// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomStructureRoot.hpp>
#include <stdair/bom/BomContentRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/InventoryList.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  InventoryList_T::
  InventoryList_T (const BomStructureRoot_T& iBomStructureRoot)
    : _bomStructureRoot (iBomStructureRoot) {
  }

  // ////////////////////////////////////////////////////////////////////
  InventoryList_T::
  InventoryList_T (const InventoryList_T& iINVList)
    : _bomStructureRoot (iINVList._bomStructureRoot) {
  }

  // ////////////////////////////////////////////////////////////////////
  InventoryList_T::~InventoryList_T () {
  }

  // //////////////////////////////////////////////////////////////////////
  InventoryList_T::iterator InventoryList_T::begin () const {
    return _bomStructureRoot.inventoryListBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  InventoryList_T::iterator InventoryList_T::end () const {
    return _bomStructureRoot.inventoryListEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  InventoryList_T::reverse_iterator InventoryList_T::rbegin () const {
    return _bomStructureRoot.inventoryListRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  InventoryList_T::reverse_iterator InventoryList_T::rend () const {
    return _bomStructureRoot.inventoryListREnd ();
  }

}

