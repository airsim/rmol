// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/AirportDateKey.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    AirportDateKey_T::AirportDateKey_T (const NetworkDateKey_T& iNetworkDateKey,
                                        const AirportCode_T& iOrigin)
      : networkDateKey (iNetworkDateKey) , origin (iOrigin) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string AirportDateKey_T::describe() const {
      std::ostringstream ostr;
      const std::string& lShortKey = describeShort();
      ostr << networkDateKey.describe() << lShortKey;
      return ostr.str();
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string AirportDateKey_T::describeShort() const {
      std::ostringstream ostr;
      ostr << origin << "; ";
      return ostr.str();
    }

  }
}
