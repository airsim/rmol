#ifndef __STDAIR_BOM_FLIGHTDATE_HPP
#define __STDAIR_BOM_FLIGHTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir 
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/FlightDateKey.hpp>
#include <stdair/bom/FlightDateTypes.hpp>

namespace stdair {

  /** Class representing the actual attributes for an airline flight-date. */
  class FlightDate : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;

  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef FlightDateKey Key_T;

  public:
    // /////////// Getters ///////////////
    /** Get the flight-date key. */
    const Key_T& getKey() const { return _key; }

    /** Get the parent object. */
    BomAbstract* const getParent() const { return _parent; }
    
    /** Get the flight number (part of the primary key). */
    const FlightNumber_T& getFlightNumber() const {
      return _key.getFlightNumber();
    }

    /** Get the flight date (part of the primary key). */
    const Date_T& getFlightDate() const { return _key.getFlightDate(); }

    /** Get the map of children holders. */
    const HolderMap_T& getHolderMap() const { return _holderMap; }

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
    FlightDate (const Key_T&);
    FlightDate (const FlightDate&);
    /** Destructor. */
    virtual ~FlightDate();

  protected:
    // Attributes
    Key_T _key;
    BomAbstract* _parent;
    HolderMap_T _holderMap;
  };

}
#endif // __STDAIR_BOM_FLIGHTDATE_HPP

