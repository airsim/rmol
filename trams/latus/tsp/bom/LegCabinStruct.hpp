#ifndef __LATUS_TSP_BOM_LEGCABINSTRUCT_HPP
#define __LATUS_TSP_BOM_LEGCABINSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <vector>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/StructAbstract.hpp>

namespace LATUS {

  // Forward declarations
  namespace COM {
    class LegCabin;
  }

  namespace TSP {

    /** Utility Structure for the parsing of LegCabin details. */
    struct LegCabinStruct_T : public COM::StructAbstract {
      // Attributes
      COM::CabinCode_T _cabinCode;
      COM::CabinCapacity_T _capacity;

      /** Fill the LegCabin objects with the attributes of the
          LegCabinStruct. */
      void fill (COM::LegCabin&) const;
      
      /** Give a description of the structure (for display purposes). */
      const std::string describe() const;
    };

    /** List of LegCabin-Detail strucutres. */
    typedef std::vector<LegCabinStruct_T> LegCabinStructList_T;

  }
}
#endif // __LATUS_TSP_BOM_LEGCABINSTRUCT_HPP
