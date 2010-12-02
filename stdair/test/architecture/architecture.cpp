/*!
 * \page test_architecture_cpp Command-Line Utility to Demonstrate How To Extend StdAir BOM
 * \code
 */
// STL
#include <cassert>
#include <iostream>
#include <string>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/factory/FacBom.hpp>
#include <stdair/factory/FacBomManager.hpp>
// Local
//#include <test/architecture/MPBomRoot.hpp>
#include <test/architecture/MPInventory.hpp>

// ////////// M A I N //////////////
int main (int argc, char* argv[]) {

  // Step 0.0: initialisation
  // Create the root of the Bom tree (i.e., a BomRoot object)
  stdair::BomRoot& lBomRoot =
    stdair::FacBom<stdair::BomRoot>::instance().create();
        
  // Step 0.1: Inventory level
  // Create an Inventory (BA)
  const stdair::AirlineCode_T lAirlineCode ("BA");
  const stdair::InventoryKey lBAKey (lAirlineCode);
  myprovider::Inventory& lBAInv =
    stdair::FacBom<myprovider::Inventory>::instance().create (lBAKey);
  stdair::FacBomManager::instance().addToList (lBomRoot, lBAInv);

  // Create an Inventory for AF
  const stdair::InventoryKey lAFKey ("AF");
  myprovider::Inventory& lAFInv =
    stdair::FacBom<myprovider::Inventory>::instance().create (lAFKey);
  stdair::FacBomManager::instance().addToList (lBomRoot, lAFInv);

  // Browse the inventories
  const myprovider::InventoryList_T& lInventoryList =
      stdair::BomManager::getList<myprovider::Inventory> (lBomRoot);
  for (myprovider::InventoryList_T::const_iterator itInv =
         lInventoryList.begin(); itInv != lInventoryList.end(); ++itInv) {
    const myprovider::Inventory* lInv_ptr = *itInv;
    assert (lInv_ptr != NULL);
    
    std::cout << "Inventory: " << lInv_ptr->toString() << std::endl;
  }
  
  return 0;
}

/*!
 * \endcode
 */
