#ifndef __STDAIR_BOM_ND_HPP
#define __STDAIR_BOM_ND_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
// BOOST Fusion
#include <boost/fusion/include/map.hpp>
// STDAIR 
#include <stdair/bom/Structure.hpp>
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/NDKey.hpp>
#include <stdair/bom/NDTypes.hpp>

namespace stdair {
  // Forward declarations.
  class IN;
  class FacBomContent;
  
  /** Class representing the actual functional/business content
      for the Bom root. */
  class ND : public BomContent {
    friend class FacBomContent;
    
  public:
    // /////////////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated parent. */
    typedef IN Parent_T;

    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef NDStructure_T BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef NDKey_T Key_T;
    
    /** Define the list of children holder types. */
    typedef boost::fusion::map< > ChildrenHolderTypeMap_T;
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
    const std::string describeKey() const { return _key.describe(); }

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return _key.describe(); }

    
  public:
    // /////////// Getters /////////////
    const Key_T& getKey () const {
      return _key;
    }
    
  public:
    // //////////// Setters //////////////

  private:     
    /** Retrieve the BOM structure object. */
    BomStructure_T& getStructure () {
      return _structure;
    }
    
  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    ND ();
    ND (const ND&);
    ND (const Key_T& iKey, BomStructure_T& ioStructure);
    /** Destructor. */
    virtual ~ND();

  private:
    // Attributes
    /** Key. */
    Key_T _key;
    
    /** Reference structure. */
    BomStructure_T& _structure;

  };

}
#endif // __STDAIR_BOM_ND_HPP
