#ifndef __STDAIR_BOM_FLIGHTDATECONTENT_HPP
#define __STDAIR_BOM_FLIGHTDATECONTENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/FlightDateKey.hpp>

namespace stdair {

  /** Class representing the actual attributes for an airline flight-date. */
  class FlightDateContent : public BomContent {
  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef FlightDateKey_T BomKey_T;

  public:
    // /////////// Getters ///////////////
    /** Get the flight-date key. */
    const BomKey_T& getKey() const {
      return _key;
    }
    
    /** Get the flight number (part of the primary key). */
    const FlightNumber_T& getFlightNumber() const {
      return _key.getFlightNumber();
    }

    /** Get the flight date (part of the primary key). */
    const Date_T& getFlightDate() const {
      return _key.getFlightDate();
    }
      
    /** Get the booking counter. */
    const NbOfBookings_T& getBookingCounter () const {
      return _bookingCounter;
    }

    /** Get the total flight revenue. */
    const Revenue_T& getRevenue () const {
      return _flightRevenue;
    }

    /** Get the flight average fare. */
    const Fare_T& getAverageFare() const {
      return _flightAverageFare;
    }

    /** Get the Availability Seat Kilometer for this flight. */
    const Distance_T& getASK() const {
      return _flightASK;
    }

    /** Get the yield value for this flight. */
    const Revenue_T& getYield () const {
      return _flightYield;
    }

    /** Get the Revenue Passanger Kilometer for this flight. */
    const Distance_T& getRPK() const {
      return _flightRPK;
    }

    /** Get the unit revenue value for this flight. */
    const Revenue_T& getUnitRevenue () const {
      return _flightUnitRevenue;
    }

    /** Get the load factor value for this flight. */
    const Revenue_T& getLoadFactor () const {
      return _flightLoadFactor;
    }

  public:
    // ///////// Setters //////////
    /** Set the revenue amount. */
    void setRevenue (const Revenue_T& iFlightRevenue) {
      _flightRevenue = iFlightRevenue;
    }

    /** Set the Revenue Passanger Kilometer. */
    void setRPK (const Distance_T& iFlightRPK) {
      _flightRPK = iFlightRPK;
    }

    /** Set the unit revenue. */
    void setUnitRevenue (const Revenue_T& iFlightURevenue) {
      _flightUnitRevenue = iFlightURevenue;
    }

    /** Set the average flight fare. */
    void setAverageFare(Fare_T iFAFare) {
      _flightAverageFare = iFAFare;
    }

    /** Set the yield. */
    void setYield (const Revenue_T& iFlightYield) {
      _flightYield = iFlightYield;
    }

    /** Set the load factor. */
    void setLoadFactor (const Revenue_T& iFlightLF) {
      _flightLoadFactor = iFlightLF;
    }

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    virtual void toStream (std::ostream& ioOut) const = 0;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    virtual void fromStream (std::istream& ioIn) = 0;

   /** Get the serialised version of the Business Object. */
    virtual std::string toString() const = 0;
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    virtual const std::string describeKey() const = 0;

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    virtual const std::string describeShortKey() const = 0;

    
  protected:
    /** Default constructors. */
    FlightDateContent (const BomKey_T&);
    FlightDateContent (const FlightDateContent&);

    /** Destructor. */
    virtual ~FlightDateContent();

  protected:
    // Attributes
    /** The key of both structure and content objects. */
    BomKey_T _key;
    
    /** Counter of all bookings into this flight. */
    NbOfBookings_T _bookingCounter;

    /** Total amount of money earn with flight bookings. */
    Revenue_T _flightRevenue;

    /** Value of the average fare of this flight.*/
    Fare_T _flightAverageFare;

    /** Value of the Available Seat Kilometer for this flight.*/
    Distance_T _flightASK;

    /** Value of the Yield (Revenue/ASK). */
    Revenue_T _flightYield;

    /** Value of the Revenue Passanger Kilometer for this flight.*/
    Distance_T _flightRPK;

    /** Value of the Unit Revenue (Revenue/RPK). */
    Revenue_T _flightUnitRevenue;

    /** Value of the Load Factor (ASK/RPK). */
    Revenue_T _flightLoadFactor;

  };

}
#endif // __STDAIR_BOM_FLIGHTDATECONTENT_HPP

