// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/FlightPeriodKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  FlightPeriodKey_T::FlightPeriodKey_T (const FlightNumber_T& iFlightNumber,
                                        const PeriodStruct_T& iPeriod)
    : _flightNumber (iFlightNumber), _period (iPeriod) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightPeriodKey_T::FlightPeriodKey_T (const FlightPeriodKey_T& iKey)
    : _flightNumber (iKey._flightNumber), _period (iKey._period) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightPeriodKey_T::~FlightPeriodKey_T () {
  }

  // ////////////////////////////////////////////////////////////////////
  void FlightPeriodKey_T::toStream (std::ostream& ioOut) const {
    ioOut << "FlightPeriodKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void FlightPeriodKey_T::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string FlightPeriodKey_T::toString() const {
    std::ostringstream oStr;
    oStr << _flightNumber << ", " << _period.describeShort();
    return oStr.str();
  }

}
