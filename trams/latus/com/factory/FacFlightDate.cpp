// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/basic/BasConst_LATUS_Service.hpp>
#include <latus/com/bom/FlightDateKey.hpp>
#include <latus/com/bom/FlightDate.hpp>
#include <latus/com/bom/LegDate.hpp>
#include <latus/com/bom/SegmentDate.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacFlightDate.hpp>
#include <latus/com/factory/FacSegmentDate.hpp>
#include <latus/com/service/Logger.hpp>


namespace LATUS {

  namespace COM {

    FacFlightDate* FacFlightDate::_instance = NULL;

    // //////////////////////////////////////////////////////////////////////
    FacFlightDate::~FacFlightDate () {
      _instance = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    FacFlightDate& FacFlightDate::instance () {

      if (_instance == NULL) {
        _instance = new FacFlightDate();
        assert (_instance != NULL);
      
        FacSupervisor::instance().registerBomFactory (_instance);
      }
      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    FlightDate& FacFlightDate::create (const FlightDateKey_T& iKey) {
      FlightDate* aFlightDate_ptr = NULL;

      aFlightDate_ptr = new FlightDate (iKey);
      assert (aFlightDate_ptr != NULL);

      // The new object is added to the Bom pool
      _pool.push_back (aFlightDate_ptr);

      return *aFlightDate_ptr;
    }

    // //////////////////////////////////////////////////////////////////////
    void FacFlightDate::initLinkWithLegDate (FlightDate& ioFlightDate,
                                             LegDate& ioLegDate) {
      // Link the FlightDate to the LegDate, and vice versa
      ioLegDate.setFlightDate (&ioFlightDate);
      
      // Add the LegDate to the FlightDate internal map (of LegDate objects)
      const bool insertSucceeded = ioFlightDate._legDateList.
        insert (LegDateList_T::value_type (ioLegDate.describeShortKey(),
                                           &ioLegDate)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion failed for " << ioFlightDate.describeKey()
                         << " and " << ioLegDate.describeShortKey());
        assert (insertSucceeded == true);
      }

      // Add the LegDate to the FlightDate internal vector (of LegDate objects)
      ioFlightDate._legDateOrderedList.push_back (&ioLegDate);
    }

    // //////////////////////////////////////////////////////////////////////
    void FacFlightDate::initLinkWithSegmentDate (FlightDate& ioFlightDate,
                                                 SegmentDate& ioSegmentDate) {
      // Link the FlightDate to the SegmentDate, and vice versa
      ioSegmentDate.setFlightDate (&ioFlightDate);
      
      // Add the SegmentDate to the FlightDate internal map (of SegmentDate
      // objects)
      const bool insertSucceeded = ioFlightDate._segmentDateList.
        insert (SegmentDateList_T::value_type(ioSegmentDate.describeShortKey(),
                                              &ioSegmentDate)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion failed for " << ioFlightDate.describeKey()
                         << " and " << ioSegmentDate.describeShortKey());
        assert (insertSucceeded == true);
      }

      // Add the SegmentDate to the FlightDate internal vector (of SegmentDate
      // objects)
      ioFlightDate._segmentDateOrderedList.push_back (&ioSegmentDate);
    }

    // //////////////////////////////////////////////////////////////////////
    void FacFlightDate::createRouting (FlightDate& ioFlightDate) {
      // Note that the leg routing order for a given segment is strict,
      // contrary to the segment crossing order for a given leg. Hence,
      // we first iterate on the segments, and for each of them,
      // we build the ordered list of routing legs. At the same time, the
      // legs store their corresponding crossing segments (thanks to a
      // call to FacLegDate::initLinkWithLegDate() by
      // FacSegmentDate::initLinkWithSegmentDate()). So, at the end of the
      // process, the segments get their routing legs linked, and the legs
      // get their crossing segments linked.

      const SegmentDateList_T& lSegmentList = ioFlightDate._segmentDateList;
      for (SegmentDateList_T::const_iterator itSegment = lSegmentList.begin();
           itSegment != lSegmentList.end(); ++itSegment) {
        SegmentDate* lSegmentDate_ptr = itSegment->second;
        assert (lSegmentDate_ptr != NULL);
        
        const AirportCode_T& lBoardPoint = lSegmentDate_ptr->getBoardPoint();
        AirportCode_T currentBoardPoint = lBoardPoint;
        const AirportCode_T& lOffPoint = lSegmentDate_ptr->getOffPoint();
        AirportCode_T currentOffPoint = lBoardPoint;
        
        // Add a sanity check so as to ensure that the loop stops. If
        // there are more than MAXIMUM_NUMBER_OF_LEGS legs, there is
        // an issue somewhere in the code (not in the parser, as the
        // segments are derived from the legs thanks to the
        // FlightPeriodStruct::buildSegments() method).
        unsigned short i = 1;
        while (currentOffPoint != lOffPoint
               && i <= MAXIMUM_NUMBER_OF_LEGS_IN_FLIGHT) {
          // Retrieve the (unique) LegDate getting that Board Point
          LegDate* lLegDate_ptr = ioFlightDate.getLegDate (currentBoardPoint);
          assert (lLegDate_ptr != NULL);

          // Link the SegmentDate and LegDate together
          FacSegmentDate::initLinkWithLegDate (*lSegmentDate_ptr,
                                               *lLegDate_ptr);
          
          // Prepare the next iteration
          currentBoardPoint = lLegDate_ptr->getOffPoint();
          currentOffPoint = lLegDate_ptr->getOffPoint();
        }
        assert (i <= MAXIMUM_NUMBER_OF_LEGS_IN_FLIGHT);

        // Create the routing for the leg- and segment-cabins.
        // At the same time, set the SegmentDate attributes derived from
        // its routing legs (e.g., board and off dates).
        FacSegmentDate::createRouting (*lSegmentDate_ptr);
      }
    }
      
  }
}
