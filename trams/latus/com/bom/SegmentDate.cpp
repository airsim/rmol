// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/SegmentDate.hpp>
#include <latus/com/bom/SegmentCabin.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    SegmentDate::SegmentDate (const SegmentDateKey_T& iKey)
      : _key (iKey), _flightDate (NULL) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    SegmentDate::~SegmentDate () {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string SegmentDate::describeKey() const {
      return _key.describe();
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string SegmentDate::describeShortKey() const {
      return _key.describeShort();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void SegmentDate::display() const {

      // Store current formatting flags of std::cout
      std::ios::fmtflags oldFlags = std::cout.flags();

      std::cout << describeKey() << std::endl;

      for (SegmentCabinList_T::const_iterator itSegmentCabin =
             _segmentCabinList.begin();
           itSegmentCabin != _segmentCabinList.end(); itSegmentCabin++) {
        const SegmentCabin* lSegmentCabin_ptr = itSegmentCabin->second;
        assert (lSegmentCabin_ptr != NULL);

        lSegmentCabin_ptr->display ();
      }
      
      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }
    
    // //////////////////////////////////////////////////////////////////////
    SegmentCabin* SegmentDate::
    getSegmentCabin (const std::string& iSegmentCabinKey) const {
      SegmentCabin* resultSegmentCabin_ptr = NULL;
      
      SegmentCabinList_T::const_iterator itSegmentCabin =
        _segmentCabinList.find (iSegmentCabinKey);

      if (itSegmentCabin != _segmentCabinList.end()) {
        resultSegmentCabin_ptr = itSegmentCabin->second;
      }

      return resultSegmentCabin_ptr;
    }
    
  }
}
