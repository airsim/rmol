#ifndef __STDAIR_BOM_SEGMENTCABIN_HPP
#define __STDAIR_BOM_SEGMENTCABIN_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/SegmentCabinStructure.hpp>
#include <stdair/bom/SegmentCabinContent.hpp>
#include <stdair/bom/SegmentCabinTypes.hpp>
#include <stdair/bom/BookingClassTypes.hpp>

namespace stdair {
  // Forward declarations
  class FacBomContent;
  struct SegmentCabinKey_T;

  /** Class representing the actual functional/business content for a
      segment-date. */
  class SegmentCabin : public SegmentCabinContent {
    friend class FacBomContent;

  public:
    // Type definitions
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef SegmentDate Parent_T;

    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef SegmentCabinStructure_T BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef SegmentCabinKey_T BomKey_T;

    /** Definition allowing to retrieve the associated 
         BOM content child type. */
    typedef BookingClass ContentChild_T;
   
  public:
    // /////////// Getters /////////////
    /** Get a BookingClassList_T for iteration methods. */
    BookingClassList_T getBookingClassList () const;

    /** Get a BookingClassMap_T for iteration methods. */
    BookingClassMap_T getBookingClassMap () const;

    /** Retrieve the BookingClass corresponding to the given key.
        <br>The BookingClass key is a combination of both the SegmentCabin
        key and of the BookingClass code.
        <br>When no BookingClass, matching the given key, can be found,
        the NULL point is returned.
        <br>Otherwise, a pointer is returned on the BookingClass object. */
    //BookingClass* getBookingClass (const BookingClassKey_T&) const;

    /** Retrieve the BookingClass corresponding to the given ClassCode.
        <br>A temporary BookingClass key is built, from the combination
        of both the SegmentCabin key and of the BookingClass code. Then,
        the getBookingClass() method is called with that BookingClass key.
        <br>When no BookingClass, matching the given key, can be found,
        the NULL point is returned.
        <br>Otherwise, a pointer is returned on the BookingClass object. */
    //BookingClass* getBookingClass (const ClassCode_T& iClassCode) const;

    /** Retrieve the load factor threshold corresponding to the given ClassCode.
        <br>A temporary BookingClass key is built, from the combination
        of both the SegmentCabin key and of the BookingClass code. 
        <br>When no item, matching the given key, can be found,
        the default value of load factor is returned and a warning message is logged out.
        <br>Otherwise, the load factor value is returned. */
    //const Percentage_T getLoadFactor (const BookingClassKey_T&) const;

    /** Retrieve the DTD threshold corresponding to the given ClassCode.
        <br>A temporary BookingClass key is built, from the combination
        of both the SegmentCabin key and of the BookingClass code.
        <br>When no item, matching the given key, can be found,
        the default value of DTD is returned and a warning message is logged out.
        <br>Otherwise, the DTD value is returned. */
    //const DayDuration_T getDTD (const BookingClassKey_T&) const;

//     /** Get the airline code (from the parent class). */
//     const AirlineCode_T& getAirlineCode() const;
      
//     /** Get the flight number (from the parent class). */
//     const FlightNumber_T& getFlightNumber() const;

//     /** Get the flight-date (from the parent class). */
//     const Date_T& getFlightDateDate() const;
      
//     /** Get the board point (from the parent class). */
//     const AirportCode_T& getBoardPoint () const;

//     /** Get the off point (from the parent class). */
//     const AirportCode_T& getOffPoint () const;

//     /** Get the board date (from the parent class). */
//     const Date_T& getBoardDate () const;

//     /** Get the board time (from the parent class). */
//     const Duration_T& getBoardTime () const;

//     /** Get the off date (from the parent class). */
//     const Date_T& getOffDate () const;

//     /** Get the off time (from the parent class). */
//     const Duration_T& getOffTime () const;

//     /** Get the elapsed time (from the parent class). */
//     const Duration_T& getElapsedTime() const;

//     /** Get the distance (from the parent class). */
//     const Distance_T& getDistance() const;

//     /** Get the date off set  (from the parent class). */
//     const DateOffSet_T getDateOffSet () const;

//     /** Get the time off set between board and off points (from the
//         parent class). */
//     const Duration_T getTimeOffSet() const;

//     /** Get the reference on the PolicyHolder. */
//     PolicyHolder& getPolicyHolder() const;

  private:
    /** Retrieve the BOM structure object. */
    BomStructure_T& getBomStructure () {
      return _segmentCabinStructure;
    }

  public:
    // //////////// Setters ///////////
    /** Set the PolicyHolder. */
//     void setPolicyHolder (PolicyHolder& iPolicyHolder) {
//       _FFPolicyHolder = &iPolicyHolder;
//     }
     
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
    
    /** Display the full SegmentCabin context. */
    //const std::string display() const;
    
  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    SegmentCabin ();
    SegmentCabin (const SegmentCabin&);
    SegmentCabin (const BomKey_T&, BomStructure_T&);

    /** Destructor. */
    virtual ~SegmentCabin();

  protected:
    // Attributes
    /** Reference structure. */
    BomStructure_T& _segmentCabinStructure;
    
    /** List of routing LegCabin objects. */
    // LegCabinList_T _legCabinList;
    
    /** List of threshold DTD. */
    //DTDThresholdList_T _rmsDtdList;

//     /** List of fare family objects. */
//     FareFamilyList_T _fareFamilyList;

//     /** List of load factors. */
//     LoadFactorList_T _rmsLoadFactorList;

//     /** PolicyHolder of the FareFamily policies*/
//     PolicyHolder* _FFPolicyHolder;

  };

}
#endif // __STDAIR_BOM_SEGMENTCABIN_HPP

