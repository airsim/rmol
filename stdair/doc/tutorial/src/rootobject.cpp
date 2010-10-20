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

  // Display the Bomroot object code
  cout << lBomRoot.describeKey() << endl;

  // Exit program:
  return 0;
}
