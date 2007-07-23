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
    LegDateKey_T::LegDateKey_T (const FlightKey_T& iFlightKey,
                  const DateTime_T& iBoardDate,
                  const AirportCode_T& iBoardPoint)
      : flightKey (iFlightKey), boardDate (iBoardDate),
        boardPoint (iBoardPoint) {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string LegDateKey_T::describe() const {
      std::ostringstream ostr;
      ostr << flightKey.describe() << boardPoint << "; ";
      return ostr.str();
    }

  }
}
