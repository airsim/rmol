// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/basic/BasConst_TravelSolution.hpp>
#include <stdair/bom/BomSource.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentPathPeriod::SegmentPathPeriod (const Key_T& iKey,
                              Structure_T& ioSegmentPathPeriodStructure)
    : SegmentPathPeriodContent (iKey),
      _structure (ioSegmentPathPeriodStructure) {
    init ();
  }
  
  // ////////////////////////////////////////////////////////////////////
  SegmentPathPeriod::~SegmentPathPeriod () {
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentPathPeriod::init () {
    _structure.initChildrenHolder<SegmentPeriod>();
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentPathPeriod::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentPathPeriod::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string SegmentPathPeriod::toString() const {
    std::ostringstream oStr;

    // First, put the key of that level
    oStr << describeShortKey() << std::endl;

    // Then, browse the children
    // [...] (no child for now)
    
    return oStr.str();
  }
    
  // ////////////////////////////////////////////////////////////////////
  const std::string SegmentPathPeriod::describeKey() const {
    std::ostringstream oStr;
    oStr << _structure.describeParentKey() << ", " << describeShortKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentPeriodList_T SegmentPathPeriod::getSegmentPeriodList () const {
    return _structure.getChildrenHolder<SegmentPeriod>();
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentPeriodMap_T SegmentPathPeriod::getSegmentPeriodMap () const {
    return _structure.getChildrenHolder<SegmentPeriod>();
  }

  // ////////////////////////////////////////////////////////////////////
  const SegmentPathPeriod::Parent_T& SegmentPathPeriod::getParent () const {
    return _structure.getParent().getContent();
  }

  // ////////////////////////////////////////////////////////////////////
  const SegmentPeriod* SegmentPathPeriod::getLastSegmentPeriod () const {
    const SegmentPeriod* oSegment_ptr = NULL;
    
    // Retrieve the last segment of the list
    SegmentPeriodList_T lSegmentPeriodList = getSegmentPeriodList();
    SegmentPeriodList_T::reverse_iterator itLastSegment =
      lSegmentPeriodList.rbegin();

    if (itLastSegment == lSegmentPeriodList.rend()) {
      return oSegment_ptr;
    }
    
    oSegment_ptr = &*itLastSegment;
    assert (oSegment_ptr != NULL);

    return oSegment_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  const SegmentPeriod* SegmentPathPeriod::getFirstSegmentPeriod () const {
    const SegmentPeriod* oSegment_ptr = NULL;
    
    // Retrieve the first segment of the list
    SegmentPeriodList_T lSegmentPeriodList = getSegmentPeriodList();
    SegmentPeriodList_T::iterator itFirstSegment= lSegmentPeriodList.begin();

    if (itFirstSegment == lSegmentPeriodList.end()) {
      return oSegment_ptr;
    }
    
    oSegment_ptr = &*itFirstSegment;
    assert (oSegment_ptr != NULL);

    return oSegment_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  const AirportCode_T& SegmentPathPeriod::getDestination () const {
    const SegmentPeriod* lLastSegment_ptr = getLastSegmentPeriod();
    assert (lLastSegment_ptr != NULL);
    return lLastSegment_ptr->getOffPoint();
  }  

  // ////////////////////////////////////////////////////////////////////
  bool SegmentPathPeriod::
  isAirlineFlown (const AirlineCode_T& iAirlineCode) const {
    bool oAirlineFlown = false;

    const SegmentPeriodList_T& lSegmentPeriodList = getSegmentPeriodList ();
    for (SegmentPeriodList_T::iterator itSegmentPeriod =
           lSegmentPeriodList.begin();
         itSegmentPeriod != lSegmentPeriodList.end(); ++itSegmentPeriod) {
      const SegmentPeriod& lSegmentPeriod = *itSegmentPeriod;

      const AirlineCode_T& lSegmentAirlineCode =
        lSegmentPeriod.getParent().getParent().getAirlineCode();
      if (lSegmentAirlineCode == iAirlineCode) {
        oAirlineFlown = true;
        break;
      }
    }

    return oAirlineFlown;
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentPathPeriodKey_T SegmentPathPeriod::
  connectWithAnotherSegment(const SegmentPathPeriod& iSingleSegmentPath) const {
    SegmentPathPeriodKey_T oSegmentPathPeriodKey;

    // Retrieve the (only) segment period of the single segment path.
    const SegmentPeriod* lNextSegmentPeriod_ptr =
      iSingleSegmentPath.getFirstSegmentPeriod ();
    assert (lNextSegmentPeriod_ptr != NULL);

    // Retrive the last segment period of the current segment path and check
    // if the combination of the last segment and the next segment that we
    // want to add to the current segment path will create a new segment
    // (i.e., the two segment period belongs to the same flight number).
    const SegmentPeriod* lLastSegmentPeriod_ptr = getLastSegmentPeriod ();
    assert (lLastSegmentPeriod_ptr != NULL);
    const FlightPeriod& lLastFlightPeriod = lLastSegmentPeriod_ptr->getParent();
    const FlightPeriod& lNextFlightPeriod = lNextSegmentPeriod_ptr->getParent();
    if (lLastFlightPeriod.getFlightNumber()==lNextFlightPeriod.getFlightNumber()
        && lLastFlightPeriod.getParent().getAirlineCode() ==
        lNextFlightPeriod.getParent().getAirlineCode()) {
      return oSegmentPathPeriodKey;
    }
    
    // Check if the new segment period will create a circle.
    const AirportCode_T& lDestination = lNextSegmentPeriod_ptr->getOffPoint();
    if (checkCircle (lDestination) == true) {
      return oSegmentPathPeriodKey;
    }

    // Check if a passenger can connect from the last segment of the
    // current segment path to the first segment of the to-be-added
    // segment path. If yes, build a new departure period for the new
    // segment path.
    DateOffsetList_T lBoardingDateOffsetList = 
      getBoardingDateOffsetList();
    const PeriodStruct_T& lCurrentDeparturePeriod = getDeparturePeriod();
    const PeriodStruct_T& lNextDeparturePeriod =
      iSingleSegmentPath.getDeparturePeriod();
    const Duration_T& lLastOffTime = lLastSegmentPeriod_ptr->getOffTime();
    const Duration_T& lNextBoardingTime =
      lNextSegmentPeriod_ptr->getBoardingTime();
    // If the next boarding time is later than the last off time, check if
    // the passengers will have enough time for the transfer. If the next
    // boarding time is earlier than the last off time, check if the passengers
    // can connect to a flight in the next day.
    if (lNextBoardingTime >= lLastOffTime) {
      const Duration_T lStopTime = lNextBoardingTime - lLastOffTime;
      if (lStopTime < DEFAULT_MINIMUM_CONNECTION_TIME) {
        return oSegmentPathPeriodKey;
      } else {
        // Calulcate the date offset of the next segment compare to
        // the first one. In this case, this value is equal to the offset
        // of the off date of the last segment compare to the boarding date
        // of the first segment.
        const DateOffset_T& lLastBoardingDateOffset =
          lBoardingDateOffsetList.at (getNbOfSegments() - 1);
        const DateOffset_T lNextBoardingDateOffset =
          lLastBoardingDateOffset + lLastSegmentPeriod_ptr->getOffDateOffset()
          - lLastSegmentPeriod_ptr->getBoardingDateOffset();
        const DateOffset_T lNegativeNextBoardingDateOffset =
          DateOffset_T (0) - lNextBoardingDateOffset;

        // Compute the adjusted departure period of the next segment by
        // substracting the origin one with the boarding date offset.
        const PeriodStruct_T lAdjustedNextDeparturePeriod =
          lNextDeparturePeriod.addDateOffset (lNegativeNextBoardingDateOffset);

        // Build the intersection of the two periods.
        const PeriodStruct_T lNewDeparturePeriod =
          lCurrentDeparturePeriod.intersection (lAdjustedNextDeparturePeriod);
        Duration_T lNewElapsed = getElapsedTime() + lStopTime +
          lNextSegmentPeriod_ptr->getElapsedTime();
        lBoardingDateOffsetList.push_back (lNextBoardingDateOffset);
        oSegmentPathPeriodKey.setPeriod (lNewDeparturePeriod);
        oSegmentPathPeriodKey.setElapsedTime (lNewElapsed);
      }
    } else {
      const Duration_T lStopTime = 
        lNextBoardingTime - lLastOffTime + Duration_T (24, 0, 0);
      if (lStopTime < DEFAULT_MINIMUM_CONNECTION_TIME) {
        return oSegmentPathPeriodKey;
      } else {
        // Calulcate the date offset of the next segment compare to
        // the first one.
        const DateOffset_T& lLastBoardingDateOffset =
          lBoardingDateOffsetList.at (getNbOfSegments() - 1);
        const DateOffset_T lNextBoardingDateOffset =
          lLastBoardingDateOffset + lLastSegmentPeriod_ptr->getOffDateOffset()
          - lLastSegmentPeriod_ptr->getBoardingDateOffset() + DateOffset_T (1);
        const DateOffset_T lNegativeNextBoardingDateOffset =
          DateOffset_T (0) - lNextBoardingDateOffset;

        // Compute the adjusted departure period of the next segment by
        // substracting the origin one with the boarding date offset.
        const PeriodStruct_T lAdjustedNextDeparturePeriod =
          lNextDeparturePeriod.addDateOffset (lNegativeNextBoardingDateOffset);

        // Build the intersection of the two periods.
        const PeriodStruct_T lNewDeparturePeriod =
          lCurrentDeparturePeriod.intersection (lAdjustedNextDeparturePeriod);
        Duration_T lNewElapsed = getElapsedTime() + lStopTime +
          lNextSegmentPeriod_ptr->getElapsedTime();
        lBoardingDateOffsetList.push_back (lNextBoardingDateOffset);
        oSegmentPathPeriodKey.setPeriod (lNewDeparturePeriod);
        oSegmentPathPeriodKey.setElapsedTime (lNewElapsed);
      }
    }
    
    const Duration_T& lBoardingTime = getBoardingTime();
    oSegmentPathPeriodKey.setBoardingTime (lBoardingTime);
    oSegmentPathPeriodKey.setBoardingDateOffsetList (lBoardingDateOffsetList);
    
    return oSegmentPathPeriodKey;
  }

  // ////////////////////////////////////////////////////////////////////
  bool SegmentPathPeriod::
  checkCircle (const AirlineCode_T& iDestination) const {
    const SegmentPeriodList_T& lSegmentPeriodList = getSegmentPeriodList();
    for (SegmentPeriodList_T::iterator itSegment = lSegmentPeriodList.begin();
         itSegment != lSegmentPeriodList.end(); ++itSegment) {
      const SegmentPeriod& lCurrentSegment = *itSegment;
      const AirlineCode_T& lCurrentBoardingPoint =
        lCurrentSegment.getBoardingPoint();
      if (lCurrentBoardingPoint == iDestination) {
        return true;
      }
    }
    return false;
  }

  // ////////////////////////////////////////////////////////////////////
  bool SegmentPathPeriod::
  isDepartureDateValid (const Date_T& iDepartureDate) const {
    const PeriodStruct_T& lPeriod = getDeparturePeriod ();

    // Check if the departure date is within the date range.
    const DatePeriod_T& lDeparturePeriod = lPeriod.getDateRange ();
    if (lDeparturePeriod.contains (iDepartureDate) == false) {
      return false;
    }

    // Check if the departure date is valid within the DOW.
    // 0 = Sunday, 1 = Monday, etc.
    const short lDay = iDepartureDate.day_of_week ();
    const DoWStruct_T& lDoW = lPeriod.getDoW ();
    if (lDoW.getStandardDayOfWeek (lDay) == false) {
      return false;
    }

    return true;
  }
  
}

