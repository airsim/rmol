// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/OutboundPath.hpp>
#include <latus/com/bom/AirportDate.hpp>
#include <latus/com/bom/SegmentDate.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    OutboundPath::OutboundPath (const OutboundPathKey_T& iKey)
      : _airportDate (NULL), _key (iKey) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    OutboundPath::~OutboundPath () {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string OutboundPath::describeKey() const {
      return _key.describe();
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string OutboundPath::describeShortKey() const {
      return _key.describeShort();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void OutboundPath::display() const {

      // Store current formatting flags of std::cout
      std::ios::fmtflags oldFlags = std::cout.flags();

      std::cout << describeKey() << std::endl;

      for (SegmentDateLightList_T::const_iterator itSegmentDate =
             _segmentDateLightList.begin();
           itSegmentDate != _segmentDateLightList.end(); ++itSegmentDate) {
        const SegmentDate* lSegmentDate_ptr = *itSegmentDate;
        assert (lSegmentDate_ptr != NULL);

        std::cout << lSegmentDate_ptr->describeKey() << std::endl;
      }
      
      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }

    // //////////////////////////////////////////////////////////////////////
    const DateTime_T& OutboundPath::getOffDate() const {
      assert (_segmentDateLightList.size() >= 1);
      
      const SegmentDate* lastSegmentDate_ptr = getLastSegmentDate();
      assert (lastSegmentDate_ptr != NULL);

      // A small sanity check: check that the destination is the same as the
      // off point of the last segment.
      const AirportCode_T& lDestination = lastSegmentDate_ptr->getOffPoint();
      assert (lDestination == _key.destination);
      
      return lastSegmentDate_ptr->getOffDate();
    }

    // //////////////////////////////////////////////////////////////////////
    AirportDate* OutboundPath::getDestinationAirportDate() const {
      AirportDate* oAirportDate_ptr = NULL;
      
      // Retrieve the off point description (reference date + airport code).
      const AirportCode_T& lDestination = getDestination();
      const DateTime_T& lReferenceDate = getOffDate();
      
      // Retrieve the destination airport corresponding to the destination
      // reference date and airport code.
      assert (_airportDate != NULL);
      oAirportDate_ptr = _airportDate->getAirportDate (lDestination,
                                                       lReferenceDate);
      
      return oAirportDate_ptr;
    }

    // //////////////////////////////////////////////////////////////////////
    bool OutboundPath::
    isAirlineFlown (const AirlineCode_T& iAirlineCode) const {
      bool oAirlineFlown = false;
      
      for (SegmentDateLightList_T::const_iterator itSegmentDate =
             _segmentDateLightList.begin();
           itSegmentDate != _segmentDateLightList.end(); ++itSegmentDate) {
        const SegmentDate* lSegmentDate_ptr = *itSegmentDate;
        assert (lSegmentDate_ptr != NULL);

        const AirlineCode_T& lSegmentAirlineCode =
          lSegmentDate_ptr->getAirlineCode();
        if (lSegmentAirlineCode == iAirlineCode) {
          oAirlineFlown = true;
          break;
        }
      }

      return oAirlineFlown;
    }

    // //////////////////////////////////////////////////////////////////////
    const SegmentDate* OutboundPath::getFirstSegmentDate () const {
      const SegmentDate* oSegment_ptr = NULL;
      
      if (_segmentDateLightList.size() == 0) {
        return oSegment_ptr;
      }

      // Retrieve the first segment of the list
      SegmentDateLightList_T::const_iterator firstSegment =
        _segmentDateLightList.begin();
      oSegment_ptr = *firstSegment;
      assert (oSegment_ptr != NULL);

      return oSegment_ptr;
    }

    // //////////////////////////////////////////////////////////////////////
    const SegmentDate* OutboundPath::getLastSegmentDate () const {
      const SegmentDate* oSegment_ptr = NULL;
      
      if (_segmentDateLightList.size() == 0) {
        return oSegment_ptr;
      }

      // Retrieve the last segment of the list
      SegmentDateLightList_T::const_reverse_iterator lastSegment =
        _segmentDateLightList.rbegin();
      oSegment_ptr = *lastSegment;
      assert (oSegment_ptr != NULL);

      return oSegment_ptr;
    }

    // //////////////////////////////////////////////////////////////////////
    bool OutboundPath::isConnectable (const OutboundPath& iOutboundPath) const {
      // Delegate the check on the two (potentially) connecting SegmentDate
      // objects, i.e., the last SegmentDate of the current OutboundPath,
      // and the first SegmentDate of the given OutboundPath.
      const SegmentDate* lOffSegment_ptr = getLastSegmentDate();
      assert (lOffSegment_ptr != NULL);

      const SegmentDate* lBoardSegment_ptr =
        iOutboundPath.getFirstSegmentDate();
      assert (lBoardSegment_ptr != NULL);
      
      return lOffSegment_ptr->isConnectable (*lBoardSegment_ptr);
    }

    // //////////////////////////////////////////////////////////////////////
    const Duration_T OutboundPath::
    calculateElapsedTimeFromRouting (const SegmentDate& iLastSegment) const {

      const DateTime_T& lOutboundPathOffDate = getOffDate();
      const AirportCode_T& lOutboundPathOffPoint = getDestination();
      const DateTime_T& lSegmentDateBoardDate = iLastSegment.getBoardDate();
      const AirportCode_T& lSegmentDateBoardPoint= iLastSegment.getBoardPoint();

      assert (lOutboundPathOffDate == lSegmentDateBoardDate
              && lOutboundPathOffPoint == lSegmentDateBoardPoint);

      // Add the given segment to the end of the outbound path
      SegmentDateLightList_T lAllSegmentList = _segmentDateLightList;
      lAllSegmentList.push_back (&iLastSegment);
      
      SegmentDateLightList_T::const_iterator currentSegment =
        lAllSegmentList.begin();

      const SegmentDate* currentSegmentDate_ptr = *currentSegment;
      assert (currentSegmentDate_ptr != NULL);

      // Retrieve the elapsed time of the first segment
      Duration_T oElapsedTime = currentSegmentDate_ptr->getElapsedTime();

      // Go to the next segment, if existing. If not existing, the following
      // loop will not be entered (as it means:
      // currentSegment == _segmentDateList.end()).
      ++currentSegment;

      for (const SegmentDate* previousSegmentDate_ptr = currentSegmentDate_ptr;
           currentSegment != lAllSegmentList.end();
           ++currentSegment, previousSegmentDate_ptr = currentSegmentDate_ptr) {
        currentSegmentDate_ptr = *currentSegment;
        assert (currentSegmentDate_ptr != NULL);
        assert (previousSegmentDate_ptr != NULL);

        // As the board point (and date) of the current segment are
        // the same as the off point (and date) of the previous
        // segment (by construction), there is no time difference.
        assert (currentSegmentDate_ptr->getBoardPoint()
                   == previousSegmentDate_ptr->getOffPoint()
                && currentSegmentDate_ptr->getBoardDate()
                   == previousSegmentDate_ptr->getOffDate());
        const Duration_T& lStopOverTime = currentSegmentDate_ptr->getBoardTime()
          - previousSegmentDate_ptr->getOffTime();
        oElapsedTime += lStopOverTime;

        // Add the elapsed time of the current outbound path
        const Duration_T& currentElapsedTime =
          currentSegmentDate_ptr->getElapsedTime();
        oElapsedTime += currentElapsedTime;
      }
      
      // Store the result
      return oElapsedTime;
    }

    // //////////////////////////////////////////////////////////////////////
    bool OutboundPath::buildCheapestSolution (ClassStructList_T& lCSL, const SeatNumber_T& lST) const {

      bool available = true;
      for (SegmentDateLightList_T::const_iterator itSegmentDate =
             _segmentDateLightList.begin();
           itSegmentDate != _segmentDateLightList.end(); ++itSegmentDate) {
        const SegmentDate* lSegmentDate_ptr = *itSegmentDate;
        assert (lSegmentDate_ptr != NULL);
        available = lSegmentDate_ptr->buildCheapestSolution(lCSL, lST);
        if (available == false) {
          break;
        }
      }
      return available;
    }
    
  }
}
