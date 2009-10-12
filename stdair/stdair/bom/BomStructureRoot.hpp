#ifndef __STDAIR_BOM_BOMSTRUCTUREROOT_HPP
#define __STDAIR_BOM_BOMSTRUCTUREROOT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomStructure.hpp>
#include <stdair/bom/BomStructureRootKey.hpp>
#include <stdair/bom/BomChildrenHolderImp.hpp>
// MPL
#include <boost/mpl/vector.hpp>

namespace stdair {
  // Forward declarations.
  template <typename BOM_CONTENT> class InventoryStructure;
  class BomStructureDummy;
  class BomContentDummy;

  /** Wrapper class aimed at holding the actual content, modeled
      by a specific BomContentRoot class. */
  template <typename BOM_CONTENT>
  class BomStructureRoot : public BomStructure {
    friend class FacBomStructure;
    friend class FacBomContent;

    // Type definitions
    /** Definition allowing to retrieve the associated BOM content type. */
    typedef BOM_CONTENT Content_T;

    /** Definition allowing to retrieve the  children type of the
        BOM_CONTENT. */
    typedef typename BOM_CONTENT::ContentChild_T ContentChild_T;
    
  private:
    // Type definitions
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef BomStructureRootKey<BOM_CONTENT> BomKey_T;

    /** Definition allowing to retrieve the associated children type. */
    typedef boost::mpl::vector<InventoryStructure<ContentChild_T>, BomStructureDummy> ChildrenBomTypeList_T;

    /** Definition allowing to retrive the default children bom holder type. */
    typedef BomChildrenHolderImp<BomContentDummy> DefaultChildrenBomHolder_T;
    
    /** Definition allowing to retrive the  children bom holder type. */
    typedef BomChildrenHolderImp<ContentChild_T> ChildrenBomHolder_T;

  public:
     /** Define the iterators of the inventory list. */
    typedef typename ChildrenBomHolder_T::ListIterator_T InventoryListIterator_T;
    typedef typename ChildrenBomHolder_T::ListReverseIterator_T InventoryListReverseIterator_T;

    /** Define the iterators of the inventory map. */
    typedef typename ChildrenBomHolder_T::MapIterator_T InventoryMapIterator_T;
    typedef typename ChildrenBomHolder_T::MapReverseIterator_T InventoryMapReverseIterator_T;

  public:

    // /////////// Getters /////////////
    /** Get the BomStructureRoot key. */
    const BomKey_T& getKey() const {
      return _key;
    }
    
    /** Get the list of inventories. */
    const ChildrenBomHolder_T& getChildrenList() const {
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
    const std::string describeKey() const { return _key.toString(); }

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return _key.toString(); }

    public:
    // /////////// Iteration methods //////////
    /** Initialise the internal iterator on inventory:
        return the iterator at the begining of the list. */
    InventoryListIterator_T inventoryListBegin () const {
      assert (_childrenList != NULL);
      return _childrenList->listBegin ();
    }
    
    /** Initialise the internal iterator on inventory:
        return the iterator at the end of the list. */
    InventoryListIterator_T inventoryListEnd () const {
      assert (_childrenList != NULL);
      return _childrenList->listEnd ();
    }
    
    /** Initialise the internal reverse iterator on inventory:
        return the reverse iterator at the rbegining of the list. */
    InventoryListReverseIterator_T inventoryListRBegin () const {
      assert (_childrenList != NULL);
      return _childrenList->listRBegin ();
    }
    
    /** Initialise the internal reverse iterator on inventory:
        return the reverse iterator at the rend of the list. */
    InventoryListReverseIterator_T inventoryListREnd () const {
      assert (_childrenList != NULL);
      return _childrenList->listREnd ();
    }

    /** Initialise the internal iterator on inventory:
        return the iterator at the begining of the map. */
    InventoryMapIterator_T inventoryMapBegin () const {
      assert (_childrenList != NULL);
      return _childrenList->mapBegin ();
    }
    
    /** Initialise the internal iterator on inventory:
        return the iterator at the end of the map. */
    InventoryMapIterator_T inventoryMapEnd () const {
      assert (_childrenList != NULL);
      return _childrenList->mapEnd ();
    }
    
    /** Initialise the internal reverse iterator on inventory:
        return the reverse iterator at the rbegining of the map. */
    InventoryMapReverseIterator_T inventoryMapRBegin () const {
      assert (_childrenList != NULL);
      return _childrenList->mapRBegin ();
    }
    
    /** Initialise the internal reverse iterator on inventory:
        return the reverse iterator at the rend of the map. */
    InventoryMapReverseIterator_T inventoryMapREnd () const {
      assert (_childrenList != NULL);
      return _childrenList->mapREnd ();
    }

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    BomStructureRoot ();
    BomStructureRoot (const BomStructureRoot&);
    BomStructureRoot (const BomKey_T& iKey) { _key = iKey; }

    /** Destructor. */
    ~BomStructureRoot () { }

  private:
    // Attributes
    /** The key of both the structure and content objects. */
    BomKey_T _key; 

    /** The actual functional (Business Object) content. */
    BOM_CONTENT* _content;

    /** List of inventories. */
    ChildrenBomHolder_T* _childrenList;
  };

}
#endif // __STDAIR_BOM_BOMSTRUCTUREROOT_HPP

