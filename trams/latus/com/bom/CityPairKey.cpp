// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/CityPairKey.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    CityPairKey_T::CityPairKey_T (const AirportPairKey_T& iAirportPairKey)
      : airportPairKey (iAirportPairKey) {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string CityPairKey_T::describe() const {
      std::ostringstream ostr;
      const std::string& lShortKey = describeShort();
      ostr << lShortKey;
      return ostr.str();
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string CityPairKey_T::describeShort() const {
      std::ostringstream ostr;
      ostr << airportPairKey.describe();
      return ostr.str();
    }

    // //////////////////////////////////////////////////////////////////////
    bool CityPairKey_T::
    operator== (const CityPairKey_T& iCityPairKey) const {
      return (airportPairKey == iCityPairKey.airportPairKey);
    }

  }
}
