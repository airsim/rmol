#ifndef __STDAIR_BOM_YIELDSTORE_HPP
#define __STDAIR_BOM_YIELDSTORE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
// BOOST Fusion
#include <boost/fusion/include/map.hpp>
// STDAIR 
#include <stdair/bom/YieldStoreContent.hpp>
#include <stdair/bom/YieldStoreTypes.hpp>

namespace stdair {

  // Forward declarations.
  class BR;
  
  /** Class representing the actual functional/business content
      for the Bom root. */
  class YieldStore : public YieldStoreContent {
    friend class FacBomContent;
    
  public:
    // /////////////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated parent. */
    typedef BR Parent_T;
    
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef YieldStoreStructure_T BomStructure_T;
    
    /** Define the list of children holder types. */
    typedef boost::fusion::map< > ChildrenHolderTypeMap_T;
    // /////////////////////////////////////////////////////////////////////////
    
  public:
    // /////////// Getters /////////////

    
  private:     
    /** Retrieve the BOM structure object. */
    BomStructure_T& getStructure () {
      return _structure;
    }

    
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
    const std::string describeKey() const { return _key.toString(); }

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return _key.toString(); }

    
  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    YieldStore ();
    YieldStore (const YieldStore&);
    YieldStore (const BomKey_T& iKey, BomStructure_T& ioStructure);
    /** Destructor. */
    virtual ~YieldStore();

  private:
    // Attributes
    /** Reference structure. */
    BomStructure_T& _structure;
  };

}
#endif // __STDAIR_BOM_YIELDSTORE_HPP
