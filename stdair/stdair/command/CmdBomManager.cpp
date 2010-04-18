// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// Boost
#include <boost/make_shared.hpp>
// StdAir
#include <stdair/bom/BR.hpp>
#include <stdair/bom/YieldStore.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/AirlineFeatureSet.hpp>
#include <stdair/bom/AirlineFeature.hpp>
#include <stdair/bom/DemandStreamTypes.hpp>
// Inventory: child of BomRoot, needed for creation of BomRoot
#include <stdair/bom/Inventory.hpp>
// Network: child of BomRoot, needed for creation of BomRoot
#include <stdair/bom/Network.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/factory/FacSupervisor.hpp>
#include <stdair/factory/FacBomContent.hpp>
#include <stdair/command/CmdBomManager.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  void CmdBomManager::initAirlineFeatureSet (BomRoot& ioBomRoot) {  
    // Initialise the set of required airline features
    AirlineFeatureSet& lAirlineFeatureSet =
      FacBomContent::instance().create<AirlineFeatureSet>();
    // Set the AirlineFeatureSet for the BomRoot.
    ioBomRoot.setAirlineFeatureSet (&lAirlineFeatureSet);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void CmdBomManager::addAirlineFeature (BomRoot& ioBomRoot,
                                         const AirlineCode_T& iAirlineCode) {
    
    // Initialise an AirlineFeature object
    AirlineFeatureKey_T lAirlineFeatureKey (iAirlineCode);
    AirlineFeature& lAirlineFeature = FacBomContent::
      instance().create<AirlineFeature> (lAirlineFeatureKey);
    
    // Retrieve the AirlineFeatureSet object
    AirlineFeatureSet& lAirlineFeatureSet = ioBomRoot.getAirlineFeatureSet();
    
    // Add the AirlineFeature object to its AirlineFeatureSet parent
    FacBomContent::linkWithParent<AirlineFeature> (lAirlineFeature,
                                                   lAirlineFeatureSet);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void CmdBomManager::initDemandStreamList (BomRoot& ioBomRoot) {  
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
    FacBomContent::linkWithParent<Inventory> (lInventory, ioBomRoot);
      
    return lInventory;
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory& CmdBomManager::
  getOrCreateInventory (BomRoot& ioBomRoot,
                        const AirlineCode_T& iAirlineCode) {
    Inventory* lInventory_ptr = ioBomRoot.getInventory (iAirlineCode);

    // If there is no Inventory object for that airline already, create one
    if (lInventory_ptr == NULL) {
      const InventoryKey_T lInventoryKey (iAirlineCode);

      // Instantiate an Inventory object with the given airline code
      lInventory_ptr = &createInventoryInternal (ioBomRoot, iAirlineCode);
      assert (lInventory_ptr != NULL);

      // Set the AirlineFeature for the inventory.
      addAirlineFeature (ioBomRoot, iAirlineCode);

      // TODO: find a more elegant way to link the AirlineFeature back to the
      // Inventory object
      
      // Link the AirlineFeature with the Inventory object
      const AirlineFeatureSet& lAirlineFeatureSet =
        ioBomRoot.getAirlineFeatureSet ();
      const AirlineFeature* lAirlineFeature_ptr =
        lAirlineFeatureSet.getAirlineFeature (iAirlineCode);

      if (lAirlineFeature_ptr == NULL) {
        STDAIR_LOG_ERROR (lAirlineFeatureSet.display()
                          << "Needed airline code: " << iAirlineCode);
        assert (false);
      }
      
      lInventory_ptr->setAirlineFeature (lAirlineFeature_ptr);
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
      stdair::FacBomContent::instance().testCreate<YieldStore> (lYieldStoreKey);

    // TODO: migrate to the new StdAir structure (e.g., IN, FD, etc.)
    // Link the created YieldStore with the bom root.
    // FacBomContent::testLink<YieldStore> (lYieldStore, ioBomRoot);
      
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
