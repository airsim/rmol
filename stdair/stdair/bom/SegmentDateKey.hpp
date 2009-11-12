#ifndef __STDAIR_BOM_SEGMENTDATEKEY_HPP
#define __STDAIR_BOM_SEGMENTDATEKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomKey.hpp>
#include <stdair/bom/FlightDateKey.hpp>

namespace stdair {
  /** Key of segment-date. */
  struct SegmentDateKey_T : public BomKey_T {
    friend struct SegmentCabinKey_T;
    
  public:
    // /////////// Typedefs ////////////
    /** Definition allowing to retrieve the parent key type. */
    typedef FlightDateKey_T ParentKey_T;

  private:
    // /////////// Default constructor //////////
    SegmentDateKey_T () { };
    
  public:
    // /////////// Construction ///////////
    /** Constructors. */
    SegmentDateKey_T (const AirportCode_T&, const AirportCode_T&);
    SegmentDateKey_T (const SegmentDateKey_T&);

    /** Destructor. */
    ~SegmentDateKey_T ();
    
    // /////////// Getters //////////
    /** Get the boarding point. */
    const AirportCode_T& getBoardPoint() const {
      return _boardPoint;
    }

    /** Get the arrival point. */
    const AirportCode_T& getOffPoint() const {
      return _offPoint;
    }

    // /////////// Setters /////////////
    void setParentKey (const ParentKey_T& iParentKey) {
      _parentKey = iParentKey;
    }
    
    // /////////// Display support methods /////////
    /** Dump a Business Object Key into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Read a Business Object Key from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

   /** Get the serialised version of the Business Object Key.
       <br>That string is unique, at the level of a given Business Object,
       when among children of a given parent Business Object.
       <br>For instance, "H" and "K" allow to differentiate among two
       marketing classes for the same segment-date. */
    const std::string toString() const;
    
    /** Display of the key. */
    const std::string describe() const;

  private:
    // Attributes
    /** Flight-date Key.*/
    ParentKey_T _parentKey;
    
    /** Boarding airport. */
    AirportCode_T _boardPoint;

    /** Arrival airport. */
    AirportCode_T _offPoint;
  };

}
#endif // __STDAIR_BOM_SEGMENTDATEKEY_HPP
