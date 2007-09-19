#ifndef __LATUS_COM_BOM_SEGMENTCABIN_HPP
#define __LATUS_COM_BOM_SEGMENTCABIN_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/SegmentCabinKey.hpp>
#include <latus/com/bom/LegCabinList.hpp>
#include <latus/com/bom/ClassStruct.hpp>

namespace LATUS {

  namespace COM {

    // Forward declarations
    class SegmentDate;
    
    /** Class wrapping the Segment-Cabin specific attributes and methods. */
    class SegmentCabin : public BomAbstract {
      friend class FacSegmentCabin;
    public:
      // /////////// Getters //////////////
      /** Get the parent class. */
      SegmentDate* getParent() const {
        return getSegmentDate();
      }

      /** Get the SegmentDate (parent class). */
      SegmentDate* getSegmentDate() const {
        return _segmentDate;
      }

      /** Get the primary key. */
      const SegmentCabinKey_T& getPrimaryKey() const {
        return getSegmentCabinKey();
      }

      /** Get the flight-cabin key. */
      const SegmentCabinKey_T& getSegmentCabinKey() const {
        return _key;
      }

      /** Get the cabin code (primary key). */
      const CabinCode_T& getCabinCode() const {
        return _key.cabinCode;
      }
      
      /** Get the off cabin. */
      const CabinCapacity_T& getCapacity () const {
        return _capacity;
      }

       /** Get the number of reserved seats. */
      const ReservedSeats_T& getReservedSeats () const {
        return _reservedSeats;
      }

       /** Get the booking counter. */
      const BookingNumber_T& getBookingCounter () const {
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

      // ///////// Setters //////////
      /** Set the SegmentDate (parent class). */
      void setSegmentDate (SegmentDate* ioSegmentDatePtr) {
        _segmentDate = ioSegmentDatePtr;
      }

      /** Set the off cabin. */
      void setCapacity (const CabinCapacity_T& iCapacity) {
        _capacity = iCapacity;
      }

      /** Set the number of reserved seats. */
      void setReservedSeats (const ReservedSeats_T& iReservedSeats) {
        _reservedSeats = iReservedSeats;
      }

      /** Set the total number of bookings. */
      void setBookingCounter (const BookingNumber_T& iBookingCounter) {
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

      // ///////// Display Methods //////////
      /** Get a string describing the key. */
      const std::string describeKey() const;

      /** Get a string describing the short key. */
      const std::string describeShortKey() const;

      /** Display the full SegmentCabin context. */
      void display() const;

      // ///////// Counting Methods //////////
      /** Update the booking counters. */
      void updateBookingAndSeatCounters();

      /** Update the commited spaces in cabins. */
      void updateCommitedSpaces();

      /** Update the availability pool for the whole segmentcabin. */
      void updateAvailabilityPools();

      /** Update availibilities for each class. */
      void updateAllAvailabilities();
      
    private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      SegmentCabin (const SegmentCabinKey_T&); 

      /** Destructor. */
      virtual ~SegmentCabin();

    private:
      /** Get the (ordered) list of (children) LegCabin objects. */
      const LegCabinOrderedList_T& getLegCabinList () const {
        return _legCabinList;
      }


    private:
      // Parent
      /** Parent class: SegmentDate. */
      SegmentDate* _segmentDate;
      
      // Primary Key
      /** Segment-Cabin Key is composed of the cabin code. */
      SegmentCabinKey_T _key;

      /** Children: lists of classes. */
      ClassStructOrderedList_T _classOrderedList;
      ClassStructList_T _classList;
      
      /** List of routing LegCabin objects. */
      LegCabinOrderedList_T _legCabinList;

      // Attributes
      /** Capacity of the cabin. */
      CabinCapacity_T _capacity;

      /** Reserved seats in the cabin. */
      ReservedSeats_T _reservedSeats;      

      /** Counter of all bookings into the cabin. */
      BookingNumber_T _bookingCounter;

      /** Commited space (seat unity) */
      CommitedSpace_T _commitedSpace;

       /** Value of the availibility pool */
      Availability_T _availabilityPool;
    };

  }
}
#endif // __LATUS_COM_BOM_SEGMENTCABIN_HPP
