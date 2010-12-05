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
  BookingRequestStruct::
  BookingRequestStruct (const AirportCode_T& iOrigin,
                        const AirportCode_T& iDestination,
                        const AirportCode_T& iPOS,
                        const Date_T& iDepartureDate,
                        const DateTime_T& iRequestDateTime,
                        const CabinCode_T& iPreferredCabin,
                        const NbOfSeats_T& iPartySize,
                        const ChannelLabel_T& iChannel,
                        const TripType_T& iTripType,
                        const DayDuration_T& iStayDuration,
                        const FrequentFlyer_T& iFrequentFlyerType,
                        const Duration_T& iPreferredDepartureTime,
                        const WTP_T& iWTP,
                        const PriceValue_T& iValueOfTime)
    : _origin (iOrigin), _destination (iDestination),
      _pos (iPOS), _preferredDepartureDate (iDepartureDate), 
      _requestDateTime (iRequestDateTime),
      _preferredCabin (iPreferredCabin), _partySize (iPartySize),
      _channel (iChannel), _tripType (iTripType),
      _stayDuration (iStayDuration), _frequentFlyerType (iFrequentFlyerType),
      _preferredDepartureTime (iPreferredDepartureTime), _wtp (iWTP),
      _valueOfTime (iValueOfTime) {
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
    oStr << _origin << " - " << _destination
         << " " << _pos << " " << _preferredDepartureDate
         << " " << _requestDateTime << " " << _preferredCabin
         << " " << _partySize << " " << _channel << " " << _tripType 
         << " " << _stayDuration << " " << _frequentFlyerType
         << " " << _preferredDepartureTime << " " << _wtp
         << " " << _valueOfTime;
    return oStr.str();
  }

}
