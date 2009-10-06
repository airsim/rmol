#ifndef __STDAIR_BOM_FLIGHTDATE_HPP
#define __STDAIR_BOM_FLIGHTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// MPL
#include <boost/mpl/vector.hpp>
// STDAIR 
#include <stdair/bom/BomStructure.hpp>
#include <stdair/bom/FlightDateKey.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/BomChildrenHolderImp.hpp>

namespace stdair {

  // Forward declaration
  template <typename BOM_CONTENT> class Inventory;
  class BomContentDummy;
  
  /** Wrapper class aimed at holding the actual content, modeled
      by an external specific FlightDate class (for instance,
      in the AIRSCHED library). */
  template <class BOM_CONTENT>
  class FlightDate : public BomStructure {
    friend class FacBomStructure;
    friend class FacBomContent;
    friend class BomStructure;
    
  public:
    // Type definitions
    /** Definition allowing to retrieve the associated BOM content type. */
    typedef BOM_CONTENT Content_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef FlightDateKey<BOM_CONTENT> BomKey_T;

    /** Definition allowing to retrieve the associated parent
        BOM structure type. */
    typedef typename BOM_CONTENT::ParentBomContent_T::BomStructure_T ParentBomStructure_T;

    /** Definition allowing to retrieve the  children type of the
        BOM_CONTENT. */
    typedef typename BOM_CONTENT::ContentChild_T ContentChild_T;

    /** Definition allowing to retrieve the second children type of the
        BOM_CONTENT. */
    typedef typename BOM_CONTENT::SecondContentChild_T SecondContentChild_T;
    
    /** Definition allowing to retrieve the associated children type. */
    typedef boost::mpl::vector<SegmentDate<ContentChild_T>,
                               LegDate<SecondContentChild_T> > ChildrenBomTypeList_T;

    /** Definition allowing to retrive the default children bom holder type. */
    typedef BomChildrenHolderImp<BomContentDummy> DefaultChildrenBomHolder_T;

    /** Definition allowing to retrive the  children bom holder type. */
    typedef BomChildrenHolderImp<ContentChild_T> ChildrenBomHolder_T;

    /** Definition allowing to retrive the second children bom holder type. */
    typedef BomChildrenHolderImp<SecondContentChild_T> SecondChildrenBomHolder_T;

    /** Define the iterators of the segment-date list. */
    typedef typename ChildrenBomHolder_T::ListConstIterator_T SegmentDateListConstIterator_T;
    typedef typename ChildrenBomHolder_T::ListConstReverseIterator_T SegmentDateListConstReverseIterator_T;
    typedef typename ChildrenBomHolder_T::ListIterator_T SegmentDateListIterator_T;
    typedef typename ChildrenBomHolder_T::ListReverseIterator_T SegmentDateListReverseIterator_T;

    /** Define the iterators of the segment-date map. */
    typedef typename ChildrenBomHolder_T::MapConstIterator_T SegmentDateMapConstIterator_T;
    typedef typename ChildrenBomHolder_T::MapConstReverseIterator_T SegmentDateMapConstReverseIterator_T;
    typedef typename ChildrenBomHolder_T::MapIterator_T SegmentDateMapIterator_T;
    typedef typename ChildrenBomHolder_T::MapReverseIterator_T SegmentDateMapReverseIterator_T;

    /** Define the iterators of the leg-date list. */
    typedef typename SecondChildrenBomHolder_T::ListConstIterator_T LegDateListConstIterator_T;
    typedef typename SecondChildrenBomHolder_T::ListConstReverseIterator_T LegDateListConstReverseIterator_T;
    typedef typename SecondChildrenBomHolder_T::ListIterator_T LegDateListIterator_T;
    typedef typename SecondChildrenBomHolder_T::ListReverseIterator_T LegDateListReverseIterator_T;

    /** Define the iterators of the leg-date map. */
    typedef typename SecondChildrenBomHolder_T::MapConstIterator_T LegDateMapConstIterator_T;
    typedef typename SecondChildrenBomHolder_T::MapConstReverseIterator_T LegDateMapConstReverseIterator_T;
    typedef typename SecondChildrenBomHolder_T::MapIterator_T LegDateMapIterator_T;
    typedef typename SecondChildrenBomHolder_T::MapReverseIterator_T LegDateMapReverseIterator_T;

    
  public:
    // /////////// Getters /////////////
    /** Get the (parent) Inventory object. */
    ParentBomStructure_T* getInventoryPtr() const {
      return _parent;
    }
    
    /** Get the (parent) Inventory object. */
    ParentBomStructure_T& getInventory() const {
      assert (_parent != NULL);
      return *_parent;
    }
    
    /** Get the flight-date key. */
    const BomKey_T& getKey() const {
      return _key;
    }

    /** Get the list of segment-dates. */
    const ChildrenBomHolder_T& getChildrenList() const {
      return *_childrenList;
    }

    /** Get the list of leg-dates. */
    const SecondChildrenBomHolder_T& getSecondChildrenList() const {
      return *_secondChildrenList;
    }

    /** Get the list of segment-dates. */
    void getChildrenList (ChildrenBomHolder_T*& ioChildrenList) {
      ioChildrenList = _childrenList;
    }

    /** Get the list of leg-dates. */
    void getChildrenList (SecondChildrenBomHolder_T*& ioChildrenList) {
      ioChildrenList = _secondChildrenList;
    }

  private:
    // /////////// Setters /////////////
    /** Set the (parent) FlightDate object. */
    void setBomStructureRoot (ParentBomStructure_T& ioParent) {
      _parent = &ioParent;
    }
    
    /** Default children list setter. */
    void setChildrenList (DefaultChildrenBomHolder_T&) { }
    
    /** Set the segment-date children list. */
    void setChildrenList (ChildrenBomHolder_T& ioChildrenList) {
      _childrenList = &ioChildrenList;
    }

    /** Set the leg-date children list. */
    void setChildrenList (SecondChildrenBomHolder_T& ioChildrenList) {
      _secondChildrenList = &ioChildrenList;
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
      displaySegmentDateList (ioOut);
      displayLegDateList (ioOut);
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

    /** Dump the segment-date children list in to an output stream.
        @param ostream& the output stream. */
    void displaySegmentDateList (std::ostringstream& ioOut) const {
      ioOut << "SegmentDates: " << std::endl;
      assert (_childrenList != NULL);
      _childrenList->describeFull (ioOut);
    }

    /** Dump the leg-date children list in to an output stream.
        @param ostream& the output stream. */
    void displayLegDateList (std::ostringstream& ioOut) const {
      ioOut << "LegDates: " << std::endl;
      assert (_secondChildrenList != NULL);
      _secondChildrenList->describeFull (ioOut);
    }

  public:
    // /////////// Iteration methods //////////
    /** Initialise the internal const iterator on segment date:
        return the const iterator at the begining of the list. */
    SegmentDateListConstIterator_T segmentDateListBegin () const {
      assert (_childrenList != NULL);
      return _childrenList->listBegin ();
    }
    
    /** Initialise the internal const iterator on segment date:
        return the const iterator at the end of the list. */
    SegmentDateListConstIterator_T segmentDateListConstIteratorEnd () const {
      assert (_childrenList != NULL);
      return _childrenList->listConstIteratorEnd ();
    }
    
    /** Initialise the internal const reverse iterator on segment date:
        return the const reverse iterator at the rbegining of the list. */
    SegmentDateListConstReverseIterator_T segmentDateListConstIteratorRBegin () const {
      assert (_childrenList != NULL);
      return _childrenList->listConstIteratorRBegin ();
    }
    
    /** Initialise the internal const reverse iterator on segment date:
        return the const reverse iterator at the rend of the list. */
    SegmentDateListConstReverseIterator_T segmentDateListConstIteratorREnd () const {
      assert (_childrenList != NULL);
      return _childrenList->listConstIteratorREnd ();
    }

    /** Initialise the internal iterator on segment date:
        return the iterator at the begining of the list. */
    SegmentDateListIterator_T segmentDateListBegin () const {
      assert (_childrenList != NULL);
      return _childrenList->listBegin ();
    }
    
    /** Initialise the internal iterator on segment date:
        return the iterator at the end of the list. */
    SegmentDateListIterator_T segmentDateListIteratorEnd () const {
      assert (_childrenList != NULL);
      return _childrenList->listIteratorEnd ();
    }
    
    /** Initialise the internal reverse iterator on segment date:
        return the reverse iterator at the rbegining of the list. */
    SegmentDateListReverseIterator_T segmentDateListIteratorRBegin () const {
      assert (_childrenList != NULL);
      return _childrenList->listIteratorRBegin ();
    }
    
    /** Initialise the internal reverse iterator on segment date:
        return the reverse iterator at the rend of the list. */
    SegmentDateListReverseIterator_T segmentDateListIteratorREnd () const {
      assert (_childrenList != NULL);
      return _childrenList->listIteratorREnd ();
    }

    /** Initialise the internal const iteratorson segment date:
        return the const iterator at the begining of the map. */
    SegmentDateMapConstIterator_T segmentDateMapConstIteratorBegin () const {
      assert (_childrenList != NULL);
      return _childrenList->mapConstIteratorBegin ();
    }
    
    /** Initialise the internal const iterator on segment date:
        return the const iterator at the end of the map. */
    SegmentDateMapConstIterator_T segmentDateMapConstIteratorEnd () const {
      assert (_childrenList != NULL);
      return _childrenList->mapConstIteratorEnd ();
    }

    /** Initialise the internal const reverse iterator on segment date:
        return the const reverse iterator at the rbegining of the map. */
    SegmentDateMapConstReverseIterator_T segmentDateMapConstIteratorRBegin () const {
      assert (_childrenList != NULL);
      return _childrenList->mapConstIteratorRBegin ();
    }
    
    /** Initialise the internal const reverse iterator on segment date:
        return the const reverse iterator at the rend of the map. */
    SegmentDateMapConstReverseIterator_T segmentDateMapConstIteratorREnd () const {
      assert (_childrenList != NULL);
      return _childrenList->mapConstIteratorREnd ();
    }

    /** Initialise the internal iterator on segment date:
        return the iterator at the begining of the map. */
    SegmentDateMapIterator_T segmentDateMapIteratorBegin () const {
      assert (_childrenList != NULL);
      return _childrenList->mapIteratorBegin ();
    }
    
    /** Initialise the internal iterator on segment date:
        return the iterator at the end of the map. */
    SegmentDateMapIterator_T segmentDateMapIteratorEnd () const {
      assert (_childrenList != NULL);
      return _childrenList->mapIteratorEnd ();
    }
    
    /** Initialise the internal reverse iterator on segment date:
        return the reverse iterator at the rbegining of the map. */
    SegmentDateMapReverseIterator_T segmentDateMapIteratorRBegin () const {
      assert (_childrenList != NULL);
      return _childrenList->mapIteratorRBegin ();
    }
    
    /** Initialise the internal reverse iterator on segment date:
        return the reverse iterator at the rend of the map. */
    SegmentDateMapReverseIterator_T segmentDateMapIteratorREnd () const {
      assert (_childrenList != NULL);
      return _childrenList->mapIteratorREnd ();
    }


    /** Initialise the internal const iterator on leg date:
        return the const iterator at the begining of the list. */
    LegDateListConstIterator_T legDateListBegin () const {
      assert (_secondChildrenList != NULL);
      return _secondChildrenList->listBegin ();
    }
    
    /** Initialise the internal const iterator on leg date:
        return the const iterator at the end of the list. */
    LegDateListConstIterator_T legDateListConstIteratorEnd () const {
      assert (_secondChildrenList != NULL);
      return _secondChildrenList->listConstIteratorEnd ();
    }
    
    /** Initialise the internal const reverse iterator on leg date:
        return the const reverse iterator at the rbegining of the list. */
    LegDateListConstReverseIterator_T legDateListConstIteratorRBegin () const {
      assert (_secondChildrenList != NULL);
      return _secondChildrenList->listConstIteratorRBegin ();
    }
    
    /** Initialise the internal const reverse iterator on leg date:
        return the const reverse iterator at the rend of the list. */
    LegDateListConstReverseIterator_T legDateListConstIteratorREnd () const {
      assert (_secondChildrenList != NULL);
      return _secondChildrenList->listConstIteratorREnd ();
    }

    /** Initialise the internal iterator on leg date:
        return the iterator at the begining of the list. */
    LegDateListIterator_T legDateListBegin () const {
      assert (_secondChildrenList != NULL);
      return _secondChildrenList->listBegin ();
    }
    
    /** Initialise the internal iterator on leg date:
        return the iterator at the end of the list. */
    LegDateListIterator_T legDateListIteratorEnd () const {
      assert (_secondChildrenList != NULL);
      return _secondChildrenList->listIteratorEnd ();
    }
    
    /** Initialise the internal reverse iterator on leg date:
        return the reverse iterator at the rbegining of the list. */
    LegDateListReverseIterator_T legDateListIteratorRBegin () const {
      assert (_secondChildrenList != NULL);
      return _secondChildrenList->listIteratorRBegin ();
    }
    
    /** Initialise the internal reverse iterator on leg date:
        return the reverse iterator at the rend of the list. */
    LegDateListReverseIterator_T legDateListIteratorREnd () const {
      assert (_secondChildrenList != NULL);
      return _secondChildrenList->listIteratorREnd ();
    }

    /** Initialise the internal const iteratorson leg date:
        return the const iterator at the begining of the map. */
    LegDateMapConstIterator_T legDateMapConstIteratorBegin () const {
      assert (_secondChildrenList != NULL);
      return _secondChildrenList->mapConstIteratorBegin ();
    }
    
    /** Initialise the internal const iterator on leg date:
        return the const iterator at the end of the map. */
    LegDateMapConstIterator_T legDateMapConstIteratorEnd () const {
      assert (_secondChildrenList != NULL);
      return _secondChildrenList->mapConstIteratorEnd ();
    }

    /** Initialise the internal const reverse iterator on leg date:
        return the const reverse iterator at the rbegining of the map. */
    LegDateMapConstReverseIterator_T legDateMapConstIteratorRBegin () const {
      assert (_secondChildrenList != NULL);
      return _secondChildrenList->mapConstIteratorRBegin ();
    }
    
    /** Initialise the internal const reverse iterator on leg date:
        return the const reverse iterator at the rend of the map. */
    LegDateMapConstReverseIterator_T legDateMapConstIteratorREnd () const {
      assert (_secondChildrenList != NULL);
      return _secondChildrenList->mapConstIteratorREnd ();
    }

    /** Initialise the internal iterator on leg date:
        return the iterator at the begining of the map. */
    LegDateMapIterator_T legDateMapIteratorBegin () const {
      assert (_secondChildrenList != NULL);
      return _secondChildrenList->mapIteratorBegin ();
    }
    
    /** Initialise the internal iterator on leg date:
        return the iterator at the end of the map. */
    LegDateMapIterator_T legDateMapIteratorEnd () const {
      assert (_secondChildrenList != NULL);
      return _secondChildrenList->mapIteratorEnd ();
    }
    
    /** Initialise the internal reverse iterator on leg date:
        return the reverse iterator at the rbegining of the map. */
    LegDateMapReverseIterator_T legDateMapIteratorRBegin () const {
      assert (_secondChildrenList != NULL);
      return _secondChildrenList->mapIteratorRBegin ();
    }
    
    /** Initialise the internal reverse iterator on leg date:
        return the reverse iterator at the rend of the map. */
    LegDateMapReverseIterator_T legDateMapIteratorREnd () const {
      assert (_secondChildrenList != NULL);
      return _secondChildrenList->mapIteratorREnd ();
    }

    
  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    FlightDate ();
    FlightDate (const FlightDate&);
    FlightDate (const BomKey_T& iKey)
      : _parent (NULL), _key (iKey), _childrenList (NULL),
        _secondChildrenList (NULL) { }

    /** Destructor. */
    virtual ~FlightDate() { }

  private:
    // Attributes
    /** Parent root. */
    ParentBomStructure_T* _parent;

     /** The actual functional (Business Object) content. */
    BOM_CONTENT* _content;
    
    /** The key of both the structure and content objects. */
    BomKey_T _key;
    
    /** List of segment-dates. */
    ChildrenBomHolder_T* _childrenList;

    /** List of leg-dates. */
    SecondChildrenBomHolder_T* _secondChildrenList;

  };

}
#endif // __STDAIR_BOM_FLIGHTDATE_HPP

