// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <sstream>
// LATUS COM
#include <latus/com/bom/ClassKey.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    ClassKey_T::ClassKey_T (const SegmentCabinKey_T& iSegmentCabinKey,
                            const ClassCode_T& iClassCode)
      : segmentCabinKey (iSegmentCabinKey), classCode (iClassCode) {
    }
      
    // //////////////////////////////////////////////////////////////////////
    const std::string ClassKey_T::describe() const {
      std::ostringstream ostr;
      const std::string& lShortKey = describeShort();
      ostr << segmentCabinKey.describe() << lShortKey;
      return ostr.str();
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string ClassKey_T::describeShort() const {
      std::ostringstream ostr;
      ostr << classCode << "; ";
      return ostr.str();
    }

    

  }
}
