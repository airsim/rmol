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
      ostr << legDateKey.describe() << "; " << cabinCode << "; ";
      return ostr.str();
    }

  }
}
