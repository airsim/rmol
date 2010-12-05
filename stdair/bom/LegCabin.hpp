#ifndef __STDAIR_BOM_LEGCABIN_HPP
#define __STDAIR_BOM_LEGCABIN_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/LegCabinKey.hpp>
#include <stdair/bom/LegCabinTypes.hpp>

namespace stdair {

  /** Class representing the actual attributes for an airline leg-cabin. */
  class LegCabin : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;

  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef LegCabinKey Key_T;

  public:
    // /////////// Getters ////////////
     /** Get the leg-cabin key. */
    const Key_T& getKey() const { return _key; }

    /** Get the parent object. */
    BomAbstract* const getParent() const { return _parent; }
    
    /** Get the cabin code (from key). */
    const CabinCode_T& getCabinCode() const { return _key.getCabinCode(); }

    /** Get the cabin offered capacity. */
    const CabinCapacity_T& getOfferedCapacity () const {return _offeredCapacity;}

    /** Get the cabin physical capacity. */
    const CabinCapacity_T& getPhysicalCapacity () const {
      return _physicalCapacity;
    }

    /** Get the number of sold seat. */
    const NbOfBookings_T& getSoldSeat () const { return _soldSeat; }

    /** Get the value of commited space. */
    const CommitedSpace_T& getCommitedSpace () const { return _commitedSpace; }

    /** Get the value of the availability pool. */
    const Availability_T& getAvailabilityPool () const {
      return _availabilityPool;
    }

    /** Get the value of the availability. */
    const Availability_T& getAvailability () const { return _availability; }

    /** Retrive the current Bid-Price. */
    const BidPrice_T& getCurrentBidPrice () const { return _currentBidPrice; }
    
    /** Retrive the Bid-Price Vector. */
    BidPriceVector_T& getBidPriceVector () { return _bidPriceVector; }

    /** Get the map of children holders. */
    const HolderMap_T& getHolderMap() const { return _holderMap; }

  public:
    // ///////////// Setters ///////////////
    /** Set the offered and physical capacities. */
    void setCapacities (const CabinCapacity_T& iCapacity) {
      _offeredCapacity = iCapacity;
      _physicalCapacity = iCapacity;
    }
    
    /** Set the number of sold seat. */
    void setSoldSeat (const NbOfBookings_T& iSoldSeat) {
      _soldSeat = iSoldSeat;
    }

    /** Set the value of commited space. */
    void setCommitedSpace (const CommitedSpace_T& iCommitedSpace) {
      _commitedSpace = iCommitedSpace;
    }

    /** Set the value of availability pool. */
    void setAvailabilityPool (const Availability_T& iAvailabilityPool) {
      _availabilityPool = iAvailabilityPool;
    }

    /** Set the value of availability. */
    void setAvailability (const Availability_T& iAvailability) {
      _availability = iAvailability;
    }

    /** Set the current Bid-Price. */
    void setCurrentBidPrice (const BidPrice_T& iBidPrice) {
      _currentBidPrice = iBidPrice;
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
    LegCabin (const Key_T&);
    LegCabin (const LegCabin&);
    /** Destructor. */
    ~LegCabin();

  public:
    // Test AIRINV
    stdair::CapacityAdjustment_T _dcsRegrade;
    stdair::AuthorizationLevel_T _au;
    stdair::UPR_T _upr;
    stdair::Availability_T _nav;
    stdair::Availability_T _gav;
    stdair::OverbookingRate_T _acp;
    stdair::NbOfBookings_T _etb;
    stdair::NbOfBookings_T _staffNbOfBookings;
    stdair::NbOfBookings_T _wlNbOfBookings;
    stdair::NbOfBookings_T _groupNbOfBookings;
    
  protected:
    Key_T _key;
    BomAbstract* _parent;
    CabinCapacity_T _offeredCapacity;
    CabinCapacity_T _physicalCapacity;
    NbOfBookings_T  _soldSeat;
    CommitedSpace_T  _commitedSpace;
    Availability_T _availabilityPool;
    Availability_T _availability;
    BidPriceVector_T _bidPriceVector;
    BidPrice_T _currentBidPrice;
    HolderMap_T _holderMap;
  };

}
#endif // __STDAIR_BOM_LEGCABIN_HPP

