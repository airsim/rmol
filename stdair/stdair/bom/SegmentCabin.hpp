#ifndef __STDAIR_BOM_SEGMENTCABIN_HPP
#define __STDAIR_BOM_SEGMENTCABIN_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/SegmentCabinKey.hpp>
#include <stdair/bom/SegmentCabinTypes.hpp>

namespace stdair {

  /** Class representing the actual attributes for an airline segment-cabin. */
  class SegmentCabin : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;
    
  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef SegmentCabinKey Key_T;

  public:
    // /////////// Getters ///////////// 
    /** Get the segment-cabin key. */
    const Key_T& getKey() const { return _key; }

    /** Get the parent object. */
    BomAbstract* const getParent() const { return _parent; }
    
    /** Get the cabin code (primary key). */
    const CabinCode_T& getCabinCode() const { return _key.getCabinCode(); }
    
    /** Get the off cabin. */
    const CabinCapacity_T& getCapacity () const { return _capacity; }

    /** Get the number of reserved seats. */
    const BlockSpace_T& getBlockSpace () const { return _blockSpace; }

    /** Get the booking counter. */
    const NbOfBookings_T& getBookingCounter () const { return _bookingCounter; }

    /** Get the commited Space value. */
    const CommitedSpace_T& getCommitedSpace () const { return _commitedSpace; }

    /** Get the availability pool value. */
    const Availability_T& getAvailabilityPool () const {
      return _availabilityPool;
    }

    /** Retrive the current Bid-Price. */
    const BidPrice_T& getCurrentBidPrice () const { return _currentBidPrice; }

    /** Retrive the Bid-Price Vector. */
    BidPriceVector_T& getBidPriceVector () { return _bidPriceVector; }

    /** Get the map of children holders. */
    const HolderMap_T& getHolderMap() const { return _holderMap; }

  public:
    // ///////// Setters //////////
    /** Set the cabin capacity. */
    void setCapacity (const CabinCapacity_T& iCapacity) { _capacity = iCapacity;}

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
    // /////////// Business methods //////////
    /** Register a sale. */
    void updateFromReservation (const NbOfBookings_T&);

    
  protected:
    /** Default constructors. */
    SegmentCabin (const Key_T&);
    SegmentCabin (const SegmentCabin&);
    /** Destructor. */
    ~SegmentCabin();

  protected:
    // Attributes
    Key_T _key;
    BomAbstract* _parent;
    CabinCapacity_T _capacity;
    BlockSpace_T _blockSpace;     
    NbOfBookings_T _bookingCounter;
    CommitedSpace_T _commitedSpace;
    Availability_T _availabilityPool;
    BidPriceVector_T _bidPriceVector;
    BidPrice_T _currentBidPrice;
    HolderMap_T _holderMap;
  };

}
#endif // __STDAIR_BOM_SEGMENTCABIN_HPP

