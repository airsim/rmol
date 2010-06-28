#ifndef __STDAIR_BOM_SEGMENTPATHPERIOD_HPP
#define __STDAIR_BOM_SEGMENTPATHPERIOD_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost Fusion
#include <boost/version.hpp>
#if BOOST_VERSION >= 103500
#include <boost/fusion/include/map.hpp>
#else // BOOST_VERSION >= 103500
#include <boost/mpl/map.hpp>
#endif // BOOST_VERSION >= 103500
// StdAir 
#include <stdair/bom/SegmentPathPeriodContent.hpp>
#include <stdair/bom/SegmentPathPeriodTypes.hpp>
#include <stdair/bom/SegmentPeriodTypes.hpp>

namespace stdair {
  // Forward declarations
  class OriginDestinationSet;
  class SegmentPeriod;

  /** Class representing the actual functional/business content for a
      outbound path. */
  class SegmentPathPeriod : public SegmentPathPeriodContent {
    friend class FacBomContent;

  public:
    // //////////////////////////////////////////////////////////////////
    // See the explanations, within the BomRoot class, for all
    // the types which require to be specified below
    // //////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef SegmentPathPeriodStructure_T Structure_T;

    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef OriginDestinationSet Parent_T;

    /** Definition allowing to retrieve the map/multimap type using by
        BomChildrenHolder. */
    typedef std::multimap<const MapKey_T, const Structure_T*> Map_T;

    /** Define the list of children holder types. */
#if BOOST_VERSION >= 103500
    typedef boost::fusion::map<
      boost::fusion::pair<SegmentPeriod, SegmentPeriodHolder_T*>
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
    SegmentPeriodList_T getSegmentPeriodList () const;
    SegmentPeriodMap_T getSegmentPeriodMap () const;

    /** Get the last SegmentPeriod (constant) object of the list.
        <br>Return a NULL pointer if the list is empty. */
    const SegmentPeriod* getLastSegmentPeriod () const;

    /** Get the first SegmentPeriod (constant) object of the list.
        <br>Return a NULL pointer if the list is empty. */
    const SegmentPeriod* getFirstSegmentPeriod () const;

    /** Get the destination of the segment path (i.e., the destination
        of the last segment. */
    const AirportCode_T& getDestination () const;

  public:
    /** Check if the (i-1)-length segment path period can be fused with the
        single segment segment path period in order to create an i-length
        segment path period. The function will return a valid or non-valid
        segment path period key.
        <br>The two segment path period above can be fused (and will produce a
        valid new segment path period key) if:
        1. A passenger can connect from the last segment of the
        first segment path and the first segment of the next segment path.
        These two segments should not create another segment.
        2. There is no circle within the new segment path.
        3. The intersection of the two periods is non-empty.
    */
    const SegmentPathPeriodKey_T connectWithAnotherSegment (const SegmentPathPeriod&) const;
    
    /** States whether or not the given SegmentPathPeriod may connect with the
        current one.
        <br>Basically, the board time of the given SegmentPathPeriod should be
        such as to allow the passenger connecting from the previous flight
        (current SegmentPathPeriod object) to the next one
        (given SegmentPathPeriod).
        <br>Note that this method relies on the eponym method of the
        SegmentPeriod class. */
    bool isConnectable (const SegmentPathPeriod&) const;

    /** Check if the given destination airport the departure point of
        one of the segment member. If yes, a circle exists. */
    bool checkCircle (const AirportCode_T&) const;

    /** State whether or not the given airline is flown by (at least) one of
        the segments of the internal list. */
    bool isAirlineFlown (const AirlineCode_T&) const;
        
    /** Update Airline Code. */
    void updateAirlineCode ();

    /** Update the total flight time and the flight path code after
        adding a segment-date. */
    void updateAfterAddingSegmentPeriod (const SegmentPeriod&);

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
    SegmentPathPeriod (const Key_T&, Structure_T&);
    /** Destructor. */
    ~SegmentPathPeriod();
    /** Initialise all the pointers of children holder to NULL. */
    void init();
    /** Default constructors. */
    SegmentPathPeriod ();
    SegmentPathPeriod (const SegmentPathPeriod&);

  protected:
    // Attributes
    /** Reference structure. */
    Structure_T& _structure;
  };

}
#endif // __STDAIR_BOM_SEGMENTPATHPERIOD_HPP

