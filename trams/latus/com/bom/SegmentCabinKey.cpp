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
      ostr << segmentDateKey.describe() << "; " << cabinCode << "; ";
      return ostr.str();
    }

  }
}
