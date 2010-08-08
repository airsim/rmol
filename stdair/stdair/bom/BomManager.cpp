// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <ostream>
// StdAir
#include <stdair/STDAIR_Types.hpp>
#include <stdair/basic/BasConst_BomManager.hpp>
#include <stdair/bom/BomSource.hpp>
#include <stdair/bom/BookingRequestStruct.hpp>
#include <stdair/bom/BomManager.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
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

    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }
  
  // ////////////////////////////////////////////////////////////////////
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
  
  // ////////////////////////////////////////////////////////////////////
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
            << " (" << iFlightDate.getFlightDate() << std::endl;
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
  
  // ////////////////////////////////////////////////////////////////////
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
      const DateOffset_T lDateOffset = lCurrentLD.getDateOffset();      
      oStream << iFlightDate.getFlightNumber();
      oStream << " (" << iFlightDate.getFlightDate() << "), ";
      oStream << lCurrentLD.getBoardingPoint() << "-";
      oStream << lCurrentLD.getOffPoint() << ", ";
      oStream << lCurrentLD.getBoardingDate() << " -> ";
      oStream << lCurrentLD.getOffDate() << " / ";
      oStream << lDateOffset.days() << ", ";
      oStream << lCurrentLD.getBoardingTime() << " -> ";
      oStream << lCurrentLD.getOffTime() << " (";
      oStream << lCurrentLD.getTimeOffset() << ") / ";
      oStream << lCurrentLD.getElapsedTime() << ", ";
      oStream << lCurrentLD.getDistance() << ", ";
      oStream << lCurrentLD.getCapacity() << ", "
              << std::endl;
    }
    oStream << "******************************************" << std::endl;
    
    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }
  
  // ////////////////////////////////////////////////////////////////////
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
                << lCurrentLC.getOfferedCapacity() << ", "
                << lCurrentLC.getPhysicalCapacity() << ", "
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
  
  // ////////////////////////////////////////////////////////////////////
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

  // ////////////////////////////////////////////////////////////////////
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
        const DateOffset_T lDateOffset = lCurrentSD.getDateOffset();
        
        oStream << lCurrentSD.getBoardingPoint() << "-"
                << lCurrentSD.getOffPoint() << ", "
                << lCurrentSC.getCabinCode() << ", "          
                << lCurrentSD.getBoardingDate() << " -> "
                << lCurrentSD.getOffDate() << " / "
                << lDateOffset.days() << ", "
                << lCurrentSD.getBoardingTime() << " -> "
                << lCurrentSD.getOffTime() << " ("
                << lCurrentSD.getTimeOffset() << ") / "
                << lCurrentSD.getElapsedTime() << ", "
                << lCurrentSD.getDistance() << ", "
                << std::endl;
      }
    }
    oStream << "******************************************" << std::endl;

    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }
  
  // ////////////////////////////////////////////////////////////////////
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

  // ////////////////////////////////////////////////////////////////////
  void BomManager::display (std::ostream& oStream,
                            const BookingClass& iBookingClass) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    // Booking-class level
    oStream << iBookingClass.describeKey() << std::endl;
    
    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }

  // ////////////////////////////////////////////////////////////////////
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

  // ////////////////////////////////////////////////////////////////////
  void BomManager::displaySegmentPathNetwork (std::ostream& oStream,
                                              const BomRoot& iBomRoot) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    oStream << std::endl;

    // Browse the reachable universe objects.
    const ReachableUniverseList_T& lRUList = iBomRoot.getReachableUniverseList();
    for (ReachableUniverseList_T::iterator itRU = lRUList.begin();
         itRU != lRUList.end(); ++itRU) {
      const ReachableUniverse& lCurrentRU = *itRU;

      display (oStream, lCurrentRU);
    }

    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }

  // ////////////////////////////////////////////////////////////////////
  void BomManager::display (std::ostream& oStream,
                            const ReachableUniverse& iReachableUniverse) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    oStream << std::endl << "Reachable Universe level: "
            << iReachableUniverse.describeShortKey() << std::endl;

    // Browse the origin-destination set objects.
    const OriginDestinationSetList_T& lODSetList =
      iReachableUniverse.getOriginDestinationSetList ();
    for (OriginDestinationSetList_T::iterator itODS = lODSetList.begin();
         itODS != lODSetList.end(); ++itODS) {
      const OriginDestinationSet& lCurrentODS = *itODS;

      display (oStream, lCurrentODS);
    }

    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }

  // ////////////////////////////////////////////////////////////////////
  void BomManager::display (std::ostream& oStream,
                            const OriginDestinationSet& iOriginDestinationSet) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    oStream << "Origine-Destination Set level: "
            << iOriginDestinationSet.describeShortKey () << std::endl;
    
    // Browse the segment path period objects.
    const SegmentPathPeriodList_T& lSegmentPathPeriodList =
      iOriginDestinationSet.getSegmentPathPeriodList ();
    for (SegmentPathPeriodList_T::iterator itSegmentPath =
           lSegmentPathPeriodList.begin();
         itSegmentPath != lSegmentPathPeriodList.end(); ++itSegmentPath) {
      const SegmentPathPeriod& lCurrentSegmentPath = *itSegmentPath;

      display (oStream, lCurrentSegmentPath);
    }

    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }

  // ////////////////////////////////////////////////////////////////////
  void BomManager::display (std::ostream& oStream,
                            const SegmentPathPeriod& iSegmentPathPeriod) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    oStream << "Segment Path Period level: "
            << iSegmentPathPeriod.describeShortKey () << std::endl;

    // Browse the segment period objects.
    const SegmentPeriodList_T& lSegmentPeriodList =
      iSegmentPathPeriod.getSegmentPeriodList();
    for (SegmentPeriodList_T::iterator itSegmentPeriod =
           lSegmentPeriodList.begin();
         itSegmentPeriod != lSegmentPeriodList.end(); ++itSegmentPeriod) {
      const SegmentPeriod& lCurrentSegmentPeriod = *itSegmentPeriod;
      oStream << "Segment Period details: "
              << lCurrentSegmentPeriod.describeKey() << std::endl;
    }

    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }
  
}
