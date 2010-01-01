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
    const InventoryList_T lInventoryList= iBomRoot.getInventoryList ();
    for (InventoryList_T::iterator itInv = lInventoryList.begin();
         itInv != lInventoryList.end(); ++itInv) {
      const Inventory& lCurrentInventory = *itInv;
      oStream << "Inventory: " << lCurrentInventory.toString();

      // Browse the FlightDate objects
      const FlightDateList_T lFDList =
        lCurrentInventory.getFlightDateList ();
      for (FlightDateList_T::iterator itFD = lFDList.begin();
           itFD != lFDList.end(); ++itFD) {
        const FlightDate& lCurrentFD = *itFD;
        oStream << "Flight-date: " << lCurrentFD.toString();

        // Browse the LegDate objects
        const LegDateList_T lLDList = lCurrentFD.getLegDateList();
        for (LegDateList_T::iterator itLD = lLDList.begin();
             itLD != lLDList.end(); ++itLD) {
          const LegDate& lCurrentLD = *itLD;
          oStream << "Leg-date: " << lCurrentLD.toString();
          
          // Browse the LegCabin objects
          const LegCabinList_T lLCList = lCurrentLD.getLegCabinList();
          for (LegCabinList_T::iterator itLC = lLCList.begin();
               itLC != lLCList.end(); ++itLC) {
            const LegCabin& lCurrentLC = *itLC;
            oStream << "Leg-cabin: " << lCurrentLC.toString();
          }
        }
        
        // Browse the SegmentDate objects
        const SegmentDateList_T lSDList =
          lCurrentFD.getSegmentDateList();
        for (SegmentDateList_T::iterator itSD = lSDList.begin();
             itSD != lSDList.end(); ++itSD) {
          const SegmentDate& lCurrentSD = *itSD;
          oStream << "Segment-date: " << lCurrentSD.toString();

          // Browse the SegmentCabin objects
          const SegmentCabinList_T lSCList =
            lCurrentSD.getSegmentCabinList();
          for (SegmentCabinList_T::iterator itSC = lSCList.begin();
               itSC != lSCList.end(); ++itSC) {
            const SegmentCabin& lCurrentSC = *itSC;
            oStream << "Segment-cabin: " << lCurrentSC.toString();

            // Browse the BookingClass objects
            const BookingClassList_T lBCList =
              lCurrentSC.getBookingClassList ();
            for (BookingClassList_T::iterator itBC = lBCList.begin();
                   itBC != lBCList.end(); ++itBC) {
              const BookingClass& lCurrentBC = *itBC;
              oStream << "Booking class: " << lCurrentBC.toString();
            }
          }
        }
      }
    }
  }    

}
