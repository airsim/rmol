/*!
 * \page tut_rootinvobject_cpp Tutorial for the BOM Root and Inventory Objects Creation
 * \code
 */
// STL
#include <cassert>
// StdAir
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/factory/FacBomManager.hpp>

// /////////////////////// M A I N ///////////////////////////
int main() {

  // Create the root of the Bom tree (i.e., a BomRoot object)
  stdair::BomRoot& lBomRoot =
    stdair::FacBom<stdair::BomRoot>::instance().create();

  // Create an Inventory for the Airline BA
  const stdair::InventoryKey lBAKey ("BA");
  stdair::Inventory& lBAInv =
    stdair::FacBom<stdair::Inventory>::instance().create (lBAKey);
  
  // Link the inventory for the Airline BA with the root of the Bom tree
  stdair::FacBomManager::instance().addToList (lBomRoot, lBAInv);

  // Display the Bomroot object
  std::cout << lBomRoot << std::endl;

  // Store the list of airline inventory
  const stdair::InventoryList_T& lInventoryList =
    stdair::BomManager::getList<stdair::Inventory> (lBomRoot);

  // Browse through the airline inventory list
  for (stdair::InventoryList_T::const_iterator itInv = lInventoryList.begin();
       itInv != lInventoryList.end(); ++itInv) {
    const stdair::Inventory* lInv_ptr = *itInv;
    assert (lInv_ptr != NULL);
    
    // Display the airline code
    std::cout << " Inventory: " << *lInv_ptr << std::endl;
  }
  
  // Exit program
  return 0;
}

/*!
 * \endcode
 */
