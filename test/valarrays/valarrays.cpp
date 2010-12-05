// //////////////////////////////////////////////////////////////
// Test case for the STL valarray structure.
// It is not very robust and well supported (see p547 of the
// N. Josuttis' book: The C++ Standard Library - ISBN: 0201379260).
// Alternatives may be:
// * Boost.Array class (by the same N. Josuttis:
//     http://www.boost.org/doc/libs/1_37_0/doc/html/boost/array.html)
//     which however does not provide the + operator we are wanting here.
// * Blitz Numerics Arrays (http://www.oonumerics.org/blitz/)
// //////////////////////////////////////////////////////////////
// STL
#include <iostream>
#include <valarray>
#include <string>
// Blitz
// #include <blitz/array.h>

// ///////////////////////////////////////////////////////////////
typedef std::valarray<int> List_T;

// ///////////////////////////////////////////////////////////////
void display (const std::string& iMessage, const List_T& iList) {

  std::cout << iMessage << std::endl;
  
  
  for (unsigned int idx = 0; idx != iList.size(); ++idx) {
    std::cout << "[" << idx << "]: " << iList[idx] << std::endl;
  }
}


// /////////////////////// M A I N //////////////////////////////
int main (int argc, char* agrv[]) {

  // Initialise two vectors of integers
  const unsigned int lSize = 10;
  List_T v1(lSize), v2(lSize);
  for (unsigned int i = 0; i != lSize; ++i) {
    v1[i] = i;
    v2[i] = lSize - i;
  }

  //
  display ("v1", v1);
  display ("v2", v2);

  // Create a third vector being the sum of the two above
  List_T v3 = v1 + v2;

  //
  display ("v3", v3);

  // //// Blitz ////
  // blitz::Array<int,1> bv1(lSize), bv2(lSize);

  return 0;
}
