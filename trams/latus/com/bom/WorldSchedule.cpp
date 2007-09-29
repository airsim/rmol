// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream> // DEBUG
// LATUS COM
#include <latus/com/bom/WorldSchedule.hpp>
#include <latus/com/bom/Inventory.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    WorldSchedule::WorldSchedule (const DateTime_T& iUpdateDate)
      : _updateDate (iUpdateDate), _network (NULL) {
    }

    // //////////////////////////////////////////////////////////////////////
    WorldSchedule::~WorldSchedule() {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string WorldSchedule::describeKey() const {
      std::ostringstream ostr;
      ostr << _updateDate;
      return ostr.str();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void WorldSchedule::display() const {

      // Store current formatting flags of std::cout
      std::ios::fmtflags oldFlags = std::cout.flags();

      std::cout << _updateDate << std::endl;
      
      int j = 1;
      for (InventoryList_T::const_iterator itInventory =
             _inventoryList.begin();
           itInventory != _inventoryList.end(); ++itInventory, ++j) {
        const Inventory* lInventory_ptr = itInventory->second;
        assert (lInventory_ptr != NULL);

        lInventory_ptr->display ();
      }
      
      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }

    // //////////////////////////////////////////////////////////////////////
    void WorldSchedule::updateBookingAndSeatCounters() const {
      
      for (InventoryList_T::const_iterator itInventory =
             _inventoryList.begin();
           itInventory != _inventoryList.end(); ++itInventory) {
        const Inventory* lInventory_ptr = itInventory->second;
        assert (lInventory_ptr != NULL);

         lInventory_ptr->updateBookingsAndSeatCounters ();
      }
    }

     // //////////////////////////////////////////////////////////////////////
    void WorldSchedule::updateCommitedSpaces() const {
      
      for (InventoryList_T::const_iterator itInventory =
             _inventoryList.begin();
           itInventory != _inventoryList.end(); ++itInventory) {
        const Inventory* lInventory_ptr = itInventory->second;
        assert (lInventory_ptr != NULL);

         lInventory_ptr->updateCommitedSpaces ();
      }
    }

     // //////////////////////////////////////////////////////////////////////
    void WorldSchedule::updateAvailabilityPools() const {
      for (InventoryList_T::const_iterator itInventory =
             _inventoryList.begin();
           itInventory != _inventoryList.end(); ++itInventory) {
        const Inventory* lInventory_ptr = itInventory->second;
        assert (lInventory_ptr != NULL);

         lInventory_ptr->updateAvailabilityPools ();
      }
    }

     // //////////////////////////////////////////////////////////////////////
    void WorldSchedule::updateAllAvailabilities() const {
      for (InventoryList_T::const_iterator itInventory =
             _inventoryList.begin();
           itInventory != _inventoryList.end(); ++itInventory) {
        const Inventory* lInventory_ptr = itInventory->second;
        assert (lInventory_ptr != NULL);

         lInventory_ptr->updateAllAvailabilities ();
      }
    }
    
    // //////////////////////////////////////////////////////////////////////
    Network& WorldSchedule::getNetwork () const {
      assert (_network != NULL);
      return *_network;
    }
    
    // //////////////////////////////////////////////////////////////////////
    Inventory* WorldSchedule::
    getInventoryInternal (const std::string& iInventoryKey) const {
      Inventory* resultInventory_ptr = NULL;
      
      InventoryList_T::const_iterator itInventory =
        _inventoryList.find (iInventoryKey);

      if (itInventory != _inventoryList.end()) {
        resultInventory_ptr = itInventory->second;
      }

      return resultInventory_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    Inventory* WorldSchedule::
    getInventory (const AirlineCode_T& iAirlineCode) const {
      const InventoryKey_T lInventoryKey (iAirlineCode);
      const std::string& lInventoryKeyString = lInventoryKey.describeShort();
      return getInventoryInternal (lInventoryKeyString);
    }
    
  }
}
