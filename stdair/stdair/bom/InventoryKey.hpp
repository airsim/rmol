#ifndef __STDAIR_BOM_INVENTORYKEY_HPP
#define __STDAIR_BOM_INVENTORYKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomKey.hpp>

namespace stdair {

  // Forward declarations
  template<typename BOM_CONTENT> class Inventory;

  /** Key of flight-date. */
  template <typename BOM_CONTENT>
  class InventoryKey : public BomKey {
    friend class FacBomStructure;
    friend class FacBomContent;
    
  private:
    // Type definitions
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef Inventory<BOM_CONTENT> BomStructure_T;

  public:
    // /////////// Construction ///////////
    /** Constructor. */
    InventoryKey (const AirlineCode_T& iAirlineCode)
      : _airlineCode (iAirlineCode) {
    }

    /** Destructor. */
    ~InventoryKey () { }
    
    // /////////// Getters //////////
    /** Get the airline code. */
    const AirlineCode_T& getAirlineCode() const {
      return _airlineCode;
    }

    // /////////// Display support methods /////////
    /** Dump a Business Object Key into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const {
      ioOut << "InventoryKey: " << toString() << std::endl;
    }
    
    /** Read a Business Object Key from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }
    
   /** Get the serialised version of the Business Object Key.
       <br>That string is unique, at the level of a given Business Object,
       when among children of a given parent Business Object.
       <br>For instance, "H" and "K" allow to differentiate among two
       marketing classes for the same segment-date. */
    std::string toString() const {
      std::ostringstream oStr;
      oStr << _airlineCode;
      return oStr.str();
    }
    
  private:
    // Attributes
    /** Airline code. */
    AirlineCode_T _airlineCode;
  };

}
#endif // __STDAIR_BOM_INVENTORYKEY_HPP
