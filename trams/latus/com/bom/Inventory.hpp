#ifndef __LATUS_COM_BOM_INVENTORY_HPP
#define __LATUS_COM_BOM_INVENTORY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/InventoryKey.hpp>
#include <latus/com/bom/FlightDateList.hpp>

namespace LATUS {

  // Forward declarations
  namespace TSP {
    class NetworkGenerator;
  }
  
  namespace COM {

    // Forward declarations
    class WorldSchedule;
    
    /** Class wrapping the Inventory for a specific airline/provider. */
    class Inventory : public BomAbstract {
      friend class FacInventory;
      friend class TSP::NetworkGenerator;
    public:
      // /////////// Getters //////////////
      /** Get the parent class. */
      WorldSchedule* getParent() const {
        return getWorldSchedule();
      }

      /** Get the WorldSchedule (parent class). */
      WorldSchedule* getWorldSchedule() const {
        return _worldSchedule;
      }

      /** Get the primary key. */
      const InventoryKey_T& getPrimaryKey() const {
        return getInventoryKey();
      }

      /** Get the flight-date key. */
      const InventoryKey_T& getInventoryKey() const {
        return _key;
      }

      /** Get the airline code (primary key). */
      const AirlineCode_T& getAirlineCode() const {
        return _key.airlineCode;
      }
      
      /** Retrieve, if existing, the FlightDate corresponding to the
          given flight number and flight date (FlightDate key).
          <br>If not existing, return the NULL pointer. */
      FlightDate* getFlightDate (const FlightNumber_T& iFlightNumber,
                                 const DateTime_T& iFlightDate) const;
      
      
      // ///////// Setters //////////
      /** Set the WorldSchedule (parent class). */
      void setWorldSchedule (WorldSchedule* ioWorldSchedulePtr) {
        _worldSchedule = ioWorldSchedulePtr;
      }

      // ///////// Display Methods //////////
      /** Get a string describing the key. */
      const std::string describeKey() const;

      /** Get a string describing the short key. */
      const std::string describeShortKey() const;

      /** Display the full Inventory context. */
      void display() const;

       // ///////// Counting methods  //////////
      /** Update the counters. */
       void updateBookingsAndSeatCounters() const;

      /** Update the commited spaces in cabins. */
       void updateCommitedSpaces() const;

      /** Update the availability pools from leg to segment cabins. */
      void updateAvailabilityPools() const;

      /** Update all availabilities in the inventory. */
      void updateAllAvailabilities() const;


    private:
      /** Get the list of (children) FlightDate objects. */
      const FlightDateList_T& getFlightDateList () const {
        return _flightDateList;
      }

      /** Retrieve, if existing, the FlightDate corresponding to the
          given FlightDate key (InventoryKey + flight number).
          <br>If not existing, return the NULL pointer.
          <br>Note that the string must be formed thanks to the
          FlightDateKey::describeShort() method, as that latter is used when
          inserting the FlightDate within the Inventory dedicated list. */
      FlightDate*
      getFlightDateInternal (const std::string& iFlightDateKey) const;
      

    private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      Inventory (const InventoryKey_T&); 

      /** Destructor. */
      virtual ~Inventory();

      
    private:
      // Parent
      /** Parent class: WorldSchedule. */
      WorldSchedule* _worldSchedule;
      
      // Primary Key
      /** Inventory Key is composed of the airline code. */
      InventoryKey_T _key;
      
      // Attributes
      //
      
      // Children: List of FlightDate objects
      FlightDateList_T _flightDateList;
    };

  }
}
#endif // __LATUS_COM_BOM_INVENTORY_HPP
