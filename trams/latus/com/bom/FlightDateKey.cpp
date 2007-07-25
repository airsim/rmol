// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <sstream>
// LATUS COM
#include <latus/com/bom/FlightDateKey.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    FlightDateKey_T::FlightDateKey_T (const FlightKey_T& iFlightKey,
                     const DateTime_T& iFlightDate)
      : flightKey (iFlightKey), flightDate (iFlightDate) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string FlightDateKey_T::describe() const {
      return describeShort();
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string FlightDateKey_T::describeShort() const {
      std::ostringstream ostr;
      ostr << flightKey.describe() << "; " << flightDate << "; ";
      return ostr.str();
    }

  }
}
