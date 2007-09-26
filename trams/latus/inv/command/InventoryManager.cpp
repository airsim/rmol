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
      : _worldSchedule (NULL), _inputFileName (iInputFileName) {

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
