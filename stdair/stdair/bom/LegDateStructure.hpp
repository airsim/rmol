#ifndef __STDAIR_BOM_LEGDATESTRUCTURE_HPP
#define __STDAIR_BOM_LEGDATESTRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// MPL
#include <boost/mpl/vector.hpp>
// STDAIR 
#include <stdair/bom/BomStructureDummy.hpp>
#include <stdair/bom/BomContentDummy.hpp>
#include <stdair/bom/LegCabinStructure.hpp>
#include <stdair/bom/LegCabinKey.hpp>

namespace stdair {  
  // Forward declarations.
  template <typename BOM> struct BomMap_T;
  
  /** Wrapper class aimed at holding the actual content, modeled
      by an external specific LegDate class (for instance,
      in the AIRSCHED library). */
  template <class BOM_CONTENT>
  class LegDateStructure : public BomStructure {
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
    typedef LegCabinKey_T ChildKey_T;

    /** Define the map of ContentChild_T. */
    typedef BomMap_T<ContentChild_T> ChildrenMap_T;
    
    /** Definition allowing to retrieve the associated children type. */
    typedef boost::mpl::vector <LegCabinStructure<ContentChild_T>,
                                BomStructureDummy> ChildrenBomTypeList_T;

    /** Definition allowing to retrieve the default children bom holder type. */
    typedef BomChildrenHolderImp<BomContentDummy> DefaultChildrenBomHolder_T;

    /** Definition allowing to retrive the  children bom holder type. */
    typedef BomChildrenHolderImp<ContentChild_T> ChildrenBomHolder_T;

    /** Define the associated segment-date holder type.*/
    typedef BomChildrenHolderImp<typename BOM_CONTENT::SegmentDateContent_T> SegmentDateHolder_T;

  public:
    // /////////// Getters /////////////
    /** Get the (parent) FlightDateStructure object. */
    ParentBomStructure_T* getFlightDateStructurePtr() const {
      return _parent;
    }
    
    /** Get the (parent) FlightDateStructure object. */
    ParentBomStructure_T& getFlightDateStructure() const;
    
    /** Get the leg-date key. */
    const BomKey_T& getKey() const {
      assert (_content != NULL);
      return _content->getKey();
    }

    /** Get the list of leg-cabins. */
    const ChildrenBomHolder_T& getChildrenList() const {
      return *_childrenList;
    }

    /** Get the list of leg-cabins. */
    void getChildrenList (ChildrenBomHolder_T*& ioChildrenList) {
      ioChildrenList = _childrenList;
    }

    /** Retrieve, if existing, the leg-cabin corresponding to the
        given key.
        <br>If not exissting, return the NULL pointer. */
    ContentChild_T* getContentChild (const ChildKey_T& iKey) const {
      ContentChild_T* oContentChild_ptr = NULL;
      
      ChildrenMap_T lChildrenMap (getChildrenList());
      const MapKey_T lMapKey = iKey.toString();
      
      typename ChildrenMap_T::iterator itContentChild =
        lChildrenMap.find (lMapKey);
      
      if (itContentChild != lChildrenMap.end()) {
        oContentChild_ptr = itContentChild->second;
        assert (oContentChild_ptr != NULL);
      }
      
      return oContentChild_ptr;
    }
    
  private:
    // /////////// Setters /////////////
    /** Set the (parent) FlightDateStructure object. */
    void setFlightDateStructure (ParentBomStructure_T& ioFlightDateStructure) {
      _parent = &ioFlightDateStructure;
    }
    
    /** Default children list setter. */
    void setChildrenList (DefaultChildrenBomHolder_T&) { }

    /** Set the leg-cabin children list. */
    void setChildrenList (ChildrenBomHolder_T& ioChildrenList) {
      _childrenList = &ioChildrenList;
    }

    /** Set the segment-date holder. */
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
    LegDateStructure () : _parent (NULL), _content (NULL),
                          _childrenList (NULL), _segmentDateHolder (NULL) { }
    LegDateStructure (const LegDateStructure&);

    /** Destructor. */
    virtual ~LegDateStructure() { }

  private:
    // Attributes
    /** Parent flight-date. */
    ParentBomStructure_T* _parent;

    /** The actual functional (Business Object) content. */
    BOM_CONTENT* _content;

    /** List of leg-cabins. */
    ChildrenBomHolder_T* _childrenList;

    /** Holder of associated segment-dates. */
    SegmentDateHolder_T* _segmentDateHolder;
  };

}
#endif // __STDAIR_BOM_LEGDATESTRUCTURE_HPP
