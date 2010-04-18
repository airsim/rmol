// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomRootStructure.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/BomList.hpp>
#include <stdair/bom/BomMap.hpp>
#include <stdair/bom/YieldStore.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/Network.hpp>
#include <stdair/bom/DemandStream.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  BomRoot::BomRoot (const BomKey_T& iKey, BomStructure_T& ioBomRootStructure)
    : BomRootContent (iKey), _bomRootStructure (ioBomRootStructure),
      _airlineFeatureSet (NULL) {
  }

  // ////////////////////////////////////////////////////////////////////
  BomRoot::~BomRoot () {
  }

  // ////////////////////////////////////////////////////////////////////
  InventoryList_T BomRoot::getInventoryList () const {
    return _bomRootStructure.getChildrenHolder();
  }

  // ////////////////////////////////////////////////////////////////////
  InventoryMap_T BomRoot::getInventoryMap () const {
    return _bomRootStructure.getChildrenHolder();
  }

  // ////////////////////////////////////////////////////////////////////
  NetworkList_T BomRoot::getNetworkList () const {
    return _bomRootStructure.getSecondChildrenHolder();
  }

  // ////////////////////////////////////////////////////////////////////
  NetworkMap_T BomRoot::getNetworkMap () const {
    return _bomRootStructure.getSecondChildrenHolder();
  }
  
  // //////////////////////////////////////////////////////////////////////
  DemandStreamList_T BomRoot::getDemandStreamList () const {
    return _bomRootStructure.getDemandStreamHolder();
  }

  // //////////////////////////////////////////////////////////////////////
  DemandStreamMap_T BomRoot::getDemandStreamMap () const {
    return _bomRootStructure.getDemandStreamHolder();
  }

  // ////////////////////////////////////////////////////////////////////
  YieldStore* BomRoot::getYieldStore (const AirlineCode_T& iAirlineCode) const {
    YieldStore* oYieldStore_ptr = NULL;

    // TODO: migrate to the new StdAir structure (e.g., IN, FD, etc.)
    /*
    YieldStoreMap_T lYieldStoreMap = getYieldStoreMap ();
    YieldStoreMap_T::iterator itInv = lYieldStoreMap.find (iAirlineCode);

    if (itInv != lYieldStoreMap.end()) {
      oYieldStore_ptr = itInv->second;
    }
    */
    
    return oYieldStore_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  Inventory* BomRoot::getInventory (const AirlineCode_T& iAirlineCode) const {
    Inventory* oInventory_ptr = NULL;

    InventoryMap_T lInventoryMap = getInventoryMap ();
    InventoryMap_T::iterator itInv = lInventoryMap.find (iAirlineCode);

    if (itInv != lInventoryMap.end()) {
      oInventory_ptr = itInv->second;
    }
    
    return oInventory_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  Network* BomRoot::getNetwork (const NetworkID_T& iNetworkID) const {
    Network* oNetwork_ptr = NULL;

    NetworkMap_T lNetworkMap = getNetworkMap ();
    NetworkMap_T::iterator itNetwork = lNetworkMap.find (iNetworkID);

    if (itNetwork != lNetworkMap.end()) {
      oNetwork_ptr = itNetwork->second;
    }
    
    return oNetwork_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  DemandStream& BomRoot::
  getDemandStream (const DemandStreamKeyStr_T& iKey) const {
    DemandStreamMap_T lDemandStreamMap = getDemandStreamMap ();

    DemandStreamMap_T::iterator itDemandStream = lDemandStreamMap.find (iKey);
    assert (itDemandStream != lDemandStreamMap.end());

    DemandStream* oDemandStream_ptr = itDemandStream->second;
    assert (oDemandStream_ptr != NULL);
    
    return *oDemandStream_ptr;
  }
  
  // ////////////////////////////////////////////////////////////////////
  AirlineFeatureSet& BomRoot::getAirlineFeatureSet() const {
    assert (_airlineFeatureSet != NULL);
    return *_airlineFeatureSet;
  }
  
}
