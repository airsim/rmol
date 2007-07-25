// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/LegDate.hpp>
#include <latus/com/bom/LegCabin.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    LegCabin::LegCabin (const LegCabinKey_T& iKey)
      : _key (iKey), _legDate (NULL) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    LegCabin::~LegCabin () {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string LegCabin::describeKey() const {
      return _key.describe();
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string LegCabin::describeShortKey() const {
      return _key.describeShort();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void LegCabin::display() const {

      // Store current formatting flags of std::cout
      std::ios::fmtflags oldFlags = std::cout.flags();

      std::cout << describeKey() << std::endl;

      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }
    
  }
}
