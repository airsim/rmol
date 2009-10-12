// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomStructureRoot.hpp>
#include <stdair/bom/BomContentRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/InventoryMap.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  InventoryMap_T::
  InventoryMap_T (const BomStructureRoot_T& iBomStructureRoot)
    : _bomStructureRoot (iBomStructureRoot) {
  }

  // ////////////////////////////////////////////////////////////////////
  InventoryMap_T::
  InventoryMap_T (const InventoryMap_T& iINVMap)
    : _bomStructureRoot (iINVMap._bomStructureRoot) {
  }

  // ////////////////////////////////////////////////////////////////////
  InventoryMap_T::~InventoryMap_T () {
  }

  // //////////////////////////////////////////////////////////////////////
  InventoryMap_T::iterator InventoryMap_T::begin () const {
    return _bomStructureRoot.inventoryMapBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  InventoryMap_T::iterator InventoryMap_T::end () const {
    return _bomStructureRoot.inventoryMapEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  InventoryMap_T::reverse_iterator InventoryMap_T::rbegin () const {
    return _bomStructureRoot.inventoryMapRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  InventoryMap_T::reverse_iterator InventoryMap_T::rend () const {
    return _bomStructureRoot.inventoryMapREnd ();
  }

}

