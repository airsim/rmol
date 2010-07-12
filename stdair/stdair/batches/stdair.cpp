// STL
#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
// StdAir
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomList.hpp>
#include <stdair/bom/BomSource.hpp>
#include <stdair/factory/FacBomContent.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/STDAIR_Service.hpp>


// ///////// M A I N ////////////
int main (int argc, char* argv[]) {
  
  try {
    
    // Test create objects.
    
    // Output log File
    std::string lLogFilename ("stdair.log");
    
    // Set the log parameters
    std::ofstream logOutputFile;
    // open and clean the log outputfile
    logOutputFile.open (lLogFilename.c_str());
    logOutputFile.clear();

    const stdair::BasLogParams lLogParams (stdair::LOG::DEBUG, logOutputFile);
    stdair::STDAIR_Service stdairService (lLogParams);

    // DEBUG
    STDAIR_LOG_DEBUG ("Welcome to stdair");

    // Step 0.0: initialisation
    // Create the root of the Bom tree (i.e., a BomRoot object)
    stdair::BomRoot& lBomRoot =
      stdair::FacBomContent::instance().create<stdair::BomRoot>();
    
    
    // Step 0.1: Inventory level
    // Create an Inventory (BA)
    const stdair::AirlineCode_T lAirlineCode ("BA");
    stdair::InventoryKey_T lInventoryKey (lAirlineCode);

    stdair::Inventory& lInventory =
      stdair::FacBomContent::instance().create<stdair::Inventory>(lInventoryKey);
    stdair::FacBomContent::linkWithParent (lInventory, lBomRoot);

    // Display the inventory
    STDAIR_LOG_DEBUG ("Inventory: " << lInventory.toString());
    
    // Step 0.2: Flight-date level
    // Create a FlightDate (BA15/10-JUN-2010)
    const stdair::FlightNumber_T lFlightNumber = 15;
    const stdair::Date_T lDate (2010, 6, 10);
    stdair::FlightDateKey_T lFlightDateKey (lFlightNumber, lDate);

    stdair::FlightDate& lFlightDate = stdair::FacBomContent::
      instance().create<stdair::FlightDate> (lFlightDateKey);
    stdair::FacBomContent::linkWithParent (lFlightDate, lInventory);
    
    // Display the flight-date
    STDAIR_LOG_DEBUG ("FlightDate: " << lFlightDate.toString());
    
    // Step 0.3: Segment-date level
    // Create a first SegmentDate (LHR-SYD)
    const stdair::AirportCode_T lLHR ("LHR");
    const stdair::AirportCode_T lSYD ("SYD");
    stdair::SegmentDateKey_T lSegmentDateKey (lLHR, lSYD);

    stdair::SegmentDate& lLHRSYDSegment =
      stdair::FacBomContent::
      instance().create<stdair::SegmentDate> (lSegmentDateKey);
    stdair::FacBomContent::linkWithParent (lLHRSYDSegment, lFlightDate);

    // Display the segment-date
    STDAIR_LOG_DEBUG ("SegmentDate: " << lLHRSYDSegment.toString());


    // Create a second SegmentDate (LHR-BKK)
    const stdair::AirportCode_T lBKK ("BKK");
    lSegmentDateKey = stdair::SegmentDateKey_T (lLHR, lBKK);

    stdair::SegmentDate& lLHRBKKSegment =
      stdair::FacBomContent::
      instance().create<stdair::SegmentDate> (lSegmentDateKey);
    stdair::FacBomContent::linkWithParent (lLHRBKKSegment, lFlightDate);

    // Display the segment-date
    STDAIR_LOG_DEBUG ("SegmentDate: " << lLHRBKKSegment.toString());


    // Create a third SegmentDate (BKK-SYD)
    lSegmentDateKey = stdair::SegmentDateKey_T (lBKK, lSYD);

    stdair::SegmentDate& lBKKSYDSegment =
      stdair::FacBomContent::
      instance().create<stdair::SegmentDate> (lSegmentDateKey);
    stdair::FacBomContent::linkWithParent (lBKKSYDSegment, lFlightDate);

    // Display the segment-date
    STDAIR_LOG_DEBUG ("SegmentDate: " << lBKKSYDSegment.toString());

    
    // Step 0.4: Leg-date level
    // Create a first LegDate (LHR)
    stdair::LegDateKey_T lLegDateKey (lLHR);

    stdair::LegDate& lLHRLeg =
      stdair::FacBomContent::instance().create<stdair::LegDate> (lLegDateKey);
    stdair::FacBomContent::linkWithParent<stdair::LegDate>(lLHRLeg, lFlightDate);

    // Display the leg-date
    STDAIR_LOG_DEBUG ("LegDate: " << lLHRLeg.toString());
    
    // Create a second LegDate (BKK)
    lLegDateKey = stdair::LegDateKey_T (lBKK);

    stdair::LegDate& lBKKLeg =
      stdair::FacBomContent::instance().create<stdair::LegDate> (lLegDateKey);
    stdair::FacBomContent::linkWithParent (lBKKLeg, lFlightDate);

    // Display the leg-date
    STDAIR_LOG_DEBUG ("LegDate: " << lBKKLeg.toString());

    // Step 0.5: segment-cabin level
    // Create a SegmentCabin (Y) of the Segment LHR-BKK;
    const stdair::CabinCode_T lY ("Y");
    stdair::SegmentCabinKey_T lYSegmentCabinKey (lY);

    stdair::SegmentCabin& lLHRBKKSegmentYCabin =
      stdair::FacBomContent::
      instance().create<stdair::SegmentCabin> (lYSegmentCabinKey);
    stdair::FacBomContent::
      linkWithParent (lLHRBKKSegmentYCabin, lLHRBKKSegment);

    // Display the segment-cabin
    STDAIR_LOG_DEBUG ("SegmentCabin: " << lLHRBKKSegmentYCabin.toString());

    // Create a SegmentCabin (Y) of the Segment BKK-SYD;
    stdair::SegmentCabin& lBKKSYDSegmentYCabin =
      stdair::FacBomContent::
      instance().create<stdair::SegmentCabin> (lYSegmentCabinKey);
    stdair::FacBomContent::
      linkWithParent (lBKKSYDSegmentYCabin, lBKKSYDSegment);
     
    // Display the segment-cabin
    STDAIR_LOG_DEBUG ("SegmentCabin: " << lBKKSYDSegmentYCabin.toString());

    // Create a SegmentCabin (Y) of the Segment LHR-SYD;
    stdair::SegmentCabin& lLHRSYDSegmentYCabin =
      stdair::FacBomContent::
      instance().create<stdair::SegmentCabin> (lYSegmentCabinKey);
    stdair::FacBomContent::
      linkWithParent (lLHRSYDSegmentYCabin, lLHRSYDSegment);
      
    // Display the segment-cabin
    STDAIR_LOG_DEBUG ("SegmentCabin: " << lLHRSYDSegmentYCabin.toString());

    
    // Step 0.6: leg-cabin level
    // Create a LegCabin (Y) of the Leg LHR-BKK;
    stdair::LegCabinKey_T lYLegCabinKey (lY);

    stdair::LegCabin& lLHRLegYCabin =
      stdair::FacBomContent::instance().create<stdair::LegCabin> (lYLegCabinKey);
    stdair::FacBomContent::linkWithParent (lLHRLegYCabin, lLHRLeg);

    // Display the leg-cabin
    STDAIR_LOG_DEBUG ("LegCabin: " << lLHRLegYCabin.toString());

    // Create a LegCabin (Y) of the Leg BKK-SYD;
    stdair::LegCabin& lBKKLegYCabin =
      stdair::FacBomContent::instance().create<stdair::LegCabin> (lYLegCabinKey);
    stdair::FacBomContent::linkWithParent (lBKKLegYCabin, lBKKLeg);

    // Display the leg-cabin
    STDAIR_LOG_DEBUG ("LegCabin: " << lBKKLegYCabin.toString());

    // Step 0.7: booking class level
    // Create a BookingClass (Q) of the Segment LHR-BKK, cabin Y;
    const stdair::ClassCode_T lQ ("Q");
    stdair::BookingClassKey_T lQBookingClassKey (lQ);

    stdair::BookingClass& lLHRBKKSegmentYCabinQClass =
      stdair::FacBomContent::
      instance().create<stdair::BookingClass> (lQBookingClassKey);
    stdair::FacBomContent::
      linkWithParent (lLHRBKKSegmentYCabinQClass, lLHRBKKSegmentYCabin);

    // Display the booking class
    STDAIR_LOG_DEBUG ("BookingClass: "
		      << lLHRBKKSegmentYCabinQClass.toString());

    // Browse the BomRoot and display the created objects.
    STDAIR_LOG_DEBUG ("Browse the BomRoot");
    
    const stdair::InventoryList_T& lInventoryList = lBomRoot.getInventoryList();
    for (stdair::InventoryList_T::iterator itInv = lInventoryList.begin();
         itInv != lInventoryList.end(); ++itInv) {
      const stdair::Inventory& lCurrentInventory = *itInv;
      STDAIR_LOG_DEBUG ("Inventory: " << lCurrentInventory.toString());
      
      const stdair::FlightDateMap_T& lFlightDateMap = 
        lCurrentInventory.getFlightDateMap ();
      for (stdair::FlightDateMap_T::iterator itFlightDate = 
             lFlightDateMap.begin();
           itFlightDate != lFlightDateMap.end(); ++itFlightDate) {
        const stdair::FlightDate* lCurrentFlightDate = itFlightDate->second;
        STDAIR_LOG_DEBUG ("FlightDate: " << lCurrentFlightDate->describeKey());
      }
    }
    
    // Close the Log outputFile
    logOutputFile.close();

  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    return -1;
    
  } catch (...) {
    return -1;
  }
  
  return 0;	
}
