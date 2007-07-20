// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/FlightPeriod.hpp>
#include <latus/com/bom/LegPeriod.hpp>
#include <latus/com/bom/SegmentPeriod.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    FlightPeriod::FlightPeriod (const FlightPeriodKey_T& iKey)
      : _key (iKey) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    FlightPeriod::~FlightPeriod () {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string FlightPeriod::describeKey() const {
      return _key.describe();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void FlightPeriod::display() const {

      // Store current formatting flags of std::cout
      std::ios::fmtflags oldFlags = std::cout.flags();

      std::cout << describeKey() << std::endl;

      for (LegPeriodList_T::const_iterator itLegPeriod = _legPeriodList.begin();
           itLegPeriod != _legPeriodList.end(); itLegPeriod++) {
        const LegPeriod* lLegPeriod_ptr = itLegPeriod->second;
        assert (lLegPeriod_ptr != NULL);

        lLegPeriod_ptr->display ();
      }
      
      for (SegmentPeriodList_T::const_iterator itSegmentPeriod =
             _segmentPeriodList.begin();
           itSegmentPeriod != _segmentPeriodList.end(); itSegmentPeriod++) {
        const SegmentPeriod* lSegmentPeriod_ptr = itSegmentPeriod->second;
        assert (lSegmentPeriod_ptr != NULL);

        lSegmentPeriod_ptr->display ();
      }
      
      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }
    
    // //////////////////////////////////////////////////////////////////////
    LegPeriod* FlightPeriod::
    getLegPeriod (const std::string& iLegPeriodKey) const {
      LegPeriod* resultLegPeriod_ptr = NULL;
      
      LegPeriodList_T::const_iterator itLegPeriod =
        _legPeriodList.find (iLegPeriodKey);

      if (itLegPeriod != _legPeriodList.end()) {
        resultLegPeriod_ptr = itLegPeriod->second;
      }

      return resultLegPeriod_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    SegmentPeriod* FlightPeriod::
    getSegmentPeriod (const std::string& iSegmentPeriodKey) const {
      SegmentPeriod* resultSegmentPeriod_ptr = NULL;
      
      SegmentPeriodList_T::const_iterator itSegmentPeriod =
        _segmentPeriodList.find (iSegmentPeriodKey);

      if (itSegmentPeriod != _segmentPeriodList.end()) {
        resultSegmentPeriod_ptr = itSegmentPeriod->second;
      }

      return resultSegmentPeriod_ptr;
    }
    
  }
}
