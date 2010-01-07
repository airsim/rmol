#ifndef __STDAIR_BOM_OUTBOUNDPATHSTRUCTURE_HPP
#define __STDAIR_BOM_OUTBOUNDPATHSTRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// MPL
#include <boost/mpl/vector.hpp>
// STDAIR  
#include <stdair/bom/BomStopStructure.hpp>
#include <stdair/bom/BomStopContent.hpp>

namespace stdair {
  // Forward declarations.
  template <typename BOM> struct BomMap_T;
  struct AirportDateKey_T;
  struct NetworkDateKey_T;

  /** Wrapper class aimed at holding the actual content, modeled
      by an external specific OutboundPath class (for instance,
      in the AIRSCHED library). */
  template <class BOM_CONTENT>
  class OutboundPathStructure : public BomStructure {
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
    
    /** Definition allowing to retrieve the associated children type. */
    typedef boost::mpl::vector <BomStopStructure,
                                BomStopStructure> ChildrenBomTypeList_T;

    /** Definition allowing to retrieve the default children bom holder type. */
    typedef BomChildrenHolderImp<BomStopContent> DefaultChildrenBomHolder_T;

    /** Define the children segment-date type. */
    typedef typename BOM_CONTENT::SegmentDateContent_T SegmentDate_T;
    
    /** Define the children segment-date holder type. */
    typedef BomChildrenHolderImp<SegmentDate_T> SegmentDateHolder_T;
    
    /** Define the map of segment-date. */
    typedef BomMap_T<SegmentDate_T> SegmentDateMap_T;

    /** Definition allowing to retrieve the AirportDate type. */
    typedef typename BOM_CONTENT::Parent_T AirportDate_T;
    
  public:
    // /////////// Getters /////////////
    /** Get the (parent) AirportDateStructure object. */
    ParentBomStructure_T* getAirportDateStructurePtr() const {
      return _parent;
    }
    
    /** Get the (parent) AirportDateStructure object. */
    ParentBomStructure_T& getAirportDateStructure() const {
      assert (_parent != NULL);
      return *_parent;
    }
    
    /** Get the outbound path key. */
    const BomKey_T& getKey() const {
      assert (_content != NULL);
      return _content->getKey();
    }
    /** Get the holder of segment-dates. */
    SegmentDateHolder_T& getSegmentDateHolder() const {
      assert (_segmentDateHolder);
      return *_segmentDateHolder;
    }

    /** Get the AirportDate (from the Network parent class) corresponding
        to the given key (reference date + airport code).
        <br>Return the NULL pointer if not existing. */
    AirportDate_T* getAirportDate (const AirportDateKey_T& iAirportDateKey,
                                   const NetworkDateKey_T& iNetworkDateKey)const{
      assert (_parent != NULL);
      return _parent->getAirportDate (iAirportDateKey, iNetworkDateKey);
    }
    
  private:
    // /////////// Setters /////////////
    /** Set the (parent) AirportDateStructure object. */
    void setAirportDateStructure(ParentBomStructure_T& ioAirportDateStructure){
      _parent = &ioAirportDateStructure;
    }
    
    /** Default children holder setter. */
    void setChildrenHolder (DefaultChildrenBomHolder_T&) { }

    /** Set the  segment-date holder. */
    void setSegmentDateHolder (SegmentDateHolder_T& ioSegmentDateHolder) {
      _segmentDateHolder = &ioSegmentDateHolder;
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
    OutboundPathStructure () : _parent (NULL), _content (NULL),
                               _segmentDateHolder (NULL) { }
    OutboundPathStructure (const OutboundPathStructure&);

    /** Destructor. */
    virtual ~OutboundPathStructure() { }

  private:
    // Attributes
    /** Parent segment-cabin. */
    ParentBomStructure_T* _parent;

    /** The actual functional (Business Object) content. */
    BOM_CONTENT* _content;

    /** Holder of segment-dates. */
    SegmentDateHolder_T* _segmentDateHolder;

  };

}
#endif // __STDAIR_BOM_OUTBOUNDPATHSTRUCTURE_HPP
