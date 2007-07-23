#ifndef __LATUS_COM_BOM_LEGPERIODKEY_HPP
#define __LATUS_COM_BOM_LEGPERIODKEY_HPP

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

    /** Define the key elements of a leg-period. */
    struct LegPeriodKey_T {
      FlightKey_T flightKey;
      AirportCode_T boardPoint;

      /** Constructor. */
      LegPeriodKey_T (const FlightKey_T& iFlightKey,
                      const AirportCode_T& iBoardPoint);

      /** Display of the key. */
      const std::string describe() const;
    };
    
  }
}
#endif // __LATUS_COM_BOM_LEGPERIODKEY_HPP
