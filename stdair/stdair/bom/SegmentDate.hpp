#ifndef __STDAIR_BOM_SEGMENTDATE_HPP
#define __STDAIR_BOM_SEGMENTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/SegmentDateStructure.hpp>
#include <stdair/bom/SegmentDateTypes.hpp>
#include <stdair/bom/SegmentCabinTypes.hpp>
#include <stdair/bom/SegmentDateContent.hpp>

namespace stdair {
  // Forward declarations
  class FacBomContent;
  struct SegmentDateKey_T;

  /** Class representing the actual functional/business content for a
      segment-date. */
  class SegmentDate : public SegmentDateContent {
    friend class FacBomContent;

  public:
    // Type definitions
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef FlightDate Parent_T;

    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef SegmentDateStructure_T BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef SegmentDateKey_T BomKey_T;

    /** Definition allowing to retrieve the associated 
         BOM content child type. */
    typedef SegmentCabin ContentChild_T;
        
  public:
    // /////////// Getters /////////////
    /** Get a SegmentCabinList_T for iteration methods. */
    SegmentCabinList_T getSegmentCabinList () const;

    /** Get a SegmentCabinMap_T for iteration methods. */
    SegmentCabinMap_T getSegmentCabinMap () const;

//     /** Get the airline code (from the parent class). */
//     const AirlineCode_T& getAirlineCode() const;
      
//     /** Get the flight number (from the parent class). */
//     const FlightNumber_T& getFlightNumber() const;

//     /** Get the flight-date (from the parent class). */
//     const Date_T& getFlightDateDate() const;
      
    /** Retrieve the BookingClass corresponding to the given ClassCode.
        <br>When no BookingClass, matching the given key, can be found,
        the NULL pointer is returned.
        <br>Otherwise, a pointer is returned on the BookingClass object. */
    //BookingClass* getBookingClass (const ClassCode_T&) const;
      
  private:
    /** Retrieve the BOM structure object. */
    BomStructure_T& getBomStructure () {
      return _segmentDateStructure;
    }

  public:
    // /////////// Business Methods //////////////
    /** States whether or not the given SegmentDate may connect with the
        current one.
        <br>Basically, the board time of the given SegmentDate should be
        such as to allow the passenger connecting from the previous flight
        (current SegmentDate object) to the next one (given SegmentDate). */
    //    bool isConnectable (const SegmentDate&) const;

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
    
    /** Display the full SegmentDate context. */
    // const std::string display() const;
    
    /** Display the SegmentDate context. */
    //    const std::string displayLimitedInformations () const;


  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    SegmentDate ();
    SegmentDate (const SegmentDate&);
    SegmentDate (const BomKey_T&, BomStructure_T&);

    /** Destructor. */
    virtual ~SegmentDate();

  protected:
    // Attributes
    /** Reference structure. */
    BomStructure_T& _segmentDateStructure;
    
//     /** Map between ClassCode and SegmentCabin pointer. */
//     ClassSegmentCabinList_T _classSegmentCabinList;

//     /** List of routing LegDate objects. */
//     LegDateOrderedList_T _legDateList;
    
    /** MultiMap linking MatchingIndicator values
        and BookingClass. */
    //    BookingClassIndicatorList_T _classIndicatorList;
  };

}
#endif // __STDAIR_BOM_SEGMENTDATE_HPP

