#ifndef __LATUS_COM_BOM_WORLDSCHEDULE_HPP
#define __LATUS_COM_BOM_WORLDSCHEDULE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost (Extended STL)
#include <boost/date_time/gregorian/gregorian.hpp>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/InventoryList.hpp>

namespace LATUS {

  // Forward declarations
  namespace TSP {
    class NetworkGenerator;
  }
  
  namespace COM {

    // Forward declarations
    class Network;

    /** Class wrapping the inventories of all the available airlines. */
    class WorldSchedule : public BomAbstract {
      friend class FacWorldSchedule;
      friend class TSP::NetworkGenerator;
    public:
      // /////////// Getters //////////////
      /** Get the primary key. */
      const DateTime_T& getPrimaryKey() const {
        return getUpdateDate();
      }

      /** Get the update/creation date for the world schedule data. */
      const DateTime_T& getUpdateDate() const {
        return _updateDate;
      }

      /** Get the reference on the Network object. */
      Network& getNetwork () const;
      
      /** Retrieve, if existing, the Inventory corresponding to the
          given airline code (Inventory key).
          <br>If not existing, return the NULL pointer. */
      Inventory* getInventory (const AirlineCode_T&) const;
      

      // ///////// Setters //////////
      /** Set the update/creation date for the world schdule data. */
      void setUpdateDate (const DateTime_T& iUpdateDate) {
        _updateDate = iUpdateDate;
      }

      /** Set the reference to the Network object. */
      void setNetwork (Network* ioNetworkPtr) {
        _network = ioNetworkPtr;
      }

      // ///////// Display Methods //////////
      /** Get a string describing the key. */
      const std::string describeKey() const;

      /** Display the full BookingDay context. */
      void display() const;

       // ///////// Counting methods  //////////
      /** Update counters for all bookings and seats for all flights */
      void updateBookingAndSeatCounters() const;

       /** Update the commited spaces for all Segment Cabin and for all Legs */
      void updateCommitedSpaces() const;

       /** Update the availability pools for all LegCabin then for all  SegmentCabin */
      void updateAvailabilityPools() const;

       /** Update all the availabilities */
      void updateAllAvailabilities() const;

      
    private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      WorldSchedule (const DateTime_T& iUpdateDate); 

      /** Destructor. */
      virtual ~WorldSchedule();

      /** Get the list of (children) WorldSchedule objects. */
      const InventoryList_T& getInventoryList () const {
        return _inventoryList;
      }

      /** Retrieve, if existing, the Inventory corresponding to the
          given Inventory key (airline code).
          <br>If not existing, return the NULL pointer.
          <br>Note that the string must be formed thanks to the
          InventoryKey::describeShort() method, as that latter is used when
          inserting the Inventory within the WorldSchedule dedicated list. */
      Inventory* getInventoryInternal (const std::string& iInventoryKey) const;
      

    private:
      // Attributes
      /** Children: list of Inventory objects. */
      InventoryList_T _inventoryList;

      /** Update/creation date for the World Schedule data. */
      DateTime_T _updateDate;

      /** Sibling: Network. A reference on a Network object is stored within
          the WorldSchedule instance, so that the ScheduleParser command,
          when building the WorldSchedule BOM (including FlightDate,
          SegmentDate, etc.), may as well prepare the building of the Network
          BOM. */
      Network* _network;
    };

  }

}

#endif // __LATUS_COM_BOM_WORLDSCHEDULE_HPP
