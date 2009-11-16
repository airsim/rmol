#ifndef __STDAIR_BOM_FLIGHTDATESTRUCTURE_HPP
#define __STDAIR_BOM_FLIGHTDATESTRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// MPL
#include <boost/mpl/vector.hpp>
// STDAIR 
#include <stdair/bom/BomStopStructure.hpp>
#include <stdair/bom/BomStopContent.hpp>
#include <stdair/bom/SegmentDateStructure.hpp>
#include <stdair/bom/LegDateStructure.hpp>
#include <stdair/bom/SegmentDateKey.hpp>
#include <stdair/bom/LegDateKey.hpp>
#include <stdair/bom/BookingClassKey.hpp>

namespace stdair {
  // Forward declarations.
  template <typename BOM> struct BomMap_T;
  
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

    /** Definition allowing to retrieve the  key type of the
        ContentChild_T. */
    typedef SegmentDateKey_T ChildKey_T;

    /** Definition allowing to retrieve the  key type of the
        SecondContentChild_T. */
    typedef LegDateKey_T SecondChildKey_T;

    /** Definition allowing to retrieve the associated parent
        BOM structure type. */
    typedef typename BOM_CONTENT::Parent_T::BomStructure_T ParentBomStructure_T;

    /** Definition allowing to retrieve the  children type of the
        BOM_CONTENT. */
    typedef typename BOM_CONTENT::ContentChild_T ContentChild_T;

    /** Define the map of ContentChild_T. */
    typedef BomMap_T<ContentChild_T> ChildrenMap_T;
    
    /** Definition allowing to retrieve the second children type of the
        BOM_CONTENT. */
    typedef typename BOM_CONTENT::SecondContentChild_T SecondContentChild_T;

     /** Define the map of SecondContentChild_T. */
    typedef BomMap_T<SecondContentChild_T> SecondChildrenMap_T;
    
    /** Definition allowing to retrieve the associated children type. */
    typedef boost::mpl::vector<SegmentDateStructure<ContentChild_T>,
                               LegDateStructure<SecondContentChild_T> > ChildrenBomTypeList_T;

    /** Definition allowing to retrive the default children bom holder type. */
    typedef BomChildrenHolderImp<BomStopContent> DefaultChildrenBomHolder_T;

    /** Definition allowing to retrive the  children bom holder type. */
    typedef BomChildrenHolderImp<ContentChild_T> ChildrenBomHolder_T;

    /** Definition allowing to retrive the second children bom holder type. */
    typedef BomChildrenHolderImp<SecondContentChild_T> SecondChildrenBomHolder_T;

    /** Define the children booking class type. */
    typedef typename BOM_CONTENT::BookingClassContent_T BookingClass_T;
    
    /** Define the children booking class holder type. */
    typedef BomChildrenHolderImp<BookingClass_T> BookingClassHolder_T;
    
    /** Define the map of booking class. */
    typedef BomMap_T<BookingClass_T> BookingClassMap_T;
   
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

    /** Get the holder of segment-dates. */
    const ChildrenBomHolder_T& getChildrenHolder() const {
      assert (_childrenHolder != NULL);
      return *_childrenHolder;
    }

    /** Get the holder of leg-dates. */
    const SecondChildrenBomHolder_T& getSecondChildrenHolder() const {
      assert (_secondChildrenHolder != NULL);
      return *_secondChildrenHolder;
    }

    /** Get the holder of booking classes. */
    BookingClassHolder_T& getBookingClassHolder() const {
      assert (_bookingClassHolder);
      return *_bookingClassHolder;
    }

    /** Get the holder of segment-dates. */
    void getChildrenHolder (ChildrenBomHolder_T*& ioChildrenHolder) {
      ioChildrenHolder = _childrenHolder;
    }

    /** Get the holder of leg-dates. */
    void getChildrenHolder (SecondChildrenBomHolder_T*& ioChildrenHolder) {
      ioChildrenHolder = _secondChildrenHolder;
    }
    
    /** Retrieve, if existing, the segment-date corresponding to the
        given key.
        <br>If not exissting, return the NULL pointer. */
    ContentChild_T* getContentChild (const ChildKey_T& iKey) const {
      ContentChild_T* oContentChild_ptr = NULL;
      
      ChildrenMap_T lChildrenMap (getChildrenHolder());
      const MapKey_T lMapKey = iKey.toString();
      
      typename ChildrenMap_T::iterator itContentChild =
        lChildrenMap.find (lMapKey);
      
      if (itContentChild != lChildrenMap.end()) {
        oContentChild_ptr = itContentChild->second;
        assert (oContentChild_ptr != NULL);
      }
      
      return oContentChild_ptr;
    }

    /** Retrieve, if existing, the leg-date corresponding to the
        given key.
        <br>If not exissting, return the NULL pointer. */
    SecondContentChild_T* getSecondContentChild (const SecondChildKey_T& iKey) const {
      SecondContentChild_T* oContentChild_ptr = NULL;
      
      SecondChildrenMap_T lChildrenMap (getSecondChildrenHolder());
      const MapKey_T lMapKey = iKey.toString();
      
      typename SecondChildrenMap_T::iterator itContentChild =
        lChildrenMap.find (lMapKey);
      
      if (itContentChild != lChildrenMap.end()) {
        oContentChild_ptr = itContentChild->second;
        assert (oContentChild_ptr != NULL);
      }
      
      return oContentChild_ptr;
    }

    /** Retrieve, if existing, the booking class corresponding to the
        given key.
        <br>If not exissting, return the NULL pointer. */
    BookingClass_T* getBookingClass (const BookingClassKey_T& iKey) const {
      BookingClass_T* oBookingClass_ptr = NULL;
      
      BookingClassMap_T lBookingClassMap (getBookingClassHolder());
      const MapKey_T lMapKey = iKey.toString();
      
      typename BookingClassMap_T::iterator itBookingClass =
        lBookingClassMap.find (lMapKey);
      
      if (itBookingClass != lBookingClassMap.end()) {
        oBookingClass_ptr = itBookingClass->second;
        assert (oBookingClass_ptr != NULL);
      }
      
      return oBookingClass_ptr;
    }
    
  private:
    // /////////// Setters /////////////
    /** Set the (parent) FlightDate object. */
    void setInventoryStructure (ParentBomStructure_T& ioParent) {
      _parent = &ioParent;
    }
    
    /** Default children holder setter. */
    void setChildrenHolder (DefaultChildrenBomHolder_T&) { }
    
    /** Set the segment-date children holder. */
    void setChildrenHolder (ChildrenBomHolder_T& ioChildrenHolder) {
      _childrenHolder = &ioChildrenHolder;
    }

    /** Set the leg-date children holder. */
    void setChildrenHolder (SecondChildrenBomHolder_T& ioChildrenHolder) {
      _secondChildrenHolder = &ioChildrenHolder;
    }
    
    /** Set the  booking class holder. */
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
                             _childrenHolder (NULL),
                             _secondChildrenHolder (NULL),
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
    
    /** Holder of segment-dates. */
    ChildrenBomHolder_T* _childrenHolder;

    /** Holder of leg-dates. */
    SecondChildrenBomHolder_T* _secondChildrenHolder;

    /** Holder of booking classes. */
    BookingClassHolder_T* _bookingClassHolder;

  };

}
#endif // __STDAIR_BOM_FLIGHTDATESTRUCTURE_HPP

