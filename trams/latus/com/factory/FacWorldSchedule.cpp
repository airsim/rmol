// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/WorldSchedule.hpp>
#include <latus/com/bom/Inventory.hpp>
#include <latus/com/bom/InventoryList.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacWorldSchedule.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    FacWorldSchedule* FacWorldSchedule::_instance = NULL;

    // //////////////////////////////////////////////////////////////////////
    FacWorldSchedule::~FacWorldSchedule () {
      _instance = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    FacWorldSchedule& FacWorldSchedule::instance () {

      if (_instance == NULL) {
        _instance = new FacWorldSchedule();
        assert (_instance != NULL);
      
        FacSupervisor::instance().registerBomFactory (_instance);
      }
      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    WorldSchedule& FacWorldSchedule::
    create (const boost::gregorian::date& iUpdateDate) {
      WorldSchedule* aWorldSchedule_ptr = NULL;

      aWorldSchedule_ptr = new WorldSchedule (iUpdateDate);
      assert (aWorldSchedule_ptr != NULL);

      // The new object is added to the Bom pool
      _pool.push_back (aWorldSchedule_ptr);

      return *aWorldSchedule_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    void FacWorldSchedule::
    initLinkWithInventory (WorldSchedule& ioWorldSchedule,
                           Inventory& ioInventory) {
      // Link the WorldSchedule to the Inventory, and vice versa
      ioInventory.setWorldSchedule (&ioWorldSchedule);
      
      // Link the WorldSchedule to the Inventory
      const bool insertSucceeded = ioWorldSchedule._inventoryList.
        insert (InventoryList_T::value_type (ioInventory.getPrimaryKey(),
                                            &ioInventory)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion failed for " << ioWorldSchedule.describeKey()
                         << " and " << ioInventory.describeKey());
        assert (insertSucceeded == true);
      }
    }
  
    // //////////////////////////////////////////////////////////////////////
    void FacWorldSchedule::
    createLegCabin (WorldSchedule& ioWorldSchedule,
                    const AirlineCode_T& iAirlineCode,
                    const FlightNumber_T& iFlightNumber,
                    const AirportCode_T& iBoardPoint,
                    const AirportCode_T& iOffPoint,
                    const DateTime_T& iFlightDate,
                    const CabinCode_T& iCabinCode) {
      /* TODO: implement the BOM for that (Inventory, FlightDate, etc.)
      const InventoryList_T& lInventoryList =
        ioWorldSchedule.getInventoryList();
    
      InventoryList_T::const_iterator itInventory =
        lInventoryList.find (iInventoryDescription);
    
      // If the Inventory instance does not exist yet, create it
      if (itInventory == lInventoryList.end()) {
        Inventory& aInventory =
          FacInventory::instance().create (iInventoryDescription);

        initLinkWithInventory (ioWorldSchedule, aInventory);
      
        itInventory = lInventoryList.find (iInventoryDescription);
        assert (itInventory != lInventoryList.end());
      }
    
      Inventory* lInventory_ptr = itInventory->second;
      assert (lInventory_ptr != NULL);
    
      // Forward the ClassPath object creation request to FacInventory
      FacInventory::createLegCabin (*lInventory_ptr, iAirlineCode,
                                    iFlightNumber, iBoardPoint, iOffPoint,
                                    iFlightDate, iCabinCode);
      */
    }
  
  }
}
