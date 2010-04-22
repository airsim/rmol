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
                     const NbOfAirlines_T& iNbOfAirlines,
                     const Duration_T& iBoardingTime)
    : _destination (iDestination),
      _elapsed (iElapsedTime),
      _nbOfSegments (iNbOfSegments),
      _nbOfAirlines (iNbOfAirlines),
      _boardingTime (iBoardingTime){
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
         << _nbOfSegments << ", " << _nbOfAirlines << ", " << _boardingTime;
    return oStr.str();
  }
  
}
