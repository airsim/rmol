#ifndef __STDAIR_BOM_LEGDATEKEY_HPP
#define __STDAIR_BOM_LEGDATEKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomKey.hpp>
#include <stdair/bom/FlightDateKey.hpp>

namespace stdair {
  /** Key of leg-date. */
  struct LegDateKey_T : public BomKey_T {
    friend struct LegCabinKey_T;
 
  public:
    // /////////// Typedefs ////////////
    /** Definition allowing to retrieve the parent key type. */
    typedef FlightDateKey_T ParentKey_T;
    
  private:
    // /////////// Default constructor //////////
    LegDateKey_T () { };
    
  public:
    // /////////// Construction ///////////
    /** Constructors. */
    LegDateKey_T (const AirportCode_T& iBoardPoint);
    LegDateKey_T (const LegDateKey_T&);

    /** Destructor. */
    ~LegDateKey_T ();
    
    // /////////// Getters //////////
    /** Get the boarding point. */
    const AirportCode_T& getBoardPoint() const {
      return _boardPoint;
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
       marketing classes for the same leg-date. */
    const std::string toString() const;
    
    /** Display of the key. */
    const std::string describe() const;
    
  private:
    // Attributes
    /** Flight-date Key.*/
    ParentKey_T _parentKey;
    
    /** Boarding airport. */
    AirportCode_T _boardPoint;
  };

}
#endif // __STDAIR_BOM_LEGDATEKEY_HPP
