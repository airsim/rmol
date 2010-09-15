// STL
#include <cassert>
#include <iostream>
#include <string>
#include <list>
// Local
#include <test/archi_static_cast/BomRoot.hpp>
#include <test/archi_static_cast/Inventory.hpp>
#include <test/archi_static_cast/BomHolder.hpp>
#include <test/archi_static_cast/BomManager.hpp>
#include <test/archi_static_cast/FacBomManager.hpp>
#include <test/archi_static_cast/FacBom.hpp>

// ////////// M A I N //////////////
using namespace myairline;

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
