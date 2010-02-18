#ifndef __STDAIR_BOM_AIRPORTDATESTRUCTURE_HPP
#define __STDAIR_BOM_AIRPORTDATESTRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// MPL
#include <boost/mpl/vector.hpp>
// STDAIR 
#include <stdair/bom/BomStopStructure.hpp>
#include <stdair/bom/BomStopContent.hpp>
#include <stdair/bom/OutboundPathStructure.hpp>
#include <stdair/bom/OutboundPathKey.hpp>

namespace stdair {  
  // Forward declarations.
  template <typename BOM> struct BomMap_T;
  struct NetworkDateKey_T;
  
  /** Wrapper class aimed at holding the actual content, modeled
      by an external specific AirportDate class (for instance,
      in the AIRSCHED library). */
  template <class BOM_CONTENT>
  class AirportDateStructure : public BomStructure {
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

    /** Definition allowing to retrieve the child key type. */
    typedef OutboundPathKey_T ChildKey_T;

    /** Define the map of ContentChild_T. */
    typedef BomMap_T<ContentChild_T> ChildrenMap_T;
    
    /** Definition allowing to retrieve the associated children type. */
    typedef boost::mpl::vector <OutboundPathStructure<ContentChild_T>,
                                BomStopStructure> ChildrenBomTypeList_T;

    /** Definition allowing to retrieve the default children bom holder type. */
    typedef BomChildrenHolderImp<BomStopContent> DefaultChildrenBomHolder_T;

    /** Definition allowing to retrive the  children bom holder type. */
    typedef BomChildrenHolderImp<ContentChild_T> ChildrenBomHolder_T;
    

  public:
    // /////////// Getters /////////////
    /** Get the (parent) NetworkDateStructure object. */
    ParentBomStructure_T* getNetworkDateStructurePtr() const {
      return _parent;
    }
    
    /** Get the (parent) NetworkDateStructure object. */
    ParentBomStructure_T& getNetworkDateStructure() const;
    
    /** Get the airport-date key. */
    const BomKey_T& getKey() const {
      assert (_content != NULL);
      return _content->getKey();
    }

    /** Get the holder of outbound paths. */
    const ChildrenBomHolder_T& getChildrenHolder() const {
      return *_childrenHolder;
    }

    /** Get the holder of outbound paths. */
    void getChildrenHolder (ChildrenBomHolder_T*& ioChildrenHolder) {
      ioChildrenHolder = _childrenHolder;
    }

    /** Retrieve, if existing, the outbound path corresponding to the
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

    /** Get the AirportDate (from the Network parent class) corresponding
        to the given key (reference date + airport code).
        <br>Return the NULL pointer if not existing. */
    Content_T* getAirportDate (const BomKey_T& iAirportDateKey,
                               const NetworkDateKey_T& iNetworkDateKey)const{
      assert (_parent != NULL);
      return _parent->getAirportDate (iAirportDateKey, iNetworkDateKey);
    }
    
  private:
    // /////////// Setters /////////////
    /** Set the (parent) NetworkDateStructure object. */
    void setNetworkDateStructure (ParentBomStructure_T& ioNetworkDateStructure) {
      _parent = &ioNetworkDateStructure;
    }
    
    /** Default children holder setter. */
    void setChildrenHolder (DefaultChildrenBomHolder_T&) { }

    /** Set the outbound path children holder. */
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
    AirportDateStructure () : _parent (NULL), _content (NULL),
                          _childrenHolder (NULL) { }
    AirportDateStructure (const AirportDateStructure&);

    /** Destructor. */
    virtual ~AirportDateStructure() { }

  private:
    // Attributes
    /** Parent network-date. */
    ParentBomStructure_T* _parent;

    /** The actual functional (Business Object) content. */
    BOM_CONTENT* _content;

    /** Holder of outbound paths. */
    ChildrenBomHolder_T* _childrenHolder;
  };

}
#endif // __STDAIR_BOM_AIRPORTDATESTRUCTURE_HPP
