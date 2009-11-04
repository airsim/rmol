// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomChildrenHolderImp.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/InventoryMap.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  InventoryMap_T::
  InventoryMap_T (const InventoryHolder_T& iInventoryHolder)
    : _inventoryHolder (iInventoryHolder) {
  }

  // ////////////////////////////////////////////////////////////////////
  InventoryMap_T::
  InventoryMap_T (const InventoryMap_T& iINVMap)
    : _inventoryHolder (iINVMap._inventoryHolder) {
  }

  // ////////////////////////////////////////////////////////////////////
  InventoryMap_T::~InventoryMap_T () {
  }

  // //////////////////////////////////////////////////////////////////////
  InventoryMap_T::iterator InventoryMap_T::begin () const {
    return _inventoryHolder.mapBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  InventoryMap_T::iterator InventoryMap_T::end () const {
    return _inventoryHolder.mapEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  InventoryMap_T::reverse_iterator InventoryMap_T::rbegin () const {
    return _inventoryHolder.mapRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  InventoryMap_T::reverse_iterator InventoryMap_T::rend () const {
    return _inventoryHolder.mapREnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  InventoryMap_T::
  iterator InventoryMap_T::find (const MapKey_T& iKey) const {
    return _inventoryHolder.find (iKey);
  }

}

