// StdAir
#include <stdair/factory/FacBomManager.hpp>
#include <stdair/bom/BomRoot.hpp>

// These lines are needed for use of cout and endl
using std::cout;
using std::endl;

int main()
{
  // Create the root of the Bom tree (i.e., a BomRoot object)
  stdair::BomRoot& lBomRoot =
    stdair::FacBom<stdair::BomRoot>::instance().create();

  // Create an Inventory for the Airline BA
  const stdair::InventoryKey lBAKey ("BA");
  stdair::Inventory& lBAInv =
    stdair::FacBom<stdair::Inventory>::instance().create (lBAKey);
  
  // Link the inventory for the Airline BA with the root of the Bom tree
  stdair::FacBomManager::instance().addToList (lBomRoot, lBAInv);

  // Display the Bomroot object code
  cout << lBomRoot.describeKey() << endl;

  // Store the list of airline inventory
  const stdair::InventoryList_T& lInventoryList =
    stdair::BomManager::getList<stdair::Inventory> (lBomRoot);
  // Skim through the airline inventory list
  for (stdair::InventoryList_T::const_iterator itInv = lInventoryList.begin();
           itInv != lInventoryList.end(); ++itInv) {
        const stdair::Inventory* lInv_ptr = *itInv;
        // Display the airline code
        cout << " Inventory: " << lInv_ptr->describeKey() << endl;
  }
  
  // Exit program:
  return 0;
}
