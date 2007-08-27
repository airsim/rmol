// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/Inventory.hpp>
#include <latus/com/bom/FlightDate.hpp>
#include <latus/com/bom/FlightDateList.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacInventory.hpp>
#include <latus/com/factory/FacFlightDate.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    FacInventory* FacInventory::_instance = NULL;

    // //////////////////////////////////////////////////////////////////////
    FacInventory::~FacInventory () {
      _instance = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    FacInventory& FacInventory::instance () {

      if (_instance == NULL) {
        _instance = new FacInventory();
        assert (_instance != NULL);
      
        FacSupervisor::instance().registerBomFactory (_instance);
      }
      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    Inventory& FacInventory::create (const InventoryKey_T& iInventoryKey) {
      Inventory* aInventory_ptr = NULL;

      aInventory_ptr = new Inventory (iInventoryKey);
      assert (aInventory_ptr != NULL);

      // The new object is added to the Bom pool
      _pool.push_back (aInventory_ptr);

      return *aInventory_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    void FacInventory::
    initLinkWithFlightDate (Inventory& ioInventory,
                            FlightDate& ioFlightDate) {
      // Link the Inventory to the FlightDate, and vice versa
      ioFlightDate.setInventory (&ioInventory);
      
      // Link the Inventory to the FlightDate
      const bool insertSucceeded = ioInventory._flightDateList.
        insert (FlightDateList_T::value_type (ioFlightDate.describeShortKey(),
                                              &ioFlightDate)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion failed for " << ioInventory.describeKey()
                         << " and " << ioFlightDate.describeShortKey());
        assert (insertSucceeded == true);
      }
    }
  
    // //////////////////////////////////////////////////////////////////////
    void FacInventory::createRouting (Inventory& ioInventory) {
      const FlightDateList_T& lFlightDateList = ioInventory.getFlightDateList();
      for (FlightDateList_T::const_iterator itFlightDate =
             lFlightDateList.begin();
           itFlightDate != lFlightDateList.end(); itFlightDate++) {
        FlightDate* lFlightDate_ptr = itFlightDate->second;
        assert (lFlightDate_ptr != NULL);
        
        FacFlightDate::createRouting (*lFlightDate_ptr);
      }
    }
      
  }
}
