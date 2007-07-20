// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/LegDate.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    LegDate::LegDate (const LegDateKey_T& iKey)
      : _key (iKey) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    LegDate::~LegDate () {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string LegDate::describeKey() const {
      return _key.describe();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void LegDate::display() const {

      // Store current formatting flags of std::cout
      std::ios::fmtflags oldFlags = std::cout.flags();

      std::cout << describeKey() << std::endl;

      /*      
      for (LegCabinList_T::const_iterator itLegCabin =
             _cityPairList.begin();
           itLegCabin != _cityPairList.end(); itLegCabin++) {
        const LegCabin* lLegCabin_ptr = itLegCabin->second;
        assert (lLegCabin_ptr != NULL);

        lLegCabin_ptr->display ();
      }
      */
      
      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }
    
  }
}
