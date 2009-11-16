#ifndef __STDAIR_BOM_BOMSTOPCONTENT_HPP
#define __STDAIR_BOM_BOMSTOPCONTENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomContent.hpp>

namespace stdair {
  // Forward declarations.
  class BomStopStructure;
  class BomKey;

  /** Class representing the actual functional/business content
      for the Bom stop.
      <br>That class is just an utility tool to mark the stop
      of the Bom tree. */
  class BomStopContent : public BomContent {
    friend class FacBomContent;

  public:
    // Type definitions
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef BomStopStructure BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef BomKey BomKey_T;

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const { ioOut << toString(); }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object. */
    std::string toString() const { return describeKey(); }
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const { return std::string (""); }

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return std::string (""); }

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    BomStopContent ();
    BomStopContent (const BomStopContent&);
    BomStopContent (const BomStructure_T& iBomStructure)
      : _bomStructure (iBomStructure) { }

    /** Destructor. */
    virtual ~BomStopContent() { }

  private:
    // Attributes
    /** Reference structure. */
    const BomStructure_T& _bomStructure;
  };

}
#endif // __STDAIR_BOM_BOMSTOPCONTENT_HPP
