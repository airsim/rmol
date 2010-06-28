// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/SegmentPeriodKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentPeriodKey_T::SegmentPeriodKey_T (const AirportCode_T& iBoardingPoint,
                                      const AirportCode_T& iOffPoint)
    : _boardingPoint (iBoardingPoint), _offPoint (iOffPoint) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentPeriodKey_T::SegmentPeriodKey_T (const SegmentPeriodKey_T& iKey)
    : _boardingPoint (iKey._boardingPoint), _offPoint (iKey._offPoint) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentPeriodKey_T::~SegmentPeriodKey_T () {
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentPeriodKey_T::toStream (std::ostream& ioOut) const {
    ioOut << "SegmentPeriodKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentPeriodKey_T::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string SegmentPeriodKey_T::toString() const {
    std::ostringstream oStr;
    oStr << _boardingPoint << "-" << _offPoint;
    return oStr.str();
  }

}
