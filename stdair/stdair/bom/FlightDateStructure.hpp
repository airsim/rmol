#ifndef __STDAIR_BOM_FLIGHTDATESTRUCTURE_HPP
#define __STDAIR_BOM_FLIGHTDATESTRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// MPL
#include <boost/mpl/vector.hpp>
// STDAIR 
#include <stdair/bom/BomStructure.hpp>
#include <stdair/bom/FlightDateKey.hpp>
#include <stdair/bom/SegmentDateStructure.hpp>
#include <stdair/bom/LegDateStructure.hpp>
#include <stdair/bom/BomChildrenHolderImp.hpp>

namespace stdair {

  // Forward declaration
  template <typename BOM_CONTENT> class Inventory;
  class BomContentDummy;
  
  /** Wrapper class aimed at holding the actual content, modeled
      by an external specific FlightDate class (for instance,
      in the AIRSCHED library). */
  template <class BOM_CONTENT>
  class FlightDateStructure : public BomStructure {
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
    typedef boost::mpl::vector<SegmentDateStructure<ContentChild_T>,
                               LegDateStructure<SecondContentChild_T> > ChildrenBomTypeList_T;

    /** Definition allowing to retrive the default children bom holder type. */
    typedef BomChildrenHolderImp<BomContentDummy> DefaultChildrenBomHolder_T;

    /** Definition allowing to retrive the  children bom holder type. */
    typedef BomChildrenHolderImp<ContentChild_T> ChildrenBomHolder_T;

    /** Definition allowing to retrive the second children bom holder type. */
    typedef BomChildrenHolderImp<SecondContentChild_T> SecondChildrenBomHolder_T;

    /** Define the iterators of the segment-date list. */
    typedef typename ChildrenBomHolder_T::ListIterator_T SegmentDateListIterator_T;
    typedef typename ChildrenBomHolder_T::ListReverseIterator_T SegmentDateListReverseIterator_T;

    /** Define the iterators of the segment-date map. */
    typedef typename ChildrenBomHolder_T::MapIterator_T SegmentDateMapIterator_T;
    typedef typename ChildrenBomHolder_T::MapReverseIterator_T SegmentDateMapReverseIterator_T;

    /** Define the iterators of the leg-date list. */
    typedef typename SecondChildrenBomHolder_T::ListIterator_T LegDateListIterator_T;
    typedef typename SecondChildrenBomHolder_T::ListReverseIterator_T LegDateListReverseIterator_T;

    /** Define the iterators of the leg-date map. */
    typedef typename SecondChildrenBomHolder_T::MapIterator_T LegDateMapIterator_T;
    typedef typename SecondChildrenBomHolder_T::MapReverseIterator_T LegDateMapReverseIterator_T;

    
  public:
    // /////////// Getters /////////////
    /** Get the (parent) InventoryStructure object. */
    ParentBomStructure_T* getInventoryStructurePtr() const {
      return _parent;
    }
    
    /** Get the (parent) InventoryStructure object. */
    ParentBomStructure_T& getInventoryStructure() const {
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
    void setInventoryStructure (ParentBomStructure_T& ioParent) {
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
    /** Initialise the internal iterator on segment date:
        return the iterator at the begining of the list. */
    SegmentDateListIterator_T segmentDateListBegin () const {
      assert (_childrenList != NULL);
      return _childrenList->listBegin ();
    }
    
    /** Initialise the internal iterator on segment date:
        return the iterator at the end of the list. */
    SegmentDateListIterator_T segmentDateListEnd () const {
      assert (_childrenList != NULL);
      return _childrenList->listEnd ();
    }
    
    /** Initialise the internal reverse iterator on segment date:
        return the reverse iterator at the rbegining of the list. */
    SegmentDateListReverseIterator_T segmentDateListRBegin () const {
      assert (_childrenList != NULL);
      return _childrenList->listRBegin ();
    }
    
    /** Initialise the internal reverse iterator on segment date:
        return the reverse iterator at the rend of the list. */
    SegmentDateListReverseIterator_T segmentDateListREnd () const {
      assert (_childrenList != NULL);
      return _childrenList->listREnd ();
    }

    /** Initialise the internal iterator on segment date:
        return the iterator at the begining of the map. */
    SegmentDateMapIterator_T segmentDateMapBegin () const {
      assert (_childrenList != NULL);
      return _childrenList->mapBegin ();
    }
    
    /** Initialise the internal iterator on segment date:
        return the iterator at the end of the map. */
    SegmentDateMapIterator_T segmentDateMapEnd () const {
      assert (_childrenList != NULL);
      return _childrenList->mapEnd ();
    }
    
    /** Initialise the internal reverse iterator on segment date:
        return the reverse iterator at the rbegining of the map. */
    SegmentDateMapReverseIterator_T segmentDateMapRBegin () const {
      assert (_childrenList != NULL);
      return _childrenList->mapRBegin ();
    }
    
    /** Initialise the internal reverse iterator on segment date:
        return the reverse iterator at the rend of the map. */
    SegmentDateMapReverseIterator_T segmentDateMapREnd () const {
      assert (_childrenList != NULL);
      return _childrenList->mapREnd ();
    }


    /** Initialise the internal iterator on leg date:
        return the iterator at the begining of the list. */
    LegDateListIterator_T legDateListBegin () const {
      assert (_secondChildrenList != NULL);
      return _secondChildrenList->listBegin ();
    }
    
    /** Initialise the internal iterator on leg date:
        return the iterator at the end of the list. */
    LegDateListIterator_T legDateListEnd () const {
      assert (_secondChildrenList != NULL);
      return _secondChildrenList->listEnd ();
    }
    
    /** Initialise the internal reverse iterator on leg date:
        return the reverse iterator at the rbegining of the list. */
    LegDateListReverseIterator_T legDateListRBegin () const {
      assert (_secondChildrenList != NULL);
      return _secondChildrenList->listRBegin ();
    }
    
    /** Initialise the internal reverse iterator on leg date:
        return the reverse iterator at the rend of the list. */
    LegDateListReverseIterator_T legDateListREnd () const {
      assert (_secondChildrenList != NULL);
      return _secondChildrenList->listREnd ();
    }

    /** Initialise the internal iterator on leg date:
        return the iterator at the begining of the map. */
    LegDateMapIterator_T legDateMapBegin () const {
      assert (_secondChildrenList != NULL);
      return _secondChildrenList->mapBegin ();
    }
    
    /** Initialise the internal iterator on leg date:
        return the iterator at the end of the map. */
    LegDateMapIterator_T legDateMapEnd () const {
      assert (_secondChildrenList != NULL);
      return _secondChildrenList->mapEnd ();
    }
    
    /** Initialise the internal reverse iterator on leg date:
        return the reverse iterator at the rbegining of the map. */
    LegDateMapReverseIterator_T legDateMapRBegin () const {
      assert (_secondChildrenList != NULL);
      return _secondChildrenList->mapRBegin ();
    }
    
    /** Initialise the internal reverse iterator on leg date:
        return the reverse iterator at the rend of the map. */
    LegDateMapReverseIterator_T legDateMapREnd () const {
      assert (_secondChildrenList != NULL);
      return _secondChildrenList->mapREnd ();
    }

    
  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    FlightDateStructure ();
    FlightDateStructure (const FlightDateStructure&);
    FlightDateStructure (const BomKey_T& iKey)
      : _parent (NULL), _key (iKey), _childrenList (NULL),
        _secondChildrenList (NULL) { }

    /** Destructor. */
    virtual ~FlightDateStructure() { }

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
#endif // __STDAIR_BOM_FLIGHTDATESTRUCTURE_HPP

