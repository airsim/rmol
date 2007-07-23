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
    SegmentDateKey_T::SegmentDateKey_T (const FlightKey_T& iFlightKey,
                      const DateTime_T& iBoardDate,
                      const AirportPairKey_T& iAirportPairKey)
      : flightKey (iFlightKey), boardDate (iBoardDate),
        airportPairKey (iAirportPairKey) {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string SegmentDateKey_T::describe() const {
      std::ostringstream ostr;
      ostr << flightKey.describe() << "; "
           << airportPairKey.describe() << "; ";
      return ostr.str();
    }

  }
}
