#ifndef __STDAIR_BOM_LEGDATEKEY_HPP
#define __STDAIR_BOM_LEGDATEKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomKey.hpp>

namespace stdair {
  /** Key of leg-date. */
  struct LegDateKey_T : public BomKey_T {

  public:
    // /////////// Construction ///////////
    /** Constructor. */
    LegDateKey_T (const AirportCode_T& iBoardPoint);

    /** Destructor. */
    ~LegDateKey_T ();
    
    // /////////// Getters //////////
    /** Get the boarding point. */
    const AirportCode_T& getBoardPoint() const {
      return _boardPoint;
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
    std::string toString() const;
    
  private:
    // Attributes
    /** Boarding airport. */
    AirportCode_T _boardPoint;
  };

}
#endif // __STDAIR_BOM_LEGDATEKEY_HPP
