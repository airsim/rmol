#ifndef __LATUS_COM_BOM_LEGDATEKEY_HPP
#define __LATUS_COM_BOM_LEGDATEKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/KeyAbstract.hpp>
#include <latus/com/bom/FlightDateKey.hpp>

namespace LATUS {

  namespace COM {

    /** Define the key elements of a leg-date. */
    struct LegDateKey_T : public KeyAbstract {
      FlightDateKey_T flightDateKey;
      AirportCode_T boardPoint;

      /** Constructor. */
      LegDateKey_T (const FlightDateKey_T& iFlightDateKey,
                    const AirportCode_T& iBoardPoint);

      /** Display of the key. */
      const std::string describe() const;

      /** Display of the short key. */
      const std::string describeShort() const;
    };
    
  }
}
#endif // __LATUS_COM_BOM_LEGDATEKEY_HPP
