#ifndef __STDAIR_BOM_FLIGHTDATE_HPP
#define __STDAIR_BOM_FLIGHTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/FlightDateContent.hpp>
#include <stdair/bom/FlightDateTypes.hpp>
#include <stdair/bom/SegmentDateTypes.hpp>
#include <stdair/bom/LegDateTypes.hpp>

namespace stdair {
  // Forward declarations
  class Inventory;
  class LegDate;
  class SegmentDate;
  struct SegmentDateKey_T;
  
  /** Class representing the actual functional/business content for a
      flight-date. */
  class FlightDate : public FlightDateContent {
    friend class FacBomContent;

  public:
    // Type definitions
    // //////////////////////////////////////////////////////////////////
    // See the explanations, within the BomRoot class, for all
    // the types which require to be specified below
    // //////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef FlightDateStructure_T Structure_T;

    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef Inventory Parent_T;

    /** Definition allowing to retrieve the map/multimap type using by
        BomChildrenHolder. */
    typedef std::map<const MapKey_T, const Structure_T*> Map_T;

    /** Define the list of children holder types. */
    typedef boost::fusion::map<
      boost::fusion::pair<LegDate, LegDateHolder_T*>,
      boost::fusion::pair<SegmentDate, SegmentDateHolder_T*>
      > ChildrenHolderMap_T;
    // //////////////////////////////////////////////////////////////////

  public:
    // /////////// Getters /////////////
    /** Get a list or map of a children type for iteration methods. */
    SegmentDateList_T getSegmentDateList () const;
    SegmentDateMap_T getSegmentDateMap () const;
    LegDateList_T getLegDateList () const;
    LegDateMap_T getLegDateMap () const;

    /** Retrieve, if existing, the LegDate corresponding to the
        given boarding point.
        <br>If not existing, return the NULL pointer. */
    LegDate* getLegDate (const AirportCode_T&) const;

    /** Retrieve, if existing, the SegmentDate corresponding to the
        given SegmentDate key.
        <br>If not existing, return the NULL pointer. */
    SegmentDate* getSegmentDate (const SegmentDateKey_T&) const;
  
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
    FlightDate (const Key_T&, Structure_T&);
    /** Destructor. */
    ~FlightDate();
    /** Initialise all the pointers of children holder to NULL. */
    void init();
    /** Default constructors. */
    FlightDate ();
    FlightDate (const FlightDate&);

  protected:
    // Attributes
    /** Reference structure. */
    Structure_T& _structure;
  };

}
#endif // __STDAIR_BOM_FLIGHTDATE_HPP

