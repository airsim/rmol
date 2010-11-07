/*!
 * \page tut_invobject_cpp Tutorial for the BOM Inventory Object Creation
 * \code
 */
// StdAir
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/factory/FacBomManager.hpp>

// /////////////////////// M A I N ///////////////////////////
int main() {  

  // Create an inventory key (i.e., an airline code)
  const stdair::InventoryKey lBAKey ("BA");

  // Create an inventory object whose airline code is BA
  stdair::Inventory& lBAInv =
    stdair::FacBom<stdair::Inventory>::instance().create (lBAKey);

  // Display the inventory object (including its key, i.e., the airline code)
  std::cout << " Inventory: " << lBAInv << std::endl;

  // Exit program
  return 0;
}

/*!
 * \endcode
 */
