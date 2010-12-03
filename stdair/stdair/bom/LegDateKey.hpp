#ifndef __STDAIR_BOM_LEGDATEKEY_HPP
#define __STDAIR_BOM_LEGDATEKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/bom/KeyAbstract.hpp>

namespace stdair {
  /** Key of leg-date. */
  struct LegDateKey : public KeyAbstract {
    
  private:
    // /////////// Default constructor //////////
    LegDateKey () { };
  public:
    // /////////// Construction ///////////
    /** Constructors. */
    LegDateKey (const AirportCode_T& iBoardingPoint);
    LegDateKey (const LegDateKey&);
    /** Destructor. */
    ~LegDateKey ();
    
    // /////////// Getters //////////
    /** Get the boarding point. */
    const AirportCode_T& getBoardingPoint() const {
      return _boardingPoint;
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
    
  private:
    // Attributes
    /** Boardinging airport. */
    AirportCode_T _boardingPoint;
  };

}
#endif // __STDAIR_BOM_LEGDATEKEY_HPP
