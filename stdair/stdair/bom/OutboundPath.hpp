#ifndef __STDAIR_BOM_OUTBOUNDPATH_HPP
#define __STDAIR_BOM_OUTBOUNDPATH_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/AirportDate.hpp>
#include <stdair/bom/OutboundPathStructure.hpp>
#include <stdair/bom/OutboundPathContent.hpp>
#include <stdair/bom/AirportDateTypes.hpp>
#include <stdair/bom/OutboundPathTypes.hpp>
#include <stdair/bom/SegmentDateTypes.hpp>

namespace stdair {
  // Forward declarations
  class FacBomContent;
  class SegmentDate;
  struct OutboundPathKey_T;

  /** Class representing the actual functional/business content for a
      outbound path. */
  class OutboundPath : public OutboundPathContent {
    friend class FacBomContent;

  public:
    // Type definitions
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef AirportDate Parent_T;

    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef OutboundPathStructure_T BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef OutboundPathKey_T BomKey_T;

    /** Definition allowing to retrieve the associated 
         BOM content child type. */
    typedef OutboundPath ContentChild_T;

    /** Definition allowing to retrieve the specific SegmentDate type. */
    typedef SegmentDate SegmentDateContent_T;

  public:
    // /////////// Getters /////////////
    /** Get a SegmentDateList_T for iteration methods. */
    SegmentDateList_T getSegmentDateList () const;

    /** Get a SegmentDateMap_T for iteration methods. */
    SegmentDateMap_T getSegmentDateMap () const;

    /** Get the off date. */
    const Date_T& getOffDate () const;
    
    /** Get the last SegmentDate (constant) object of the list.
        <br>Return a NULL pointer if the list is empty. */
    const SegmentDate* getLastSegmentDate () const;

    /** Get the first SegmentDate (constant) object of the list.
        <br>Return a NULL pointer if the list is empty. */
    const SegmentDate* getFirstSegmentDate () const;

    
  public:
    // ///////// Setters //////////      

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

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const;

  private:
    // ////////////// Business methods //////////////
    /** Increments the total flight time of the outbound path.*/
    void incrementTotalFlightTime (const Duration_T&);

  public:
    /** Get the AirportDate corresponding to the destination of the
        outbound-path, i.e., the off point of the last segment-date
        of the (segment) list.
        <br>Return the NULL pointer if there is no such AirportDate object,
        e.g., when the destination is an end point (i.e., when no other
        SegmentDate is starting from the destination). */
    AirportDate* getDestinationAirportDate() const;

    /** States whether or not the given OutboundPath may connect with the
        current one.
        <br>Basically, the board time of the given OutboundPath should be
        such as to allow the passenger connecting from the previous flight
        (current OutboundPath object) to the next one (given OutboundPath).
        <br>Note that this method relies on the eponym method of the
        SegmentDate class. */
    bool isConnectable (const OutboundPath&) const;

    /** State whether or not the given airline is flown by (at least) one of
        the segments of the internal list. */
    bool isAirlineFlown (const AirlineCode_T&) const;
    
    /** Calculate the elapsed time according to the segment routing.
        <br>Note that the given segment-date should come at the end of the
        outbound-path. An assertion will fail if the given board point and
        board date do not correspond to the off point and off date of the
        last segment-date of the outbound-path.
        <br>That method is a helper function allowing calculating the
        elapsed time of a to-be-built OutboundPath object. Indeed, the
        elapsed time can not be set after the object creation, as it is
        part of the primary key (needed at the time of object creation).
        <br>Actually, the elapsed time of the outbound path is the sum of the
        elapsed times of the routing segments, plus the stop-over times.
        The stop-over time is the difference between the board time of a
        routing segment, and the off time of the previous segment. That is,
        it is the time spent at the corresponding airport.
        <br>Of course, in case of mono-segment outbound pathes, there is no
        stop-over, and the elapsed time of the outbound-path is equal to the
        elapsed time of the single routing segment. */
    const Duration_T calculateElapsedTimeFromRouting ()const;


  public:
    // ////////////// Business methods //////////////
    /** Update Airline Code. */
    void updateAirlineCode ();
    
  private:
    /** Retrieve the BOM structure object. */
    BomStructure_T& getBomStructure () {
      return _outboundPathStructure;
    }

  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    OutboundPath ();
    OutboundPath (const OutboundPath&);
    OutboundPath (const BomKey_T&, BomStructure_T&);

    /** Destructor. */
    virtual ~OutboundPath();

  protected:
    // Attributes
    /** Reference structure. */
    BomStructure_T& _outboundPathStructure;
  };

}
#endif // __STDAIR_BOM_OUTBOUNDPATH_HPP

