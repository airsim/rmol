#ifndef __STDAIR_BOM_BOMROOTKEY_HPP
#define __STDAIR_BOM_BOMROOTKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomKey.hpp>

namespace stdair {
  /** Key of the BOM structure root. */
  struct BomRootKey_T : public BomKey_T {

  public:
    // /////////// Construction ///////////
    /** Constructor. */
    BomRootKey_T ();
    /** Destructor. */
    ~BomRootKey_T ();
    
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
       marketing classes for the same segment-date. */
    const std::string toString() const;
    
    /** Display of the key. */
    const std::string describe() const;
    
  };

}
#endif // __STDAIR_BOM_BOMROOTKEY_HPP
