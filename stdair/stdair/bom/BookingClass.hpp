#ifndef __STDAIR_BOM_BOOKINGCLASS_HPP
#define __STDAIR_BOM_BOOKINGCLASS_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/BookingClassKey.hpp>
#include <stdair/bom/BookingClassTypes.hpp>

namespace stdair {

  /** Class representing the actual attributes for an airline booking class. */
  class BookingClass : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;

  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef BookingClassKey Key_T;

  public:
    // /////////// Getters ////////////
    /** Get the booking class key. */
    const Key_T& getKey() const { return _key; }
    
    /** Get the booking code (part of the primary key). */
    const ClassCode_T& getClassCode() const { return _key.getClassCode(); }

    /** Get the parent object. */
    BomAbstract* const getParent() const { return _parent; }

    /** Get the map of children holders. */
    const HolderMap_T& getHolderMap() const { return _holderMap; }

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const { ioOut << toString(); }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object. */
    std::string toString() const;
    
    /** Get a string describing the  key. */
    const std::string describeKey() const { return _key.toString(); }

  public:
    // ////////////// Business Methodes /////////////////
    /** Register a sale. */
    void sell (const NbOfBookings_T&);

  protected:
    /** Default constructors. */
    BookingClass (const Key_T&);
    BookingClass (const BookingClass&);
    /** Destructor. */
    ~BookingClass();

  public:
    // Attributes
    Key_T _key;
    BomAbstract* _parent;
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
    HolderMap_T _holderMap;
    
  };

}
#endif // __STDAIR_BOM_BOOKINGCLASS_HPP

