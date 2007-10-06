// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// BOOST (STL Extension)
#include <boost/date_time/date_iterator.hpp>
// LATUS Common
#include <latus/com/basic/BasConst_BOOST_DateTime.hpp>
#include <latus/com/bom/WorldSchedule.hpp>
#include <latus/com/bom/Inventory.hpp>
#include <latus/com/bom/FlightDate.hpp>
#include <latus/com/bom/LegDate.hpp>
#include <latus/com/bom/SegmentDate.hpp>
#include <latus/com/bom/LegCabin.hpp>
#include <latus/com/bom/SegmentCabin.hpp>
#include <latus/com/factory/FacWorldSchedule.hpp>
#include <latus/com/factory/FacInventory.hpp>
#include <latus/com/factory/FacFlightDate.hpp>
#include <latus/com/factory/FacLegDate.hpp>
#include <latus/com/factory/FacSegmentDate.hpp>
#include <latus/com/factory/FacLegCabin.hpp>
#include <latus/com/factory/FacSegmentCabin.hpp>
#include <latus/com/service/Logger.hpp>
// LATUS TSP
#include <latus/tsp/bom/FlightPeriodStruct.hpp>
#include <latus/tsp/command/InventoryGenerator.hpp>

namespace LATUS {

  namespace TSP {

    // //////////////////////////////////////////////////////////////////////
    void InventoryGenerator::
    createFlightDates (COM::WorldSchedule& ioWorldSchedule,
                       const FlightPeriodStruct_T& iFlightPeriod) {
      const COM::AirlineCode_T& lAirlineCode = iFlightPeriod._airlineCode;

      COM::Inventory* lInventory_ptr =
        ioWorldSchedule.getInventory (lAirlineCode);
      
      if (lInventory_ptr == NULL) {
        // Instantiate an Inventory object for the given key (airline code)
        lInventory_ptr = &createInventory (ioWorldSchedule, lAirlineCode);
        assert (lInventory_ptr != NULL);
      }

      // Generate all the dates corresponding to the period
      // and create the corresponding flight-dates.
      const COM::DatePeriod_T lDateRange = iFlightPeriod._dateRange;

      for (boost::gregorian::day_iterator itDate = lDateRange.begin();
           itDate != lDateRange.end(); ++itDate) {
        const COM::DateTime_T currentDate = *itDate;

        // Retrieve, for the current day, the Day-Of-the-Week (thanks to Boost)
        const unsigned short currentDOW = currentDate.day_of_week().as_number();
        
        // The FlightPeriod structure stores which Days (-Of-the-Week) are
        // active within the week. For each day (Mon., Tue., etc.), a boolean
        // states whether the Flight is active for that day.
        const DOWStruct_T& lDOWList = iFlightPeriod._dow;
        const bool isDOWActive = lDOWList.getStandardDayOfWeek (currentDOW);

        if (isDOWActive == true) {
          createFlightDate (*lInventory_ptr, currentDate, iFlightPeriod);
        }
      }
    }
    
    // //////////////////////////////////////////////////////////////////////
    void InventoryGenerator::
    createRouting (COM::WorldSchedule& ioWorldSchedule) {
      COM::FacWorldSchedule::createRouting (ioWorldSchedule);
    }

     // //////////////////////////////////////////////////////////////////////
    void InventoryGenerator::
    recalculateAvailabilities (COM::WorldSchedule& ioWorldSchedule) {
      ioWorldSchedule.recalculateAvailabilities ();      
    }
      
    // //////////////////////////////////////////////////////////////////////
    COM::Inventory& InventoryGenerator::
    createInventory (COM::WorldSchedule& ioWorldSchedule,
                     const COM::AirlineCode_T& iAirlineCode) {
      const COM::InventoryKey_T lInventoryKey (iAirlineCode);

      // Instantiate an Inventory object with the given airline code
      COM::Inventory& lInventory =
        COM::FacInventory::instance().create (lInventoryKey);
      
      // Link the Inventory with the WorldSchedule
      COM::FacWorldSchedule::initLinkWithInventory (ioWorldSchedule,
                                                    lInventory);
      
      return lInventory;
    }
      
    // //////////////////////////////////////////////////////////////////////
    void InventoryGenerator::
    createFlightDate (COM::Inventory& ioInventory,
                      const COM::DateTime_T& iFlightDate,
                      const FlightPeriodStruct_T& iFlightPeriod) {
      // Create the FlightDateKey
      const COM::InventoryKey_T& lInventoryKey = ioInventory.getPrimaryKey();
      const COM::FlightNumber_T& lFlightNumber = iFlightPeriod._flightNumber;
      const COM::FlightKey_T lFlightKey (lInventoryKey, lFlightNumber);
      const COM::FlightDateKey_T lFlightDateKey (lFlightKey, iFlightDate);

      // Check that the FlightDate object is not already existing. If a
      // FlightDate object with the same key has already been created,
      // it means that the schedule input file is invalid (two flight-periods
      // are overlapping).
      COM::FlightDate* lFlightDate_ptr =
        ioInventory.getFlightDate (lFlightNumber, iFlightDate);

      if (lFlightDate_ptr != NULL) {
        // TODO: transform that error into an exception (duplicated
        // entry in schedule input file), as there should not be any
        // duplicated Flight-Date.
        LATUS_LOG_ERROR ("The flight-date: " << lFlightDateKey
                         << " is duplicated within the schedule input file.");
        return;
      }
      assert (lFlightDate_ptr == NULL);
      
      // Instantiate a FlightDate object for the given key (flight number and
      // flight date)
      lFlightDate_ptr = &COM::FacFlightDate::instance().create (lFlightDateKey);
      assert (lFlightDate_ptr != NULL);
        
      // Link the FlightDate with the Inventory
      COM::FacInventory::initLinkWithFlightDate (ioInventory, *lFlightDate_ptr);

      // Iterate on the Leg-Dates
      COM::Duration_T currentOffTime (0, 0, 0);
      COM::AirportCode_T previousOffPoint;
      const LegStructList_T& lLegList = iFlightPeriod._legList;
      for (LegStructList_T::const_iterator itLeg = lLegList.begin();
           itLeg != lLegList.end(); ++itLeg) {
        const LegStruct_T& lLeg = *itLeg;

        // Create the Leg-branch of the FlightDate BOM
        COM::LegDate& lLegDate =
          createLegDate (*lFlightDate_ptr, iFlightDate, lLeg);

        // TODO: Check that the board date/time of the next leg is greated
        // than the off date/time of the current leg. Throw an exception
        // otherwise.

        // TODO: specify, in the schedule input file specifications, that the
        // legs should be given in their natural order.
        // Then, replace the assertion by a thrown exception.
        //
        // Check that the legs are given in their natural order. If the schedule
        // input does not respect that assumption, the following assertion will
        // fail.
        if (itLeg != lLegList.begin()) {
          const COM::AirportCode_T& currentBoardPoint =
            lLegDate.getBoardPoint();
          assert (currentBoardPoint == previousOffPoint);
        }
        
        // Set the local variable for the next iteration
        previousOffPoint = lLegDate.getOffPoint();
      }

      // Iterate on the Segment structures
      const SegmentStructList_T& lSegmentList = iFlightPeriod._segmentList;
      for (SegmentStructList_T::const_iterator itSegment = lSegmentList.begin();
           itSegment != lSegmentList.end(); ++itSegment) {
        const SegmentStruct_T& lSegment = *itSegment;

        createSegmentDate (*lFlightDate_ptr, lSegment);
      }
    }

    // //////////////////////////////////////////////////////////////////////
    COM::LegDate& InventoryGenerator::
    createLegDate (COM::FlightDate& ioFlightDate,
                   const COM::DateTime_T& iReferenceDate,
                   const LegStruct_T& iLeg) {
      // Set the Leg-Date primary key
      const COM::FlightDateKey_T& lFlightDateKey = ioFlightDate.getPrimaryKey();
      const COM::AirportCode_T& lBoardPoint = iLeg._boardPoint;
      const COM::LegDateKey_T lLegDateKey (lFlightDateKey, lBoardPoint);

      // Create the Leg-Date object
      COM::LegDate& lLegDate =
        COM::FacLegDate::instance().create (lLegDateKey);

      // Link the Flight-Date and Leg-Date objects
      COM::FacFlightDate::initLinkWithLegDate (ioFlightDate, lLegDate);

      // Set the Leg-Date attributes
      iLeg.fill (iReferenceDate, lLegDate);
      
      // Iterate on the Cabins
      const LegCabinStructList_T& lCabinList = iLeg._cabinList;
      for (LegCabinStructList_T::const_iterator itCabin = lCabinList.begin();
           itCabin != lCabinList.end(); ++itCabin) {
        const LegCabinStruct_T& lCabin = *itCabin;

        // Create the Leg-cabin-branch of the FlightDate BOM
        createLegCabin (lLegDate, lCabin);
      }

      return lLegDate;
    }

    // //////////////////////////////////////////////////////////////////////
    void InventoryGenerator::
    createLegCabin (COM::LegDate& ioLegDate,
                    const LegCabinStruct_T& iCabin) {
      // Set the Leg-Cabin primary key
      const COM::LegDateKey_T& lLegDateKey = ioLegDate.getPrimaryKey();
      const COM::CabinCode_T& lCabinCode = iCabin._cabinCode;
      const COM::LegCabinKey_T lLegCabinKey (lLegDateKey, lCabinCode);
      
      // Create the Leg-Cabin object
      COM::LegCabin& lLegCabin =
        COM::FacLegCabin::instance().create (lLegCabinKey);
      
      // Link the Flight-Date and Leg-Date objects
      COM::FacLegDate::initLinkWithLegCabin (ioLegDate, lLegCabin);

      // Set the Leg-Cabin attributes
      iCabin.fill (lLegCabin);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void InventoryGenerator::
    createSegmentDate (COM::FlightDate& ioFlightDate,
                       const SegmentStruct_T& iSegment) {
      // Set the Segment-Date primary key
      const COM::FlightDateKey_T& lFlightDateKey = ioFlightDate.getPrimaryKey();
      const COM::AirportCode_T& lBoardPoint = iSegment._boardPoint;
      const COM::AirportCode_T& lOffPoint = iSegment._offPoint;
      const COM::AirportPairKey_T lAirportPAirKey (lBoardPoint, lOffPoint);
      const COM::SegmentDateKey_T lSegmentDateKey (lFlightDateKey,
                                                   lAirportPAirKey);

      // Create the Segment-Date object
      COM::SegmentDate& lSegmentDate =
        COM::FacSegmentDate::instance().create (lSegmentDateKey);

      // Link the Flight-Date and Segment-Date objects
      COM::FacFlightDate::initLinkWithSegmentDate (ioFlightDate, lSegmentDate);

      // Set the Segment-Date attributes
      iSegment.fill (lSegmentDate);
      
      // Iterate on the Cabins
      const SegmentCabinStructList_T& lCabinList = iSegment._cabinList;
      for (SegmentCabinStructList_T::const_iterator itCabin =
             lCabinList.begin(); itCabin != lCabinList.end(); ++itCabin) {
        const SegmentCabinStruct_T& lCabin = *itCabin;

        // Create the Segment-cabin-branch of the FlightDate BOM
        createSegmentCabin (lSegmentDate, lCabin);
      }
    }
    
    // //////////////////////////////////////////////////////////////////////
    void InventoryGenerator::
    createSegmentCabin (COM::SegmentDate& ioSegmentDate,
                        const SegmentCabinStruct_T& iCabin) {
      // Set the Segment-Cabin primary key
      const COM::SegmentDateKey_T& lSegmentDateKey =
        ioSegmentDate.getPrimaryKey();
      const COM::CabinCode_T& lCabinCode = iCabin._cabinCode;
      const COM::SegmentCabinKey_T lSegmentCabinKey (lSegmentDateKey,
                                                     lCabinCode);
      
      // Create the Segment-Cabin object
      COM::SegmentCabin& lSegmentCabin =
        COM::FacSegmentCabin::instance().create (lSegmentCabinKey);
      
      // Link the Flight-Date and Segment-Date objects
      COM::FacSegmentDate::initLinkWithSegmentCabin (ioSegmentDate,
                                                     lSegmentCabin);

      // Set the Segment-Cabin attributes
      iCabin.fill (lSegmentCabin);

      // Iterate on the Classes
      const COM::ClassList_String_T& lClassList = iCabin._classes;
      for (COM::ClassList_String_T::const_iterator itClass =
             lClassList.begin(); itClass != lClassList.end(); ++itClass) {
        // Transform the single-character class code into a STL string
        std::ostringstream ostr;
        ostr << *itClass;
        const COM::ClassCode_T lClassCode (ostr.str());

        // Create the Segment-class-branch of the FlightDate BOM
        createClass (lSegmentCabin, lClassCode);
      }
    }
    
    // //////////////////////////////////////////////////////////////////////
    void InventoryGenerator::
    createClass (COM::SegmentCabin& ioSegmentCabin,
                 const COM::ClassCode_T& iClassCode) {
      // Set the Class primary key
      const COM::SegmentCabinKey_T& lSegmentCabinKey =
        ioSegmentCabin.getPrimaryKey();
      const COM::ClassKey_T lClassKey (lSegmentCabinKey, iClassCode);
      
      // Create the Class structure
      COM::ClassStruct_T lClass (lClassKey);
      
      // Link the Flight-Date and Segment-Date objects
      COM::FacSegmentCabin::initLinkWithClass (ioSegmentCabin, lClass);
    }
    
  }
}
