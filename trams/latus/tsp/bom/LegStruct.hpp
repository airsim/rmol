#ifndef __LATUS_TSP_BOM_LEGSTRUCT_HPP
#define __LATUS_TSP_BOM_LEGSTRUCT_HPP

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
#include <latus/tsp/bom/LegCabinStruct.hpp>

namespace LATUS {

  // Forward declarations
  namespace COM {
    class LegDate;
  }

  namespace TSP {

    /** Utility Structure for the parsing of Leg structures. */
    struct LegStruct_T : public COM::StructAbstract {
      // Attributes
      COM::AirportCode_T _boardPoint;
      COM::Duration_T _boardTime;
      COM::AirportCode_T _offPoint;
      COM::DateOffSet_T _dateOffSet;
      COM::Duration_T _offTime;
      COM::Duration_T _elapsed;
      LegCabinStructList_T _cabinList;

      /** Fill the LegDate objects with the attributes of the LegStruct. */
      void fill (const COM::DateTime_T& iRefDate, COM::LegDate&) const;
      
      /** Give a description of the structure (for display purposes). */
      const std::string describe() const;

      /** Default Constructor. */
      LegStruct_T();
    };

    /** List of Leg strucutres. */
    typedef std::vector<LegStruct_T> LegStructList_T;

  }
}
#endif // __LATUS_TSP_BOM_LEGSTRUCT_HPP
