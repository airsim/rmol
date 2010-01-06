// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/OutboundPathKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  OutboundPathKey_T::
  OutboundPathKey_T (const AirportCode_T& iDestination,
                     const Duration_T& iElapsedTime,
                     const NbOfSegments_T& iNbOfSegments,
                     const NbOfAirlines_T& iNbOfAirlines)
    : _destination (iDestination),
      _elapsed (iElapsedTime),
      _nbOfSegments (iNbOfSegments),
      _nbOfAirlines (iNbOfAirlines) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  OutboundPathKey_T::~OutboundPathKey_T () {
  }

  // ////////////////////////////////////////////////////////////////////
  void OutboundPathKey_T::toStream (std::ostream& ioOut) const {
    ioOut << "OutboundPathKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void OutboundPathKey_T::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string OutboundPathKey_T::toString() const {
    std::ostringstream oStr;
    oStr << _destination << ", " << _elapsed << ", "
         << _nbOfSegments << ", " << _nbOfAirlines;
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string OutboundPathKey_T::describe() const {
    std::ostringstream oStr;
    oStr << _parentKey.describe() << ", " << toString();
    return oStr.str();
  }
    
  // //////////////////////////////////////////////////////////////////////
  const AirportCode_T& OutboundPathKey_T::getBoardingPoint() const {
    return _parentKey.getBoardingPoint();
  }
  
  // //////////////////////////////////////////////////////////////////////
  const Date_T& OutboundPathKey_T::getBoardingDate() const {
    return _parentKey.getBoardingDate();
  }
  
}
