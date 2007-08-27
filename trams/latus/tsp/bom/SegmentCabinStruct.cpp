// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream>
// LATUS Common
#include <latus/com/bom/SegmentCabin.hpp>
// LATUS TSP
#include <latus/tsp/bom/SegmentCabinStruct.hpp>

namespace LATUS {

  namespace TSP {

    // //////////////////////////////////////////////////////////////////////
    const std::string SegmentCabinStruct_T::describe() const {
      std::ostringstream ostr;
      ostr << "        " << _cabinCode << " " << _classes << ", ";
      return ostr.str();
    }

    // //////////////////////////////////////////////////////////////////////
    void SegmentCabinStruct_T::fill (COM::SegmentCabin& ioSegmentCabin) const {
      
    }

  }
}
