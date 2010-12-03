// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <sstream>
// StdAir
#include <stdair/bom/FlightDateKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  FlightDateKey::FlightDateKey (const FlightNumber_T& iFlightNumber,
                                const Date_T& iFlightDate)
    : _flightNumber (iFlightNumber), _flightDate (iFlightDate) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDateKey::FlightDateKey (const FlightDateKey& iKey)
    : _flightNumber (iKey._flightNumber), _flightDate (iKey._flightDate) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDateKey::~FlightDateKey () {
  }

  // ////////////////////////////////////////////////////////////////////
  void FlightDateKey::toStream (std::ostream& ioOut) const {
    ioOut << "FlightDateKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void FlightDateKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string FlightDateKey::toString() const {
    std::ostringstream oStr;
    oStr << _flightNumber << ", " << _flightDate;
    return oStr.str();
  }

}
