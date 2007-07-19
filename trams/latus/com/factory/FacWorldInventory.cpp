// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/WorldInventory.hpp>
#include <latus/com/bom/Inventory.hpp>
#include <latus/com/bom/InventoryList.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacWorldInventory.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    FacWorldInventory* FacWorldInventory::_instance = NULL;

    // //////////////////////////////////////////////////////////////////////
    FacWorldInventory::~FacWorldInventory () {
      _instance = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    FacWorldInventory& FacWorldInventory::instance () {

      if (_instance == NULL) {
        _instance = new FacWorldInventory();
        assert (_instance != NULL);
      
        FacSupervisor::instance().registerBomFactory (_instance);
      }
      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    WorldInventory& FacWorldInventory::create () {
      WorldInventory* aWorldInventory_ptr = NULL;

      aWorldInventory_ptr = new WorldInventory ();
      assert (aWorldInventory_ptr != NULL);

      // The new object is added to the Bom pool
      _pool.push_back (aWorldInventory_ptr);

      return *aWorldInventory_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    void FacWorldInventory::
    initLinkWithInventory (WorldInventory& ioWorldInventory,
                           Inventory& ioInventory) {
      // Link the WorldInventory to the Inventory, and vice versa
      ioInventory.setWorldInventory (&ioWorldInventory);
      
      // Link the WorldInventory to the Inventory
      const bool insertSucceeded = ioWorldInventory._inventoryList.
        insert (InventoryList_T::value_type (ioInventory.getPrimaryKey(),
                                            &ioInventory)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion failed for " << ioWorldInventory.describeKey()
                         << " and " << ioInventory.describeKey());
        assert (insertSucceeded == true);
      }
    }
  
    // //////////////////////////////////////////////////////////////////////
    void FacWorldInventory::
    createLegCabin (WorldInventory& ioWorldInventory,
                    const AirlineCode_T& iAirlineCode,
                    const FlightNumber_T& iFlightNumber,
                    const AirportCode_T& iBoardPoint,
                    const AirportCode_T& iOffPoint,
                    const DateTime_T& iFlightDate,
                    const CabinCode_T& iCabinCode) {
      /* TODO: implement the BOM for that (Inventory, FlightDate, etc.)
      const InventoryList_T& lInventoryList =
        ioWorldInventory.getInventoryList();
    
      InventoryList_T::const_iterator itInventory =
        lInventoryList.find (iInventoryDescription);
    
      // If the Inventory instance does not exist yet, create it
      if (itInventory == lInventoryList.end()) {
        Inventory& aInventory =
          FacInventory::instance().create (iInventoryDescription);

        initLinkWithInventory (ioWorldInventory, aInventory);
      
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
