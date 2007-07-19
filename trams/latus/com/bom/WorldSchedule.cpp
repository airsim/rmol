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
    WorldSchedule::WorldSchedule (const boost::gregorian::date& iUpdateDate)
      : _updateDate (iUpdateDate) {
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
           itInventory != _inventoryList.end(); itInventory++, j++) {
        const Inventory* lInventory_ptr = itInventory->second;
        assert (lInventory_ptr != NULL);

        lInventory_ptr->display ();
      }
      
      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }
    
  }
}
