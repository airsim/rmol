// STL
#include <cassert>
//#include <iostream>
//#include <sstream>
//#include <string>
//#include <vector>
// Local
#include <test/archi_intru/TestManager.hpp>

// /////////////////////////// M A I N /////////////////////////
/** Main.
    <br>Run with the following command:
    <tt>make check && ((./bom && echo "Success") || echo "Failure")</tt>
    <br>To run the program with Valgrind, type:
    <tt>libtool --mode=execute valgrind --leak-check=full ./bom</tt>
*/
int main (int argc, char* argv[]) {

  //
  TestManager lTestManager;
  
  // Initialise the internal (STL) vector, (Boost.Intrusive) list and set
  lTestManager.init();
  
  // Now test lists
  lTestManager.testIntrusiveList();
  
  // Now, test iterator_to()
  lTestManager.testIntrusiveIteratorTo();
  
  // Now, test sets
  lTestManager.testIntrusiveSets();
  
  return 0;
}
