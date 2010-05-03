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
    typedef FlightDateKey_T Key_T;

  public:
    // /////////// Getters ///////////////
    /** Get the flight-date key. */
    const Key_T& getKey() const {
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
    FlightDateContent (const Key_T&);
    FlightDateContent (const FlightDateContent&);
    /** Destructor. */
    virtual ~FlightDateContent();

  protected:
    // Attributes
    /** The key of both structure and content objects. */
    Key_T _key;
  };

}
#endif // __STDAIR_BOM_FLIGHTDATECONTENT_HPP

