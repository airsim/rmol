// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/NetworkDateKey.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    NetworkDateKey_T::NetworkDateKey_T (const DateTime_T& iReferenceDate)
      : referenceDate (iReferenceDate) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string NetworkDateKey_T::describe() const {
      std::ostringstream ostr;
      const std::string& lShortKey = describeShort();
      ostr << lShortKey;
      return ostr.str();
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string NetworkDateKey_T::describeShort() const {
      std::ostringstream ostr;
      ostr << referenceDate << "; ";
      return ostr.str();
    }

  }
}
