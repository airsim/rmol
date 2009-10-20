#ifndef __STDAIR_BOM_LEGCABINKEY_HPP
#define __STDAIR_BOM_LEGCABINKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomKey.hpp>

namespace stdair {
  /** Key of leg-cabin. */
  struct LegCabinKey_T : public BomKey_T {

  public:
    // /////////// Construction ///////////
    /** Constructor. */
    LegCabinKey_T (const CabinCode_T& iCabinCode);

    /** Destructor. */
    ~LegCabinKey_T ();
    
    // /////////// Getters //////////
    /** Get the cabin code. */
    const CabinCode_T& getCabinCode () const {
      return _cabinCode;
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
       marketing classes for the same leg-cabin. */
    std::string toString() const;
    
  private:
    // Attributes
    /** Cabin code. */
    CabinCode_T _cabinCode;
  };

}
#endif // __STDAIR_BOM_LEGCABINKEY_HPP
