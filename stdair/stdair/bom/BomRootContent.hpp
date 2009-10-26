#ifndef __STDAIR_BOM_BOMROOTCONTENT_HPP
#define __STDAIR_BOM_BOMROOTCONTENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/BomRootKey.hpp>

namespace stdair {
  /** Class representing the actual attributes for the Bom root. */
  class BomRootContent : public BomContent {

  public:
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef BomRootKey_T BomKey_T;

  public:
    // /////////// Getters //////////////
    /** Get the BomRoot key. */
    const BomKey_T& getKey() const {
      return _key;
    }

    /** Get the update/creation date for the world schedule data. */
    const Date_T& getUpdateDate() const {
      return _updateDate;
    }

    /** Get the number of generated flight dates. */
    const NbOfFlightDates_T getNumberOfFlightDates() const {
      return _flightDateCounter;
    }

    /** Get the booking counter. */
    const NbOfBookings_T& getBookingCounter () const {
      return _bookingCounter;
    }

    /** Get the total revenue of the whole world schedule. */
    const Revenue_T& getRevenue () const {
      return _worldScheduleRevenue;
    }

    /** Get the world schedule average fare. */
    const Fare_T& getAverageFare() const {
      return _wScheduleAverageFare;
    }

    /** Get the Availability Seat Kilometer for the
        world schedule. */
    const Distance_T& getASK() const {
      return _worldScheduleASK;
    }

    /** Get the yield value for the worldSchedule. */
    const Revenue_T& getYield () const {
      return _worldScheduleYield;
    }

    /** Get the Revenue Passanger Kilometer for the world schedule. */
    const Distance_T& getRPK() const {
      return _worldScheduleRPK;
    }

    /** Get the unit revenue value for the worldSchedule. */
    const Revenue_T& getUnitRevenue () const {
      return _wScheduleUnitRevenue;
    }

    /** Get the load factor value for the world schedule. */
    const Revenue_T& getLoadFactor () const {
      return _wScheduleLoadFactor;
    }

  public:
    // ///////// Setters //////////
    /** Set the update/creation date for the world schdule data. */
    void setUpdateDate (const Date_T& iUpdateDate) {
      _updateDate = iUpdateDate;
    }

    /** Set the revenue amount. */
    void setRevenue (const Revenue_T& iWCRevenue) {
      _worldScheduleRevenue = iWCRevenue;
    }

    /** Set the Revenue Passanger Kilometer. */
    void setRPK (const Distance_T& iWSRPK) {
      _worldScheduleRPK = iWSRPK;
    }

    /** Set the unit revenue. */
    void setUnitRevenue (const Revenue_T& iWSURevenue) {
      _wScheduleUnitRevenue = iWSURevenue;
    }

    /** Set the average fare. */
    void setAverageFare(Fare_T iWSAFare) {
      _wScheduleAverageFare = iWSAFare;
    }

    /** Set the yield. */
    void setYield (const Revenue_T& iWSYield) {
      _worldScheduleYield = iWSYield;
    }

    /** Set the load factor. */
    void setLoadFactor (const Revenue_T& iWSLF) {
      _wScheduleLoadFactor = iWSLF;
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
    BomRootContent ();
    BomRootContent (const BomRootContent&);
    BomRootContent (const BomKey_T& iKey);

    /** Destructor. */
    virtual ~BomRootContent();

  protected:
    // Attributes
    /** The key of both structure and content objects. */
    BomKey_T _key; 

    /** Update/creation date for the World Schedule data. */
    Date_T _updateDate;

    /** Counter of all generated flight dates in the world schedule. */
    NbOfFlightDates_T _flightDateCounter;

    /** Counter of all bookings into the worldSchedule. */
    NbOfBookings_T _bookingCounter;

    /** Total amount of money earn with all flight bookings. */
    Revenue_T _worldScheduleRevenue;

    /** Value of the average fare of the worldcshedule.*/
    Fare_T _wScheduleAverageFare;

    /** Value of the Available Seat Kilometer for the whole worldSchedule.*/
    Distance_T _worldScheduleASK;

    /** Value of the Yield (Revenue/ASK). */
    Revenue_T _worldScheduleYield;

    /** Value of the Revenue Passanger Kilometer for the worldSchedule.*/
    Distance_T _worldScheduleRPK;

    /** Value of the Unit Revenue (Revenue/RPK). */
    Revenue_T _wScheduleUnitRevenue;

    /** Value of the Load Factor (ASK/RPK). */
    Revenue_T _wScheduleLoadFactor;
  };

}
#endif // __STDAIR_BOM_BOMROOTCONTENT_HPP
