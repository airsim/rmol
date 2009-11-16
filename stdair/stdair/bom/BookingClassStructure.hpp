#ifndef __STDAIR_BOM_BOOKINGCLASSSTRUCTURE_HPP
#define __STDAIR_BOM_BOOKINGCLASSSTRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// MPL
#include <boost/mpl/vector.hpp>
// STDAIR  
#include <stdair/bom/BomStopStructure.hpp>
#include <stdair/bom/BomStopContent.hpp>

namespace stdair {
  /** Wrapper class aimed at holding the actual content, modeled
      by an external specific BookingClass class (for instance,
      in the AIRSCHED library). */
  template <class BOM_CONTENT>
  class BookingClassStructure : public BomStructure {
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

  public:
    // /////////// Getters /////////////
    /** Get the (parent) SegmentCabinStructure object. */
    ParentBomStructure_T* getSegmentCabinStructurePtr() const {
      return _parent;
    }
    
    /** Get the (parent) SegmentCabinStructure object. */
    ParentBomStructure_T& getSegmentCabinStructure() const;
    
    /** Get the segment-cabin key. */
    const BomKey_T& getKey() const {
      assert (_content != NULL);
      return _content->getKey();
    }
    
  private:
    // /////////// Setters /////////////
    /** Set the (parent) SegmentCabinStructure object. */
    void setSegmentCabinStructure(ParentBomStructure_T& ioSegmentCabinStructure){
      _parent = &ioSegmentCabinStructure;
    }
    
    /** Default children holder setter. */
    void setChildrenHolder (DefaultChildrenBomHolder_T&) { }
    
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
    BookingClassStructure () : _parent (NULL), _content (NULL) { }
    BookingClassStructure (const BookingClassStructure&);

    /** Destructor. */
    virtual ~BookingClassStructure() { }

  private:
    // Attributes
    /** Parent segment-cabin. */
    ParentBomStructure_T* _parent;

    /** The actual functional (Business Object) content. */
    BOM_CONTENT* _content;

  };

}
#endif // __STDAIR_BOM_BOOKINGCLASSSTRUCTURE_HPP
