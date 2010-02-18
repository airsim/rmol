#ifndef __STDAIR_BOM_DEMANDSTREAMSTRUCTURE_HPP
#define __STDAIR_BOM_DEMANDSTREAMSTRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
// MPL
#include <boost/mpl/vector.hpp>
// STDAIR  
#include <stdair/bom/BomStopStructure.hpp>
#include <stdair/bom/BomStopContent.hpp>

namespace stdair {
  /** Wrapper class aimed at holding the actual content, modeled
      by an external specific DemandStream class (for instance,
      in the AIRSCHED library). */
  template <class BOM_CONTENT>
  class DemandStreamStructure : public BomStructure {
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
    /** Get the (parent) BomRootStructure object. */
    ParentBomStructure_T* getBomRootStructurePtr() const {
      return _parent;
    }
    
    /** Get the (parent) BomRootStructure object. */
    ParentBomStructure_T& getBomRootStructure() const;
    
    /** Get the segment-cabin key. */
    const BomKey_T& getKey() const {
      assert (_content != NULL);
      return _content->getKey();
    }
    
  private:
    // /////////// Setters /////////////
    /** Set the (parent) BomRootStructure object. */
    void setBomRootStructure (ParentBomStructure_T& ioBomRootStructure){
      _parent = &ioBomRootStructure;
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
    DemandStreamStructure () : _parent (NULL), _content (NULL) { }
    DemandStreamStructure (const DemandStreamStructure&);

    /** Destructor. */
    virtual ~DemandStreamStructure() { }

  private:
    // Attributes
    /** Parent segment-cabin. */
    ParentBomStructure_T* _parent;

    /** The actual functional (Business Object) content. */
    BOM_CONTENT* _content;
  };

}
#endif // __STDAIR_BOM_DEMANDSTREAMSTRUCTURE_HPP
