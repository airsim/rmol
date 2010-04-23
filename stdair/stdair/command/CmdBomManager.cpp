// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/bom/BomSource.hpp>
#include <stdair/factory/FacBomContent.hpp>
#include <stdair/command/CmdBomManager.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  void CmdBomManager::createAirlineFeature (const BomRoot& iBomRoot,
                                            const AirlineCode_T& iAirlineCode) {
    
    // Initialise an AirlineFeature object
    AirlineFeatureKey_T lAirlineFeatureKey (iAirlineCode);
    AirlineFeature& lAirlineFeature = FacBomContent::
      instance().create<AirlineFeature> (lAirlineFeatureKey);
    
    // Add the AirlineFeature object to its AirlineFeatureSet parent
    FacBomContent::linkWithParent (lAirlineFeature, iBomRoot);

    // Link the AirlineFeature with its corresponding inventory (if exist)
    Inventory* lInventory_ptr = iBomRoot.getInventory (iAirlineCode);
    if (lInventory_ptr != NULL) {
      lInventory_ptr->setAirlineFeature (&lAirlineFeature);
    }
  }

  // //////////////////////////////////////////////////////////////////////
  YieldStore& CmdBomManager::
  createYieldStore (const BomRoot& iBomRoot,
                    const AirlineCode_T& iAirlineCode) {
    // Instantiate an YieldStore object with the given airline code
    YieldStoreKey_T lYieldStoreKey (iAirlineCode);
    YieldStore& oYieldStore =
      stdair::FacBomContent::instance().create<YieldStore> (lYieldStoreKey);
    // Link the created YieldStore with the bom root.
    FacBomContent::linkWithParent (oYieldStore, iBomRoot);

    return oYieldStore;
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory& CmdBomManager::
  createInventory (const BomRoot& iBomRoot,
                   const AirlineCode_T& iAirlineCode) {
    // Instantiate an inventory object with the given airline code
    InventoryKey_T lInventoryKey (iAirlineCode);
    Inventory& oInventory =
      FacBomContent::instance().create<Inventory> (lInventoryKey);
    // Link the created inventory with the bom root.
    FacBomContent::linkWithParent (oInventory, iBomRoot);

    // Create the AirlineFeature for the inventory.
    createAirlineFeature (iBomRoot, iAirlineCode);
    
    return oInventory;
  }
  
  // //////////////////////////////////////////////////////////////////////
  FlightDate& CmdBomManager::
  createFlightDate (const Inventory& iInventory,
                    const FlightDateKey_T& iFlightDateKey) {
    // Instantiate a flight-date object with the given key.
    FlightDate& oFlightDate =
      FacBomContent::instance().create<FlightDate> (iFlightDateKey);
    // Link the created inventory with the inventory.
    FacBomContent::linkWithParent (oFlightDate, iInventory);
    
    return oFlightDate;
  }

  // //////////////////////////////////////////////////////////////////////
  LegDate& CmdBomManager::
  createLegDate (const FlightDate& iFlightDate,
                 const AirportCode_T& iBoardingPoint) {
    // Instantiate a leg-date object with the given boarding point
    LegDateKey_T lLegDateKey (iBoardingPoint);
    LegDate& oLegDate = FacBomContent::instance().create<LegDate> (lLegDateKey);
    // Link the created leg-date with the flight-date.
    FacBomContent::linkWithParent (oLegDate, iFlightDate);
    
    return oLegDate;
  }

  // //////////////////////////////////////////////////////////////////////
  LegCabin& CmdBomManager::
  createLegCabin (const LegDate& iLegDate,
                  const CabinCode_T& iCabinCode) {
    // Instantiate a leg-cabin object with the given cabin code
    LegCabinKey_T lLegCabinKey (iCabinCode);
    LegCabin& oLegCabin =
      FacBomContent::instance().create<LegCabin> (lLegCabinKey);
    // Link the created leg-cabin with the leg-date.
    FacBomContent::linkWithParent (oLegCabin, iLegDate);
    
    return oLegCabin;
  }
  
  // //////////////////////////////////////////////////////////////////////
  SegmentDate& CmdBomManager::
  createSegmentDate (const FlightDate& iFlightDate,
                    const SegmentDateKey_T& iSegmentDateKey) {
    // Instantiate a segment-date object with the given key.
    SegmentDate& oSegmentDate =
      FacBomContent::instance().create<SegmentDate> (iSegmentDateKey);
    // Link the created segment-date with the flight-date.
    FacBomContent::linkWithParent (oSegmentDate, iFlightDate);
    
    return oSegmentDate;
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentCabin& CmdBomManager::
  createSegmentCabin (const SegmentDate& iSegmentDate,
                      const CabinCode_T& iCabinCode) {
    // Instantiate a segment-cabin object with the given cabin code
    SegmentCabinKey_T lSegmentCabinKey (iCabinCode);
    SegmentCabin& oSegmentCabin =
      FacBomContent::instance().create<SegmentCabin> (lSegmentCabinKey);
    // Link the created segment-cabin with the segment-date.
    FacBomContent::linkWithParent (oSegmentCabin, iSegmentDate);
    
    return oSegmentCabin;
  }

  // ////////////////////////////////////////////////////////////////////
  void CmdBomManager::createBookingClass (const SegmentCabin& iSegmentCabin,
                                          const ClassCode_T& iClassCode) {
    // Instantiate a booking class object with the given class code
    const BookingClassKey_T lClassKey (iClassCode);
    BookingClass& lClass =
      FacBomContent::instance().create<BookingClass> (lClassKey);
    // Link the created booking-class with its parent segment-cabin.
    FacBomContent::linkWithParent (lClass, iSegmentCabin);
  }  

  // //////////////////////////////////////////////////////////////////////
  Network& CmdBomManager::
  createNetwork (const BomRoot& iBomRoot,
                 const NetworkKey_T& iNetworkKey) {
    // Instantiate an network object with the given key
    Network& oNetwork =
      FacBomContent::instance().create<Network> (iNetworkKey);
    // Link the created inventory with the bom root.
    FacBomContent::linkWithParent (oNetwork, iBomRoot);
    
    return oNetwork;
  }
  
  // //////////////////////////////////////////////////////////////////////
  NetworkDate& CmdBomManager::
  createNetworkDate (const Network& iNetwork, const Date_T& iDate) {
    // Instantiate a network-date object with the given date.
    const NetworkDateKey_T lNetworkDateKey (iDate);
    NetworkDate& oNetworkDate =
      FacBomContent::instance().create<NetworkDate> (lNetworkDateKey);
    // Link the created network with the bom root
    FacBomContent::linkWithParent (oNetworkDate, iNetwork);
    
    return oNetworkDate;
  }

  // //////////////////////////////////////////////////////////////////////
  AirportDate& CmdBomManager::
  createAirportDate (const NetworkDate& iNetworkDate,
                 const AirportCode_T& iBoardingPoint) {
    // Instantiate a airport-date object with the given boarding point
    AirportDateKey_T lAirportDateKey (iBoardingPoint);
    AirportDate& oAirportDate =
      FacBomContent::instance().create<AirportDate> (lAirportDateKey);
    // Link the created airport-date with the network-date.
    FacBomContent::linkWithParent (oAirportDate, iNetworkDate);
    
    return oAirportDate;
  }
  
  // //////////////////////////////////////////////////////////////////////
  OutboundPath& CmdBomManager::
  createOutboundPath (const AirportDate& iAirportDate,
                    const OutboundPathKey_T& iOutboundPathKey) {
    // Instantiate a outbound path object with the given key.
    OutboundPath& oOutboundPath =
      FacBomContent::instance().create<OutboundPath> (iOutboundPathKey);
    // Link the created outbound path with the airport-date
    FacBomContent::linkWithParent (oOutboundPath, iAirportDate);
    
    return oOutboundPath;
  }
  
}
