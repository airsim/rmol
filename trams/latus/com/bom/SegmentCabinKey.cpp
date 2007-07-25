// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <sstream>
// LATUS COM
#include <latus/com/bom/SegmentCabinKey.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    SegmentCabinKey_T::
    SegmentCabinKey_T (const SegmentDateKey_T& iSegmentDateKey,
                       const CabinCode_T& iCabinCode)
      : segmentDateKey (iSegmentDateKey), cabinCode (iCabinCode) {
    }
      
    // //////////////////////////////////////////////////////////////////////
    const std::string SegmentCabinKey_T::describe() const {
      std::ostringstream ostr;
      const std::string& lShortKey = describeShort();
      ostr << segmentDateKey.describe() << lShortKey;
      return ostr.str();
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string SegmentCabinKey_T::describeShort() const {
      std::ostringstream ostr;
      ostr << cabinCode << "; ";
      return ostr.str();
    }

  }
}
