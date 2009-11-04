#ifndef __STDAIR_BOM_LEGDATECONTENT_HPP
#define __STDAIR_BOM_LEGDATECONTENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/LegDateKey.hpp>

namespace stdair {

  /** Class representing the actual attributes for an airline leg-date. */
  class LegDateContent : public BomContent {
  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef LegDateKey_T BomKey_T;

  public:
    // /////////// Getters /////////////
    /** Get the leg-date key. */
    const BomKey_T& getKey() const {
      return _key;
    }

    /** Get the board point (part of the primary key). */
    const AirportCode_T& getBoardPoint () const {
      return _key.getBoardPoint();
    }

    /** Get the off point. */
    const AirportCode_T& getOffPoint () const {
      return _offPoint;
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

    /** Get the leg capacity. */
    const CabinCapacity_T& getCapacity () const {
      return _capacity;
    }

    /** Get the Availability Seat Kilometer for this leg. */
    const Distance_T& getASK() const {
      return _legASK;
    }

    /** Get the number of sold seat. */
    const NbOfBookings_T& getSoldSeat () const {
      return _legSoldSeat;
    }

    /** Get the load factor value for this leg. */
    const Revenue_T& getLoadFactor () const {
      return _legLoadFactor;
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
    /** Set the off point. */
    void setOffPoint (const AirportCode_T& iOffPoint) {
      _offPoint = iOffPoint;
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

    /** Set the number of sold seat. */
    void setSoldSeat (const NbOfBookings_T& iLSoldSeat) {
      _legSoldSeat = iLSoldSeat;
    }

    /** Set the elapsed time. */
    void setElapsedTime (const Duration_T&);
    
    /** Method computing the distance of the segment (in kilometers).*/
    void updateDistanceFromElapsedTime ();
    
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
    LegDateContent (const BomKey_T&);
    LegDateContent (const LegDateContent&);

    /** Destructor. */
    virtual ~LegDateContent();

  protected:
    // Attributes
    /** The key of both structure and content objects. */
    BomKey_T _key;
    
    /** Off Point. */
    AirportCode_T _offPoint;

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

    /** Capacity of the leg. */
    CabinCapacity_T _capacity;

    /** Value of the Available Seat Kilometer for this leg.*/
    Distance_T _legASK;

    /** Sold seat into the leg. */
    NbOfBookings_T  _legSoldSeat;
     
    /** Value of the Load Factor (ASK/RPK) or
        (sold seats/ capacity) for the leg level. */
    Revenue_T _legLoadFactor;
  };

}
#endif // __STDAIR_BOM_LEGDATECONTENT_HPP

