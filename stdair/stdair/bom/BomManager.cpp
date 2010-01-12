// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <ostream>
// STDAIR
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/AirlineFeatureSet.hpp>
#include <stdair/bom/AirlineFeature.hpp>
#include <stdair/bom/BomList.hpp>
#include <stdair/bom/BomMap.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/Network.hpp>
#include <stdair/bom/NetworkDate.hpp>
#include <stdair/bom/AirportDate.hpp>
#include <stdair/bom/OutboundPath.hpp>
#include <stdair/bom/BomManager.hpp>

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  void BomManager::display (std::ostream& oStream, const BomRoot& iBomRoot) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    // Browse the Inventory objects
    const InventoryList_T& lInventoryList= iBomRoot.getInventoryList ();
    for (InventoryList_T::iterator itInv = lInventoryList.begin();
         itInv != lInventoryList.end(); ++itInv) {
      const Inventory& lCurrentInventory = *itInv;

      // Call recursively the display() method on the children objects
      display (oStream, lCurrentInventory);
    }    

    // Browse the Network objects
    const NetworkList_T& lNetworkList= iBomRoot.getNetworkList ();
    for (NetworkList_T::iterator itInv = lNetworkList.begin();
         itInv != lNetworkList.end(); ++itInv) {
      const Network& lCurrentNetwork = *itInv;

      // Call recursively the display() method on the children objects
      oStream << std::endl;
      display (oStream, lCurrentNetwork);
    }    

    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void BomManager::display (std::ostream& oStream, const Inventory& iInventory) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    // Inventory level
    oStream << "Inventory: " << iInventory.describeKey() << std::endl;
    
    // Browse the FlightDate objects
    const FlightDateList_T& lFDList = iInventory.getFlightDateList ();
    for (FlightDateList_T::iterator itFD = lFDList.begin();
         itFD != lFDList.end(); ++itFD) {
      const FlightDate& lCurrentFD = *itFD;
      
      // Call recursively the display() method on the children objects
      display (oStream, lCurrentFD);
    }
    
    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void BomManager::display (std::ostream& oStream,
                            const FlightDate& iFlightDate) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    // Flight-date level
    oStream << iFlightDate.describeKey() << std::endl;
    
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
    
    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void BomManager::display (std::ostream& oStream,
                            const LegDate& iLegDate) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    // Leg-date level
    oStream << iLegDate.describeKey() << std::endl;
    
    // Browse the LegCabin objects
    const LegCabinList_T& lLCList = iLegDate.getLegCabinList();
    for (LegCabinList_T::iterator itLC = lLCList.begin();
         itLC != lLCList.end(); ++itLC) {
      const LegCabin& lCurrentLC = *itLC;

      // Call recursively the display() method on the children objects
      display (oStream, lCurrentLC);
    }
    
    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void BomManager::display (std::ostream& oStream,
                            const LegCabin& iLegCabin) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    // Leg-cabin level
    oStream << iLegCabin.describeKey() << std::endl;
    
    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void BomManager::display (std::ostream& oStream,
                            const SegmentDate& iSegmentDate) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    // Segment-date level
    oStream << iSegmentDate.describeKey() << std::endl;

    // Browse the SegmentCabin objects
    const SegmentCabinList_T& lSCList = iSegmentDate.getSegmentCabinList();
    for (SegmentCabinList_T::iterator itSC = lSCList.begin();
         itSC != lSCList.end(); ++itSC) {
      const SegmentCabin& lCurrentSC = *itSC;

      // Call recursively the display() method on the children objects
      display (oStream, lCurrentSC);
    }
    
    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void BomManager::display (std::ostream& oStream,
                            const SegmentCabin& iSegmentCabin) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    // Segment-cabin level
    oStream << iSegmentCabin.describeKey() << std::endl;
    
    // Browse the BookingClass objects
    const BookingClassList_T& lBCList = iSegmentCabin.getBookingClassList();
    for (BookingClassList_T::iterator itBC = lBCList.begin();
         itBC != lBCList.end(); ++itBC) {
      const BookingClass& lCurrentBC = *itBC;

      // Call recursively the display() method on the children objects
      display (oStream, lCurrentBC);
    } 
    
    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }

  // //////////////////////////////////////////////////////////////////////
  void BomManager::display (std::ostream& oStream,
                            const BookingClass& iBookingClass) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    // Booking-class level
    oStream << iBookingClass.describeKey() << std::endl;
    
    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }

  // //////////////////////////////////////////////////////////////////////
  void BomManager::display (std::ostream& oStream,
                            const Network& iNetwork) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    oStream << "Network: " << std::endl;

    int j = 1;
    const NetworkDateList_T& lNetworkDateList = iNetwork.getNetworkDateList();
    for (NetworkDateList_T::iterator itNetworkDate =
           lNetworkDateList.begin();
         itNetworkDate != lNetworkDateList.end(); ++itNetworkDate, ++j) {
      const NetworkDate& lCurrentNetworkDate = *itNetworkDate;
      

      // Call recursively the display() method on the children objects
      display (oStream, lCurrentNetworkDate);
    }
    
    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void BomManager::display (std::ostream& oStream,
                            const NetworkDate& iNetworkDate) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    oStream << iNetworkDate.describeKey() << std::endl;

    const AirportDateList_T& lAirportDateList= iNetworkDate.getAirportDateList();
    for (AirportDateList_T::iterator itAirportDate = lAirportDateList.begin();
         itAirportDate != lAirportDateList.end(); ++itAirportDate) {
      const AirportDate& lCurrentAirportDate = *itAirportDate;
      
      // Call recursively the display() method on the children objects
      display (oStream, lCurrentAirportDate);
    }
    
    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void BomManager::display (std::ostream& oStream,
                            const AirportDate& iAirportDate) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();
    
    oStream << iAirportDate.describeKey() << std::endl;

    const OutboundPathList_T& lOutboundPathList =
      iAirportDate.getOutboundPathList();
    for (OutboundPathList_T::iterator itPath = lOutboundPathList.begin();
         itPath != lOutboundPathList.end(); ++itPath) {
      const OutboundPath& lCurrentOutboundPath = *itPath;
      
      // Call recursively the display() method on the children objects
      display (oStream, lCurrentOutboundPath);
    }
    
    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void BomManager::display (std::ostream& oStream,
                            const OutboundPath& iOutboundPath) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    oStream << iOutboundPath.describeKey() << std::endl;

    const SegmentDateList_T& lSegmentDateList =
      iOutboundPath.getSegmentDateList();
    for (SegmentDateList_T::iterator itSegmentDate = lSegmentDateList.begin();
         itSegmentDate != lSegmentDateList.end(); ++itSegmentDate) {
      const SegmentDate& lCurrentSegmentDate = *itSegmentDate;
      
      oStream << lCurrentSegmentDate.describeKey() << std::endl;
    }
    
    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }
    
}
