#ifndef __LATUS_COM_BOM_SEGMENTPERIODKEY_HPP
#define __LATUS_COM_BOM_SEGMENTPERIODKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/bom/FlightKey.hpp>
#include <latus/com/bom/AirportPairKey.hpp>

namespace LATUS {

  namespace COM {

    /** Define the key elements of a segment-period. */
    struct SegmentPeriodKey_T {
      FlightKey_T flightKey;
      AirportPairKey_T airportPairKey;

      /** Constructor. */
      SegmentPeriodKey_T (const FlightKey_T& iFlightKey,
                          const AirportPairKey_T& iAirportPairKey);

      /** Display of the key. */
      const std::string describe() const;
    };
 
  }
}
#endif // __LATUS_COM_BOM_SEGMENTPERIODKEY_HPP
