#ifndef __STDAIR_BOM_NETWORKDATESTRUCTURE_HPP
#define __STDAIR_BOM_NETWORKDATESTRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// (Boost) MPL
#include <boost/mpl/vector.hpp>
// STDAIR 
#include <stdair/bom/BomStopStructure.hpp>
#include <stdair/bom/BomStopContent.hpp>
#include <stdair/bom/AirportDateStructure.hpp>
#include <stdair/bom/AirportDateKey.hpp>

namespace stdair {
  // Forward declarations.
  template <typename BOM> struct BomMap_T;
  struct AirportDateKey_T;

  /** Wrapper class aimed at holding the actual content, modeled
      by an external specific NetworkDate class (for instance,
      in the AIRSCHED library). */
  template <class BOM_CONTENT>
  class NetworkDateStructure : public BomStructure {
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
    
    /** Definition allowing to retrieve the  key type of the
        ContentChild_T. */
    typedef AirportDateKey_T ChildKey_T;

    /** Define the map of ContentChild_T. */
    typedef BomMap_T<ContentChild_T> ChildrenMap_T;

    /** Definition allowing to retrieve the associated parent
        BOM structure type. */
    typedef typename BOM_CONTENT::Parent_T::BomStructure_T ParentBomStructure_T;

    /** Definition allowing to retrieve the associated children type. */
    typedef boost::mpl::vector<AirportDateStructure<ContentChild_T>,
                               BomStopStructure> ChildrenBomTypeList_T;

    /** Define the default children bom holder type. */
    typedef BomChildrenHolderImp<BomStopContent> DefaultChildrenBomHolder_T;

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
    
    /** Get the network-date key. */
    const BomKey_T& getKey() const {
      assert (_content != NULL);
      return _content->getKey ();
    }

    /** Get the holder of airport-dates. */
    const ChildrenBomHolder_T& getChildrenHolder() const {
      assert (_childrenHolder != NULL);
      return *_childrenHolder;
    }
    
    /** Get the holder of airport-dates. */
    void getChildrenHolder (ChildrenBomHolder_T*& ioChildrenHolder) {
      ioChildrenHolder = _childrenHolder;
    }

    /** Retrieve, if existing, the airport-date corresponding to the
        given key.
        <br>If not exissting, return the NULL pointer. */
    ContentChild_T* getContentChild (const ChildKey_T& iKey) const {
      ContentChild_T* oContentChild_ptr= NULL;
      
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

    /** Get the AirportDate (from the Network parent class) corresponding
        to the given key (reference date + airport code).
        <br>Return the NULL pointer if not existing. */
    ContentChild_T* getAirportDate (const AirportDateKey_T& iAirportDateKey,
                                    const BomKey_T& iNetworkDateKey) const {
      assert (_parent != NULL);
      ContentChild_T* oAirportDate_ptr = NULL;

      const BOM_CONTENT* lNetworkDate_ptr =
        _parent->getContentChild (iNetworkDateKey);

      
      if (lNetworkDate_ptr != NULL) {
        oAirportDate_ptr =
          lNetworkDate_ptr->getAirportDate (iAirportDateKey);
      }
      
      return oAirportDate_ptr;
    }
    
  private:
    // /////////// Setters /////////////
    /** Set the (parent) network-date object. */
    void setBomStructureRoot (ParentBomStructure_T& ioParent) {
      _parent = &ioParent;
    }

    /** Default children holder setter. */
    void setChildrenHolder (DefaultChildrenBomHolder_T&) { }
    
    /** Set the  children holder. */
    void setChildrenHolder (ChildrenBomHolder_T& ioChildrenHolder) {
      _childrenHolder = &ioChildrenHolder;
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
    std::string toString() const { return describeShortKey(); }
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const { return getKey().describe(); }

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return getKey().toString(); }

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    NetworkDateStructure () : _parent (NULL), _content (NULL),
                            _childrenHolder (NULL) { }

    NetworkDateStructure (const NetworkDateStructure&);
    /** Destructor. */
    virtual ~NetworkDateStructure() { }

  private:
    // Attributes
    /** Parent root. */
    ParentBomStructure_T* _parent;
    
    /** The actual functional (Business Object) content. */
    BOM_CONTENT* _content;

    /** Holder of airport-dates. */
    ChildrenBomHolder_T* _childrenHolder;
  };

}
#endif // __STDAIR_BOM_NETWORKDATESTRUCTURE_HPP
