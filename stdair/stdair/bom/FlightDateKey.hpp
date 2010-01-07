#ifndef __STDAIR_BOM_FLIGHTDATEKEY_HPP
#define __STDAIR_BOM_FLIGHTDATEKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomKey.hpp>
#include <stdair/bom/InventoryKey.hpp>

namespace stdair {
  /** Key of flight-date. */
  struct FlightDateKey_T : public BomKey_T {
    friend struct SegmentDateKey_T;
    friend struct LegDateKey_T;

  public:
    // /////////// Typedefs ////////////
    /** Definition allowing to retrieve the parent key type. */
    typedef InventoryKey_T ParentKey_T;
    
  private:
    // /////////// Default constructor //////////
    FlightDateKey_T () { };
    
  public:
    // /////////// Construction ///////////
    /** Constructors. */
    FlightDateKey_T (const FlightNumber_T&, const Date_T&);
    FlightDateKey_T (const FlightDateKey_T&);

    /** Destructor. */
    ~FlightDateKey_T ();
    
    // /////////// Getters //////////
    /** Get the flight number. */
    const FlightNumber_T& getFlightNumber() const {
      return _flightNumber;
    }

    /** Get the departure date of the (first leg of the) flight. */
    const Date_T& getFlightDate() const {
      return _flightDate;
    }

    /** Get the airline code of the flight-date. */
    const AirlineCode_T& getAirlineCode () const {
      return _parentKey.getAirlineCode();
    }
    
    // /////////// Setters /////////////
    /** Set the parent key. */
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
    /** Inventory Key.*/
    ParentKey_T _parentKey;
    
    /** Flight number. */
    FlightNumber_T _flightNumber;

    /** Departure date of the (first leg of the) flight. */
    Date_T _flightDate;
  };

}
#endif // __STDAIR_BOM_FLIGHTDATEKEY_HPP
