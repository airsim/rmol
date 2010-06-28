#ifndef __STDAIR_BOM_SEGMENTPERIODCONTENT_HPP
#define __STDAIR_BOM_SEGMENTPERIODCONTENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/SegmentPeriodKey.hpp>

namespace stdair {

  /** Class representing the actual attributes for an airline segment-period. */
  class SegmentPeriodContent : public BomContent {
  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef SegmentPeriodKey_T Key_T;

  public:
    // /////////// Getters /////////////
    /** Get the segment-period key. */
    const Key_T& getKey() const {
      return _key;
    }
    
    /** Get the boarding point (part of the primary key). */
    const AirportCode_T& getBoardingPoint () const {
      return _key.getBoardingPoint();
    }

    /** Get the off point (part of the primary key). */
    const AirportCode_T& getOffPoint () const {
      return _key.getOffPoint();
    }

    /** Get the boarding time. */
    const Duration_T& getBoardingTime () const {
      return _boardingTime;
    }

    /** Get the off time. */
    const Duration_T& getOffTime () const {
      return _offTime;
    }

    /** Get the boarding date offset. */
    const DateOffset_T& getBoardingDateOffset () const {
      return _boardingDateOffset;
    }

    /** Get the off date offset. */
    const DateOffset_T& getOffDateOffset () const {
      return _offDateOffset;
    }
    
    /** Get the elapsed time. */
    const Duration_T& getElapsedTime() const {
      return _elapsedTime;
    }

  public:
    // ///////// Setters //////////
    /** Set the boarding time. */
    void setBoardingTime (const Duration_T& iBoardingTime) {
      _boardingTime = iBoardingTime;
    }

    /** Set the off time. */
    void setOffTime (const Duration_T& iOffTime) {
      _offTime = iOffTime;
    }

    /** Set the boarding date offset. */
    void setBoardingDateOffset (const DateOffset_T& iDateOffset) {
      _boardingDateOffset = iDateOffset;
    }

    /** Set the off date offset. */
    void setOffDateOffset (const DateOffset_T& iDateOffset) {
      _offDateOffset = iDateOffset;
    }

    /** Set the elapsed time. */
    void setElapsedTime (const Duration_T& iElapsedTime) {
      _elapsedTime = iElapsedTime;
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

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return _key.toString(); }

    
  protected:
    /** Default constructors. */
    SegmentPeriodContent (const Key_T&);
    SegmentPeriodContent (const SegmentPeriodContent&);
    /** Destructor. */
    ~SegmentPeriodContent();

  protected:
    // Attributes
    Key_T _key;
    Duration_T _boardingTime;
    Duration_T _offTime;
    DateOffset_T _boardingDateOffset;
    DateOffset_T _offDateOffset;
    Duration_T _elapsedTime;
  };

}
#endif // __STDAIR_BOM_SEGMENTPERIODCONTENT_HPP

