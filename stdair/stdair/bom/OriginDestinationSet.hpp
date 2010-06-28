#ifndef __STDAIR_BOM_ORIGINDESTINATIONSET_HPP
#define __STDAIR_BOM_ORIGINDESTINATIONSET_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/OriginDestinationSetContent.hpp>
#include <stdair/bom/OriginDestinationSetTypes.hpp>
#include <stdair/bom/SegmentPathPeriodTypes.hpp>

namespace stdair {
  // Forward declarations
  class ReachableUniverse;
  class SegmentPathPeriod;
  
  /** Class representing the actual functional/business content for
      a network. */
  class OriginDestinationSet : public OriginDestinationSetContent {
    friend class FacBomContent;

  public:
    // //////////////////////////////////////////////////////////////////
    // See the explanations, within the BomRoot class, for all
    // the types which require to be specified below
    // //////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef OriginDestinationSetStructure_T Structure_T;
    
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef ReachableUniverse Parent_T;

    /** Definition allowing to retrieve the map/multimap type using by
        BomChildrenHolder. */
    typedef std::map<const MapKey_T, const Structure_T*> Map_T;

    /** Define the list of children holder types. */
    typedef boost::fusion::map<
      boost::fusion::pair<SegmentPathPeriod, SegmentPathPeriodHolder_T*>
      > ChildrenHolderMap_T;
    // //////////////////////////////////////////////////////////////////

  public:
    // /////////// Getters /////////////
    /** Get the parent object. */
    const Parent_T& getParent () const;

    /** Get a list or map of a children type for iteration methods. */
    SegmentPathPeriodList_T getSegmentPathPeriodList () const;
    SegmentPathPeriodMultimap_T getSegmentPathPeriodMultimap () const;

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

    /** Get the serialised version of the Business Object. */
    std::string toString() const;
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const;     

  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Constructors. */
    OriginDestinationSet (const Key_T&, Structure_T&);
    /** Destructor. */
    ~OriginDestinationSet();
    /** Initialise all the pointers of children holder to NULL. */
    void init();
    /** Default constructors. */
    OriginDestinationSet ();
    OriginDestinationSet (const OriginDestinationSet&);

  protected:
    // Attributes
    /** Reference structure. */
    Structure_T& _structure;
  };

}
#endif // __STDAIR_BOM_ORIGINDESTINATIONSET_HPP

