// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/FlightPeriodKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  FlightPeriodKey_T::FlightPeriodKey_T (const FlightNumber_T& iFlightNumber,
                                        const DatePeriod_T& iDatePeriod,
                                        const DoWStruct_T& iDoW)
    : _flightNumber (iFlightNumber), _dateRange (iDatePeriod), _dow (iDoW) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightPeriodKey_T::FlightPeriodKey_T (const FlightPeriodKey_T& iKey)
    : _flightNumber (iKey._flightNumber), _dateRange (iKey._dateRange),
      _dow (iKey._dow) {
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
    oStr << _flightNumber << ", " << _dateRange << ", "
         << _dow.describeShort();
    return oStr.str();
  }

}
