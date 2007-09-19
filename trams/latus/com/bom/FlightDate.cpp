// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/Inventory.hpp>
#include <latus/com/bom/FlightDate.hpp>
#include <latus/com/bom/LegDate.hpp>
#include <latus/com/bom/SegmentDate.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    FlightDate::FlightDate (const FlightDateKey_T& iKey)
      : _key (iKey), _inventory (NULL) {
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

      for (LegDateOrderedList_T::const_iterator itLegDate =
             _legDateOrderedList.begin();
           itLegDate != _legDateOrderedList.end(); ++itLegDate) {
        const LegDate* lLegDate_ptr = *itLegDate;
        assert (lLegDate_ptr != NULL);

        lLegDate_ptr->display ();
      }
      
      for (SegmentDateOrderedList_T::const_iterator itSegmentDate =
             _segmentDateOrderedList.begin();
           itSegmentDate != _segmentDateOrderedList.end(); ++itSegmentDate) {
        const SegmentDate* lSegmentDate_ptr = *itSegmentDate;
        assert (lSegmentDate_ptr != NULL);

        lSegmentDate_ptr->display ();
      }
      
      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }

    // //////////////////////////////////////////////////////////////////////
    void FlightDate::updateBookingsAndSeatCounters() const {

      for (LegDateOrderedList_T::const_iterator itLegDate =
             _legDateOrderedList.begin();
           itLegDate != _legDateOrderedList.end(); ++itLegDate) {
        const LegDate* lLegDate_ptr = *itLegDate;
        assert (lLegDate_ptr != NULL);

        lLegDate_ptr->updateBookingsAndSeatCounters ();
      }
      
      for (SegmentDateOrderedList_T::const_iterator itSegmentDate =
             _segmentDateOrderedList.begin();
           itSegmentDate != _segmentDateOrderedList.end(); ++itSegmentDate) {
        const SegmentDate* lSegmentDate_ptr = *itSegmentDate;
        assert (lSegmentDate_ptr != NULL);

        lSegmentDate_ptr->updateBookingAndSeatCounters();
      }
      
    }

     // //////////////////////////////////////////////////////////////////////
    void FlightDate::updateCommitedSpaces() const {
      
      for (SegmentDateOrderedList_T::const_iterator itSegmentDate =
             _segmentDateOrderedList.begin();
           itSegmentDate != _segmentDateOrderedList.end(); ++itSegmentDate) {
        const SegmentDate* lSegmentDate_ptr = *itSegmentDate;
        assert (lSegmentDate_ptr != NULL);

        lSegmentDate_ptr->updateCommitedSpaces();
      }
      
      for (LegDateOrderedList_T::const_iterator itLegDate =
             _legDateOrderedList.begin();
           itLegDate != _legDateOrderedList.end(); ++itLegDate) {
        const LegDate* lLegDate_ptr = *itLegDate;
        assert (lLegDate_ptr != NULL);

        lLegDate_ptr->updateCommitedSpaces ();
      }
      
    }

    // //////////////////////////////////////////////////////////////////////
    void FlightDate::updateAvailabilityPools() const {

      for (LegDateOrderedList_T::const_iterator itLegDate =
             _legDateOrderedList.begin();
           itLegDate != _legDateOrderedList.end(); ++itLegDate) {
        const LegDate* lLegDate_ptr = *itLegDate;
        assert (lLegDate_ptr != NULL);

        lLegDate_ptr->updateAvailabilityPools ();
      }
      
      for (SegmentDateOrderedList_T::const_iterator itSegmentDate =
             _segmentDateOrderedList.begin();
           itSegmentDate != _segmentDateOrderedList.end(); ++itSegmentDate) {
        const SegmentDate* lSegmentDate_ptr = *itSegmentDate;
        assert (lSegmentDate_ptr != NULL);

        lSegmentDate_ptr->updateAvailabilityPools();
      }
      
    }

    // //////////////////////////////////////////////////////////////////////
    void FlightDate::updateAllAvailabilities() const {

      for (LegDateOrderedList_T::const_iterator itLegDate =
             _legDateOrderedList.begin();
           itLegDate != _legDateOrderedList.end(); ++itLegDate) {
        const LegDate* lLegDate_ptr = *itLegDate;
        assert (lLegDate_ptr != NULL);

        lLegDate_ptr->updateAllAvailabilities ();
      }
      
      for (SegmentDateOrderedList_T::const_iterator itSegmentDate =
             _segmentDateOrderedList.begin();
           itSegmentDate != _segmentDateOrderedList.end(); ++itSegmentDate) {
        const SegmentDate* lSegmentDate_ptr = *itSegmentDate;
        assert (lSegmentDate_ptr != NULL);

        lSegmentDate_ptr->updateAllAvailabilities();
      }
      
    }

    // //////////////////////////////////////////////////////////////////////
    const AirlineCode_T& FlightDate::getAirlineCode() const {
      assert (_inventory != NULL);
      return _inventory->getAirlineCode();
    }
    
    // //////////////////////////////////////////////////////////////////////
    LegDate* FlightDate::
    getLegDateInternal (const std::string& iLegDateKey) const {
      LegDate* resultLegDate_ptr = NULL;
      
      LegDateList_T::const_iterator itLegDate =
        _legDateList.find (iLegDateKey);

      if (itLegDate != _legDateList.end()) {
        resultLegDate_ptr = itLegDate->second;
      }

      return resultLegDate_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    LegDate* FlightDate::getLegDate (const AirportCode_T& iBoardPoint) const {
      const FlightDateKey_T& lFlightDateKey = getPrimaryKey();
      const LegDateKey_T lLegDateKey (lFlightDateKey, iBoardPoint);
      const std::string& lLegDateKeyString = lLegDateKey.describeShort();
      return getLegDateInternal (lLegDateKeyString);
    }
    
    // //////////////////////////////////////////////////////////////////////
    SegmentDate* FlightDate::
    getSegmentDateInternal (const std::string& iSegmentDateKey) const {
      SegmentDate* resultSegmentDate_ptr = NULL;
      
      SegmentDateList_T::const_iterator itSegmentDate =
        _segmentDateList.find (iSegmentDateKey);

      if (itSegmentDate != _segmentDateList.end()) {
        resultSegmentDate_ptr = itSegmentDate->second;
      }

      return resultSegmentDate_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    SegmentDate* FlightDate::
    getSegmentDate (const AirportCode_T& iBoardPoint,
                    const AirportCode_T& iOffPoint) const {
      const FlightDateKey_T& lFlightDateKey = getPrimaryKey();
      const AirportPairKey_T lAirportPairKey (iBoardPoint, iOffPoint);
      const SegmentDateKey_T lSegmentDateKey (lFlightDateKey, lAirportPairKey);
      const std::string& lSegmentDateKeyString =
        lSegmentDateKey.describeShort();
      return getSegmentDateInternal (lSegmentDateKeyString);
    }
    
  }
}
