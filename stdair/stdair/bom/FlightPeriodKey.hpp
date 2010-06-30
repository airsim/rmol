#ifndef __STDAIR_BOM_FLIGHTPERIODKEY_HPP
#define __STDAIR_BOM_FLIGHTPERIODKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomKey.hpp>
#include <stdair/bom/PeriodStruct.hpp>

namespace stdair {
  /** Key of flight-period. */
  struct FlightPeriodKey_T : public BomKey_T {
    
  private:
    // /////////// Default constructor //////////
    FlightPeriodKey_T ();
  public:
    // /////////// Construction ///////////
    /** Constructors. */
    FlightPeriodKey_T (const FlightNumber_T&, const PeriodStruct_T&);
    FlightPeriodKey_T (const FlightPeriodKey_T&);
    /** Destructor. */
    ~FlightPeriodKey_T ();
    
    // /////////// Getters //////////
    /** Get the flight number. */
    const FlightNumber_T& getFlightNumber() const {
      return _flightNumber;
    }

    /** Get the active days-of-week. */
    const PeriodStruct_T& getPeriod () const {
      return _period;
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
       marketing classes for the same segment-period. */
    const std::string toString() const;
    
  private:
    // Attributes
    /** Flight number. */
    FlightNumber_T _flightNumber;

    /** Period during the departure period. */
    PeriodStruct_T _period;
    
  };

}
#endif // __STDAIR_BOM_FLIGHTPERIODKEY_HPP
