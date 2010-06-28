// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/basic/BasConst_Period_BOM.hpp>
#include <stdair/basic/BasConst_TravelSolution.hpp>
#include <stdair/bom/SegmentPathPeriodKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentPathPeriodKey_T::SegmentPathPeriodKey_T ()
    : _dateRange (BOOST_DEFAULT_DATE_PERIOD),
      _dow (DEFAULT_DOW_STRING),
      _boardingTime (NULL_BOOST_TIME_DURATION),
      _elapsed (NULL_BOOST_TIME_DURATION),
      _nbOfSegments (0),
      _nbOfAirlines (0){
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentPathPeriodKey_T::
  SegmentPathPeriodKey_T (const DatePeriod_T& iDeparturePeriod,
                          const DoWStruct_T& iDoW,
                          const Duration_T& iBoardingTime,
                          const Duration_T& iElapsedTime,
                          const NbOfSegments_T& iNbOfSegments,
                          const NbOfAirlines_T& iNbOfAirlines)
    : _dateRange (iDeparturePeriod),
      _dow (iDoW),
      _boardingTime (iBoardingTime),
      _elapsed (iElapsedTime),
      _nbOfSegments (iNbOfSegments),
      _nbOfAirlines (iNbOfAirlines){
  }
  
  // ////////////////////////////////////////////////////////////////////
  SegmentPathPeriodKey_T::~SegmentPathPeriodKey_T () {
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentPathPeriodKey_T::toStream (std::ostream& ioOut) const {
    ioOut << "SegmentPathPeriodKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentPathPeriodKey_T::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string SegmentPathPeriodKey_T::toString() const {
    std::ostringstream oStr;
    oStr << _dateRange << ", " << _dow.describeShort () << ", "
         << _boardingTime << ", "  << _elapsed << ", "
         << _nbOfSegments << ", " << _nbOfAirlines ;
    return oStr.str();
  }
  
}
