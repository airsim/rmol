#ifndef __STDAIR_BOM_LEGDATESTRUCTURE_HPP
#define __STDAIR_BOM_LEGDATESTRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// MPL
#include <boost/mpl/vector.hpp>
// STDAIR 
#include <stdair/bom/BomStructure.hpp>
#include <stdair/bom/LegDateKey.hpp>
#include <stdair/bom/LegCabinStructure.hpp>
#include <stdair/bom/BomChildrenHolderImp.hpp>

namespace stdair {

  // Forward declarations
  template <typename BOM_CONTENT> class FlightDateStructure;
  class BomStructureDummy;
  class BomContentDummy;
  
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
    typedef LegDateKey<BOM_CONTENT> BomKey_T;

    /** Definition allowing to retrieve the associated parent
        BOM structure type. */
    typedef typename BOM_CONTENT::Parent_T::BomStructure_T ParentBomStructure_T;

    /** Definition allowing to retrieve the  children type of the
        BOM_CONTENT. */
    typedef typename BOM_CONTENT::ContentChild_T ContentChild_T;
    
    /** Definition allowing to retrieve the associated children type. */
    typedef boost::mpl::vector <LegCabinStructure<ContentChild_T>,
                                BomStructureDummy> ChildrenBomTypeList_T;

    /** Definition allowing to retrieve the default children bom holder type. */
    typedef BomChildrenHolderImp<BomContentDummy> DefaultChildrenBomHolder_T;

    /** Definition allowing to retrive the  children bom holder type. */
    typedef BomChildrenHolderImp<ContentChild_T> ChildrenBomHolder_T;

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
      return _key;
    }

    /** Get the list of leg-cabins. */
    const ChildrenBomHolder_T& getChildrenList() const {
      return *_childrenList;
    }

    /** Get the list of leg-cabins. */
    void getChildrenList (ChildrenBomHolder_T*& ioChildrenList) {
      ioChildrenList = _childrenList;
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
      displayLegCabinList (ioOut);
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

    /** Dump the leg-cabin children list in to an output stream.
        @param ostream& the output stream. */
    void displayLegCabinList (std::ostringstream& ioOut) const {
      ioOut << "LegCabins: " << std::endl;
      assert (_childrenList != NULL);
      _childrenList->describeFull (ioOut);
    }
    
  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    LegDateStructure ();
    LegDateStructure (const LegDateStructure&);
    LegDateStructure (const BomKey_T& iKey) : _parent (NULL), _key (iKey) { }

    /** Destructor. */
    virtual ~LegDateStructure() { }

  private:
    // Attributes
    /** Parent flight-date. */
    ParentBomStructure_T* _parent;

    /** The actual functional (Business Object) content. */
    BOM_CONTENT* _content;

    /** The key of both the structure and content objects. */
    BomKey_T _key;
    
    /** List of leg-cabins. */
    ChildrenBomHolder_T* _childrenList;
  };

}
#endif // __STDAIR_BOM_LEGDATESTRUCTURE_HPP
