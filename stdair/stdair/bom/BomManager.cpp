// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <ostream>
// STDAIR
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/BomList.hpp>
#include <stdair/bom/BomMap.hpp>
#include <stdair/bom/AirlineFeatureSet.hpp>
#include <stdair/bom/AirlineFeature.hpp>
#include <stdair/bom/BomManager.hpp>

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  void BomManager::display (std::ostream& oStream, const BomRoot& iBomRoot) {
    // Browse the Inventory objects
    const InventoryList_T& lInventoryList= iBomRoot.getInventoryList ();
    for (InventoryList_T::iterator itInv = lInventoryList.begin();
         itInv != lInventoryList.end(); ++itInv) {
      const Inventory& lCurrentInventory = *itInv;

      // Call recursively the display() method on the children objects
      display (oStream, lCurrentInventory);
    }    

  }
  
  // //////////////////////////////////////////////////////////////////////
  void BomManager::display (std::ostream& oStream, const Inventory& iInventory) {
    // Inventory level
    oStream << "Inventory: " << iInventory.toString();
    
    // Browse the FlightDate objects
    const FlightDateList_T& lFDList = iInventory.getFlightDateList ();
    for (FlightDateList_T::iterator itFD = lFDList.begin();
         itFD != lFDList.end(); ++itFD) {
      const FlightDate& lCurrentFD = *itFD;
      
      // Call recursively the display() method on the children objects
      display (oStream, lCurrentFD);
    }
  }
  
  // //////////////////////////////////////////////////////////////////////
  void BomManager::display (std::ostream& oStream,
                            const FlightDate& iFlightDate) {
    // Flight-date level
    oStream << "Flight-date: " << iFlightDate.toString();
    
    // Browse the LegDate objects
    const LegDateList_T& lLDList = iFlightDate.getLegDateList();
    for (LegDateList_T::iterator itLD = lLDList.begin();
         itLD != lLDList.end(); ++itLD) {
      const LegDate& lCurrentLD = *itLD;
      
      // Call recursively the display() method on the children objects
      display (oStream, lCurrentLD);
    }
    
    // Browse the SegmentDate objects
    const SegmentDateList_T& lSDList = iFlightDate.getSegmentDateList();
    for (SegmentDateList_T::iterator itSD = lSDList.begin();
         itSD != lSDList.end(); ++itSD) {
      const SegmentDate& lCurrentSD = *itSD;
      
      // Call recursively the display() method on the children objects
      display (oStream, lCurrentSD);
    }
  }
  
  // //////////////////////////////////////////////////////////////////////
  void BomManager::display (std::ostream& oStream,
                            const LegDate& iLegDate) {
    // Leg-date level
    oStream << "Leg-date: " << iLegDate.toString();
    
    // Browse the LegCabin objects
    const LegCabinList_T& lLCList = iLegDate.getLegCabinList();
    for (LegCabinList_T::iterator itLC = lLCList.begin();
         itLC != lLCList.end(); ++itLC) {
      const LegCabin& lCurrentLC = *itLC;

      // Call recursively the display() method on the children objects
      display (oStream, lCurrentLC);
    }
  }
  
  // //////////////////////////////////////////////////////////////////////
  void BomManager::display (std::ostream& oStream,
                            const LegCabin& iLegCabin) {
    // Leg-cabin level
    oStream << "Leg-cabin: " << iLegCabin.toString();
  }
  
  // //////////////////////////////////////////////////////////////////////
  void BomManager::display (std::ostream& oStream,
                            const SegmentDate& iSegmentDate) {
    // Segment-date level
    oStream << "Segment-date: " << iSegmentDate.toString();

    // Browse the SegmentCabin objects
    const SegmentCabinList_T& lSCList = iSegmentDate.getSegmentCabinList();
    for (SegmentCabinList_T::iterator itSC = lSCList.begin();
         itSC != lSCList.end(); ++itSC) {
      const SegmentCabin& lCurrentSC = *itSC;

      // Call recursively the display() method on the children objects
      display (oStream, lCurrentSC);
    }
  }
  
  // //////////////////////////////////////////////////////////////////////
  void BomManager::display (std::ostream& oStream,
                            const SegmentCabin& iSegmentCabin) {
    // Segment-cabin level
    oStream << "Segment-cabin: " << iSegmentCabin.toString();
    
    // Browse the BookingClass objects
    const BookingClassList_T& lBCList = iSegmentCabin.getBookingClassList ();
    for (BookingClassList_T::iterator itBC = lBCList.begin();
         itBC != lBCList.end(); ++itBC) {
      const BookingClass& lCurrentBC = *itBC;

      // Call recursively the display() method on the children objects
      display (oStream, lCurrentBC);
    } 
  }

  // //////////////////////////////////////////////////////////////////////
  void BomManager::display (std::ostream& oStream,
                            const BookingClass& iBookingClass) {
    // Booking-class level
    oStream << "Booking class: " << iBookingClass.toString();
  }
  
}
