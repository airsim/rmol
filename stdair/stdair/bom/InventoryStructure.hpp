#ifndef __STDAIR_BOM_INVENTORYSTRUCTURE_HPP
#define __STDAIR_BOM_INVENTORYSTRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// (Boost) MPL
#include <boost/mpl/vector.hpp>
// STDAIR 
#include <stdair/bom/BomStructureDummy.hpp>
#include <stdair/bom/BomContentDummy.hpp>
#include <stdair/bom/FlightDateStructure.hpp>

namespace stdair {
  /** Wrapper class aimed at holding the actual content, modeled
      by an external specific Inventory class (for instance,
      in the AIRSCHED library). */
  template <class BOM_CONTENT>
  class InventoryStructure : public BomStructure {
    friend class FacBomStructure;
    friend class FacBomContent;
    friend class BomStructure;

  public:
    // Type definitions
    /** Definition allowing to retrieve the associated BOM content type. */
    typedef BOM_CONTENT Content_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef typename BOM_CONTENT::BomKey_T BomKey_T;

    /** Definition allowing to retrieve the  children type of the
        BOM_CONTENT. */
    typedef typename BOM_CONTENT::ContentChild_T ContentChild_T;

    /** Definition allowing to retrieve the associated parent
        BOM structure type. */
    typedef typename BOM_CONTENT::Parent_T::BomStructure_T ParentBomStructure_T;

    /** Definition allowing to retrieve the associated children type. */
    typedef boost::mpl::vector<FlightDateStructure<ContentChild_T>,
                               BomStructureDummy> ChildrenBomTypeList_T;

    /** Define the default children bom holder type. */
    typedef BomChildrenHolderImp<BomContentDummy> DefaultChildrenBomHolder_T;

    /** Define the  children bom holder type. */
    typedef BomChildrenHolderImp<ContentChild_T> ChildrenBomHolder_T;

  public:
    // /////////// Getters /////////////
    /** Get the (parent) BomStructureRoot object. */
    ParentBomStructure_T* getBomStructureRootPtr() const {
      return _parent;
    }
    
    /** Get the (parent) BomStructureRoot object. */
    ParentBomStructure_T& getBomStructureRoot() const {
      assert (_parent != NULL);
      return *_parent;
    }
    
    /** Get the inventory key. */
    const BomKey_T& getKey() const {
      assert (_content != NULL);
      return _content->getKey ();
    }

    /** Get the list of flight-dates. */
    const ChildrenBomHolder_T& getChildrenList() const {
      assert (_childrenList != NULL);
      return *_childrenList;
    }

     /** Get the list of flight-dates. */
    void getChildrenList (ChildrenBomHolder_T*& ioChildrenList) {
      ioChildrenList = _childrenList;
    }
    
  private:
    // /////////// Setters /////////////
    /** Set the (parent) Inventory object. */
    void setBomStructureRoot (ParentBomStructure_T& ioParent) {
      _parent = &ioParent;
    }

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
    InventoryStructure () : _parent (NULL), _content (NULL),
                            _childrenList (NULL) { }

    InventoryStructure (const InventoryStructure&);
    /** Destructor. */
    virtual ~InventoryStructure() { }

  private:
    // Attributes
    /** Parent root. */
    ParentBomStructure_T* _parent;
    
    /** The actual functional (Business Object) content. */
    BOM_CONTENT* _content;

    /** List of flight-dates. */
    ChildrenBomHolder_T* _childrenList;
  };

}
#endif // __STDAIR_BOM_INVENTORYSTRUCTURE_HPP

