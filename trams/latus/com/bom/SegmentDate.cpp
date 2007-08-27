// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/FlightDate.hpp>
#include <latus/com/bom/SegmentDate.hpp>
#include <latus/com/bom/SegmentCabin.hpp>
#include <latus/com/bom/LegDate.hpp>

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

      std::cout << describeKey()
                << ", " << _boardDate << " --> " << _offDate
                << ", " << _boardTime << " --> " << _offTime
                << " / " << _elapsedTime
                << " ; ";

      for (LegDateOrderedList_T::const_iterator itLegDate =
             _legDateList.begin();
           itLegDate != _legDateList.end(); ++itLegDate) {
        const LegDate* lLegDate_ptr = *itLegDate;
        assert (lLegDate_ptr != NULL);

        std::cout << lLegDate_ptr->getBoardPoint() << "-";
      }
      std::cout << std::endl;

      for (SegmentCabinOrderedList_T::const_iterator itSegmentCabin =
             _segmentCabinOrderedList.begin();
           itSegmentCabin != _segmentCabinOrderedList.end(); ++itSegmentCabin) {
        const SegmentCabin* lSegmentCabin_ptr = *itSegmentCabin;
        assert (lSegmentCabin_ptr != NULL);

        lSegmentCabin_ptr->display ();
      }
      
      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }
    
    // //////////////////////////////////////////////////////////////////////
    const AirlineCode_T& SegmentDate::getAirlineCode() const {
      assert (_flightDate != NULL);
      return _flightDate->getAirlineCode();
    }
    
    // //////////////////////////////////////////////////////////////////////
    const FlightNumber_T& SegmentDate::getFlightNumber() const {
      assert (_flightDate != NULL);
      return _flightDate->getFlightNumber();
    }
    
    // //////////////////////////////////////////////////////////////////////
    const Duration_T SegmentDate::getTimeOffSet() const {
      // TimeOffSet = (OffTime - BoardTime) + (OffDate - BoardDate) * 24
      //              - ElapsedTime
      Duration_T oTimeOffSet = (_offTime - _boardTime);
      const DateOffSet_T& lDateOffSet = getDateOffSet();
      const Duration_T lDateOffSetInHours (lDateOffSet.days() * 24, 0, 0);
      oTimeOffSet += lDateOffSetInHours - _elapsedTime;
      return oTimeOffSet;
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
    
    // //////////////////////////////////////////////////////////////////////
    void SegmentDate::updateElapsedTimeFromRouting() {
      LegDateOrderedList_T::const_iterator currentLeg = _legDateList.begin();

      const LegDate* currentLegDate_ptr = *currentLeg;
      assert (currentLegDate_ptr != NULL);

      // Retrieve the elapsed time of the first leg
      Duration_T oElapsedTime = currentLegDate_ptr->getElapsedTime();

      // Go to the next leg, if existing. If not existing, the following
      // loop will not be entered (as it means:
      // currentLeg == _legDateList.end()).
      ++currentLeg;

      for (const LegDate* previousLegDate_ptr = currentLegDate_ptr;
           currentLeg != _legDateList.end();
           ++currentLeg, previousLegDate_ptr = currentLegDate_ptr) {
        currentLegDate_ptr = *currentLeg;
        assert (currentLegDate_ptr != NULL);
        assert (previousLegDate_ptr != NULL);

        // As the board point of the current leg is the same as the off point
        // of the previous leg (by construction), there is no time difference.
        assert (currentLegDate_ptr->getBoardPoint()
                == previousLegDate_ptr->getOffPoint());
        const Duration_T& lStopOverTime = currentLegDate_ptr->getBoardTime()
          - previousLegDate_ptr->getOffTime();
        oElapsedTime += lStopOverTime;
      }
      
      // Store the result
      setElapsedTime (oElapsedTime);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void SegmentDate::fillFromRouting() {
      // Retrieve the first and the last legs of the routing.
      // Note that in the majority of the cases, as flights are mono-legs,
      // the first and last legs are thus the same.
      LegDateOrderedList_T::const_iterator firstLeg = _legDateList.begin();
      const LegDate* firstLegDate_ptr = *firstLeg;
      assert (firstLegDate_ptr != NULL);
      
      LegDateOrderedList_T::const_reverse_iterator lastLeg =
        _legDateList.rbegin();
      const LegDate* lastLegDate_ptr = *lastLeg;
      assert (lastLegDate_ptr != NULL);
      
      // Set the Board Date
      const DateTime_T& lBoardDate = firstLegDate_ptr->getBoardDate();
      setBoardDate (lBoardDate);

      // Set the Board Time
      const Duration_T& lBoardTime = firstLegDate_ptr->getBoardTime();
      setBoardTime (lBoardTime);
      
      // Set the Off Date
      const DateTime_T& lOffDate = lastLegDate_ptr->getOffDate();
      setOffDate (lOffDate);

      // Set the Off Time
      const Duration_T& lOffTime = lastLegDate_ptr->getOffTime();
      setOffTime (lOffTime);

      // Set the Elapsed Time for the whole path
      updateElapsedTimeFromRouting();
    }

  }
}
