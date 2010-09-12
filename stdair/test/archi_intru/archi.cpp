// STL
#include <cassert>
//#include <iostream>
//#include <sstream>
//#include <string>
//#include <vector>
// Local
#include <test/archi_intru/TestIntrusive.hpp>
#include <test/archi_intru/BomRoot.hpp>
#include <test/archi_intru/FlightDate.hpp>

// /////////////////////////// M A I N /////////////////////////
/** Main.
    <br>Run with the following command:
    <tt>make check && ((./bom && echo "Success") || echo "Failure")</tt>
    <br>To run the program with Valgrind, type:
    <tt>libtool --mode=execute valgrind --leak-check=full ./bom</tt>
*/
int main (int argc, char* argv[]) {

  //
  TestIntrusive::test();
  
  return 0;
}
