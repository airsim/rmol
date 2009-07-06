// STL
#include <iostream>
// Book on Boost MPL
#include "contrib/binary.hpp"

// ///////////// M A I N //////////////
int main (int argc, char* argv[]) {

  const long l42 = binary<101010>::value;
  std::cout << "The 101010 binary number is equal to: " << l42 << std::endl;
  
  return 0;
}
