// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <sstream>
// LATUS Common
#include <latus/com/bom/FlightKey.hpp>


namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    FlightKey_T::FlightKey_T (const AirlineCode_T& iAirlineCode,
                            const FlightNumber_T& iFlightNumber)
      : airlineCode (iAirlineCode), flightNumber (iFlightNumber) {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string FlightKey_T::describe() const {
      std::ostringstream ostr;
      ostr << airlineCode << "; " << flightNumber << "; ";
      return ostr.str();
    }

  }
}
