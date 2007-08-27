// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream>
// LATUS Common
#include <latus/com/bom/LegCabin.hpp>
// LATUS TSP
#include <latus/tsp/bom/LegCabinStruct.hpp>

namespace LATUS {

  namespace TSP {

    // //////////////////////////////////////////////////////////////////////
    const std::string LegCabinStruct_T::describe() const {
      std::ostringstream ostr;
      ostr << "        " << _cabinCode << " " << _capacity << ", ";
      return ostr.str();
    }

    // //////////////////////////////////////////////////////////////////////
    void LegCabinStruct_T::fill (COM::LegCabin& ioLegCabin) const {
      // Set the Capacity
      ioLegCabin.setCapacity (_capacity);
    }

  }
}
