#ifndef __LATUS_TSP_BOM_SEGMENTCABINSTRUCT_HPP
#define __LATUS_TSP_BOM_SEGMENTCABINSTRUCT_HPP

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
    class SegmentCabin;
  }

  namespace TSP {

    /** Utility Structure for the parsing of SegmentCabin details. */
    struct SegmentCabinStruct_T : public COM::StructAbstract {
      // Attributes
      COM::CabinCode_T _cabinCode;
      COM::ClassList_String_T _classes;

      /** Fill the SegmentCabin objects with the attributes of the
          SegmentCabinStruct. */
      void fill (COM::SegmentCabin&) const;
      
      /** Give a description of the structure (for display purposes). */
      const std::string describe() const;
    };

    /** List of SegmentCabin-Detail strucutres. */
    typedef std::vector<SegmentCabinStruct_T> SegmentCabinStructList_T;

  }
}
#endif // __LATUS_TSP_BOM_SEGMENTCABINSTRUCT_HPP
