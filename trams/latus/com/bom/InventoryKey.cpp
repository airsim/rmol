// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <sstream>
// LATUS Common
#include <latus/com/bom/InventoryKey.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    InventoryKey_T::InventoryKey_T (const AirlineCode_T& iAirlineCode) 
      : airlineCode (iAirlineCode) {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string InventoryKey_T::describe() const {
      std::ostringstream ostr;
      const std::string& lShortKey = describeShort();
      ostr << lShortKey;
      return ostr.str();
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string InventoryKey_T::describeShort() const {
      std::ostringstream ostr;
      ostr << airlineCode << "; ";
      return ostr.str();
    }

  }
}
