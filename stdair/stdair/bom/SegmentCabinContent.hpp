#ifndef __STDAIR_BOM_SEGMENTCABINCONTENT_HPP
#define __STDAIR_BOM_SEGMENTCABINCONTENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/SegmentCabinKey.hpp>

namespace stdair {

  /** Class representing the actual attributes for an airline segment-cabin. */
  class SegmentCabinContent : public BomContent {
  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef SegmentCabinKey_T Key_T;

  public:
    // /////////// Getters ///////////// 
    /** Get the segment-cabin key. */
    const Key_T& getKey() const {
      return _key;
    }
    
    /** Get the cabin code (primary key). */
    const CabinCode_T& getCabinCode() const {
      return _key.getCabinCode();
    }

    /** Get the off cabin. */
    const CabinCapacity_T& getCapacity () const {
      return _capacity;
    }

    /** Get the number of reserved seats. */
    const BlockSpace_T& getBlockSpace () const {
      return _blockSpace;
    }

    /** Get the booking counter. */
    const NbOfBookings_T& getBookingCounter () const {
      return _bookingCounter;
    }

    /** Get the commited Space value. */
    const CommitedSpace_T& getCommitedSpace () const {
      return _commitedSpace;
    }

    /** Get the availability pool value. */
    const Availability_T& getAvailabilityPool () const {
      return _availabilityPool;
    }

    /** Get the total cabin revenue. */
    const Revenue_T& getRevenue () const {
      return _cabinRevenue;
    }

    /** Get the cabin average fare. */
    const Fare_T& getAverageFare() const {
      return _cabinAverageFare;
    }

    /** Get the unit revenue value for this cabin. */
    const Revenue_T& getUnitRevenue () const {
      return _cabinUnitRevenue;
    }

    /** Get the Revenue Passanger Kilometer for this cabin. */
    const Distance_T& getRPK() const {
      return _cabinRPK;
    }

    /** Retrive the current Bid-Price. */
    const BidPrice_T& getCurrentBidPrice () const {
      return _currentBidPrice;
    }

    /** Retrive the Bid-Price Vector. */
    BidPriceVector_T& getBidPriceVector () {
      return _bidPriceVector;
    }

  public:
    // ///////// Setters //////////
    /** Set the cabin capacity. */
    void setCapacity (const CabinCapacity_T& iCapacity) {
      _capacity = iCapacity;
    }

    /** Set the number of reserved seats. */
    void setBlockSpace (const BlockSpace_T& iBlockSpace) {
      _blockSpace = iBlockSpace;
    }

    /** Set the total number of bookings. */
    void setBookingCounter (const NbOfBookings_T& iBookingCounter) {
      _bookingCounter = iBookingCounter;
    }

    /** Set the value of commited space. */
    void setCommitedSpace (const CommitedSpace_T& iCommitedSpace) {
      _commitedSpace = iCommitedSpace;
    }

    /** Set the value of availability pool. */
    void setAvailabilityPool (const Availability_T& iAvailabilityPool) {
      _availabilityPool = iAvailabilityPool;
    }

    /** Set the revenue amount. */
    void setRevenue (const Revenue_T& iCabinRevenue) {
      _cabinRevenue = iCabinRevenue;
    }

    /** Set the average cabin fare. */
    void setAverageCabinFare(Fare_T iCAFare) {
      _cabinAverageFare = iCAFare;
    }

    /** Set the Revenue Passanger Kilometer. */
    void setRPK (const Distance_T& iCabinRPK) {
      _cabinRPK = iCabinRPK;
    }
      
    /** Set the Unit Revenue. */
    void setUnitRevenue (const Revenue_T& iCabinURevenue) {
      _cabinUnitRevenue = iCabinURevenue;
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
    SegmentCabinContent (const Key_T&);
    SegmentCabinContent (const SegmentCabinContent&);
    /** Destructor. */
    ~SegmentCabinContent();

  protected:
    // Attributes
    /** The key of both structure and content objects. */
    Key_T _key;

    /** Capacity of the cabin. */
    CabinCapacity_T _capacity;

    /** Reserved seats in the cabin. */
    BlockSpace_T _blockSpace;      

    /** Counter of all bookings into the cabin. */
    NbOfBookings_T _bookingCounter;

    /** Commited space (seat unity) */
    CommitedSpace_T _commitedSpace;

    /** Value of the availibility pool */
    Availability_T _availabilityPool;

    /** Bid Price Vector. */
    BidPriceVector_T _bidPriceVector;

    /** Current BidPrice. */
    BidPrice_T _currentBidPrice;

    /** Total amount of money earned with cabin bookings. */
    Revenue_T _cabinRevenue;

    /** Value of the average fare of this cabin.*/
    Fare_T _cabinAverageFare;

    /** Value of the Unit Revenue (Revenue/ASK). */
    Revenue_T _cabinUnitRevenue;

    /** Value of the Revenue Passanger Kilometer for this cabin.*/
    Distance_T _cabinRPK;
  };

}
#endif // __STDAIR_BOM_SEGMENTCABINCONTENT_HPP

