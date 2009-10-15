#ifndef __STDAIR_BOM_LEGCABIN_HPP
#define __STDAIR_BOM_LEGCABIN_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/LegCabinContent.hpp>
#include <stdair/bom/LegCabinTypes.hpp>

namespace stdair {
  // Forward declarations
  class FacBomContent;
  class LegDate;

  /** Class representing the actual functional/business content for a
      leg-date. */
  class LegCabin : public LegCabinContent {
    friend class FacBomContent;

  public:
    // Type definitions
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef LegDate ParentBomContent_T;

    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef LegCabinStructure_T BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef LegCabinKey_T BomKey_T;
    
  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

   /** Get the serialised version of the Business Object. */
    std::string toString() const;
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const;

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const;
    
  private:
    /** Retrieve the BOM structure object. */
    BomStructure_T& getBomStructure () {
      return _legCabinStructure;
    }

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    LegCabin ();
    LegCabin (const LegCabin&);
    LegCabin (BomStructure_T&);

    /** Destructor. */
    virtual ~LegCabin();

  protected:
    // Attributes
    /** Reference structure. */
    BomStructure_T& _legCabinStructure;
  };

}
#endif // __STDAIR_BOM_LEGCABIN_HPP

