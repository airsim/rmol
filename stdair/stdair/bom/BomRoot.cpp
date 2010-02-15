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
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/Network.hpp>
#include <stdair/bom/DemandStream.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  BomRoot::BomRoot (const BomKey_T& iKey, BomStructure_T& ioBomRootStructure)
    : BomRootContent (iKey), _bomRootStructure (ioBomRootStructure) {
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
  AirlineFeatureSet& BomRoot::getAirlineFeatureSet() const {
    assert (_airlineFeatureSet != NULL);
    return *_airlineFeatureSet;
  }

  // ////////////////////////////////////////////////////////////////////
  DemandStreamList_T& BomRoot::getDemandStreamListRef() const {
    // TODO: check that the Boost smart pointer is not NULL
    STDAIR_LOG_ERROR ("!!!!TODO: check that the Boost smart pointer is not NULL!!!!");
    return *_demandStreamList;
  }
  
  // ////////////////////////////////////////////////////////////////////
  void BomRoot::addDemandStream (const DemandStreamKeyStr_T& iKeyStr,
                                 DemandStream& ioDemandStream) {
    // TODO: check that the Boost smart pointer is not NULL
    STDAIR_LOG_ERROR ("!!!!TODO: check that the Boost smart pointer is not NULL!!!!");
    
    // Insert the reference on the given DemandStream object into the
    // dedicated list
    const bool hasInsertBeenSuccessfull =
      _demandStreamList->insert (DemandStreamList_T::
                                 value_type (iKeyStr, &ioDemandStream)).second;
    if (hasInsertBeenSuccessfull == false) {
      STDAIR_LOG_ERROR ("The DemandStream object with key: " << iKeyStr
                        << " can not be inserted into the dedicated list");
      STDAIR_LOG_ERROR ("DemandStream object: " << ioDemandStream);
      assert (false);
    }
  }
  
}
