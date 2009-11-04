#ifndef __STDAIR_BOM_SEGMENTDATECONTENT_HPP
#define __STDAIR_BOM_SEGMENTDATECONTENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/SegmentDateKey.hpp>

namespace stdair {

  /** Class representing the actual attributes for an airline segment-date. */
  class SegmentDateContent : public BomContent {
  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef SegmentDateKey_T BomKey_T;

  public:
    // /////////// Getters /////////////
    /** Get the segment-date key. */
    const BomKey_T& getKey() const {
      return _key;
    }
    
    /** Get the board point (part of the primary key). */
    const AirportCode_T& getBoardPoint () const {
      return _key.getBoardPoint();
    }

    /** Get the off point (part of the primary key). */
    const AirportCode_T& getOffPoint () const {
      return _key.getOffPoint();
    }

    /** Get the booking counter. */
    const NbOfBookings_T& getBookingCounter() const {
      return _bookingCounter;
    }

    /** Get the total segment revenue. */
    const Revenue_T& getRevenue () const {
      return _segmentRevenue;
    }

    /** Get the segment average fare. */
    const Fare_T& getAverageFare() const {
      return _segmentAverageFare;
    }

    /** Get the unit revenue value for this segment. */
    const Revenue_T& getUnitRevenue () const {
      return _segmentUnitRevenue;
    }

    /** Get the Revenue Passanger Kilometer for this segment. */
    const Distance_T& getRPK() const {
      return _segmentRPK;
    }

    /** Get the board date. */
    const Date_T& getBoardDate () const {
      return _boardDate;
    }

    /** Get the board time. */
    const Duration_T& getBoardTime () const {
      return _boardTime;
    }

    /** Get the off date. */
    const Date_T& getOffDate () const {
      return _offDate;
    }

    /** Get the off time. */
    const Duration_T& getOffTime () const {
      return _offTime;
    }

    /** Get the elapsed time. */
    const Duration_T& getElapsedTime() const {
      return _elapsedTime;
    }

    /** Get the distance. */
    const Distance_T& getDistance() const {
      return _distance;
    }

    /** Get the date off set (off date - board date). */
    const DateOffSet_T getDateOffSet () const {
      return _offDate - _boardDate;
    }

    /** Get the time off set between board and off points.
        <br>It is defined as being:
        TimeOffSet = (OffTime - BoardTime) + (OffDate - BoardDate) * 24
        - ElapsedTime. */
    const Duration_T getTimeOffSet() const;

  public:
    // ///////// Setters //////////
    /** Set the revenue amount. */
    void setRevenue (const Revenue_T& iSegmentRevenue) {
      _segmentRevenue = iSegmentRevenue;
    }

    /** Set the board date. */
    void setBoardDate (const Date_T& iBoardDate) {
      _boardDate = iBoardDate;
    }

    /** Set the board time. */
    void setBoardTime (const Duration_T& iBoardTime) {
      _boardTime = iBoardTime;
    }

    /** Set the off date. */
    void setOffDate (const Date_T& iOffDate) {
      _offDate = iOffDate;
    }

    /** Set the off time. */
    void setOffTime (const Duration_T& iOffTime) {
      _offTime = iOffTime;
    }

    /** Set the elapsed time. */
    void setElapsedTime (const Duration_T& iElapsedTime) {
      _elapsedTime = iElapsedTime;
    }

    /** Set the total number of bookings. */
    void setBookingCounter (const NbOfBookings_T& iBookCounter) {
      _bookingCounter = iBookCounter;
    }

    /** Set the average segment fare. */
    void setAverageSegmentFare(Fare_T iSAFare) {
      _segmentAverageFare = iSAFare;
    }

    /** Set the Revenue Passanger Kilometer. */
    void setRPK (const Distance_T& iSegmentRPK) {
      _segmentRPK = iSegmentRPK;
    }
      
    /** Set the Unit Revenue. */
    void setUnitRevenue (const Revenue_T& iSegmentURevenue) {
      _segmentUnitRevenue = iSegmentURevenue;
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
    SegmentDateContent (const BomKey_T&);
    SegmentDateContent (const SegmentDateContent&);

    /** Destructor. */
    virtual ~SegmentDateContent();

  protected:
    // Attributes
    /** The key of both structure and content objects. */
    BomKey_T _key;
    
    /** Counter of all bookings into this segment. */
    NbOfBookings_T _bookingCounter;

    /** Total amount of money earn with segment bookings. */
    Revenue_T _segmentRevenue;

    /** Value of the average fare of this segment date.*/
    Fare_T _segmentAverageFare;

    /** Value of the Unit Revenue (Revenue/ASK). */
    Revenue_T _segmentUnitRevenue;

    /** Value of the Revenue Passanger Kilometer for this segment date.*/
    Distance_T _segmentRPK;

    /** Board Date. */
    Date_T _boardDate;

    /** Board Time. */
    Duration_T _boardTime;

    /** Off Date. */
    Date_T _offDate;

    /** Off Time. */
    Duration_T _offTime;

    /** Elapsed Time. */
    Duration_T _elapsedTime;

    /** Distance. */
    Distance_T _distance;

  };

}
#endif // __STDAIR_BOM_SEGMENTDATECONTENT_HPP

