#ifndef __STDAIR_BOM_LEGCABINKEY_HPP
#define __STDAIR_BOM_LEGCABINKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomKey.hpp>
#include <stdair/bom/LegDateKey.hpp>

namespace stdair {
  /** Key of leg-cabin. */
  struct LegCabinKey_T : public BomKey_T {
    friend struct BookingClassKey_T;

  public:
    // /////////// Typedefs ////////////
    /** Definition allowing to retrieve the parent key type. */
    typedef LegDateKey_T ParentKey_T;

  private:
    // /////////// Default constructor //////////
    LegCabinKey_T () { };
    
  public:
    // /////////// Construction ///////////
    /** Constructors. */
    LegCabinKey_T (const CabinCode_T& iCabinCode);
    LegCabinKey_T (const LegCabinKey_T&);

    /** Destructor. */
    ~LegCabinKey_T ();
    
    // /////////// Getters //////////
    /** Get the cabin code. */
    const CabinCode_T& getCabinCode () const {
      return _cabinCode;
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
       marketing classes for the same leg-cabin. */
    const std::string toString() const;
    
    /** Display of the key. */
    const std::string describe() const;
    
  private:
    // Attributes
    /** Leg-date Key.*/
    ParentKey_T _parentKey;
    
    /** Cabin code. */
    CabinCode_T _cabinCode;
  };

}
#endif // __STDAIR_BOM_LEGCABINKEY_HPP
