// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <ostream>
// StdAir
#include <stdair/basic/BasConst_BomManager.hpp>
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
#include <stdair/bom/BookingRequestStruct.hpp>
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
      csvFlightDateDisplay (oStream, lCurrentFD);
    }
    
    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void BomManager::csvFlightDateDisplay (std::ostream& oStream,
                                         const FlightDate& iFlightDate) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    // Display FlightDate-level information
    oStream << "******************************************" << std::endl;
    oStream << "FlightDate: " << iFlightDate.describeKey()  << std::endl
            << "-----------" << std::endl;
    oStream << "FlightNb (FlightDate), "
            << "SS, Rev, Fare, ASK, Yield, RPK, URev, LF, "
            << std::endl << std::endl;

    oStream << iFlightDate.getFlightNumber()
            << " (" << iFlightDate.getFlightDate() << "), "
            << iFlightDate.getBookingCounter() << ", "
            << iFlightDate.getRevenue() << ", "
            << iFlightDate.getAverageFare() << ", "
            << iFlightDate.getASK() << ", "
            << iFlightDate.getYield() << ", "
            << iFlightDate.getRPK() << ", "
            << iFlightDate.getUnitRevenue() << ", "
            << iFlightDate.getLoadFactor() << ", " << std::endl;
    oStream << "******************************************" << std::endl;
    
    // Display the leg-dates
    csvLegDateDisplay (oStream, iFlightDate);
    
    // Display the leg-cabins
    csvLegCabinDisplay (oStream, iFlightDate);
    
    // Display the buckets
    csvBPVDisplay (oStream, iFlightDate);
    
    // Display the segment-cabins
    csvSegmentCabinDisplay (oStream, iFlightDate);
    
    // Display the booking classes
    // csvClassDisplay (oStream, iFlightDate);

    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void BomManager::csvLegDateDisplay (std::ostream& oStream,
                                      const FlightDate& iFlightDate) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    // Display the header
    oStream << "******************************************" << std::endl;
    oStream << "Leg-Dates:" << std::endl
            << "----------" << std::endl;
    oStream << "FlightNb (FlightDate), Leg, "
            << "Dates, Times, Dist, Cap, ASK, SS, LF, "
            << std::endl << std::endl;
    
    // Browse the LegDate objects
    const LegDateList_T& lLDList = iFlightDate.getLegDateList();
    for (LegDateList_T::iterator itLD = lLDList.begin();
         itLD != lLDList.end(); ++itLD) {
      const LegDate& lCurrentLD = *itLD;
      
      oStream << iFlightDate.getFlightNumber()
              << " (" << iFlightDate.getFlightDate() << "), "
              << lCurrentLD.getBoardingPoint() << "-"
              << lCurrentLD.getOffPoint() << ", "
              << lCurrentLD.getBoardingDate() << " -> "
              << lCurrentLD.getOffDate() << " / "
              << lCurrentLD.getDateOffSet() << ", "
              << lCurrentLD.getBoardingTime() << " -> "
              << lCurrentLD.getOffTime() << " ("
              << lCurrentLD.getTimeOffSet() << ") / "
              << lCurrentLD.getElapsedTime() << ", "
              << lCurrentLD.getDistance() << ", "
              << lCurrentLD.getCapacity() << ", "
              << lCurrentLD.getASK() << ", "
              << lCurrentLD.getSoldSeat() << ", "
              << lCurrentLD.getLoadFactor() << ", "
              << std::endl;
    }
    oStream << "******************************************" << std::endl;
    
    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void BomManager::csvLegCabinDisplay (std::ostream& oStream,
                                       const FlightDate& iFlightDate) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    // Display the header
    oStream << "******************************************" << std::endl;
    oStream << "LegCabins:" << std::endl
            << "----------" << std::endl;
    oStream << "FlightNb (FlightDate), Leg, Cabin, "
            << "Cap, SS, CS, AvlPool, Avl, BP, "
            << std::endl;

    // Browse the LegDate objects
    const LegDateList_T& lLDList = iFlightDate.getLegDateList();
    for (LegDateList_T::iterator itLD = lLDList.begin();
         itLD != lLDList.end(); ++itLD) {
      const LegDate& lCurrentLD = *itLD;
      
      // Browse the LegCabin objects
      const LegCabinList_T& lLCList = lCurrentLD.getLegCabinList();
      for (LegCabinList_T::iterator itLC = lLCList.begin();
           itLC != lLCList.end(); ++itLC) {
        const LegCabin& lCurrentLC = *itLC;
        
        oStream << iFlightDate.getFlightNumber()
                << " (" << iFlightDate.getFlightDate() << "), "
                << lCurrentLD.getBoardingPoint() << "-"
                << lCurrentLD.getOffPoint() << ", "
                << lCurrentLC.getCabinCode() << ", "
                << lCurrentLC.getCapacity() << ", "
                << lCurrentLC.getSoldSeat() << ", "
                << lCurrentLC.getCommitedSpace() << ", "
                << lCurrentLC.getAvailabilityPool() << ", "
                << lCurrentLC.getAvailability() << ", "
                << lCurrentLC.getCurrentBidPrice() << ", " << std::endl;
      }
    }
    oStream << "******************************************" << std::endl;

    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void BomManager::csvBPVDisplay (std::ostream& oStream,
                                  const FlightDate& iFlightDate) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    // Display the header
    oStream << "******************************************" << std::endl;
    oStream << "Bid-Price Vector:" << std::endl;
    oStream << "Leg, Cabin, Yield, AV0, DSE, AV1, AV2, AV3, AV, SI" << std::endl;

    // Browse the LegDate objects
    const LegDateList_T& lLDList = iFlightDate.getLegDateList();
    for (LegDateList_T::iterator itLD = lLDList.begin();
         itLD != lLDList.end(); ++itLD) {
      const LegDate& lCurrentLD = *itLD;
      
      // Browse the LegCabin objects
      const LegCabinList_T& lLCList = lCurrentLD.getLegCabinList();
      for (LegCabinList_T::iterator itLC = lLCList.begin();
           itLC != lLCList.end(); ++itLC) {
        LegCabin& lCurrentLC = *itLC;
        
        const BidPriceVector_T& aBidPriceVector = lCurrentLC.getBidPriceVector();
        for (BidPriceVector_T::const_reverse_iterator itBidPrice =
               aBidPriceVector.rbegin();
             itBidPrice != aBidPriceVector.rend(); ++itBidPrice) {
          const BidPrice_T& aBidPrice = *itBidPrice;

          oStream << lCurrentLD.getBoardingPoint() << "-"
                  << lCurrentLD.getOffPoint() << ", "
                  << lCurrentLC.getCabinCode() << ", "
                  << aBidPrice << ", " << std::endl;
        }
      }
    }
    oStream << "******************************************" << std::endl;
    
    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }

  // //////////////////////////////////////////////////////////////////////
  void BomManager::csvSegmentCabinDisplay (std::ostream& oStream,
                                           const FlightDate& iFlightDate) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    // Display the header
    oStream << "******************************************" << std::endl;
    oStream << "SegmentCabins:" << std::endl
                << "--------------" << std::endl;
    oStream << "Segment, Cabin, Dates, Times, Dist, SS, Rev, Fare, URev, RPK, "
            << std::endl;

    // Browse the SegmentDate objects
    const SegmentDateList_T& lSDList = iFlightDate.getSegmentDateList();
    for (SegmentDateList_T::iterator itSD = lSDList.begin();
         itSD != lSDList.end(); ++itSD) {
      const SegmentDate& lCurrentSD = *itSD;
      
      // Browse the SegmentCabin objects
      const SegmentCabinList_T& lSCList = lCurrentSD.getSegmentCabinList();
      for (SegmentCabinList_T::iterator itSC = lSCList.begin();
           itSC != lSCList.end(); ++itSC) {
        const SegmentCabin& lCurrentSC = *itSC;
        
        oStream << lCurrentSD.getBoardingPoint() << "-"
                << lCurrentSD.getOffPoint() << ", "
                << lCurrentSC.getCabinCode() << ", "          
                << lCurrentSD.getBoardingDate() << " -> "
                << lCurrentSD.getOffDate() << " / "
                << lCurrentSD.getDateOffSet() << ", "
                << lCurrentSD.getBoardingTime() << " -> "
                << lCurrentSD.getOffTime() << " ("
                << lCurrentSD.getTimeOffSet() << ") / "
                << lCurrentSD.getElapsedTime() << ", "
                << lCurrentSD.getDistance() << ", "
                << lCurrentSD.getBookingCounter() << ", "
                << lCurrentSD.getRevenue() << ", "
                << lCurrentSD.getAverageFare() << ", "
                << lCurrentSD.getUnitRevenue() << ", "
                << lCurrentSD.getRPK() << ", "
                << std::endl;
      }
    }
    oStream << "******************************************" << std::endl;

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

  // //////////////////////////////////////////////////////////////////////
  void BomManager::display (std::ostream& oStream,
                            const AirlineFeatureSet& iAirlineFeatureSet) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    oStream << iAirlineFeatureSet.describeKey() << std::endl;

    const AirlineFeatureList_T& lAirlineFeatureList =
      iAirlineFeatureSet.getAirlineFeatureList();
    for (AirlineFeatureList_T::iterator itAirlineFeature =
           lAirlineFeatureList.begin();
         itAirlineFeature != lAirlineFeatureList.end(); ++itAirlineFeature) {
      const AirlineFeature& lCurrentAirlineFeature = *itAirlineFeature;
      
      oStream << lCurrentAirlineFeature.describeKey() << std::endl;
    }
    
    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }

  // //////////////////////////////////////////////////////////////////////
  void BomManager::csvDisplay (std::ostream& oStream,
                               const BookingRequestStruct& iBookingRequest) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    /**
      #id, request_date (YYMMDD), request_time (HHMMSS), POS (three-letter code),
       origin (three-letter code), destination (three-letter code),
       preferred departure date (YYMMDD), preferred departure time (HHMM),
       min departure time (HHMM), max departure time (HHMM),
       preferred cabin (F/C/M), trip type (OW/RO/RI), duration of stay (days),
       frequent flyer tier (G/S/K/N), willingness-to-pay (SGD),
       disutility per stop (SGD), preferred arrival date (YYMMDD),
       preferred arrival time (HHMM), value of time (SGD per hour)

      #Preferred cabin: F=First, C=Business M=Economy
      #Trip type: OW=One-way, RO=Round-trip outbound portion,
        RI=Round-trip inbound portion
      #Duration of stay: irrelevant in case of one-way, but set to 0
      #Frequent-flyer tier: G=Gold, S=Silver, K=Basic (Krisflyer), N=None
    */

    // Request date&time
    const DateTime_T& lRequestDateTime = iBookingRequest.getRequestDateTime();
    intDisplay (oStream, lRequestDateTime.date().year());
    intDisplay (oStream, lRequestDateTime.date().month());
    intDisplay (oStream, lRequestDateTime.date().day());
    oStream << ", ";
    intDisplay (oStream, lRequestDateTime.time_of_day().hours());
    intDisplay (oStream, lRequestDateTime.time_of_day().minutes());
    intDisplay (oStream, lRequestDateTime.time_of_day().seconds());
    oStream << ", ";
    // POS
    oStream << iBookingRequest.getPOS() << ", ";
    // Origin
    oStream << iBookingRequest.getOrigin() << ", ";
    // Destination
    oStream << iBookingRequest.getDestination() << ", ";
    // Preferred departure date
    const Date_T& lPreferredDepartureDate =
      iBookingRequest.getPreferedDepartureDate();
    intDisplay (oStream, lPreferredDepartureDate.year());
    intDisplay (oStream, lPreferredDepartureDate.month());
    intDisplay (oStream, lPreferredDepartureDate.day());
    oStream << ", ";
    // Preferred departure time
    const Duration_T& lPreferredDepartureTime =
      iBookingRequest.getPreferredDepartureTime();
    intDisplay (oStream, lPreferredDepartureTime.hours());
    intDisplay (oStream, lPreferredDepartureTime.minutes());
    oStream << ", ";
    // MIN & MAX preferred departure time (hardcode)
    oStream << "0000, 2359, ";
    // Preferred cabin
    oStream << iBookingRequest.getPreferredCabin() << ", ";
    // Trip type
    oStream << iBookingRequest.getTripType() << ", ";
    // Duration of stay
    if (iBookingRequest.getTripType() == "OW") {
      oStream << "0, ";
    } else {
      oStream << iBookingRequest.getStayDuration() << ", ";
    }
    // Frequent flyer tier
    oStream << iBookingRequest.getFrequentFlyerType() << ", ";
    // Willingness-to-pay
    oStream << iBookingRequest.getWTP() << ", ";
    // Disutility per stop (hardcode to 100)
    oStream << "100, ";
    // Preferred arrival date (hardcode to the preferred departure date)
    intDisplay (oStream, lPreferredDepartureDate.year());
    intDisplay (oStream, lPreferredDepartureDate.month());
    intDisplay (oStream, lPreferredDepartureDate.day());
    oStream << ", ";
    // Preferred arrival time (hardcode to 23:55
    oStream << "2355, ";
    // Value of time
    oStream <<iBookingRequest.getValueOfTime() << std::endl;
    
    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }

  // ////////////////////////////////////////////////////////////////////
  void BomManager::intDisplay (std::ostream& oStream, const int& iInt) {
    const int dInt = iInt - static_cast<int>(iInt/100)*100;
    if (dInt < 10) {
      oStream << "0" << dInt;
    } else {
      oStream << dInt;
    }
  }
  
}
