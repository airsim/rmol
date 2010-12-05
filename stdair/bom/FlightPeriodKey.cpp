// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/FlightPeriodKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  FlightPeriodKey::FlightPeriodKey (const FlightNumber_T& iFlightNumber,
                                        const PeriodStruct& iPeriod)
    : _flightNumber (iFlightNumber), _period (iPeriod) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightPeriodKey::FlightPeriodKey (const FlightPeriodKey& iKey)
    : _flightNumber (iKey._flightNumber), _period (iKey._period) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightPeriodKey::~FlightPeriodKey () {
  }

  // ////////////////////////////////////////////////////////////////////
  void FlightPeriodKey::toStream (std::ostream& ioOut) const {
    ioOut << "FlightPeriodKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void FlightPeriodKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string FlightPeriodKey::toString() const {
    std::ostringstream oStr;
    oStr << _flightNumber << ", " << _period.describeShort();
    return oStr.str();
  }

}
