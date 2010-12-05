#ifndef __STDAIR_BOM_FLIGHTPERIOD_HPP
#define __STDAIR_BOM_FLIGHTPERIOD_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/FlightPeriodKey.hpp>
#include <stdair/bom/FlightPeriodTypes.hpp>

namespace stdair {

  /** Class representing the actual attributes for an airline flight-period. */
  class FlightPeriod : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;

  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef FlightPeriodKey Key_T;

  public:
    // /////////// Getters ///////////////
    /** Get the flight-period key. */
    const Key_T& getKey () const { return _key; }

    /** Get the parent object. */
    BomAbstract* const getParent() const { return _parent; }
    
    /** Get the flight number (part of the primary key). */
    const FlightNumber_T& getFlightNumber () const {
      return _key.getFlightNumber();
    }

    /** Get the departure period (part of the key). */
    const PeriodStruct& getPeriod () const { return _key.getPeriod(); }

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
    FlightPeriod (const Key_T&);
    FlightPeriod (const FlightPeriod&);
    /** Destructor. */
    ~FlightPeriod();

  protected:
    // Attributes
    Key_T _key;
    BomAbstract* _parent;
    HolderMap_T _holderMap;
  };

}
#endif // __STDAIR_BOM_FLIGHTPERIOD_HPP

