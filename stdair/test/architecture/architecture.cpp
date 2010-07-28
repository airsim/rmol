// STL
#include <cassert>
#include <iostream>
#include <string>
#include <stdair/factory/FacBomContent.hpp>
#include <stdair/bom/BomSource.hpp>
#include "BomRoot.hpp"
#include "Inventory.hpp"
#include "Structure.hpp"
#include "StructureTypes.hpp"

// ////////// M A I N //////////////
int main (int argc, char* argv[]) {
  // Step 0.0: initialisation
  // Create the root of the Bom tree (i.e., a BomRoot object)
  BomRoot& lBomRoot =
    stdair::FacBomContent::instance().create<BomRoot>();
        
  // Step 0.1: Inventory level
  // Create an Inventory (BA)
  const stdair::AirlineCode_T lAirlineCode ("BA");
  stdair::InventoryKey_T lInventoryKey (lAirlineCode);
  
  Inventory& lInventory =
    stdair::FacBomContent::instance().create<Inventory>(lInventoryKey);
  stdair::FacBomContent::linkWithParent (lInventory, lBomRoot);

  const InventoryList_T& lInventoryList =
    lBomRoot._structure.getChildrenHolder<Inventory>();
  for (InventoryList_T::iterator itInv = lInventoryList.begin();
       itInv != lInventoryList.end(); ++itInv) {
    const Inventory& lCurrentInventory = *itInv;
    std::cout << "Inventory: " << lCurrentInventory.toString() << std::endl;
  }
  
  return 0;
}
