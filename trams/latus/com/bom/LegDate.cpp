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
    LegDate::LegDate (const LegDateKey_T& iKey)
      : _key (iKey), _flightDate (NULL) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    LegDate::~LegDate () {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string LegDate::describeKey() const {
      return _key.describe();
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string LegDate::describeShortKey() const {
      return _key.describeShort();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void LegDate::display() const {

      // Store current formatting flags of std::cout
      std::ios::fmtflags oldFlags = std::cout.flags();

      std::cout << describeKey() << std::endl;

      for (LegCabinList_T::const_iterator itLegCabin = _legCabinList.begin();
           itLegCabin != _legCabinList.end(); itLegCabin++) {
        const LegCabin* lLegCabin_ptr = itLegCabin->second;
        assert (lLegCabin_ptr != NULL);

        lLegCabin_ptr->display ();
      }
      
      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }
    
    // //////////////////////////////////////////////////////////////////////
    LegCabin* LegDate::getLegCabin (const std::string& iLegCabinKey) const {
      LegCabin* resultLegCabin_ptr = NULL;
      
      LegCabinList_T::const_iterator itLegCabin =
        _legCabinList.find (iLegCabinKey);

      if (itLegCabin != _legCabinList.end()) {
        resultLegCabin_ptr = itLegCabin->second;
      }

      return resultLegCabin_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    SegmentDate* LegDate::
    getSegmentDate (const std::string& iSegmentDateKey) const {
      SegmentDate* resultSegmentDate_ptr = NULL;
      
      SegmentDateList_T::const_iterator itSegmentDate =
        _segmentDateList.find (iSegmentDateKey);

      if (itSegmentDate != _segmentDateList.end()) {
        resultSegmentDate_ptr = itSegmentDate->second;
      }

      return resultSegmentDate_ptr;
    }

  }
}
