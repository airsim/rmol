#ifndef __STDAIR_BOM_BOMSTRUCTUREROOTKEY_HPP
#define __STDAIR_BOM_BOMSTRUCTUREROOTKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomKey.hpp>

namespace stdair {

  // Forward declarations
  class BomStructureRoot;

  /** Key of the BOM structure root. */
  class BomStructureRootKey : public BomKey {
    friend class FacBomStructure;
    friend class FacBomContent;
    
  private:
    // Type definitions
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef BomStructureRoot BomStructure_T;

  public:
    // /////////// Construction ///////////
    /** Constructor. */
    BomStructureRootKey () {}

    /** Destructor. */
    ~BomStructureRootKey () {}
    
    
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
    std::string toString() const;

    
  private:
    // Attributes
    // No attributes, as that class corresponds to the root of Bom structure.
  };

}
#endif // __STDAIR_BOM_BOMSTRUCTUREROOTKEY_HPP
