#ifndef __LATUS_TSP_BOM_SEGMENTSTRUCT_HPP
#define __LATUS_TSP_BOM_SEGMENTSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <vector>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/StructAbstract.hpp>
// LATUS Travel Service Provider (TSP)
#include <latus/tsp/bom/SegmentCabinStruct.hpp>

namespace LATUS {

  // Forward declarations
  namespace COM {
    class SegmentDate;
  }

  namespace TSP {

    /** Utility Structure for the parsing of Segment structures. */
    struct SegmentStruct_T : public COM::StructAbstract {
      // Attributes
      COM::AirportCode_T _boardPoint;
      COM::DateTime_T _boardDate;
      COM::Duration_T _boardTime;
      COM::AirportCode_T _offPoint;
      COM::DateTime_T _offDate;
      COM::Duration_T _offTime;
      COM::Duration_T _elapsed;
      SegmentCabinStructList_T _cabinList;

      /** Fill the SegmentDate objects with the attributes of the
          SegmentStruct. */
      void fill (COM::SegmentDate&) const;
      
      /** Give a description of the structure (for display purposes). */
      const std::string describe() const;
    };

    /** List of Segment strucutres. */
    typedef std::vector<SegmentStruct_T> SegmentStructList_T;

  }
}
#endif // __LATUS_TSP_BOM_SEGMENTSTRUCT_HPP
