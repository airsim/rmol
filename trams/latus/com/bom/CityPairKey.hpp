#ifndef __LATUS_COM_BOM_CITYPAIRKEY_HPP
#define __LATUS_COM_BOM_CITYPAIRKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/KeyAbstract.hpp>
#include <latus/com/bom/AirportPairKey.hpp>

namespace LATUS {

  namespace COM {

    /** Define the key elements of a city pair. */
    struct CityPairKey_T : public KeyAbstract {
      AirportPairKey_T airportPairKey;

      /** Constructor. */
      CityPairKey_T (const AirportPairKey_T& iAirportPairKey);

      /** Display of the key. */
      const std::string describe() const;

      /** Display of the short key. */
      const std::string describeShort() const;

      /** operator== */
      bool operator==(const CityPairKey_T&) const;
    };
    
  }
}
#endif // __LATUS_COM_BOM_CITYPAIRKEY_HPP
