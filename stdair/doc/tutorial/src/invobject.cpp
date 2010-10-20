// StdAir
#include <stdair/factory/FacBomManager.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>

// These lines are needed for use of cout and endl
using std::cout;
using std::endl;

int main()
{  
  // Create an inventory Key (i,e an airline code)
  const stdair::InventoryKey lBAKey ("BA");

  // Create an inventory object whose airline code is BA
  stdair::Inventory& lBAInv =
    stdair::FacBom<stdair::Inventory>::instance().create (lBAKey);

  // Display the airline code
  cout << " Inventory: " << lBAInv.describeKey() << endl;

  // Exit program:
  return 0;
}
