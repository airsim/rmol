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
      // See also the describeShort() comment.
      std::ostringstream ostr;
      const std::string& lShortKey = describeShort();
      ostr << lShortKey;
      return ostr.str();
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string FlightDateKey_T::describeShort() const {
      // As the describeShort() method is used to make sure FlightDate objects
      // are not duplicated within an Inventory, the unique key elements are
      // the date of the flight plus the flight number (key element of the
      // FlightKey structure), not the date of the flight alone.
      std::ostringstream ostr;
      ostr << flightKey.describe() << flightDate << "; ";
      return ostr.str();
    }

  }
}
