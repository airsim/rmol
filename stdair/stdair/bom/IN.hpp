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
#include <stdair/bom/INKey.hpp>
#include <stdair/bom/INTypes.hpp>
#include <stdair/bom/FDTypes.hpp>
#include <stdair/bom/NDTypes.hpp>
#include <stdair/bom/FD.hpp>
#include <stdair/bom/ND.hpp>
#include <stdair/bom/BomList.hpp>

namespace stdair {
  // Forward declarations.
  class BR;
  class FacBomContent;
  
  /** Class representing the actual functional/business content
      for the Bom root. */
  class IN : public BomContent {
    friend class FacBomContent;
    
  public:
    // /////////////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated parent. */
    typedef BR Parent_T;
    
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef INStructure_T BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef INKey_T Key_T;
    
/** Define the list of children holder types. */
    typedef boost::fusion::map<
      boost::fusion::pair<FD, FDHolder_T*>, 
      boost::fusion::pair<ND, NDHolder_T*> > ChildrenHolderTypeMap_T;
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

    const FDList_T getFDList () const {
      return _structure.getChildrenHolder<FD> ();
    }

    const NDList_T getNDList () const {
      return _structure.getChildrenHolder<ND> ();
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
    IN ();
    IN (const IN&);
    IN (const Key_T& iKey, BomStructure_T& ioStructure) 
      : _key (iKey), _structure (ioStructure) { }
    /** Destructor. */
    virtual ~IN() { }

  private:
    // Attributes
    /** Key. */
    Key_T _key;
    
    /** Reference structure. */
    BomStructure_T& _structure;

  };

}
#endif // __STDAIR_BOM_IN_HPP
