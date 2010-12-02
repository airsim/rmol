// STL
#include <cassert>
#include <iostream>
#include <string>
#include <list>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
// Local
#include <test/archi_static_cast/MP2BomRoot.hpp>
#include <test/archi_static_cast/MP2Inventory.hpp>
#include <test/archi_static_cast/MP2BomHolder.hpp>
#include <test/archi_static_cast/MP2BomManager.hpp>
#include <test/archi_static_cast/MP2FacBomManager.hpp>
#include <test/archi_static_cast/MP2FacBom.hpp>

// ////////// M A I N //////////////
using namespace myprovider;

int main (int argc, char* argv[]) {
  BomRoot& lBomRoot = FacBom<BomRoot>::instance().create();

  stdair::InventoryKey lBAKey ("BA");
  Inventory& lBAInv = FacBom<Inventory>::instance().create (lBAKey);

  FacBomManager::addToList (lBomRoot, lBAInv);

  std::list<Inventory*> lInventoryList =
    BomManager::getList<Inventory> (lBomRoot);

  for (std::list<Inventory*>::iterator itInv = lInventoryList.begin();
       itInv != lInventoryList.end(); ++itInv) {
    Inventory* lCurrentInv = *itInv;
    std::cout << lCurrentInv->describeKey() << std::endl;
  }
  
  return 0;
}
