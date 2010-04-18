#ifndef __STDAIR_BOM_IN_HPP
#define __STDAIR_BOM_IN_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
// BOOST Fusion
#include <boost/fusion/include/map.hpp>
// STDAIR 
#include <stdair/bom/InventoryContent.hpp>
#include <stdair/bom/INTypes.hpp>
#include <stdair/bom/FDTypes.hpp>
#include <stdair/bom/NDTypes.hpp>

namespace stdair {

  // Forward declarations.
  class BR;
  class FD;
  class ND;
  
  /** Class representing the actual functional/business content
      for the Bom root. */
  class IN : public InventoryContent {
    friend class FacBomContent;
    
  public:
    // /////////////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated parent. */
    typedef BR Parent_T;
    
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef INStructure_T BomStructure_T;
    
/** Define the list of children holder types. */
    typedef boost::fusion::map<
      boost::fusion::pair<FD, FDHolder_T*>, 
      boost::fusion::pair<ND, NDHolder_T*> > ChildrenHolderTypeMap_T;
    // /////////////////////////////////////////////////////////////////////////
    
  public:
    // /////////// Getters /////////////
    const FDList_T getFDList () const;
    const FDMap_T getFDMap () const;
    const NDList_T getNDList () const;
    const NDMap_T getNDMap () const;
    
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
    IN ();
    IN (const IN&);
    IN (const BomKey_T& iKey, BomStructure_T& ioStructure);
    /** Destructor. */
    virtual ~IN();

  private:
    // Attributes
    /** Reference structure. */
    BomStructure_T& _structure;

  };

}
#endif // __STDAIR_BOM_IN_HPP
