// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomRootStructure.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/BomList.hpp>
#include <stdair/bom/BomMap.hpp>
#include <stdair/bom/Inventory.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  BomRoot::BomRoot (const BomKey_T& iKey, BomStructure_T& ioBomRootStructure)
    : BomRootContent (iKey), _bomRootStructure (ioBomRootStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  BomRoot::~BomRoot () {
  }

  // ////////////////////////////////////////////////////////////////////
  InventoryList_T BomRoot::getInventoryList () const {
    return _bomRootStructure.getChildrenHolder();
  }

  // ////////////////////////////////////////////////////////////////////
  InventoryMap_T BomRoot::getInventoryMap () const {
    return _bomRootStructure.getChildrenHolder();
  }

  Inventory* BomRoot::getInventory (const AirlineCode_T& iAirlineCode) const {
    Inventory* oInventory_ptr = NULL;

    InventoryMap_T lInventoryMap = getInventoryMap ();
    InventoryMap_T::iterator itInv = lInventoryMap.find (iAirlineCode);

    if (itInv != lInventoryMap.end()) {
      oInventory_ptr = itInv->second;
    }
    
    return oInventory_ptr;
  }
  
}
