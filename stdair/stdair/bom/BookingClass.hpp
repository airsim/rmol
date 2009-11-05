#ifndef __STDAIR_BOM_BOOKINGCLASS_HPP
#define __STDAIR_BOM_BOOKINGCLASS_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/BookingClassStructure.hpp>
#include <stdair/bom/BookingClassContent.hpp>
#include <stdair/bom/SegmentCabinTypes.hpp>
#include <stdair/bom/BookingClassTypes.hpp>

namespace stdair {
  // Forward declarations
  class FacBomContent;
  struct BookingClassKey_T;

  /** Class representing the actual functional/business content for a
      segment-cabin. */
  class BookingClass : public BookingClassContent {
    friend class FacBomContent;

  public:
    // Type definitions
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef SegmentCabin Parent_T;

    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef BookingClassStructure_T BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef BookingClassKey_T BomKey_T;

    /** Definition allowing to retrieve the associated 
         BOM content child type. */
    typedef BookingClass ContentChild_T;

  public:
    // /////////// Getters /////////////
    /** Get the FareFamily (parent class). */
    // FareFamily* getFareFamily() const {
//       return _fareFamily;
//     }

    // ////// Getters from the parent class ///////
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

//     /** Get the cabin code (from the parent class). */
//     const CabinCode_T& getCabinCode () const;
      
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

//     /** Retrieve, if existing, theOnD corresponding to the
//         given OnDKey.
//         <br>If not existing, return the NULL pointer. */
//     OnD* getOnD (const OnDKey_T& iOnDKey) const;

//     /** Get the size of the OnD list. */
//     const unsigned int getOnDListSize () const {
//       return _onDList.size();
//     }

//     /** Get the list of OnDs related to this class. */
//     const OnDList_T& getOnDList() const {
//       return _onDList;
//     }

  public:
    // ///////// Setters //////////      
    /** Set the Fare family (parent class). */
//     void setFareFamily (FareFamily& ioFareFamily) {
//       _fareFamily = &ioFareFamily;
//     }
    
    /** Reset the number of bookings to its intial state. */
    //void reset ();

//     /** Reset the booking fare. */
//     void resetFare();

//     /** Reset the booking yield. */
//     void resetYield();

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

    /** Give a description of the structure (for display purposes). */
    //const std::string describe() const;

     /** Get a string describing the solution (Fare, MatchIndicator...). */
    //const std::string describeSolution() const;

  public:
    // ///////// Business Methods //////////
    /** Update the number of bookings. */
//     bool updateInventoryForReservation (const NbOfBookings_T&);

//     /** Update the number of cancellations. */
//     bool updateInventoryForCancellation (const NbOfCancellations_T&);

//     /** Update the number of no-shows. */
//     bool updateInventoryForNoShow (const NbOfNoShows_T&);

      
//     /** Update the revenue of the booking. */
//     bool updateRevenue (const NbOfBookings_T&, const Fare_T&,
//                         const AnalysisStatus_T&);

//     /** Add the current censorship flag into the flag list. */
//     void addCurrentCensorshipFlagToTheFlagList();

//     /** Build the Class-Segment code (for example:B-NCE-BKK->BNCEBKK). */
//     const std::string buildClassSegmentCode() const;

//     /** Insert a new OnD reference. */
//     void addOnD (OnD&);

//     /** Calculate the ratio of booking for this booking only
//         (without OnD bookings). */
//     const BookingRatio_T calculateNetProductRatio();

  protected:
    /** Update some statistics of the SegmentCabin parent object.*/
//     void updateParentStatistics (const Revenue_T&,
//                                  const NbOfBookings_T&) const;
  
  private:
    /** Retrieve the BOM structure object. */
    BomStructure_T& getBomStructure () {
      return _bookingClassStructure;
    }

  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    BookingClass ();
    BookingClass (const BookingClass&);
    BookingClass (const BomKey_T&, BomStructure_T&);

    /** Destructor. */
    virtual ~BookingClass();

  protected:
    // Attributes
    /** Reference structure. */
    BomStructure_T& _bookingClassStructure;
    
    /** Parent class: FareFamily. */
//     FareFamily* _fareFamily;
    
//     /** List of OnD references related to this bookingClass. */
//     OnDList_T _onDList;
  };

}
#endif // __STDAIR_BOM_BOOKINGCLASS_HPP

