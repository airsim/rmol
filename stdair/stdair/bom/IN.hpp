#ifndef __STDAIR_BOM_IN_HPP
#define __STDAIR_BOM_IN_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
// STDAIR 
#include <stdair/bom/Structure.hpp>
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/INTypes.hpp>
#include <stdair/bom/INKey.hpp>

namespace stdair {
  // Forward declarations.
  class FacBomContent;
  
  /** Class representing the actual functional/business content
      for the Bom root. */
  class IN : public BomContent {
    friend class FacBomContent;
    
  public:
    // /////////////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef INStructure_T Structure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef INKey_T Key_T;
    
    // /////////////////////////////////////////////////////////////////////////

    
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

    
  public:
    // /////////// Getters /////////////

    
  public:
    // //////////// Setters //////////////

  private:     
    /** Retrieve the BOM structure object. */
    Structure_T& getStructure () {
      return _structure;
    }
    
  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    IN ();
    IN (const IN&);
    IN (const Key_T&, Structure_T&);
    /** Destructor. */
    virtual ~IN();

  private:
    // Attributes
    /** Key. */
    Key_T _key;
    
    /** Reference structure. */
    Structure_T& _structure;

  };

}
#endif // __STDAIR_BOM_IN_HPP
