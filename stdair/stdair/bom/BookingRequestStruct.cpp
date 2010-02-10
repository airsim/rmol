// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <istream>
#include <ostream>
#include <sstream>
// StdAir
#include <stdair/bom/BookingRequestStruct.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  BookingRequestStruct::BookingRequestStruct (const AirportCode_T& iOrigin,
                                              const AirportCode_T& iDestination,
                                              const Date_T& iDepartureDate,
                                              const DateTime_T& iRequestDateTime,
                                              const PassengerType_T& iPaxType,
                                              const NbOfSeats_T& iPartySize)
    : _origin (iOrigin), _destination (iDestination),
      _preferredDepartureDate (iDepartureDate), 
      _requestDateTime (iRequestDateTime),
      _paxType (iPaxType), _partySize (iPartySize) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  BookingRequestStruct::~BookingRequestStruct () {
  }
  
  // //////////////////////////////////////////////////////////////////////
  void BookingRequestStruct::toStream (std::ostream& ioOut) const {
    ioOut << describe();
  }

  // //////////////////////////////////////////////////////////////////////
  void BookingRequestStruct::fromStream (std::istream& ioIn) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string BookingRequestStruct::describe() const {
    std::ostringstream oStr;
    oStr << _origin << " - " << _destination << " " << _preferredDepartureDate
         << " " << _requestDateTime << " " << _paxType << " " << _partySize;
    return oStr.str();
  }

}
