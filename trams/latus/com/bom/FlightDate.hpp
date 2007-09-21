#ifndef __LATUS_COM_BOM_FLIGHTDATE_HPP
#define __LATUS_COM_BOM_FLIGHTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/FlightDateKey.hpp>
#include <latus/com/bom/LegDateList.hpp>
#include <latus/com/bom/SegmentDateList.hpp>

namespace LATUS {

  // Forward declarations
  namespace TSP {
    class NetworkGenerator;
  }
  
  namespace COM {

    // Forward declarations
    class Inventory;

    /** Class wrapping the Flight-Date specific attributes and methods. */
    class FlightDate : public BomAbstract {
      friend class FacFlightDate;
      friend class TSP::NetworkGenerator;
    public:
      // /////////// Getters //////////////
      /** Get the parent class. */
      Inventory* getParent() const {
        return getInventory();
      }

      /** Get the Inventory (parent class). */
      Inventory* getInventory() const {
        return _inventory;
      }

      /** Get the primary key. */
      const FlightDateKey_T& getPrimaryKey() const {
        return getFlightDateKey();
      }

      /** Get the flight-date key. */
      const FlightDateKey_T& getFlightDateKey() const {
        return _key;
      }

      /** Get the flight number (part of the primary key). */
      const FlightNumber_T& getFlightNumber() const {
        return _key.flightKey.flightNumber;
      }
      
      /** Get the airline code (from the parent class). */
      const AirlineCode_T& getAirlineCode() const;
      
      /** Retrieve, if existing, the LegDate corresponding to the
          given board point (LegDate key).
          <br>If not existing, return the NULL pointer. */
      LegDate* getLegDate (const AirportCode_T& iBoardPoint) const;

      /** Retrieve, if existing, the SegmentDate corresponding to the
          given (board point, off point) pair (SegmentDate key).
          <br>If not existing, return the NULL pointer. */
      SegmentDate* getSegmentDate (const AirportCode_T& iBoardPoint,
                                   const AirportCode_T& iOffPoint) const;

      
      // ///////// Setters //////////
      /** Set the Inventory (parent class). */
      void setInventory (Inventory* ioInventoryPtr) {
        _inventory = ioInventoryPtr;
      }


      // ///////// Display Methods //////////
      /** Get a string describing the key. */
      const std::string describeKey() const;

      /** Get a string describing the short key. */
      const std::string describeShortKey() const;

      /** Display the full FlightDate context. */
      void display() const;

       // ///////// Counting Methods //////////
      /** Update counters. */
      void updateBookingsAndSeatCounters() const;

      /** Update the commited spaces in cabins. */
      void updateCommitedSpaces() const;

      /** Update the availability pools from leg to segment cabins. */
      void updateAvailabilityPools() const;

       /** Update all availabilities. */
      void updateAllAvailabilities() const;

      
    private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      FlightDate (const FlightDateKey_T&); 

      /** Default constructors. */
      FlightDate ();
      FlightDate (const FlightDate&);
      
      /** Destructor. */
      virtual ~FlightDate();


    private:
      /** Get the list of (children) LegDate objects. */
      const LegDateList_T& getLegDateList () const {
        return _legDateList;
      }

      /** Get the ordered list of (children) LegDate objects. */
      const LegDateOrderedList_T& getLegDateOrderedList () const {
        return _legDateOrderedList;
      }

      /** Retrieve, if existing, the LegDate corresponding to the
          given LegDate key (FlightDateKey + board point).
          <br>If not existing, return the NULL pointer.
          <br>Note that the string must be formed thanks to the
          LegDateKey::describeShort() method, as that latter is used when
          inserting the LegDate within the FlightDate dedicated list. */
      LegDate* getLegDateInternal (const std::string& iLegDateKey) const;
      
      /** Get the list of (children) SegmentDate objects. */
      const SegmentDateList_T& getSegmentDateList () const {
        return _segmentDateList;
      }

      /** Get the ordered list of (children) SegmentDate objects. */
      const SegmentDateOrderedList_T& getSegmentDateOrderedList () const {
        return _segmentDateOrderedList;
      }

      /** Retrieve, if existing, the SegmentDate corresponding to the
          given SegmentDate key (FlightDateKey + (board point, off point) pair).
          <br>If not existing, return the NULL pointer.
          <br>Note that the string must be formed thanks to the
          SegmentDateKey::describeShort() method, as that latter is used when
          inserting the SegmentDate within the FlightDate dedicated list. */
      SegmentDate*
      getSegmentDateInternal (const std::string& iSegmentDateKey) const;
      

    private:
      // Parent
      /** Parent class: Inventory. */
      Inventory* _inventory;
      
      // Primary Key
      /** Flight-Date Key is composed of the airline code, flight number and
          departure date of the first segment. */
      FlightDateKey_T _key;

      // Children
      /** Children: lists of LegDate objects. */
      LegDateList_T _legDateList;
      LegDateOrderedList_T _legDateOrderedList;
      
      /** Children: list of SegmentDate objects. */
      SegmentDateList_T _segmentDateList;
      SegmentDateOrderedList_T _segmentDateOrderedList;
    };

  }
}
#endif // __LATUS_COM_BOM_FLIGHTDATE_HPP
