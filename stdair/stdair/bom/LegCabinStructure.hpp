#ifndef __STDAIR_BOM_LEGCABINSTRUCTURE_HPP
#define __STDAIR_BOM_LEGCABINSTRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// MPL
#include <boost/mpl/vector.hpp>
// STDAIR 
#include <stdair/bom/BomStopStructure.hpp>
#include <stdair/bom/BomStopContent.hpp>
#include <stdair/bom/BookingClassStructure.hpp>

namespace stdair {
  // Forward declarations.
  template <typename BOM> struct BomMap_T;
  
  /** Wrapper class aimed at holding the actual content, modeled
      by an external specific LegCabin class (for instance,
      in the AIRSCHED library). */
  template <class BOM_CONTENT>
  class LegCabinStructure : public BomStructure {
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

    /** Define the associated segment-cabin type. */
    typedef typename BOM_CONTENT::SegmentCabinContent_T SegmentCabin_T;
    
    /** Define the associated segment-cabin holder type. */
    typedef BomChildrenHolderImp<SegmentCabin_T> SegmentCabinHolder_T;
    
    /** Define the map of segment-cabin. */
    typedef BomMap_T<SegmentCabin_T> SegmentCabinMap_T;

  public:
    // /////////// Getters /////////////
    /** Get the (parent) LegDateStructure object. */
    ParentBomStructure_T* getLegDateStructurePtr() const {
      return _parent;
    }
    
    /** Get the (parent) LegDateStructure object. */
    ParentBomStructure_T& getLegDateStructure() const;
    
    /** Get the leg-date key. */
    const BomKey_T& getKey() const {
      assert (_content != NULL);
      return _content->getKey();
    }
    
  private:
    // /////////// Setters /////////////
    /** Set the (parent) LegDateStructure object. */
    void setLegDateStructure (ParentBomStructure_T& ioLegDateStructure) {
      _parent = &ioLegDateStructure;
    }
    
    /** Default children holder setter. */
    void setChildrenHolder (DefaultChildrenBomHolder_T&) { }

    /** Set the segment-cabin holder. */
    void setSegmentCabinHolder (SegmentCabinHolder_T& ioSegmentCabinHolder) {
      _segmentCabinHolder = &ioSegmentCabinHolder;
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
    LegCabinStructure () : _parent (NULL), _content (NULL),
                           _segmentCabinHolder (NULL) { }
    LegCabinStructure (const LegCabinStructure&);

    /** Destructor. */
    virtual ~LegCabinStructure() { }

  private:
    // Attributes
    /** Parent leg-date. */
    ParentBomStructure_T* _parent;

    /** The actual functional (Business Object) content. */
    BOM_CONTENT* _content;

    /** Holder of the associated segment-cabins. */
    SegmentCabinHolder_T* _segmentCabinHolder;
  };

}
#endif // __STDAIR_BOM_LEGCABINSTRUCTURE_HPP
