// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <sstream>
// LATUS Common
#include <latus/com/bom/FlightPeriodKey.hpp>


namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    FlightPeriodKey_T::FlightPeriodKey_T (const FlightKey_T& iFlightKey,
                                          const PeriodKey_T& iPeriodKey)
      : flightKey (iFlightKey), periodKey (iPeriodKey) {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string FlightPeriodKey_T::describe() const {
      std::ostringstream ostr;
      ostr << flightKey.describe() << "; " << periodKey.describe() << "; ";
      return ostr.str();
    }

  }
}
