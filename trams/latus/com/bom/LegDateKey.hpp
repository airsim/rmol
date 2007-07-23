#ifndef __LATUS_COM_BOM_LEGDATEKEY_HPP
#define __LATUS_COM_BOM_LEGDATEKEY_HPP

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

    /** Define the key elements of a leg-date. */
    struct LegDateKey_T {
      FlightKey_T flightKey;
      DateTime_T boardDate;
      AirportCode_T boardPoint;

      /** Constructor. */
      LegDateKey_T (const FlightKey_T& iFlightKey,
                    const DateTime_T& iBoardDate,
                    const AirportCode_T& iBoardPoint);

      /** Display of the key. */
      const std::string describe() const;
    };
    
  }
}
#endif // __LATUS_COM_BOM_LEGDATEKEY_HPP
