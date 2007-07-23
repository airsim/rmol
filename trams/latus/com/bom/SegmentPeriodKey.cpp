// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <sstream>
// LATUS COM
#include <latus/com/bom/SegmentPeriodKey.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    SegmentPeriodKey_T::SegmentPeriodKey_T (const FlightKey_T& iFlightKey,
                        const AirportPairKey_T& iAirportPairKey)
      : flightKey (iFlightKey), airportPairKey (iAirportPairKey) {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string SegmentPeriodKey_T::describe() const {
      std::ostringstream ostr;
      ostr << flightKey.describe() << "; "
           << airportPairKey.describe() << "; ";
      return ostr.str();
    }

  }
}
