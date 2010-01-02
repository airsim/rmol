#ifndef __STDAIR_BOM_BOOKINGREQUESTSTRUCT_HPP
#define __STDAIR_BOM_BOOKINGREQUESTSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/bom/StructAbstract.hpp>
#include <stdair/STDAIR_Types.hpp>

namespace stdair {

  /** Structure holding the elements of a booking request. */
  struct BookingRequestStruct : public StructAbstract {
  public:
    // /////////////// Getters /////////////////
    /** Get the requested origin. */
    const AirportCode_T& getOrigin() const {
      return _origin;
    }

    /** Get the requested destination. */
    const AirportCode_T& getDestination() const {
      return _destination;
    }

    /** Get the requested departure date. */
    const Date_T& getDepartureDate() const {
      return _departureDate;
    }

    /** Get the passenger type. */
    const PassengerType_T& getPaxType() const {
      return _paxType;
    }

    /** Get the party size. */
    const NbOfSeats_T& getPartySize() const {
      return _partySize;
    }
    

    // /////////////// Setters /////////////////
    /** Set the requested origin. */
    void setOrigin (const AirportCode_T& iOrigin) {
      _origin = iOrigin;
    }

    /** Set the requested destination. */
    void setDestination (const AirportCode_T& iDestination) {
      _destination = iDestination;
    }

    /** Set the requested departure date. */
    void setDepartureDate (const Date_T& iDepartureDate) {
      _departureDate = iDepartureDate;
    }

    /** Set the passenger type. */
    void setPaxType (const PassengerType_T& iPaxType) {
      _paxType = iPaxType;
    }

    /** Set the party size. */
    void setPartySize (const NbOfSeats_T& iPartySize) {
      _partySize = iPartySize;
    }

    
    // /////////// Display support method /////////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

    /** Display of the structure. */
    const std::string describe() const;

    
  private:
    // /////////////// Attributes /////////////////
    /** Origin. */
    AirportCode_T _origin;

    /** Destination. */
    AirportCode_T _destination;

    /** Departure date. */
    Date_T _departureDate;

    /** Passenger type. */
    PassengerType_T _paxType;

    /** Party size. */
    NbOfSeats_T _partySize;
  };

}
#endif // __STDAIR_BOM_BOOKINGREQUESTSTRUCT_HPP
