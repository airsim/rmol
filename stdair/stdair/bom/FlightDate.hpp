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

