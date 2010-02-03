// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/FlightDateKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  FlightDateKey_T::FlightDateKey_T (const FlightNumber_T& iFlightNumber,
                                    const Date_T& iFlightDate)
    : _flightNumber (iFlightNumber), _flightDate (iFlightDate) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDateKey_T::FlightDateKey_T (const FlightDateKey_T& iKey)
    : _parentKey (iKey._parentKey),
      _flightNumber (iKey._flightNumber), _flightDate (iKey._flightDate) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDateKey_T::~FlightDateKey_T () {
  }

  // ////////////////////////////////////////////////////////////////////
  void FlightDateKey_T::toStream (std::ostream& ioOut) const {
    ioOut << "FlightDateKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void FlightDateKey_T::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string FlightDateKey_T::toString() const {
    std::ostringstream oStr;
    oStr << _flightNumber << ", " << _flightDate;
    return oStr.str();
  }
  
  // ////////////////////////////////////////////////////////////////////
  const std::string FlightDateKey_T::describe() const {
    std::ostringstream oStr;
    oStr << _parentKey.describe() << ", " << toString();
    return oStr.str();
  }

}
