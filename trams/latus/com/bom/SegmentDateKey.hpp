#ifndef __LATUS_COM_BOM_SEGMENTDATEKEY_HPP
#define __LATUS_COM_BOM_SEGMENTDATEKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/KeyAbstract.hpp>
#include <latus/com/bom/FlightDateKey.hpp>
#include <latus/com/bom/AirportPairKey.hpp>

namespace LATUS {

  namespace COM {

    /** Define the key elements of a segment-date. */
    struct SegmentDateKey_T : public KeyAbstract {
      FlightDateKey_T flightDateKey;
      AirportPairKey_T airportPairKey;

      /** Constructor. */
      SegmentDateKey_T (const FlightDateKey_T& iFlightDateKey,
                        const AirportPairKey_T& iAirportPairKey);

      /** Display of the key. */
      const std::string describe() const;

      /** Display of the short key. */
      const std::string describeShort() const;

      /** operator== */
      bool operator==(const SegmentDateKey_T&) const;
    };
    
  }
}
#endif // __LATUS_COM_BOM_SEGMENTDATEKEY_HPP
