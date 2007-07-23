#ifndef __LATUS_COM_BOM_AIRPORTPAIRKEY_HPP
#define __LATUS_COM_BOM_AIRPORTPAIRKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>

namespace LATUS {

  namespace COM {

    /** Define the key elements of an airport pair. */
    struct AirportPairKey_T {
      AirportCode_T boardPoint;
      AirportCode_T offPoint;

      /** Constructor. */
      AirportPairKey_T (const AirportCode_T& iBoardPoint,
                        const AirportCode_T& iOffPoint);

      /** Display of the airport pair. */
      const std::string describe() const;
    };

  }
}
#endif // __LATUS_COM_BOM_AIRPORTPAIRKEY_HPP
