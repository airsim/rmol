#ifndef __STDAIR_BOM_YIELDSTORE_HPP
#define __STDAIR_BOM_YIELDSTORE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/YieldStoreContent.hpp>
#include <stdair/bom/YieldStoreTypes.hpp>

namespace stdair {

  // Forward declarations.
  class BomRoot;
  
  /** Class representing the actual functional/business content
      for the Bom root. */
  class YieldStore : public YieldStoreContent {
    friend class FacBomContent;
    
  public:
    // //////////////////////////////////////////////////////////////////
    // See the explanations, within the BomRoot class, for all
    // the types which require to be specified below
    // //////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef YieldStoreStructure_T Structure_T;

    /** Definition allowing to retrieve the associated parent. */
    typedef BomRoot Parent_T;

    /** Definition allowing to retrieve the map/multimap type using by
        BomChildrenHolder. */
    typedef std::map<const MapKey_T, const Structure_T*> Map_T;
    
    /** Define the list of children holder types. */
    typedef boost::fusion::map< > ChildrenHolderMap_T;
    // //////////////////////////////////////////////////////////////////
    
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

    
  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Constructors. */
    YieldStore (const Key_T& iKey, Structure_T& ioStructure);
    /** Destructor. */
    ~YieldStore();
    /** Initialise all the pointers of children holder to NULL. */
    void init();
    /** Default constructors. */
    YieldStore ();
    YieldStore (const YieldStore&);

  private:
    // Attributes
    /** Reference structure. */
    Structure_T& _structure;
  };

}
#endif // __STDAIR_BOM_YIELDSTORE_HPP
