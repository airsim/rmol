// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <sstream>
// LATUS Common
#include <latus/com/bom/LegPeriodKey.hpp>


namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    LegPeriodKey_T::LegPeriodKey_T (const FlightKey_T& iFlightKey,
                    const AirportCode_T& iBoardPoint)
      : flightKey (iFlightKey), boardPoint (iBoardPoint) {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string LegPeriodKey_T::describe() const {
      std::ostringstream ostr;
      ostr << flightKey.describe() << "; " << boardPoint << "; ";
      return ostr.str();
    }
    

  }

}
