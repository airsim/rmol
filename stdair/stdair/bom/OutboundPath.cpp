// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/OutboundPathStructure.hpp>
#include <stdair/bom/OutboundPath.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/BomList.hpp>
#include <stdair/bom/BomMap.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  OutboundPath::OutboundPath (const BomKey_T& iKey,
                              BomStructure_T& ioOutboundPathStructure)
    : OutboundPathContent (iKey),
      _outboundPathStructure (ioOutboundPathStructure) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  OutboundPath::~OutboundPath () {
  }

  // ////////////////////////////////////////////////////////////////////
  void OutboundPath::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void OutboundPath::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string OutboundPath::toString() const {
    std::ostringstream oStr;

    // First, put the key of that level
    oStr << describeShortKey() << std::endl;

    // Then, browse the children
    // [...] (no child for now)
    
    return oStr.str();
  }
    
  // ////////////////////////////////////////////////////////////////////
  const std::string OutboundPath::describeKey() const {
    return _key.describe();
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string OutboundPath::describeShortKey() const {
    return _key.toString();
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDateList_T OutboundPath::getSegmentDateList () const {
    return _outboundPathStructure.getSegmentDateHolder();
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDateMap_T OutboundPath::getSegmentDateMap () const {
    return _outboundPathStructure.getSegmentDateHolder();
  }

  // ////////////////////////////////////////////////////////////////////
  const Date_T& OutboundPath::getOffDate () const {
    const SegmentDate* lLastSegmentDate_ptr = getLastSegmentDate ();
    assert (lLastSegmentDate_ptr != NULL);
    return (lLastSegmentDate_ptr->getOffDate ());
  }

  // ////////////////////////////////////////////////////////////////////
  const SegmentDate* OutboundPath::getLastSegmentDate () const {
    const SegmentDate* oSegment_ptr = NULL;
    
    // Retrieve the last segment of the list
    SegmentDateList_T lSegmentDateList = getSegmentDateList();
    SegmentDateList_T::reverse_iterator itLastSegment= lSegmentDateList.rbegin();

    if (itLastSegment == lSegmentDateList.rend()) {
      return oSegment_ptr;
    }
    
    oSegment_ptr = &*itLastSegment;
    assert (oSegment_ptr != NULL);

    return oSegment_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  const SegmentDate* OutboundPath::getFirstSegmentDate () const {
    const SegmentDate* oSegment_ptr = NULL;
    
    // Retrieve the first segment of the list
    SegmentDateList_T lSegmentDateList = getSegmentDateList();
    SegmentDateList_T::iterator itFirstSegment= lSegmentDateList.begin();

    if (itFirstSegment == lSegmentDateList.end()) {
      return oSegment_ptr;
    }
    
    oSegment_ptr = &*itFirstSegment;
    assert (oSegment_ptr != NULL);

    return oSegment_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  void OutboundPath::incrementTotalFlightTime (const Duration_T& iElapsed) {
    _flightTime += iElapsed;      
  }

  // ////////////////////////////////////////////////////////////////////
  void OutboundPath::updateAirlineCode() {
    // TODO: to be optimised.
    std::ostringstream ostr;
    SegmentDateList_T lSegmentDateList = getSegmentDateList();
    
    for (SegmentDateList_T::iterator itSegmentDate = lSegmentDateList.begin();
         itSegmentDate != lSegmentDateList.end(); ++itSegmentDate) {
      const SegmentDate& lSegmentDate = *itSegmentDate;
      ostr << lSegmentDate.getAirlineCode();
    }
    
    const AirlineCode_T lAirlineCode (ostr.str());
    setAirlineCode(lAirlineCode);
  }

  // ////////////////////////////////////////////////////////////////////
  AirportDate* OutboundPath::getDestinationAirportDate() const {
    AirportDate* oAirportDate_ptr = NULL;
      
    // Retrieve the off point description (reference date + airport code).
    const AirportCode_T& lDestination = getDestination();
    const Date_T& lReferenceDate = getOffDate();
    
    const AirportDateKey_T lAirportDateKey (lDestination);
    const NetworkDateKey_T lNetworkDateKey (lReferenceDate);
    // Retrieve the destination airport corresponding to the destination
    // reference date and airport code.
    oAirportDate_ptr = _outboundPathStructure.getAirportDate (lAirportDateKey,
                                                              lNetworkDateKey);
      
    return oAirportDate_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  bool OutboundPath::isConnectable (const OutboundPath& iOutboundPath) const {
    // Delegate the check on the two (potentially) connecting SegmentDate
    // objects, i.e., the last SegmentDate of the current OutboundPath,
    // and the first SegmentDate of the given OutboundPath.
    const SegmentDate* lOffSegment_ptr = getLastSegmentDate();
    assert (lOffSegment_ptr != NULL);

    const SegmentDate* lBoardingSegment_ptr =
      iOutboundPath.getFirstSegmentDate();
    assert (lBoardingSegment_ptr != NULL);
      
    return lOffSegment_ptr->isConnectable (*lBoardingSegment_ptr);
  }

  // ////////////////////////////////////////////////////////////////////
  bool OutboundPath::
  isAirlineFlown (const AirlineCode_T& iAirlineCode) const {
    bool oAirlineFlown = false;

    const SegmentDateList_T& lSegmentDateList = getSegmentDateList ();
    for (SegmentDateList_T::iterator itSegmentDate =
           lSegmentDateList.begin();
         itSegmentDate != lSegmentDateList.end(); ++itSegmentDate) {
      const SegmentDate& lSegmentDate = *itSegmentDate;

      const AirlineCode_T& lSegmentAirlineCode =
        lSegmentDate.getAirlineCode();
      if (lSegmentAirlineCode == iAirlineCode) {
        oAirlineFlown = true;
        break;
      }
    }

    return oAirlineFlown;
  }

  // //////////////////////////////////////////////////////////////////////
  const Duration_T OutboundPath::calculateElapsedTimeFromRouting () const {
    const SegmentDateList_T& lAllSegmentList = getSegmentDateList();
    SegmentDateList_T::iterator itSegmentDate = lAllSegmentList.begin();

    const SegmentDate* lCurrentSegmentDate_ptr = &*itSegmentDate;
    assert (lCurrentSegmentDate_ptr != NULL);

    // Retrieve the elapsed time of the first segment
    Duration_T oElapsedTime = lCurrentSegmentDate_ptr->getElapsedTime();

    // Go to the next segment, if existing. If not existing, the following
    // loop will not be entered (as it means:
    // itSegmentDate == _segmentDateList.end()).
    ++itSegmentDate;

    for (const SegmentDate* previousSegmentDate_ptr = lCurrentSegmentDate_ptr;
         itSegmentDate != lAllSegmentList.end();
         ++itSegmentDate, previousSegmentDate_ptr = lCurrentSegmentDate_ptr) {
      lCurrentSegmentDate_ptr = &*itSegmentDate;
      assert (lCurrentSegmentDate_ptr != NULL);
      assert (previousSegmentDate_ptr != NULL);

      // As the boarding point (and date) of the current segment are
      // the same as the off point (and date) of the previous
      // segment (by construction), there is no time difference.
      assert (lCurrentSegmentDate_ptr->getBoardingPoint()
              == previousSegmentDate_ptr->getOffPoint()
              && lCurrentSegmentDate_ptr->getBoardingDate()
              == previousSegmentDate_ptr->getOffDate());
      const Duration_T& lStopOverTime =
        lCurrentSegmentDate_ptr->getBoardingTime()
        - previousSegmentDate_ptr->getOffTime();
      oElapsedTime += lStopOverTime;

      // Add the elapsed time of the current outbound path
      const Duration_T& currentElapsedTime =
        lCurrentSegmentDate_ptr->getElapsedTime();
      oElapsedTime += currentElapsedTime;
    }
      
    // Store the result
    return oElapsedTime;
  }

  
}

