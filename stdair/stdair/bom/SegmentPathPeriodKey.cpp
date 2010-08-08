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
    : _period (),
      _boardingTime (NULL_BOOST_TIME_DURATION),
      _elapsed (NULL_BOOST_TIME_DURATION),
      _nbOfAirlines (0){
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentPathPeriodKey_T::
  SegmentPathPeriodKey_T (const PeriodStruct_T& iPeriod,
                          const Duration_T& iBoardingTime,
                          const Duration_T& iElapsedTime,
                          const DateOffsetList_T& iBoardingDateOffsetList,
                          const NbOfAirlines_T& iNbOfAirlines)
    : _period (iPeriod),
      _boardingTime (iBoardingTime),
      _elapsed (iElapsedTime),
      _boardingDateOffsetList (iBoardingDateOffsetList),
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
    oStr << _period.describeShort () << ", "
         << _boardingTime << ", "  << _elapsed << ", ";
    for (DateOffsetList_T::const_iterator itOffset =
           _boardingDateOffsetList.begin();
         itOffset != _boardingDateOffsetList.end(); ++itOffset) {
      const DateOffset_T& lDateOffset = *itOffset;
      oStr << lDateOffset.days() << ", ";
    }

    oStr << _nbOfAirlines ;
    return oStr.str();
  }
  
}
