#ifndef __STDAIR_BOM_FLIGHTPERIOD_HPP
#define __STDAIR_BOM_FLIGHTPERIOD_HPP

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
#include <stdair/bom/FlightPeriodContent.hpp>
#include <stdair/bom/FlightPeriodTypes.hpp>
#include <stdair/bom/SegmentPeriodTypes.hpp>

namespace stdair {
  // Forward declarations
  class Inventory;
  class SegmentPeriod;
  struct SegmentPeriodKey_T;
  
  /** Class representing the actual functional/business content for a
      flight-period. */
  class FlightPeriod : public FlightPeriodContent {
    friend class FacBomContent;

  public:
    // Type definitions
    // //////////////////////////////////////////////////////////////////
    // See the explanations, within the BomRoot class, for all
    // the types which require to be specified below
    // //////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef FlightPeriodStructure_T Structure_T;

    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef Inventory Parent_T;

    /** Definition allowing to retrieve the map/multimap type using by
        BomChildrenHolder. */
    typedef std::map<const MapKey_T, const Structure_T*> Map_T;

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

    /** Retrieve, if existing, the SegmentPeriod corresponding to the
        given SegmentPeriod key.
        <br>If not existing, return the NULL pointer. */
    SegmentPeriod* getSegmentPeriod (const SegmentPeriodKey_T&) const;
  
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
    FlightPeriod (const Key_T&, Structure_T&);
    /** Destructor. */
    ~FlightPeriod();
    /** Initialise all the pointers of children holder to NULL. */
    void init();
    /** Default constructors. */
    FlightPeriod ();
    FlightPeriod (const FlightPeriod&);

  protected:
    // Attributes
    /** Reference structure. */
    Structure_T& _structure;
  };

}
#endif // __STDAIR_BOM_FLIGHTPERIOD_HPP

