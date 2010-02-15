#ifndef __STDAIR_BOM_BOOKINGREQUESTSTRUCT_HPP
#define __STDAIR_BOM_BOOKINGREQUESTSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/STDAIR_Types.hpp>
#include <stdair/basic/StructAbstract.hpp>

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
    const Date_T& getPreferedDepartureDate() const {
      return _preferredDepartureDate;
    }

    /** Get the request datetime. */
    const DateTime_T& getRequestDateTime() const {
      return _requestDateTime;
    }

    /** Get the preferred cabin. */
    const CabinCode_T& getPreferredCabin() const {
      return _preferredCabin;
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
    void setPreferredDepartureDate (const Date_T& iDepartureDate) {
      _preferredDepartureDate = iDepartureDate;
    }
    
    /** Set the request datetime */
    void setRequestDateTime (const DateTime_T& iRequestDateTime) {
      _requestDateTime = iRequestDateTime;
    }
    
    /** Set the preferred cabin. */
    void setPreferredCabin (const CabinCode_T& iPreferredCabin) {
      _preferredCabin = iPreferredCabin;
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

    
    // /////////////// Constructors and Destructors /////////////////
  public :
    /** Constructor. */
    BookingRequestStruct (const AirportCode_T&, const AirportCode_T&,
                          const Date_T&, const DateTime_T&,
                          const CabinCode_T&, const NbOfSeats_T&);
  public :
    /** Default constructor. */
    BookingRequestStruct ();
    /** Copy constructor. */
    BookingRequestStruct (const BookingRequestStruct&);
  public:
    /** Destructor. */
    ~BookingRequestStruct();
    

  private:
    // /////////////// Attributes /////////////////
    /** Origin. */
    AirportCode_T _origin;

    /** Destination. */
    AirportCode_T _destination;
    
    /** Departure date. */
    Date_T _preferredDepartureDate;

    /** Request date-time */
    DateTime_T _requestDateTime;

    /** Preferred cabin. */
    CabinCode_T _preferredCabin;

    /** Party size. */
    NbOfSeats_T _partySize;
  };

}
#endif // __STDAIR_BOM_BOOKINGREQUESTSTRUCT_HPP
