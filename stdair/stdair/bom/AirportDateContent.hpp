#ifndef __STDAIR_BOM_AIRPORTDATECONTENT_HPP
#define __STDAIR_BOM_AIRPORTDATECONTENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/AirportDateKey.hpp>

namespace stdair {

  /** Class representing the actual attributes for an airport-date. */
  class AirportDateContent : public BomContent {
  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef AirportDateKey_T BomKey_T;

  public:
    // /////////// Getters /////////////
    /** Get the airport-date key. */
    const BomKey_T& getKey() const {
      return _key;
    }
    
    /** Get the (origin) airport (part of the primary key). */
    const AirportCode_T& getOrigin() const {
      return _key.getBoardingPoint();
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
    AirportDateContent (const BomKey_T&);
    AirportDateContent (const AirportDateContent&);

    /** Destructor. */
    virtual ~AirportDateContent();

  protected:
    // Attributes
    /** The key of both structure and content objects. */
    BomKey_T _key;
    
  };

}
#endif // __STDAIR_BOM_AIRPORTDATECONTENT_HPP

