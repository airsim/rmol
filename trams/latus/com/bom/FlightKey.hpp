#ifndef __LATUS_COM_BOM_FLIGHTKEY_HPP
#define __LATUS_COM_BOM_FLIGHTKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>

namespace LATUS {

  namespace COM {

    /** Structure wrapping the key elements of a flight. */
    struct FlightKey_T {
      AirlineCode_T airlineCode;
      FlightNumber_T flightNumber;

      /** Constructor. */
      FlightKey_T (const AirlineCode_T& iAirlineCode,
                   const FlightNumber_T& iFlightNumber);

      /** Display of the key. */
      const std::string describe() const;
    };

  }
}
#endif // __LATUS_COM_BOM_FLIGHTKEY_HPP
