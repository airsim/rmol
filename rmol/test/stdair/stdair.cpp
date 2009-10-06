// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <cassert>
// STL
#include <iostream>
#include <string>
// STDAIR
#include <stdair/bom/BomStructureRoot.hpp>
#include <stdair/bom/BomStructureDummy.hpp>
#include <stdair/bom/BomContentDummy.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/BomContentRoot.hpp>
#include <stdair/bom/BomIterator.hpp>
#include <stdair/factory/FacBomContent.hpp>
// RMOL
#include <rmol/bom/Inventory.hpp>
#include <rmol/bom/FlightDate.hpp>
#include <rmol/bom/LegDate.hpp>
#include <rmol/bom/SegmentDate.hpp>

// /////////////////////////////////////////////////////////////////
#define LOG_DEBUG(iToBeLogged) \
  { std::cout << __FILE__ << ":" << __LINE__ << ": " << iToBeLogged << std::endl; }

// //////////////////////////////////////////////////////////////////////
RMOL::Inventory& initialise () {
  // DEBUG
  LOG_DEBUG ("Welcome to Air-Schedule");

  // Step 0.0: initialisation
  // Create the root of the Bom tree (i.e., a BomContentRoot object)
  RMOL::BomContentRoot_T& lBomContentRoot =
    stdair::FacBomContent::instance().createBomRoot<RMOL::Inventory>();
  
    
  // Step 0.1: Inventory level
  // Create an Inventory (BA)
  const stdair::AirlineCode_T lAirlineCode ("BA");
  const RMOL::InventoryKey_T lInventoryKey (lAirlineCode);
  
  RMOL::Inventory& lInventory =
    stdair::FacBomContent::instance().create<RMOL::Inventory> (lBomContentRoot,
                                                               lInventoryKey);
    
  // Display the inventory
  LOG_DEBUG ("Inventory: " << lInventory.toString());
    
  // Step 0.2: Flight-date level
  // Create a FlightDate (BA15/10-JUN-2010)
  const stdair::FlightNumber_T lFlightNumber = 15;
  const stdair::Date_T lDate (2010, 6, 10);
  const RMOL::FlightDateKey_T lFlightDateKey (lFlightNumber, lDate);

  RMOL::FlightDate& lFlightDate =
    stdair::FacBomContent::instance().create<RMOL::FlightDate> (lInventory,
                                                                lFlightDateKey);
    
  // Display the flight-date
  LOG_DEBUG ("FlightDate: " << lFlightDate.toString());
    
  // Step 0.3: Segment-date level
  // Create a first SegmentDate (LHR-SYD)
  const stdair::AirportCode_T lLHR ("LHR");
  const stdair::AirportCode_T lSYD ("SYD");
  RMOL::SegmentDateKey_T lSegmentDateKey (lLHR, lSYD);

  RMOL::SegmentDate& lLHRSYDSegment =
    stdair::FacBomContent::instance().create<RMOL::SegmentDate>(lFlightDate,
                                                                lSegmentDateKey);

  // Display the segment-date
  LOG_DEBUG ("SegmentDate: " << lLHRSYDSegment.toString());


  // Create a second SegmentDate (LHR-BKK)
  const stdair::AirportCode_T lBKK ("BKK");
  lSegmentDateKey = RMOL::SegmentDateKey_T (lLHR, lBKK);

  RMOL::SegmentDate& lLHRBKKSegment =
    stdair::FacBomContent::instance().create<RMOL::SegmentDate>(lFlightDate,
                                                                lSegmentDateKey);

  // Display the segment-date
  LOG_DEBUG ("SegmentDate: " << lLHRBKKSegment.toString());


  // Create a third SegmentDate (BKK-SYD)
  lSegmentDateKey = RMOL::SegmentDateKey_T (lBKK, lSYD);

  RMOL::SegmentDate& lBKKSYDSegment =
    stdair::FacBomContent::instance().create<RMOL::SegmentDate>(lFlightDate,
                                                                lSegmentDateKey);

  // Display the segment-date
  LOG_DEBUG ("SegmentDate: " << lBKKSYDSegment.toString());

    
  // Step 0.4: Leg-date level
  // Create a first LegDate (LHR)
  RMOL::LegDateKey_T lLegDateKey (lLHR);

  RMOL::LegDate& lLHRLeg =
    stdair::FacBomContent::instance().create<RMOL::LegDate> (lFlightDate,
                                                             lLegDateKey);

  // Display the leg-date
  LOG_DEBUG ("LegDate: " << lLHRLeg.toString());
    
  // Create a second LegDate (BKK)
  lLegDateKey = RMOL::LegDateKey_T (lBKK);

  RMOL::LegDate& lBKKLeg =
    stdair::FacBomContent::instance().create<RMOL::LegDate> (lFlightDate,
                                                             lLegDateKey);

  // Display the leg-date
  LOG_DEBUG ("LegDate: " << lBKKLeg.toString());
    
  // Step 0.5: Initialisation results
  // Display the full structure and content
  LOG_DEBUG ("Full Inventory: " << lInventory.toString());

  return lInventory;
}

// ////////////////////////////////////////////////////////////////
void testIteratorInventory (const RMOL::Inventory& iInventory) {
  LOG_DEBUG ("Test iterator.");

  // Browse the list with a for-loop
  LOG_DEBUG ("Browse the list");
  for (RMOL::Inventory::list_const_iterator itInv =
         iInventory.flightDateListConstIteratorBegin();
       itInv != iInventory.flightDateListConstIteratorEnd(); ++itInv) {
    LOG_DEBUG ("Current flight-date: " << *itInv);
  }
    
  // Browse the map with a for-loop
  LOG_DEBUG ("Browse the map with const_iterator");
  for (RMOL::Inventory::map_const_iterator itInv =
         iInventory.flightDateMapConstIteratorBegin();
       itInv != iInventory.flightDateMapConstIteratorEnd(); ++itInv) {
    const RMOL::FlightDate* lCurrentFlightDate_ptr = itInv->second;
    LOG_DEBUG ("Current flight-date: "
               << lCurrentFlightDate_ptr->toString());
  }

  LOG_DEBUG ("Browse the map with reverse_iterator");
  for (RMOL::Inventory::map_reverse_iterator itInv =
         iInventory.flightDateMapIteratorRBegin();
       itInv != iInventory.flightDateMapIteratorREnd(); ++itInv) {
    RMOL::FlightDate* lCurrentFlightDate_ptr = itInv->second;
    LOG_DEBUG ("Current flight-date: "
               << lCurrentFlightDate_ptr->toString());
  }

  LOG_DEBUG ("Test operators: ");

  RMOL::Inventory::list_const_iterator itBegin =
    iInventory.flightDateListConstIteratorBegin();
  RMOL::Inventory::list_const_iterator itEnd =
    iInventory.flightDateListConstIteratorEnd();
  
  LOG_DEBUG ("itEnd - itBegin, should be 1: " << itEnd - itBegin);
  LOG_DEBUG ("itBegin - itEnd, should be -1: " << itBegin - itEnd);
  LOG_DEBUG ("itBegin < itEnd, should be 1: " << (itBegin < itEnd));
  LOG_DEBUG ("itEnd - (1 + itBegin), should be 0: "
                      << (itEnd - (1 + itBegin)));
  LOG_DEBUG ( *(itEnd - 1));
  LOG_DEBUG ( *(itEnd -=1));
}

// ////////////////////////////////////////////////////////////////
void testIteratorFlightDate (const RMOL::FlightDate& iFlightDate) {
  LOG_DEBUG ("Test iterator.");

  // Browse the list with a for-loop
  LOG_DEBUG ("Browse the segment-date list");
  for (RMOL::FlightDate::segment_date_list_const_iterator itSD =
         iFlightDate.segmentDateListConstIteratorBegin();
       itSD != iFlightDate.segmentDateListConstIteratorEnd(); ++itSD) {
    LOG_DEBUG ("Current segment-date: " << *itSD);
  }
    
  // Browse the map with a for-loop
  LOG_DEBUG ("Browse the segment_date map with const_iterator");
  for (RMOL::FlightDate::segment_date_map_const_iterator itSD =
         iFlightDate.segmentDateMapConstIteratorBegin();
       itSD != iFlightDate.segmentDateMapConstIteratorEnd(); ++itSD) {
    const RMOL::SegmentDate* lCurrentSegmentDate_ptr = itSD->second;
    LOG_DEBUG ("Current segment-date: "
                        << lCurrentSegmentDate_ptr->toString());
  }

  // Browse the list with a for-loop
  LOG_DEBUG ("Browse the leg-date list");
  for (RMOL::FlightDate::leg_date_list_const_iterator itLD =
         iFlightDate.legDateListConstIteratorBegin();
       itLD != iFlightDate.legDateListConstIteratorEnd(); ++itLD) {
    LOG_DEBUG ("Current leg-date: " << *itLD);
  }
    
  // Browse the map with a for-loop
  LOG_DEBUG ("Browse the leg_date map with const_iterator");
  for (RMOL::FlightDate::leg_date_map_const_iterator itLD =
         iFlightDate.legDateMapConstIteratorBegin();
       itLD != iFlightDate.legDateMapConstIteratorEnd(); ++itLD) {
    const RMOL::LegDate* lCurrentLegDate_ptr = itLD->second;
    LOG_DEBUG ("Current leg-date: "
               << lCurrentLegDate_ptr->toString());
  }
}


// ////////////// M A I N ///////////////
int main (int argc, char* argv[]) {

  RMOL::Inventory& lInventory = initialise();

  testIteratorInventory (lInventory);

  // Browse the list with a for-loop
  LOG_DEBUG ("Browse the list");
  for (RMOL::Inventory::list_const_iterator itInv =
         lInventory.flightDateListConstIteratorBegin();
       itInv != lInventory.flightDateListConstIteratorEnd(); ++itInv) {
    const RMOL::FlightDate& lFlightDate = *itInv;
    
    LOG_DEBUG ("Current flight-date: " << lFlightDate);
    testIteratorFlightDate (lFlightDate);
  }

  return 0;
}
