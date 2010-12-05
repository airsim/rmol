#ifndef __STDAIR_BOM_TRAVELSOLUTIONSTRUCT_HPP
#define __STDAIR_BOM_TRAVELSOLUTIONSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
#include <vector>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/basic/StructAbstract.hpp>
#include <stdair/bom/BookingClassTypes.hpp>

namespace stdair {

  /** Structure holding the elements of a travel solution. */
  struct TravelSolutionStruct : public StructAbstract {
  public:
    // /////////// Getters ///////////////
    /** Get the fare/price. */
    const Fare_T getFare() const {
      return _fare;
    }
    /** Get the availability. */
    const Availability_T getAvailability() const {
      return _availability;
    }
    /** Get the list of segment-date keys. */
    const KeyList_T& getSegmentDateKeyList () const {
      return _segmentDateKeyList;
    }
    /** Get the list of booking-class keys. */
    const ClassList_String_T& getBookingClassKeyList () const { 
      return _bookingClassKeyList; 
    }

  public:
    // /////////// Setters ///////////////
    /** Set the fare/price. */
    void setFare (const Fare_T& iFare) {
      _fare = iFare;
    }
    /** Set the availability. */
    void setAvailability (const Availability_T& iAvail) {
      _availability=iAvail;
    }
    /** Add a segment-date key to the dedicated list. */
    void addSegmentDateKey (const std::string& iKey) {
      _segmentDateKeyList.push_back (iKey);
    }
    /** Add a booking-class key to the dedicated list. */
    void addBookingClassKey (const char iKey) {
      _bookingClassKeyList.push_back (iKey);
    }

  public:
    // /////////// Display support method /////////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

    /** Display of the structure. */
    const std::string describe() const;
  
  public:
    // //////////// Constructors & Destructor ///////////////
    /** Main constructor. */
    TravelSolutionStruct ();
    /** Destructor. */
    ~TravelSolutionStruct ();
    /** Default copy constructor. */
    TravelSolutionStruct (const TravelSolutionStruct&);
    
  private:
    // ///////////////////// Attributes //////////////////////
    /** The list of segment-date whole keys which make the travel solution. */
    KeyList_T _segmentDateKeyList;
    
    /** The list of booking class keys which make the travel solution. */
    ClassList_String_T _bookingClassKeyList;
    
    /** The fare of the travel solution. */
    Fare_T _fare;

    /** The availability of the travel solution. */
    Availability_T _availability;
  };

}
#endif // __STDAIR_BOM_TRAVELSOLUTIONSTRUCT_HPP
