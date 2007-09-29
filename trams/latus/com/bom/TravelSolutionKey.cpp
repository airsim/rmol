// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/TravelSolutionKey.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    TravelSolutionKey_T::
    TravelSolutionKey_T (const OutboundPathKey_T& iOutboundPathKey)
      : outboundPathKey (iOutboundPathKey) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string TravelSolutionKey_T::describe() const {
      std::ostringstream ostr;
      const std::string& lShortKey = describeShort();
      ostr << outboundPathKey.describe() << lShortKey;
      return ostr.str();
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string TravelSolutionKey_T::describeShort() const {
      std::ostringstream ostr;
      ostr << outboundPathKey.describeShort();
      return ostr.str();
    }

  }
}
