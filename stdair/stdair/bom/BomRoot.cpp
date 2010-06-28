// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomSource.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  BomRoot::BomRoot (const Key_T& iKey, Structure_T& ioBomRootStructure)
    : BomRootContent (iKey), _structure (ioBomRootStructure) {
    init();
  }

  // ////////////////////////////////////////////////////////////////////
  BomRoot::~BomRoot () {
  }

  // ////////////////////////////////////////////////////////////////////
  void BomRoot::init() {
    _structure.initChildrenHolder<Inventory>();
    _structure.initChildrenHolder<ReachableUniverse>();
    _structure.initChildrenHolder<Network>();
    _structure.initChildrenHolder<AirlineFeature>();
    _structure.initChildrenHolder<DemandStream>();
    _structure.initChildrenHolder<YieldStore>();
  }

  // ////////////////////////////////////////////////////////////////////
  InventoryList_T BomRoot::getInventoryList () const {
    return _structure.getChildrenHolder<Inventory>();
  }

  // ////////////////////////////////////////////////////////////////////
  InventoryMap_T BomRoot::getInventoryMap () const {
    return _structure.getChildrenHolder<Inventory>();
  }

  // ////////////////////////////////////////////////////////////////////
  ReachableUniverseList_T BomRoot::getReachableUniverseList () const {
    return _structure.getChildrenHolder<ReachableUniverse>();
  }

  // ////////////////////////////////////////////////////////////////////
  ReachableUniverseMap_T BomRoot::getReachableUniverseMap () const {
    return _structure.getChildrenHolder<ReachableUniverse>();
  }

  // ////////////////////////////////////////////////////////////////////
  NetworkList_T BomRoot::getNetworkList () const {
    return _structure.getChildrenHolder<Network>();
  }

  // ////////////////////////////////////////////////////////////////////
  NetworkMap_T BomRoot::getNetworkMap () const {
    return _structure.getChildrenHolder<Network>();
  }
  
  // ////////////////////////////////////////////////////////////////////
  DemandStreamList_T BomRoot::getDemandStreamList () const {
    return _structure.getChildrenHolder<DemandStream>();
  }

  // ////////////////////////////////////////////////////////////////////
  DemandStreamMap_T BomRoot::getDemandStreamMap () const {
    return _structure.getChildrenHolder<DemandStream>();
  }

  // ////////////////////////////////////////////////////////////////////
  AirlineFeatureList_T BomRoot::getAirlineFeatureList () const {
    return _structure.getChildrenHolder<AirlineFeature>();
  }

  // ////////////////////////////////////////////////////////////////////
  AirlineFeatureMap_T BomRoot::getAirlineFeatureMap () const {
    return _structure.getChildrenHolder<AirlineFeature>();
  }

  // ////////////////////////////////////////////////////////////////////
  YieldStoreList_T BomRoot::getYieldStoreList () const {
    return _structure.getChildrenHolder<YieldStore>();
  }

  // ////////////////////////////////////////////////////////////////////
  YieldStoreMap_T BomRoot::getYieldStoreMap () const {
    return _structure.getChildrenHolder<YieldStore>();
  }

  // ////////////////////////////////////////////////////////////////////
  Inventory* BomRoot::getInventory (const AirlineCode_T& iAirlineCode) const {
    return _structure.getChildPtr<Inventory> (iAirlineCode);
  }

  // ////////////////////////////////////////////////////////////////////
  ReachableUniverse* BomRoot::
  getReachableUniverse (const AirportCode_T& iAirportCode) const {
    return _structure.getChildPtr<ReachableUniverse> (iAirportCode);
  }

  // ////////////////////////////////////////////////////////////////////
  Network* BomRoot::getNetwork (const NetworkID_T& iNetworkID) const {
    return _structure.getChildPtr<Network> (iNetworkID);
  }

  // ////////////////////////////////////////////////////////////////////
  YieldStore* BomRoot::getYieldStore (const AirlineCode_T& iAirlineCode) const {
    return _structure.getChildPtr<YieldStore> (iAirlineCode);
  }
  
  // ////////////////////////////////////////////////////////////////////
  AirlineFeature* BomRoot::
  getAirlineFeature (const AirlineCode_T& iAirlineCode) const {
    return _structure.getChildPtr<AirlineFeature> (iAirlineCode);
  }

  // ////////////////////////////////////////////////////////////////////
  DemandStream& BomRoot::
  getDemandStream (const DemandStreamKeyStr_T& iKey) const {
    return _structure.getChild<DemandStream> (iKey);
  }
  
}
