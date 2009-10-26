#ifndef __STDAIR_BOM_LEGCABINSTRUCTURE_HPP
#define __STDAIR_BOM_LEGCABINSTRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// MPL
#include <boost/mpl/vector.hpp>
// STDAIR 
#include <stdair/bom/BomStructureDummy.hpp>
#include <stdair/bom/BomContentDummy.hpp>
#include <stdair/bom/BookingClassStructure.hpp>

namespace stdair {
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
    typedef boost::mpl::vector <BomStructureDummy,
                                BomStructureDummy> ChildrenBomTypeList_T;

    /** Definition allowing to retrieve the default children bom holder type. */
    typedef BomChildrenHolderImp<BomContentDummy> DefaultChildrenBomHolder_T;

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
    
    /** Default children list setter. */
    void setChildrenList (DefaultChildrenBomHolder_T&) { }

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
    LegCabinStructure () : _parent (NULL), _content (NULL) { }
    LegCabinStructure (const LegCabinStructure&);

    /** Destructor. */
    virtual ~LegCabinStructure() { }

  private:
    // Attributes
    /** Parent leg-date. */
    ParentBomStructure_T* _parent;

    /** The actual functional (Business Object) content. */
    BOM_CONTENT* _content;
  };

}
#endif // __STDAIR_BOM_LEGCABINSTRUCTURE_HPP
