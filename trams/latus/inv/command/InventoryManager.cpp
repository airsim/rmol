// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/service/Logger.hpp>
// LATUS INV
#include <latus/inv/command/InventoryManager.hpp>

namespace LATUS {

  namespace INV {

    // //////////////////////////////////////////////////////////////////////
    InventoryManager::InventoryManager (const std::string& iInputFileName)
      : _inputFileName (iInputFileName), _worldSchedule (NULL) {

      // Read the input file and build the CityPairList
      const bool hasSucceeded = init();
      assert (hasSucceeded == true);
    }
      
    // //////////////////////////////////////////////////////////////////////
    InventoryManager::~InventoryManager() {
    }
    
    // //////////////////////////////////////////////////////////////////////
    bool InventoryManager::init () {
      return true;
    }
    
    // //////////////////////////////////////////////////////////////////////
    void InventoryManager::display () const {
    }

  }

}
