// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <fstream>
#include <string>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/STDAIR_Service.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/InventoryTypes.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/FlightDateTypes.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/LegDateTypes.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/LegCabinTypes.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/SegmentDateTypes.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/SegmentCabinTypes.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/BookingClassTypes.hpp>
#include <stdair/factory/FacBomManager.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/bom/SegmentDate.hpp>

// //////////////////////////////////////////////////////////////////////
stdair::Inventory& initialise () {
  // DEBUG
  STDAIR_LOG_DEBUG ("Welcome to Rmol");

  // Step 0.0: initialisation
  // Create the root of the Bom tree (i.e., a BomContentRoot object)
  stdair::BomRoot& lBomRoot =
    stdair::FacBom<stdair::BomRoot>::instance().create();
    
  // Step 0.1: Inventory level
  // Create an Inventory (BA)
  const stdair::AirlineCode_T lAirlineCode ("BA");
  const stdair::InventoryKey lInventoryKey (lAirlineCode);
  
  stdair::Inventory& lInventory =
    stdair::FacBom<stdair::Inventory>::instance().create (lInventoryKey);
  stdair::FacBomManager::instance().addToList (lBomRoot, lInventory);
    
  // Display the inventory
  STDAIR_LOG_DEBUG ("Inventory: " << lInventory.toString());
    
  // Step 0.2: Flight-date level
  // Create a FlightDate (BA15/10-JUN-2010)
  const stdair::FlightNumber_T lFlightNumber = 15;
  const stdair::Date_T lDate (2010, 6, 10);
  const stdair::FlightDateKey lFlightDateKey (lFlightNumber, lDate);

  stdair::FlightDate& lFlightDate =
    stdair::FacBom<stdair::FlightDate>::instance().create (lFlightDateKey);
  stdair::FacBomManager::instance().addToList (lInventory, lFlightDate);
    
  // Display the flight-date
  STDAIR_LOG_DEBUG ("FlightDate: " << lFlightDate.toString());
    
  // Step 0.3: Segment-date level
  // Create a first SegmentDate (LHR-SYD)
  const stdair::AirportCode_T lLHR ("LHR");
  const stdair::AirportCode_T lSYD ("SYD");
  stdair::SegmentDateKey lSegmentDateKey (lLHR, lSYD);

  stdair::SegmentDate& lLHRSYDSegment =
    stdair::FacBom<stdair::SegmentDate>::instance().create (lSegmentDateKey);
  stdair::FacBomManager::instance().addToList (lFlightDate, lLHRSYDSegment);

  // Display the segment-date
  STDAIR_LOG_DEBUG ("SegmentDate: " << lLHRSYDSegment.toString());


  // Create a second SegmentDate (LHR-BKK)
  const stdair::AirportCode_T lBKK ("BKK");
  lSegmentDateKey = stdair::SegmentDateKey (lLHR, lBKK);

  stdair::SegmentDate& lLHRBKKSegment =
    stdair::FacBom<stdair::SegmentDate>::instance().create (lSegmentDateKey);
  stdair::FacBomManager::instance().addToList (lFlightDate, lLHRBKKSegment);

  // Display the segment-date
  STDAIR_LOG_DEBUG ("SegmentDate: " << lLHRBKKSegment.toString());


  // Create a third SegmentDate (BKK-SYD)
  lSegmentDateKey = stdair::SegmentDateKey (lBKK, lSYD);

  stdair::SegmentDate& lBKKSYDSegment =
    stdair::FacBom<stdair::SegmentDate>::instance().create (lSegmentDateKey);
  stdair::FacBomManager::instance().addToList (lFlightDate, lBKKSYDSegment);

  // Display the segment-date
  STDAIR_LOG_DEBUG ("SegmentDate: " << lBKKSYDSegment.toString());

    
  // Step 0.4: Leg-date level
  // Create a first LegDate (LHR)
  stdair::LegDateKey lLegDateKey (lLHR);

  stdair::LegDate& lLHRLeg =
    stdair::FacBom<stdair::LegDate>::instance().create (lLegDateKey);
  stdair::FacBomManager::instance().addToList (lFlightDate, lLHRLeg);

  // Display the leg-date
  STDAIR_LOG_DEBUG ("LegDate: " << lLHRLeg.toString());
    
  // Create a second LegDate (BKK)
  lLegDateKey = stdair::LegDateKey (lBKK);

  stdair::LegDate& lBKKLeg =
    stdair::FacBom<stdair::LegDate>::instance().create (lLegDateKey);
  stdair::FacBomManager::instance().addToList (lFlightDate, lBKKLeg);

  // Display the leg-date
  STDAIR_LOG_DEBUG ("LegDate: " << lBKKLeg.toString());
    
  // Step 0.5: Initialisation results
  // Display the full structure and content
  STDAIR_LOG_DEBUG ("Full Inventory: " << lInventory.toString());

  return lInventory;
}

// ////////////////////////////////////////////////////////////////
void testIteratorInventory (const stdair::Inventory& iInventory) {
  // Browse the list of flight-dates
  STDAIR_LOG_DEBUG ("Browse the flight-date list");
  const stdair::FlightDateList_T& lFlightDateList =
    stdair::BomManager::getList<stdair::FlightDate> (iInventory);
  for (stdair::FlightDateList_T::const_iterator itFD = lFlightDateList.begin();
       itFD != lFlightDateList.end(); ++itFD) {
    const stdair::FlightDate* lFD_ptr = *itFD;
    assert (lFD_ptr != NULL);
    STDAIR_LOG_DEBUG ("Current flight-date: " << *lFD_ptr);
  }
}

// ////////////////////////////////////////////////////////////////
void testIteratorFlightDate (const stdair::FlightDate& iFlightDate) {
  // Browse the list of segment-dates
  STDAIR_LOG_DEBUG ("Browse the segment-date list");
  const stdair::SegmentDateList_T& lSegmentDateList =
    stdair::BomManager::getList<stdair::SegmentDate> (iFlightDate);
  for (stdair::SegmentDateList_T::const_iterator itSD =
         lSegmentDateList.begin();
       itSD != lSegmentDateList.end(); ++itSD) {
    const stdair::SegmentDate* lSD_ptr = *itSD;
    assert (lSD_ptr != NULL);
    STDAIR_LOG_DEBUG ("Current segment-date: " << *lSD_ptr);
  }

  // Browse the list of leg-dates
  STDAIR_LOG_DEBUG ("Browse the leg-date list");
  const stdair::LegDateList_T& lLegDateList =
    stdair::BomManager::getList<stdair::LegDate> (iFlightDate);
  for (stdair::LegDateList_T::const_iterator itLD =
         lLegDateList.begin();
       itLD != lLegDateList.end(); ++itLD) {
    const stdair::LegDate* lLD_ptr = *itLD;
    assert (lLD_ptr != NULL);
    STDAIR_LOG_DEBUG ("Current leg-date: " << *lLD_ptr);
  }
}


// ////////////// M A I N ///////////////
int main (int argc, char* argv[]) {

  // Output log File
  std::string lLogFilename ("stdair.log");
  
  // Set the log parameters
  std::ofstream logOutputFile;
  // Open and clean the log outputfile
  logOutputFile.open (lLogFilename.c_str());
  logOutputFile.clear();
  
  const stdair::BasLogParams lLogParams (stdair::LOG::DEBUG, logOutputFile);
  stdair::STDAIR_Service stdairService (lLogParams);
    
  //
  stdair::Inventory& lInventory = initialise();

  //
  testIteratorInventory (lInventory);

  // Browse the list with a for-loop
  STDAIR_LOG_DEBUG ("Browse the list of flight-dates");
  const stdair::FlightDateList_T& lFlightDateList =
    stdair::BomManager::getList<stdair::FlightDate> (lInventory);
  for (stdair::FlightDateList_T::const_iterator itFD = lFlightDateList.begin();
       itFD != lFlightDateList.end(); ++itFD) {
    const stdair::FlightDate* lFD_ptr = *itFD;
    assert (lFD_ptr != NULL);
    STDAIR_LOG_DEBUG ("Current flight-date: " << *lFD_ptr);
    testIteratorFlightDate (*lFD_ptr);
  }

  return 0;
}
