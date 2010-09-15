#ifndef __STDAIR_BOM_SEGMENTPERIOD_HPP
#define __STDAIR_BOM_SEGMENTPERIOD_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/SegmentPeriodKey.hpp>
#include <stdair/bom/SegmentPeriodTypes.hpp>

namespace stdair {

  /** Class representing the actual attributes for an airline segment-period. */
  class SegmentPeriod : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;

  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef SegmentPeriodKey Key_T;

  public:
    // /////////// Getters /////////////
    /** Get the segment-period key. */
    const Key_T& getKey() const { return _key; }

    /** Get the parent object. */
    BomAbstract* const getParent() const { return _parent; }
    
    /** Get the boarding point (part of the primary key). */
    const AirportCode_T& getBoardingPoint () const {
      return _key.getBoardingPoint();
    }

    /** Get the off point (part of the primary key). */
    const AirportCode_T& getOffPoint () const { return _key.getOffPoint(); }

    /** Get the boarding time. */
    const Duration_T& getBoardingTime () const { return _boardingTime; }

    /** Get the off time. */
    const Duration_T& getOffTime () const { return _offTime; }

    /** Get the boarding date offset. */
    const DateOffset_T& getBoardingDateOffset () const {
      return _boardingDateOffset;
    }

    /** Get the off date offset. */
    const DateOffset_T& getOffDateOffset () const { return _offDateOffset; }
    
    /** Get the elapsed time. */
    const Duration_T& getElapsedTime() const { return _elapsedTime; }

    /** Get the cabin booking class map. */
    const CabinBookingClassMap_T& getCabinBookingClassMap () const {
      return _cabinBookingClassMap;
    }

    /** Get the map of children holders. */
    const HolderMap_T& getHolderMap() const { return _holderMap; }

  public:
    // ///////// Setters //////////
    /** Set the boarding time. */
    void setBoardingTime (const Duration_T& iBoardingTime) {
      _boardingTime = iBoardingTime;
    }

    /** Set the off time. */
    void setOffTime (const Duration_T& iOffTime) { _offTime = iOffTime; }

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

    /** Add a pair cabin code and list of class codes within the cabin to the
        cabin booking class map. */
    void addCabinBookingClassList (const CabinCode_T&, 
                                   const ClassList_String_T&);
    
  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const { ioOut << toString(); }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object. */
    std::string toString() const;
    
    /** Get a string describing the  key. */
    const std::string describeKey() const { return _key.toString(); }
    
  protected:
    /** Default constructors. */
    SegmentPeriod (const Key_T&);
    SegmentPeriod (const SegmentPeriod&);
    /** Destructor. */
    ~SegmentPeriod();

  protected:
    // Attributes
    Key_T _key;
    BomAbstract* _parent;
    Duration_T _boardingTime;
    Duration_T _offTime;
    DateOffset_T _boardingDateOffset;
    DateOffset_T _offDateOffset;
    Duration_T _elapsedTime;
    CabinBookingClassMap_T _cabinBookingClassMap;
    HolderMap_T _holderMap;
  };

}
#endif // __STDAIR_BOM_SEGMENTPERIOD_HPP

