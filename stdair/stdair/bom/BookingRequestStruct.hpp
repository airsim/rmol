#ifndef __STDAIR_BOM_BOOKINGREQUESTSTRUCT_HPP
#define __STDAIR_BOM_BOOKINGREQUESTSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/stdair_demand_types.hpp>
#include <stdair/basic/StructAbstract.hpp>
#include <stdair/bom/BookingRequestTypes.hpp>

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

    /** Get the point-of-sale. */
    const AirportCode_T& getPOS() const {
      return _pos;
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

    /** Get the reservation channel. */
    const ChannelLabel_T& getBookingChannel() const {
      return _channel;
    }

    /** Get the trip type. */
    const TripType_T& getTripType() const {
      return _tripType;
    }

    /** Get the duration of stay. */
    const DayDuration_T& getStayDuration() const {
      return _stayDuration;
    }

    /** Get the frequent flyer type. */
    const FrequentFlyer_T& getFrequentFlyerType() const {
      return _frequentFlyerType;
    }

    /** Get the preferred departure time. */
    const Duration_T& getPreferredDepartureTime() const {
      return _preferredDepartureTime;
    }

    /** Get the willingness-to-pay. */
    const WTP_T& getWTP() const {
      return _wtp;
    }

    /** Get the value of time. */
    const PriceValue_T& getValueOfTime () const {
      return _valueOfTime;
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
                          const AirportCode_T&, const Date_T&, const DateTime_T&,
                          const CabinCode_T&, const NbOfSeats_T&,
                          const ChannelLabel_T&, const TripType_T&,
                          const DayDuration_T&, const FrequentFlyer_T&,
                          const Duration_T&, const WTP_T&, const PriceValue_T&);
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
    const AirportCode_T _origin;

    /** Destination. */
    const AirportCode_T _destination;

    /** Point-Of-Sale. */
    const AirportCode_T _pos;
    
    /** Departure date. */
    const Date_T _preferredDepartureDate;

    /** Request date-time */
    const DateTime_T _requestDateTime;

    /** Preferred cabin. */
    const CabinCode_T _preferredCabin;

    /** Party size. */
    const NbOfSeats_T _partySize;

    /** Booking channel (D=direct, I=indirect, N=oNline, F=oFfline). */
    const ChannelLabel_T _channel;

    /** Trip type (RO=outbound of round-trip, RI=inbound of round-trip, 
        OW=one way). */
    const TripType_T _tripType;

    /** Stay duration (number of days). */
    const DayDuration_T _stayDuration;

    /** Frequent flyer type (P=Platinum, G=Gold, S=Silver, M=Member, N=None). */
    const FrequentFlyer_T _frequentFlyerType;

    /** Preferred departure time. */
    const Duration_T _preferredDepartureTime;
    
    /** Willingness-To-Pay. */
    const WTP_T _wtp;

    /** Value of time. */
    const PriceValue_T _valueOfTime;
  };

}
#endif // __STDAIR_BOM_BOOKINGREQUESTSTRUCT_HPP
