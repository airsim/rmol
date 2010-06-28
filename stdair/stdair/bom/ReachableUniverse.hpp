#ifndef __STDAIR_BOM_REACHABLEUNIVERSE_HPP
#define __STDAIR_BOM_REACHABLEUNIVERSE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost Fusion
#if BOOST_VERSION >= 103500
#include <boost/fusion/include/map.hpp>
#else // BOOST_VERSION >= 103500
#include <boost/mpl/map.hpp>
#endif // BOOST_VERSION >= 103500
// StdAir 
#include <stdair/bom/ReachableUniverseContent.hpp>
#include <stdair/bom/ReachableUniverseTypes.hpp>
#include <stdair/bom/SegmentPathPeriodTypes.hpp>
#include <stdair/bom/OriginDestinationSetTypes.hpp>

namespace stdair {
  // Forward declarations
  class BomRoot;
  class SegmentPathPeriod;
  class OriginDestinationSet;

  /** Class representing the actual functional/business content for a
      airport-date. */
  class ReachableUniverse : public ReachableUniverseContent {
    friend class FacBomContent;

  public:
    // //////////////////////////////////////////////////////////////////
    // See the explanations, within the BomRoot class, for all
    // the types which require to be specified below
    // //////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef ReachableUniverseStructure_T Structure_T;

    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef BomRoot Parent_T;

    /** Definition allowing to retrieve the map/multimap type using by
        BomChildrenHolder. */
    typedef std::map<const MapKey_T, const Structure_T*> Map_T;

    /** Define the list of children holder types. */
#if BOOST_VERSION >= 103500
    typedef boost::fusion::map<
      boost::fusion::pair<OriginDestinationSet, OriginDestinationSetHolder_T*>
      > ChildrenHolderMap_T;
#else // BOOST_VERSION >= 103500
    typedef boost::mpl::map< > ChildrenHolderMap_T;
#endif // BOOST_VERSION >= 103500
    // //////////////////////////////////////////////////////////////////
    
  public:
    // /////////// Getters /////////////
    /** Get the parent object. */
    const Parent_T& getParent () const;

    /** Get a list or map of a children type for iteration methods. */
    OriginDestinationSetList_T getOriginDestinationSetList () const;
    OriginDestinationSetMap_T getOriginDestinationSetMap () const;

    /** Retrieve, if existing, the OriginDestinationSet corresponding to the
        given airport.
        <br>If not existing, return the NULL pointer. */
    OriginDestinationSet* getOriginDestinationSet (const AirportCode_T&) const;

    /** Get the SegmentPathPeriodListList. */
    const SegmentPathPeriodListList_T& getSegmentPathPeriodListList () const {
      return _segmentPathPeriodListList;
    }
    
  public:
    // //////////// Business Methods //////////////
    /** Add a segment path period to the dedicated list. **/
    void addSegmentPathPeriod (const SegmentPathPeriod&);    
       
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
    ReachableUniverse (const Key_T&, Structure_T&);
    /** Destructor. */
    ~ReachableUniverse();
    /** Initialise all the pointers of children holder to NULL. */
    void init();
    /** Default constructors. */
    ReachableUniverse ();
    ReachableUniverse (const ReachableUniverse&);

  protected:
    // Attributes
    /** Reference structure. */
    Structure_T& _structure;

    /** The list of lists of SegmentPathPeriods, used uniquement for the
        construction of the main list of SegmentPathPeriods in
        ReachableUniverseStructure. */
    SegmentPathPeriodListList_T _segmentPathPeriodListList;

  };

}
#endif // __STDAIR_BOM_REACHABLEUNIVERSE_HPP

