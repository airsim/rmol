#ifndef __STDAIR_BOM_FLIGHTDATE_HPP
#define __STDAIR_BOM_FLIGHTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDateStructure.hpp>
#include <stdair/bom/FlightDateTypes.hpp>
#include <stdair/bom/SegmentDateTypes.hpp>
#include <stdair/bom/LegDateTypes.hpp>
#include <stdair/bom/FlightDateContent.hpp>

namespace stdair {
  // Forward declarations
  class FacBomContent;
  struct FlightDateKey_T;
  
  /** Class representing the actual functional/business content for a
      flight-date. */
  class FlightDate : public FlightDateContent {
    friend class FacBomContent;

  public:
    // Type definitions
    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the BomRoot class, for all
    // the types which require to be specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef Inventory Parent_T;

    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef FlightDateStructure_T BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef FlightDateKey_T BomKey_T;

    /** Definition allowing to retrieve the associated 
         BOM content child type. */
    typedef SegmentDate ContentChild_T;

    /** Definition allowing to retrieve the associated second
        BOM content child type. */
    typedef LegDate SecondContentChild_T;

    /** Definition allowing to retrieve the specific BookingClass type. */
    typedef BookingClass BookingClassContent_T;

  public:
    // /////////// Getters /////////////
    /** Get a SegmentDateList_T for iteration methods. */
    SegmentDateList_T getSegmentDateList () const;

    /** Get a SegmentDateMap_T for iteration methods. */
    SegmentDateMap_T getSegmentDateMap () const;

    /** Get a LegDateList_T for iteration methods. */
    LegDateList_T getLegDateList () const;

    /** Get a LegDateMap_T for iteration methods. */
    LegDateMap_T getLegDateMap () const;
    
    /** Get the airline code (from the parent class). */
    //    const AirlineCode_T& getAirlineCode() const;
          
    /** Retrieve, if existing, the LegDate corresponding to the
        given LegDate key.
        <br>If not existing, return the NULL pointer. */
    LegDate* getLegDate (const LegDateKey_T&) const;

    /** Retrieve, if existing, the SegmentDate corresponding to the
        given SegmentDate key.
        <br>If not existing, return the NULL pointer. */
    SegmentDate* getSegmentDate (const SegmentDateKey_T&) const;

    /** Return the BookingClass corresponding to a given key.
        <br>When no BookingClass, matching the given key, can be found,
        the NULL pointer is returned.
        <br>Otherwise, a pointer is returned on the BookingClass object. */
    BookingClass* getBookingClass (const BookingClassKey_T&) const;

//     /** Retrieve, if existing, theOnD corresponding to the
//         given OnDKey.
//         <br>If not existing, return the NULL pointer. */
//     OnD* getOnD (const OnDKey_T& iOnDKey) const;
  
  private:
    /** Retrieve the BOM structure object. */
    BomStructure_T& getBomStructure () {
      return _flightDateStructure;
    }

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
    
    /** Display the full FlightDate context. */
    //const std::string display() const;

  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    FlightDate ();
    FlightDate (const FlightDate&);
    FlightDate (const BomKey_T&, BomStructure_T&);

    /** Destructor. */
    virtual ~FlightDate();

  protected:
    // Attributes
    /** Reference structure. */
    BomStructure_T& _flightDateStructure;
    
//     /** Children: list of BookingClass objects. */
//     BookingClassMap_T _bookingClassList;

//     /** List of similar flight date (for RM purposes). */
//     FlightDateList_T _similarFlightDateList;

//     /** List of OnDs. */
//     OnDList_T _onDList;

  };

}
#endif // __STDAIR_BOM_FLIGHTDATE_HPP

