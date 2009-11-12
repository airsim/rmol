#ifndef __STDAIR_BOM_FLIGHTDATESTRUCTURE_HPP
#define __STDAIR_BOM_FLIGHTDATESTRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// MPL
#include <boost/mpl/vector.hpp>
// STDAIR 
#include <stdair/bom/BomStructureDummy.hpp>
#include <stdair/bom/BomContentDummy.hpp>
#include <stdair/bom/SegmentDateStructure.hpp>
#include <stdair/bom/LegDateStructure.hpp>

namespace stdair {
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
    typedef typename BOM_CONTENT::BomKey_T BomKey_T;

    /** Definition allowing to retrieve the associated parent
        BOM structure type. */
    typedef typename BOM_CONTENT::Parent_T::BomStructure_T ParentBomStructure_T;

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

    /** Define the  children booking class holder type. */
    typedef BomChildrenHolderImp<typename BOM_CONTENT::BookingClassContent_T> BookingClassHolder_T;
   
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
      assert (_content != NULL);
      return _content->getKey();
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
    
    /** Set the  booking class list. */
    void setBookingClassHolder (BookingClassHolder_T& ioBookingClassHolder) {
      _bookingClassHolder = &ioBookingClassHolder;
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
    FlightDateStructure () : _parent (NULL), _content (NULL),
                             _childrenList (NULL), _secondChildrenList (NULL),
                             _bookingClassHolder (NULL) { }
    FlightDateStructure (const FlightDateStructure&);

    /** Destructor. */
    virtual ~FlightDateStructure() { }

  private:
    // Attributes
    /** Parent root. */
    ParentBomStructure_T* _parent;

     /** The actual functional (Business Object) content. */
    BOM_CONTENT* _content;
    
    /** List of segment-dates. */
    ChildrenBomHolder_T* _childrenList;

    /** List of leg-dates. */
    SecondChildrenBomHolder_T* _secondChildrenList;

    /** List of booking classes. */
    BookingClassHolder_T* _bookingClassHolder;

  };

}
#endif // __STDAIR_BOM_FLIGHTDATESTRUCTURE_HPP

