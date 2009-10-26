#ifndef __STDAIR_BOM_BOMROOTSTRUCTURE_HPP
#define __STDAIR_BOM_BOMROOTSTRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// MPL
#include <boost/mpl/vector.hpp>
// STDAIR 
#include <stdair/bom/BomStructureDummy.hpp>
#include <stdair/bom/BomContentDummy.hpp>
#include <stdair/bom/InventoryStructure.hpp>

namespace stdair {
  /** Wrapper class aimed at holding the actual content, modeled
      by a specific BomContentRoot class. */
  template <typename BOM_CONTENT>
  class BomRootStructure : public BomStructure {
    friend class FacBomStructure;
    friend class FacBomContent;
    friend class BomStructure;

  public:
    // Type definitions
    /** Definition allowing to retrieve the associated BOM content type. */
    typedef BOM_CONTENT Content_T;

    /** Definition allowing to retrieve the  children type of the
        BOM_CONTENT. */
    typedef typename BOM_CONTENT::ContentChild_T ContentChild_T;
    
  private:
    // Type definitions
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef typename BOM_CONTENT::BomKey_T BomKey_T;

    /** Definition allowing to retrieve the associated children type. */
    typedef boost::mpl::vector<InventoryStructure<ContentChild_T>, BomStructureDummy> ChildrenBomTypeList_T;

    /** Definition allowing to retrive the default children bom holder type. */
    typedef BomChildrenHolderImp<BomContentDummy> DefaultChildrenBomHolder_T;
    
    /** Definition allowing to retrive the  children bom holder type. */
    typedef BomChildrenHolderImp<ContentChild_T> ChildrenBomHolder_T;

  public:
    // /////////// Getters /////////////
    /** Get the BomRootStructure key. */
    const BomKey_T& getKey () const {
      assert (_content != NULL);
      return _content->getKey ();
    }
    
    /** Get the list of inventories. */
    const ChildrenBomHolder_T& getChildrenList() const {
      assert (_childrenList != NULL);
      return *_childrenList;
    }

    /** Get the list of inventories. */
    void getChildrenList (ChildrenBomHolder_T*& ioChildrenList) {
      ioChildrenList = _childrenList;
    }

  private: 
    /////////////// Setters ////////////////
    /** Default children list setter. */
    void setChildrenList (DefaultChildrenBomHolder_T&) { }
    
    /** Set the  children list. */
    void setChildrenList (ChildrenBomHolder_T& ioChildrenList) {
      _childrenList = &ioChildrenList;
    }

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const {
      ioOut << toString() << std::endl;
    }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object. */
    std::string toString() const { return describeKey(); }
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const { return getKey().toString(); }

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return getKey().toString(); }

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    BomRootStructure () : _content (NULL), _childrenList (NULL) { };
    BomRootStructure (const BomRootStructure&);

    /** Destructor. */
    ~BomRootStructure () { }

  private:
    // Attributes
    /** The actual functional (Business Object) content. */
    BOM_CONTENT* _content;

    /** List of inventories. */
    ChildrenBomHolder_T* _childrenList;
  };

}
#endif // __STDAIR_BOM_BOMROOTSTRUCTURE_HPP

