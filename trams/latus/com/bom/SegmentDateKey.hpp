#ifndef __LATUS_COM_BOM_SEGMENTDATEKEY_HPP
#define __LATUS_COM_BOM_SEGMENTDATEKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/FlightKey.hpp>
#include <latus/com/bom/AirportPairKey.hpp>

namespace LATUS {

  namespace COM {

    /** Define the key elements of a segment-date. */
    struct SegmentDateKey_T {
      FlightKey_T flightKey;
      DateTime_T boardDate;
      AirportPairKey_T airportPairKey;

      /** Constructor. */
      SegmentDateKey_T (const FlightKey_T& iFlightKey,
                        const DateTime_T& iBoardDate,
                        const AirportPairKey_T& iAirportPairKey);

      /** Display of the key. */
      const std::string describe() const;
    };
    
  }
}
#endif // __LATUS_COM_BOM_SEGMENTDATEKEY_HPP
