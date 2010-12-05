// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <sstream>
// StdAir
#include <stdair/bom/SegmentPeriodKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentPeriodKey::SegmentPeriodKey (const AirportCode_T& iBoardingPoint,
                                      const AirportCode_T& iOffPoint)
    : _boardingPoint (iBoardingPoint), _offPoint (iOffPoint) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentPeriodKey::SegmentPeriodKey (const SegmentPeriodKey& iKey)
    : _boardingPoint (iKey._boardingPoint), _offPoint (iKey._offPoint) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentPeriodKey::~SegmentPeriodKey () {
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentPeriodKey::toStream (std::ostream& ioOut) const {
    ioOut << "SegmentPeriodKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentPeriodKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string SegmentPeriodKey::toString() const {
    std::ostringstream oStr;
    oStr << _boardingPoint << "-" << _offPoint;
    return oStr.str();
  }

}
