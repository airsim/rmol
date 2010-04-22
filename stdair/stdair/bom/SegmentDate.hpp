#ifndef __STDAIR_BOM_SEGMENTDATE_HPP
#define __STDAIR_BOM_SEGMENTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/SegmentDateContent.hpp>
#include <stdair/bom/SegmentDateTypes.hpp>
#include <stdair/bom/LegDateTypes.hpp>
#include <stdair/bom/SegmentCabinTypes.hpp>

namespace stdair {
  // Forward declarations
  class FlightDate;
  class LegDate;
  class SegmentCabin;
  
  /** Class representing the actual functional/business content for a
      segment-date. */
  class SegmentDate : public SegmentDateContent {
    friend class FacBomContent;

  public:
    // //////////////////////////////////////////////////////////////////
    // See the explanations, within the BomRoot class, for all
    // the types which require to be specified below
    // //////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef SegmentDateStructure_T Structure_T;

    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef FlightDate Parent_T;

    /** Define the list of children holder types. */
    typedef boost::fusion::map<
      boost::fusion::pair<SegmentCabin, SegmentCabinHolder_T*>,
      boost::fusion::pair<LegDate, LegDateHolder_T*>
      > ChildrenHolderMap_T;
    // //////////////////////////////////////////////////////////////////
        
  public:
    // /////////// Getters /////////////
    /** Get a list or map of a children type for iteration methods. */
    SegmentCabinList_T getSegmentCabinList () const;
    SegmentCabinMap_T getSegmentCabinMap () const;
    LegDateList_T getLegDateList () const;
    LegDateMap_T getLegDateMap () const;

    /** Get the flight number of the segment. */
    const FlightNumber_T& getFlightNumber () const;
    
    /** Get the airline code of the segment. */
    const AirlineCode_T& getAirlineCode () const;

  public:
    // /////////// Business Methods //////////////
    /** States whether or not the given SegmentDate may connect with the
        current one.
        <br>Basically, the board time of the given SegmentDate should be
        such as to allow the passenger connecting from the previous flight
        (current SegmentDate object) to the next one (given SegmentDate). */
    bool isConnectable (const SegmentDate&) const;

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
    SegmentDate (const Key_T&, Structure_T&);
    /** Destructor. */
    ~SegmentDate();
    /** Initialise all the pointers of children holder to NULL. */
    void init();
    /** Default constructors. */
    SegmentDate ();
    SegmentDate (const SegmentDate&);

  protected:
    // Attributes
    /** Reference structure. */
    Structure_T& _structure;
    
  };

}
#endif // __STDAIR_BOM_SEGMENTDATE_HPP

