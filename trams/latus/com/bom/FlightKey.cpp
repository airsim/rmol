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
    FlightKey_T::FlightKey_T (const InventoryKey_T& iInventoryKey,
                              const FlightNumber_T& iFlightNumber)
      : inventoryKey (iInventoryKey), flightNumber (iFlightNumber) {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string FlightKey_T::describe() const {
      std::ostringstream ostr;
      const std::string& lShortKey = describeShort();
      ostr << inventoryKey.describe() << lShortKey;
      return ostr.str();
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string FlightKey_T::describeShort() const {
      std::ostringstream ostr;
      ostr << flightNumber << "; ";
      return ostr.str();
    }

  }
}
