// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/SegmentDateKey.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    SegmentDateKey_T::SegmentDateKey_T (const FlightDateKey_T& iFlightDateKey,
                      const AirportPairKey_T& iAirportPairKey)
      : flightDateKey (iFlightDateKey), airportPairKey (iAirportPairKey) {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string SegmentDateKey_T::describe() const {
      std::ostringstream ostr;
      const std::string& lShortKey = describeShort();
      ostr << flightDateKey.describe() << lShortKey;
      return ostr.str();
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string SegmentDateKey_T::describeShort() const {
      std::ostringstream ostr;
      ostr << airportPairKey.describe();
      return ostr.str();
    }

    // //////////////////////////////////////////////////////////////////////
    bool SegmentDateKey_T::
    operator== (const SegmentDateKey_T& iSegmentDateKey) const {
      // TODO: complete the implementation by comparing the FlightKey also.
      return (airportPairKey == iSegmentDateKey.airportPairKey);
    }

  }
}
