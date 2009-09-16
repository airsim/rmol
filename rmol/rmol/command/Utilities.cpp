
// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
//STL
#include <algorithm>
#include <assert.h>
// RMOL
#include <rmol/command/Utilities.hpp>

namespace RMOL {

  // /////////////////////////////////////////////////////////////////////
  const double Utilities::minimumElementOfAVector (std::vector<double> iVector) {

    assert(!iVector.empty());
    std::vector<double>::iterator pos = min_element (iVector.begin(), 
                                                     iVector.end());
    return *pos;

  }

}
