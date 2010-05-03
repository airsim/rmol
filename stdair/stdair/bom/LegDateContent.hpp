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
    typedef LegDateKey_T Key_T;

  public:
    // /////////// Getters /////////////
    /** Get the leg-date key. */
    const Key_T& getKey() const {
      return _key;
    }

    /** Get the boarding point (part of the primary key). */
    const AirportCode_T& getBoardingPoint () const {
      return _key.getBoardingPoint();
    }

    /** Get the off point. */
    const AirportCode_T& getOffPoint () const {
      return _offPoint;
    }

    /** Get the boarding date. */
    const Date_T& getBoardingDate () const {
      return _boardingDate;
    }

    /** Get the boarding time. */
    const Duration_T& getBoardingTime () const {
      return _boardingTime;
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

    /** Get the date off set (off date - boarding date). */
    const DateOffSet_T getDateOffSet () const {
      return _offDate - _boardingDate;
    }

    /** Get the time off set between boarding and off points.
        <br>It is defined as being:
        TimeOffSet = (OffTime - BoardingTime) + (OffDate - BoardingDate) * 24
        - ElapsedTime. */
    const Duration_T getTimeOffSet() const;

  public:
    // ///////// Setters //////////
    /** Set the off point. */
    void setOffPoint (const AirportCode_T& iOffPoint) {
      _offPoint = iOffPoint;
    }

    /** Set the boarding date. */
    void setBoardingDate (const Date_T& iBoardingDate) {
      _boardingDate = iBoardingDate;
    }

    /** Set the boarding time. */
    void setBoardingTime (const Duration_T& iBoardingTime) {
      _boardingTime = iBoardingTime;
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

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return _key.toString(); }

  protected:
    /** Default constructors. */
    LegDateContent (const Key_T&);
    LegDateContent (const LegDateContent&);
    /** Destructor. */
    ~LegDateContent();

  protected:
    // Attributes
    /** The key of both structure and content objects. */
    Key_T _key;
    
    /** Off Point. */
    AirportCode_T _offPoint;

    /** Boarding Date. */
    Date_T _boardingDate;

    /** Boarding Time. */
    Duration_T _boardingTime;

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
  };

}
#endif // __STDAIR_BOM_LEGDATECONTENT_HPP

