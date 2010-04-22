#ifndef __STDAIR_BOM_INVENTORYCONTENT_HPP
#define __STDAIR_BOM_INVENTORYCONTENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/InventoryKey.hpp>

namespace stdair {

  /** Class representing the actual attributes for an airline inventory. */
  class InventoryContent : public BomContent {
  public :
    // Type definitions
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef InventoryKey_T Key_T;

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
    const std::string describeShortKey() const { _key.toString(); }

  public:
    // ////////// Getters ////////////
    /** Get the airline code. */
    const AirlineCode_T& getAirlineCode () const {
      return _key.getAirlineCode();
    }
    
    /** Get the inventory key. */
    const Key_T& getKey() const {
      return _key;
    }

    /** Get the booking counter. */
    const NbOfBookings_T& getBookingCounter () const {
      return _bookingCounter;
    }

    /** Get the total inventory revenue. */
    const Revenue_T& getRevenue () const {
      return _inventoryRevenue;
    }

    /** Get the inventory average fare. */
    const Fare_T& getAverageFare() const {
      return _inventoryAverageFare;
    }

    /** Get the Availability Seat Kilometer for the inventory. */
    const Distance_T& getASK() const {
      return _inventoryASK;
    }

    /** Get the yield value for the inventory. */
    const Revenue_T& getYield () const {
      return _inventoryYield;
    }

    /** Get the Revenue Passanger Kilometer for the whole inventory. */
    const Distance_T& getRPK() const {
      return _inventoryRPK;
    }

    /** Get the unit revenue value for the whole inventory. */
    const Revenue_T& getUnitRevenue () const {
      return _inventoryUnitRevenue;
    }

    /** Get the load factor value for this inventory. */
    const Revenue_T& getLoadFactor () const {
      return _inventoryLoadFactor;
    }

  public:
    // ///////// Setters //////////
    /** Set the revenue amount. */
    void setRevenue (const Revenue_T& iInventoryRevenue) {
      _inventoryRevenue = iInventoryRevenue;
    }

    /** Set the Revenue Passanger Kilometer. */
    void setRPK (const Distance_T& iInventoryRPK) {
      _inventoryRPK = iInventoryRPK;
    }

    /** Set the unit revenue. */
    void setUnitRevenue (const Revenue_T& iInventoryURevenue) {
      _inventoryUnitRevenue = iInventoryURevenue;
    }

    /** Set the average fare. */
    void setAverageFare(Fare_T iIAFare) {
      _inventoryAverageFare = iIAFare;
    }

    /** Set the yield. */
    void setYield (const Revenue_T& iInvYield) {
      _inventoryYield = iInvYield;
    }

    /** Set the load factor. */
    void setLoadFactor (const Revenue_T& iInventoryLF) {
      _inventoryLoadFactor = iInventoryLF;
    }

  protected:
    /** Default constructors. */
    InventoryContent (const Key_T&);
    InventoryContent (const InventoryContent&);
    /** Destructor. */
    virtual ~InventoryContent();

  protected:
    // Attributes
    /** The key of both structure and content objects. */
    Key_T _key;

    /** Counter of all bookings into the inventory. */
    NbOfBookings_T _bookingCounter;
      
    /** Total amount of money earn with all flight bookings
        for one airline. */
    Revenue_T _inventoryRevenue;

    /** Value of the average fare of the inventory.*/
    Fare_T _inventoryAverageFare;

    /** Value of the Available Seat Kilometer for this Inventory.*/
    Distance_T _inventoryASK;

    /** Value of the Yield (Revenue/ASK). */
    Revenue_T _inventoryYield;

    /** Value of the Revenue Passanger Kilometer for the whole inventory.*/
    Distance_T _inventoryRPK;

    /** Value of the Unit Revenue (Revenue/RPK). */
    Revenue_T _inventoryUnitRevenue;

    /** Value of the Load Factor (ASK/RPK). */
    Revenue_T _inventoryLoadFactor;
  };

}
#endif // __STDAIR_BOM_INVENTORYCONTENT_HPP

