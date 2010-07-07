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
  
  // ////////////////////////////////////////////////////////////////////
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

  // ////////////////////////////////////////////////////////////////////
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

  // ////////////////////////////////////////////////////////////////////
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
  
  // ////////////////////////////////////////////////////////////////////
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

  // ////////////////////////////////////////////////////////////////////
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

  // ////////////////////////////////////////////////////////////////////
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
  
  // ////////////////////////////////////////////////////////////////////
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

  // ////////////////////////////////////////////////////////////////////
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
  BookingClass& CmdBomManager::
  createBookingClass (const SegmentCabin& iSegmentCabin,
                      const ClassCode_T& iClassCode) {
    // Instantiate a booking class object with the given class code
    const BookingClassKey_T lClassKey (iClassCode);
    BookingClass& oClass =
      FacBomContent::instance().create<BookingClass> (lClassKey);
    // Link the created booking-class with its parent segment-cabin.
    FacBomContent::linkWithParent (oClass, iSegmentCabin);

    return oClass;
  } 
  
  // ////////////////////////////////////////////////////////////////////
  FlightPeriod& CmdBomManager::
  createFlightPeriod (const Inventory& iInventory,
                      const FlightPeriodKey_T& iFlightPeriodKey) {
    // Instantiate a flight-period object with the given key.
    FlightPeriod& oFlightPeriod =
      FacBomContent::instance().create<FlightPeriod> (iFlightPeriodKey);
    // Link the created inventory with the inventory.
    FacBomContent::linkWithParent (oFlightPeriod, iInventory);
    
    return oFlightPeriod;
  } 
  
  // ////////////////////////////////////////////////////////////////////
  SegmentPeriod& CmdBomManager::
  createSegmentPeriod (const FlightPeriod& iFlightPeriod,
                       const SegmentPeriodKey_T& iSegmentPeriodKey) {
    // Instantiate a segment-period object with the given key.
    SegmentPeriod& oSegmentPeriod =
      FacBomContent::instance().create<SegmentPeriod> (iSegmentPeriodKey);
    // Link the created segment-period with the flight-period.
    FacBomContent::linkWithParent (oSegmentPeriod, iFlightPeriod);
    
    return oSegmentPeriod;
  }

  // ////////////////////////////////////////////////////////////////////
  ReachableUniverse& CmdBomManager::
  createReachableUniverse (const BomRoot& iBomRoot,
                           const AirportCode_T& iOrigin) {
    // Instantiate a reachable-universe with the given origin.
    const ReachableUniverseKey_T lKey (iOrigin);
    ReachableUniverse& oReachableUniverse =
      FacBomContent::instance().create<ReachableUniverse> (lKey);
    // Link the created reachable-universe to the bom root.
    FacBomContent::linkWithParent (oReachableUniverse, iBomRoot);

    return oReachableUniverse;
  }

  // ////////////////////////////////////////////////////////////////////
  OriginDestinationSet& CmdBomManager::
  createOriginDestinationSet (const ReachableUniverse& iReachableUniverse,
                              const AirportCode_T& iDestination) {
    // Instantiate a origin-destination set with the given destination.
    const OriginDestinationSetKey_T lKey (iDestination);
    OriginDestinationSet& oOriginDestinationSet =
      FacBomContent::instance().create<OriginDestinationSet> (lKey);
    // Link the created origin-destination set to the bom root.
    FacBomContent::linkWithParent (oOriginDestinationSet, iReachableUniverse);

    return oOriginDestinationSet;
  } 
  
  // ////////////////////////////////////////////////////////////////////
  SegmentPathPeriod& CmdBomManager::
  createSegmentPathPeriod (const OriginDestinationSet& iOriginDestinationSet,
                       const SegmentPathPeriodKey_T& iSegmentPathPeriodKey) {
    // Instantiate a segment path period object with the given key.
    SegmentPathPeriod& oSegmentPathPeriod =
      FacBomContent::instance().create<SegmentPathPeriod>(iSegmentPathPeriodKey);
    // Link the created segment path period with the origin-destination set.
    FacBomContent::linkWithParent (oSegmentPathPeriod, iOriginDestinationSet);
    
    return oSegmentPathPeriod;
  }
  
}
