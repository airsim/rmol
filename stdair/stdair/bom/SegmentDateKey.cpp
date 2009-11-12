// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/SegmentDateKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentDateKey_T::SegmentDateKey_T (const AirportCode_T& iBoardPoint,
                                      const AirportCode_T& iOffPoint)
    : _boardPoint (iBoardPoint), _offPoint (iOffPoint) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDateKey_T::SegmentDateKey_T (const SegmentDateKey_T& iKey)
    : _parentKey (iKey._parentKey),
      _boardPoint (iKey._boardPoint), _offPoint (iKey._offPoint) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDateKey_T::~SegmentDateKey_T () {
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentDateKey_T::toStream (std::ostream& ioOut) const {
    ioOut << "SegmentDateKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentDateKey_T::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string SegmentDateKey_T::toString() const {
    std::ostringstream oStr;
    oStr << _boardPoint << "-" << _offPoint;
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string SegmentDateKey_T::describe() const {
    std::ostringstream oStr;
    oStr << _parentKey.describe() << ", " << toString();
    return oStr.str();
  }

}
