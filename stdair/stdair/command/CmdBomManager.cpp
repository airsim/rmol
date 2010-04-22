// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// Boost
#include <boost/make_shared.hpp>
// StdAir
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/YieldStore.hpp>
#include <stdair/bom/AirlineFeature.hpp>
#include <stdair/bom/BomSource.hpp>
#include <stdair/factory/FacBomContent.hpp>
#include <stdair/command/CmdBomManager.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  void CmdBomManager::addAirlineFeature (BomRoot& ioBomRoot,
                                         const AirlineCode_T& iAirlineCode) {
    
    // Initialise an AirlineFeature object
    AirlineFeatureKey_T lAirlineFeatureKey (iAirlineCode);
    AirlineFeature& lAirlineFeature = FacBomContent::
      instance().create<AirlineFeature> (lAirlineFeatureKey);
    
    // Add the AirlineFeature object to its AirlineFeatureSet parent
    FacBomContent::linkWithParent (lAirlineFeature, ioBomRoot);

    // Link the AirlineFeature with its corresponding inventory (if exist)
    Inventory* lInventory_ptr = ioBomRoot.getInventory (iAirlineCode);
    if (lInventory_ptr != NULL) {
      lInventory_ptr->setAirlineFeature (&lAirlineFeature);
    }
  }
  
  // //////////////////////////////////////////////////////////////////////
  Inventory& CmdBomManager::
  createInventoryInternal (BomRoot& ioBomRoot,
                           const AirlineCode_T& iAirlineCode) {
    InventoryKey_T lInventoryKey (iAirlineCode);

    // Instantiate an Inventory object with the given airline code
    Inventory& lInventory =
      FacBomContent::instance().create<Inventory> (lInventoryKey);

    // Link the created inventory with the bom root.
    FacBomContent::linkWithParent (lInventory, ioBomRoot);

    // DEBUG
    STDAIR_LOG_DEBUG ("Generated inventory: " << iAirlineCode);
    const InventoryList_T lInvList = ioBomRoot.getInventoryList();
    for (InventoryList_T::iterator itInv = lInvList.begin();
         itInv != lInvList.end(); ++itInv) {
      const Inventory& lCurrentInv = *itInv;
      STDAIR_LOG_DEBUG ("Current inventory: " << lCurrentInv.describeKey());
    }
    
    return lInventory;
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory& CmdBomManager::
  getOrCreateInventory (BomRoot& ioBomRoot,
                        const AirlineCode_T& iAirlineCode) {
    Inventory* lInventory_ptr = ioBomRoot.getInventory (iAirlineCode);

    // If there is no Inventory object for that airline already, create one
    if (lInventory_ptr == NULL) {
      // Instantiate an Inventory object with the given airline code
      lInventory_ptr = &createInventoryInternal (ioBomRoot, iAirlineCode);
      assert (lInventory_ptr != NULL);

      // Set the AirlineFeature for the inventory.
      addAirlineFeature (ioBomRoot, iAirlineCode);
    }
    assert (lInventory_ptr != NULL);

    return *lInventory_ptr;
  }
  
  // //////////////////////////////////////////////////////////////////////
  YieldStore& CmdBomManager::
  createYieldStoreInternal (BomRoot& ioBomRoot,
                            const AirlineCode_T& iAirlineCode) {
    YieldStoreKey_T lYieldStoreKey (iAirlineCode);

    // Instantiate an YieldStore object with the given airline code
    YieldStore& lYieldStore =
      stdair::FacBomContent::instance().create<YieldStore> (lYieldStoreKey);

    // Link the created YieldStore with the bom root.
    FacBomContent::linkWithParent (lYieldStore, ioBomRoot);
      
    return lYieldStore;
  }

  // //////////////////////////////////////////////////////////////////////
  YieldStore& CmdBomManager::
  getOrCreateYieldStore (BomRoot& ioBomRoot,
                         const AirlineCode_T& iAirlineCode) {
    YieldStore* lYieldStore_ptr = ioBomRoot.getYieldStore (iAirlineCode);

    // If there is no YieldStore object for that airline already, create one
    if (lYieldStore_ptr == NULL) {
      const YieldStoreKey_T lYieldStoreKey (iAirlineCode);

      // Instantiate a YieldStore object with the given airline code
      lYieldStore_ptr = &createYieldStoreInternal (ioBomRoot, iAirlineCode);
      assert (lYieldStore_ptr != NULL);
    }
    assert (lYieldStore_ptr != NULL);

    return *lYieldStore_ptr;
  }
  
}
