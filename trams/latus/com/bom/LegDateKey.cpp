// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <sstream>
// LATUS COM
#include <latus/com/bom/LegDateKey.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    LegDateKey_T::LegDateKey_T (const FlightDateKey_T& iFlightDateKey,
                                const AirportCode_T& iBoardPoint)
      : flightDateKey (iFlightDateKey), boardPoint (iBoardPoint) {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string LegDateKey_T::describe() const {
      std::ostringstream ostr;
      const std::string& lShortKey = describeShort();
      ostr << flightDateKey.describe() << lShortKey;
      return ostr.str();
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string LegDateKey_T::describeShort() const {
      std::ostringstream ostr;
      ostr << boardPoint << "; ";
      return ostr.str();
    }

  }
}
