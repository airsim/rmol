// StdAir
#include <stdair/bom/BomRoot.hpp>
#include <stdair/factory/FacBomManager.hpp>

// /////////////////////// M A I N ///////////////////////////
int main() {  

  // Create the root of the BOM tree (i.e., a BomRoot object)
  stdair::BomRoot& lBomRoot =
    stdair::FacBom<stdair::BomRoot>::instance().create();

  // Display the Bomroot object
  std::cout << lBomRoot << std::endl;

  // Exit program:
  return 0;
}
