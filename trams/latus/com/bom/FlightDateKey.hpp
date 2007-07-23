#ifndef __LATUS_COM_BOM_FLIGHTDATEKEY_HPP
#define __LATUS_COM_BOM_FLIGHTDATEKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/FlightKey.hpp>

namespace LATUS {

  namespace COM {

    /** Define the key elements of a flight-date. */
    struct FlightDateKey_T {
      FlightKey_T flightKey;
      DateTime_T flightDate;

      /** Constructor. */
      FlightDateKey_T (const FlightKey_T& iFlightKey,
                       const DateTime_T& iFlightDate);

      /** Display of the key. */
      const std::string describe() const;
    };

  }
}
#endif // __LATUS_COM_BOM_FLIGHTDATEKEY_HPP
