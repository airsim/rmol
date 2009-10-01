#ifndef __STDAIR_BOM_INVENTORY_HPP
#define __STDAIR_BOM_INVENTORY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// (Boost) MPL
#include <boost/mpl/vector.hpp>
// STDAIR 
#include <stdair/bom/BomStructure.hpp>
#include <stdair/bom/InventoryKey.hpp>
#include <stdair/bom/BomChildrenHolderImp.hpp>
#include <stdair/bom/BomIterator.hpp>
#include <stdair/bom/FlightDate.hpp>

namespace stdair {

  // Forward declaration
  template <typename BOM_CONTENT> class BomStructureRoot;
  class BomStructureDummy;
  class BomContentDummy;
  
  /** Wrapper class aimed at holding the actual content, modeled
      by an external specific Inventory class (for instance,
      in the AIRSCHED library). */
  template <class BOM_CONTENT>
  class Inventory : public BomStructure {
    friend class FacBomStructure;
    friend class FacBomContent;

  public:
    // Type definitions
    /** Definition allowing to retrieve the associated BOM content type. */
    typedef BOM_CONTENT Content_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef InventoryKey<BOM_CONTENT> BomKey_T;

    /** Definition allowing to retrieve the  children type of the
        BOM_CONTENT. */
    typedef typename BOM_CONTENT::ContentChild_T ContentChild_T;

    /** Definition allowing to retrieve the associated parent
        BOM structure type. */
    typedef typename BOM_CONTENT::ParentBomContent_T::BomStructure_T ParentBomStructure_T;

    /** Definition allowing to retrieve the associated children type. */
    typedef boost::mpl::vector<FlightDate<ContentChild_T>,
                               BomStructureDummy> ChildrenBomTypeList_T;

    /** Define the default children bom holder type. */
    typedef BomChildrenHolderImp<BomContentDummy> DefaultChildrenBomHolder_T;

    /** Define the  children bom holder type. */
    typedef BomChildrenHolderImp<ContentChild_T> ChildrenBomHolder_T;

    /** Define the iterator of the flight-date list. */
    typedef typename ChildrenBomHolder_T::ListConstIterator_T FlightDateListConstIterator_T;

    /** Define the iterator of the flight-date map. */
    typedef typename ChildrenBomHolder_T::MapConstIterator_T FlightDateMapConstIterator_T;
  
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
    
    /** Get the flight-date key. */
    const BomKey_T& getKey() const {
      return _key;
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

    /** Dump a Business Object with all its children into an output stream.
        @param ostream& the output stream. */
    void describeFull (std::ostringstream& ioOut) const {
      ioOut << describeShortKey () << std::endl;
      displayFlightDateList (ioOut);
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

    /** Dump the flight-date children list in to an output stream.
        @param ostream& the output stream. */
    void displayFlightDateList (std::ostringstream& ioOut) const {
      ioOut << "FlightDates: " << std::endl;
      assert (_childrenList != NULL);
      _childrenList->describeFull (ioOut);
    }

    // /////////// Iteration methods //////////
    /** Initialise the internal const iterator on flight date:
        return the const iterator at the begining of the list. */
    FlightDateListConstIterator_T flightDateListConstIteratorBegin () const {
      assert (_childrenList != NULL);
      return _childrenList->listConstIteratorBegin ();
    }
    
    /** Initialise the internal const iterator on flight date:
        return the const iterator at the end of the list. */
    FlightDateListConstIterator_T flightDateListConstIteratorEnd () const {
      assert (_childrenList != NULL);
      return _childrenList->listConstIteratorEnd ();
    }

    /** Initialise the internal const iteratorson flight date:
        return the const iterator at the begining of the map. */
    FlightDateMapConstIterator_T flightDateMapConstIteratorBegin () const {
      assert (_childrenList != NULL);
      return _childrenList->mapConstIteratorBegin ();
    }
    
    /** Initialise the internal const iterator on flight date:
        return the const iterator at the end of the map. */
    FlightDateMapConstIterator_T flightDateMapConstIteratorEnd () const {
      assert (_childrenList != NULL);
      return _childrenList->mapConstIteratorEnd ();
    } 
    
  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    Inventory ();
    Inventory (const Inventory&);
    Inventory (const BomKey_T& iKey)
      : _parent (NULL), _key (iKey), _childrenList (NULL) { }

    /** Destructor. */
    virtual ~Inventory() { }

  private:
    // Attributes
    /** Parent root. */
    ParentBomStructure_T* _parent;
    
    /** The actual functional (Business Object) content. */
    BOM_CONTENT* _content;

    /** The key of both the structure and content objects. */
    BomKey_T _key;
    
    /** List of flight-dates. */
    ChildrenBomHolder_T* _childrenList;
  };

}
#endif // __STDAIR_BOM_INVENTORY_HPP

