// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <sstream>
// LATUS COM
#include <latus/com/bom/LegCabinKey.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    LegCabinKey_T::LegCabinKey_T (const LegDateKey_T& iLegDateKey,
                   const CabinCode_T& iCabinCode)
      : legDateKey (iLegDateKey), cabinCode (iCabinCode) {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string LegCabinKey_T::describe() const {
      std::ostringstream ostr;
      const std::string& lShortKey = describeShort();
      ostr << legDateKey.describe() << lShortKey;
      return ostr.str();
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string LegCabinKey_T::describeShort() const {
      std::ostringstream ostr;
      ostr << cabinCode << "; ";
      return ostr.str();
    }

  }
}
