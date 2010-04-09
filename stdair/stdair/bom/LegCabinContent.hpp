#ifndef __STDAIR_BOM_LEGCABINCONTENT_HPP
#define __STDAIR_BOM_LEGCABINCONTENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/LegCabinKey.hpp>

namespace stdair {

  /** Class representing the actual attributes for an airline leg-cabin. */
  class LegCabinContent : public BomContent {
  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef LegCabinKey_T BomKey_T;

  public:
    // /////////// Getters ////////////
     /** Get the leg-cabin key. */
    const BomKey_T& getKey() const {
      return _key;
    }
    
    /** Get the cabin code (from key). */
    const CabinCode_T& getCabinCode() const {
      return _key.getCabinCode();
    }

    /** Get the cabin capacity. */
    const CabinCapacity_T& getCapacity () const {
      return _capacity;
    }

    /** Get the number of sold seat. */
    const NbOfBookings_T& getSoldSeat () const {
      return _soldSeat;
    }

    /** Get the value of commited space. */
    const CommitedSpace_T& getCommitedSpace () const {
      return _commitedSpace;
    }

    /** Get the value of the availability pool. */
    const Availability_T& getAvailabilityPool () const {
      return _availabilityPool;
    }

    /** Get the value of the availability. */
    const Availability_T& getAvailability () const {
      return _availability;
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
    // ///////////// Setters ///////////////
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
    virtual void toStream (std::ostream& ioOut) const = 0;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    virtual void fromStream (std::istream& ioIn) = 0;

   /** Get the serialised version of the Business Object. */
    virtual std::string toString() const = 0;
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    virtual const std::string describeKey() const = 0;

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    virtual const std::string describeShortKey() const = 0;

  protected:
    /** Default constructors. */
    LegCabinContent (const BomKey_T&);
    LegCabinContent (const LegCabinContent&);

    /** Destructor. */
    virtual ~LegCabinContent();

  public:
    // Test AIRINV
    stdair::CapacityAdjustment_T _adjustment;
    stdair::CapacityAdjustment_T _dcsRegrade;
    stdair::AuthorizationLevel_T _au;
    stdair::UPR_T _upr;
    stdair::NbOfBookings_T _nbOfBookings;
    stdair::Availability_T _nav;
    stdair::Availability_T _gav;
    stdair::OverbookingRate_T _acp;
    stdair::NbOfBookings_T _etb;
    stdair::NbOfBookings_T _staffNbOfBookings;
    stdair::NbOfBookings_T _wlNbOfBookings;
    stdair::NbOfBookings_T _groupNbOfBookings;
    
  protected:
    // Attributes
    /** The key of both structure and content objects. */
    BomKey_T _key;
    
    /** Capacity of the cabin. */
    CabinCapacity_T _capacity;

    /** Sold seat into the cabin. */
    NbOfBookings_T  _soldSeat;

    /** Commited space for all segmentCabin composed by this LegCabin. */
    CommitedSpace_T  _commitedSpace;

    /** Availability Pool between capacity and commited spaces. */
    Availability_T _availabilityPool;

    /** Availability Pool between capacity and commited spaces. */
    Availability_T _availability;

    /** Bid Price Vector. */
    BidPriceVector_T _bidPriceVector;

    /** Current BidPrice. */
    BidPrice_T _currentBidPrice;
  };

}
#endif // __STDAIR_BOM_LEGCABINCONTENT_HPP

