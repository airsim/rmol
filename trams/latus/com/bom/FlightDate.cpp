// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/FlightDate.hpp>
#include <latus/com/bom/LegDate.hpp>
#include <latus/com/bom/SegmentDate.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    FlightDate::FlightDate (const FlightDateKey_T& iKey)
      : _key (iKey) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    FlightDate::~FlightDate () {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string FlightDate::describeKey() const {
      return _key.describe();
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string FlightDate::describeShortKey() const {
      return _key.describeShort();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void FlightDate::display() const {

      // Store current formatting flags of std::cout
      std::ios::fmtflags oldFlags = std::cout.flags();

      std::cout << describeKey() << std::endl;

      for (LegDateList_T::const_iterator itLegDate = _legDateList.begin();
           itLegDate != _legDateList.end(); itLegDate++) {
        const LegDate* lLegDate_ptr = itLegDate->second;
        assert (lLegDate_ptr != NULL);

        lLegDate_ptr->display ();
      }
      
      for (SegmentDateList_T::const_iterator itSegmentDate =
             _segmentDateList.begin();
           itSegmentDate != _segmentDateList.end(); itSegmentDate++) {
        const SegmentDate* lSegmentDate_ptr = itSegmentDate->second;
        assert (lSegmentDate_ptr != NULL);

        lSegmentDate_ptr->display ();
      }
      
      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }
    
    // //////////////////////////////////////////////////////////////////////
    LegDate* FlightDate::getLegDate (const std::string& iLegDateKey) const {
      LegDate* resultLegDate_ptr = NULL;
      
      LegDateList_T::const_iterator itLegDate =
        _legDateList.find (iLegDateKey);

      if (itLegDate != _legDateList.end()) {
        resultLegDate_ptr = itLegDate->second;
      }

      return resultLegDate_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    SegmentDate* FlightDate::
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
