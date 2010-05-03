#ifndef __STDAIR_BOM_BOOKINGCLASSCONTENT_HPP
#define __STDAIR_BOM_BOOKINGCLASSCONTENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/BookingClassKey.hpp>

namespace stdair {

  /** Class representing the actual attributes for an airline booking class. */
  class BookingClassContent : public BomContent {
  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef BookingClassKey_T Key_T;

  public:
    // /////////// Getters ////////////
    /** Get the booking class key. */
    const Key_T& getKey() const {
      return _key;
    }
    
    /** Get the booking code (part of the primary key). */
    const ClassCode_T& getClassCode() const {
      return _key.getClassCode();
    }

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    virtual void toStream (std::ostream& ioOut) const = 0;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    virtual void fromStream (std::istream& ioIn) = 0;

   /** Get the serialised version of the Business Object. */
    virtual std::string toString() const = 0;

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return _key.toString(); }

    
  protected:
    /** Default constructors. */
    BookingClassContent (const Key_T&);
    BookingClassContent (const BookingClassContent&);
    /** Destructor. */
    ~BookingClassContent();

  public:
    // Attributes
    Key_T _key;
    SubclassCode_T _subclassCode;
    AuthorizationLevel_T _cumulatedProtection;
    AuthorizationLevel_T _protection;
    NbOfSeats_T _nego;
    OverbookingRate_T _noShowPercentage;
    OverbookingRate_T _overbookingPercentage;
    NbOfBookings_T _nbOfBookings;
    NbOfBookings_T _groupNbOfBookings;
    NbOfBookings_T _groupPendingNbOfBookings;
    NbOfBookings_T _staffNbOfBookings;
    NbOfBookings_T _wlNbOfBookings;
    NbOfBookings_T _etb;
    Availability_T _netClassAvailability;
    Availability_T _segmentAvailability;
    Availability_T _netRevenueAvailability;
    
  };

}
#endif // __STDAIR_BOM_BOOKINGCLASSCONTENT_HPP

