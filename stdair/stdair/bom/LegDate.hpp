#ifndef __STDAIR_BOM_LEGDATE_HPP
#define __STDAIR_BOM_LEGDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/LegDateStructure.hpp>
#include <stdair/bom/LegDateContent.hpp>
#include <stdair/bom/LegDateTypes.hpp>
#include <stdair/bom/LegCabinTypes.hpp>

namespace stdair {
  // Forward declarations
  class FacBomContent;
  struct LegDateKey_T;
  struct LegCabinKey_T;

  /** Class representing the actual functional/business content for a
      leg-date. */
  class LegDate : public LegDateContent {
    friend class FacBomContent;

  public:
    // Type definitions
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef FlightDate Parent_T;

    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef LegDateStructure_T BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef LegDateKey_T BomKey_T;

    /** Definition allowing to retrieve the associated 
         BOM content child type. */
    typedef LegCabin ContentChild_T;
    
    /** Definition allowing to retrieve the specific SegmentDate type. */
    typedef SegmentDate SegmentDateContent_T;
    
  public:
    // /////////// Getters ////////////
    //     /** Get the airline code (from the parent class). */
    //     const AirlineCode_T& getAirlineCode() const;
    
    //     /** Get the flight number (from the parent class). */
    //     const FlightNumber_T& getFlightNumber() const;
    
    //     /** Get the flight-date (from the parent class). */
    //     const Date_T& getFlightDateDate() const;
    
    /** Retrieve, if existing, the LegCabin corresponding to the
        given LegCabin key.
        <br>If not existing, return the NULL pointer. */
    LegCabin* getLegCabin (const LegCabinKey_T&) const;
    
    //  // ///////// Counting methods  //////////
    //     /** Update the counters of booked seats. */
//     void updateBookingsAndSeatCounters();

//     /** Update the values of commited spaces. */
//     void updateCommitedSpaces() const;
      
//     /** Update the availability pools for Legs. */
//     void updateAvailabilityPools() const;
      
//     /** Update the availabilities for Legs. */
//     void updateAllAvailabilities() const;

//     /** Reset the LegDate to its initial state. */
//     void reset();

//     /** Update the capacity and the ASK value of this leg.*/ 
//     void updateCapacityAndLegASK(const CabinCapacity_T&,
//                                  const AnalysisStatus_T&);
    
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
    
  public:
    // /////////// Getters /////////////
    /** Get a LegCabinList_T for iteration methods. */
    LegCabinList_T getLegCabinList () const;

    /** Get a LegCabinMap_T for iteration methods. */
    LegCabinMap_T getLegCabinMap () const;

    /** Retrieve, if existing, the SegmentDate corresponding to the
        given board point.
        <br>If not existing, return the NULL pointer. */
    // SegmentDate* getSegmentDate (const std::string& iSegmentDateKey) const;


  private:
    /** Retrieve the BOM structure object. */
    BomStructure_T& getBomStructure () {
      return _legDateStructure;
    }

  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    LegDate ();
    LegDate (const LegDate&);
    LegDate (const BomKey_T&, BomStructure_T&);

    /** Destructor. */
    virtual ~LegDate();

  protected:
    // Attributes
    /** Reference structure. */
    BomStructure_T& _legDateStructure;

    /** List of crossing SegmentDate objects. */
    //SegmentDateMap_T _segmentDateList;
    
  };

}
#endif // __STDAIR_BOM_LEGDATE_HPP

