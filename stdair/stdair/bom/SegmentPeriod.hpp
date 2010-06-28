#ifndef __STDAIR_BOM_SEGMENTPERIOD_HPP
#define __STDAIR_BOM_SEGMENTPERIOD_HPP

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
#include <stdair/bom/SegmentPeriodContent.hpp>
#include <stdair/bom/SegmentPeriodTypes.hpp>

namespace stdair {
  // Forward declarations
  class FlightPeriod;
  
  /** Class representing the actual functional/business content for a
      segment-period. */
  class SegmentPeriod : public SegmentPeriodContent {
    friend class FacBomContent;

  public:
    // Type definitions
    // //////////////////////////////////////////////////////////////////
    // See the explanations, within the BomRoot class, for all
    // the types which require to be specified below
    // //////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef SegmentPeriodStructure_T Structure_T;

    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef FlightPeriod Parent_T;

    /** Definition allowing to retrieve the map/multimap type using by
        BomChildrenHolder. */
    typedef std::map<const MapKey_T, const Structure_T*> Map_T;

    /** Define the list of children holder types. */
#if BOOST_VERSION >= 103500
    typedef boost::fusion::map< > ChildrenHolderMap_T;
#else // BOOST_VERSION >= 103500
    typedef boost::mpl::map< > ChildrenHolderMap_T;
#endif // BOOST_VERSION >= 103500
    // //////////////////////////////////////////////////////////////////
 
  public:
    // /////////// Getters /////////////
    /** Get the parent object. */
    const Parent_T& getParent () const;

    /** Get the departure date range. */
    const DatePeriod_T& getDeparturePeriod () const;

    /** Get the active days-of-week. */
    const DoWStruct_T& getDoW () const;

  public:
    // /////////// Business Methods //////////////
    /** States whether or not the given SegmentPeriod may connect with the
        current one.
        <br>Basically, the board time of the given SegmentPeriod should be
        such as to allow the passenger connecting from the previous flight
        (current SegmentPeriod object) to the next one (given SegmentPeriod). */
    bool isConnectable (const SegmentPeriod&) const;

  
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
    SegmentPeriod (const Key_T&, Structure_T&);
    /** Destructor. */
    ~SegmentPeriod();
    /** Initialise all the pointers of children holder to NULL. */
    void init();
    /** Default constructors. */
    SegmentPeriod ();
    SegmentPeriod (const SegmentPeriod&);

  protected:
    // Attributes
    /** Reference structure. */
    Structure_T& _structure;
  };

}
#endif // __STDAIR_BOM_SEGMENTPERIOD_HPP

