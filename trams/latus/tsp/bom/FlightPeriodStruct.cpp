// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream>
// LATUS General
#include <latus/LatusTypes.hpp>
// LATUS Common
#include <latus/com/basic/BasConst_Period_BOM.hpp>
#include <latus/com/service/Logger.hpp>
// LATUS TSP
#include <latus/tsp/bom/FlightPeriodStruct.hpp>

namespace LATUS {

  namespace TSP {

    // //////////////////////////////////////////////////////////////////////
    FlightPeriodStruct_T::FlightPeriodStruct_T ()
      : _dateRange (COM::BOOST_DEFAULT_DATE_PERIOD),
        _dow (COM::DEFAULT_DOW_STRING),
        _legAlreadyDefined (false), _itSeconds (0) {
    }

    // //////////////////////////////////////////////////////////////////////
    COM::DateTime_T FlightPeriodStruct_T::getDate() const {
      return COM::DateTime_T (_itYear, _itMonth, _itDay);
    }

    // //////////////////////////////////////////////////////////////////////
    COM::Duration_T FlightPeriodStruct_T::getTime() const {
      return boost::posix_time::hours (_itHours)
        + boost::posix_time::minutes (_itMinutes)
        + boost::posix_time::seconds (_itSeconds);
    }
  
    // //////////////////////////////////////////////////////////////////////
    const std::string FlightPeriodStruct_T::describe() const {
      std::ostringstream ostr;
      ostr << _airlineCode << _flightNumber << ", " << _dateRange
           << " - " << _dow << std::endl;
      
      for (LegStructList_T::const_iterator itLeg = _legList.begin();
           itLeg != _legList.end(); ++itLeg) {
        const LegStruct_T& lLeg = *itLeg;
        ostr << lLeg.describe();
      }

      for (SegmentStructList_T::const_iterator itSegment = _segmentList.begin();
           itSegment != _segmentList.end(); ++itSegment) {
        const SegmentStruct_T& lSegment = *itSegment;
        ostr << lSegment.describe();
      }

      //ostr << "[Debug] - Staging Leg: ";
      //ostr << _itLeg.describe();
      //ostr << "[Debug] - Staging Cabin: ";
      //ostr << _itCabin.describe();

      return ostr.str();
    }

    // //////////////////////////////////////////////////////////////////////
    void FlightPeriodStruct_T::addAirport (const COM::AirportCode_T& iAirport) {
      AirportList_T::const_iterator itAirport = _airportList.find (iAirport);
      if (itAirport == _airportList.end()) {
        // Add the airport code to the airport set
        const bool insertSuccessful = _airportList.insert (iAirport).second;

		if (insertSuccessful == false) {
			// TODO: throw an exception
		}
          
        // Add the airport code to the airport vector
        _airportOrderedList.push_back (iAirport);
      }
    }

    // //////////////////////////////////////////////////////////////////////
    void FlightPeriodStruct_T::buildSegments () {
      // The list of airports encompasses all the airports on which
      // the flight takes off or lands. Moreover, that list is
      // time-ordered: the first airport is the initial departure of
      // the flight, and the last airport is the eventual point of
      // rest of the flight.
      // Be l the size of the ordered list of airports.
      // We want to generate all the segment combinations from the legs
      // and, hence, from all the possible (time-ordered) airport pairs.
      // Thus, we both iterator on i=0...l-1 and j=i+1...l
      assert (_airportOrderedList.size() >= 2);

      _segmentList.clear();
      for (AirportOrderedList_T::const_iterator itAirport_i =
             _airportOrderedList.begin();
           itAirport_i != _airportOrderedList.end()-1; ++itAirport_i) {
        for (AirportOrderedList_T::const_iterator itAirport_j = itAirport_i + 1;
             itAirport_j != _airportOrderedList.end(); ++itAirport_j) {
          SegmentStruct_T lSegmentStruct;
          lSegmentStruct._boardPoint = *itAirport_i;
          lSegmentStruct._offPoint = *itAirport_j;
          
          _segmentList.push_back (lSegmentStruct);
        }
      }

      // Clear the lists of airports, so that it is ready for the next flight
      _airportList.clear();
      _airportOrderedList.clear();
    }
      
    // //////////////////////////////////////////////////////////////////////
    void FlightPeriodStruct_T::
    addSegmentCabin (const SegmentStruct_T& iSegment,
                     const SegmentCabinStruct_T& iCabin) {
      // Retrieve the Segment structure corresponding to the (board, off) point
      // pair.
      SegmentStructList_T::iterator itSegment = _segmentList.begin();
      for ( ; itSegment != _segmentList.end(); ++itSegment) {
        const SegmentStruct_T& lSegment = *itSegment;

        const COM::AirportCode_T& lBoardPoint = iSegment._boardPoint;
        const COM::AirportCode_T& lOffPoint = iSegment._offPoint;
        if (lSegment._boardPoint == lBoardPoint
            && lSegment._offPoint == lOffPoint) {
          break;
        }
      }

      // If the segment key (airport pair) given in the schedule input file
      // does not correspond to the leg (board, off) points, throw an exception
      // so that the user knows the schedule input file is corrupted.
      if (itSegment == _segmentList.end()) {
        LATUS_LOG_ERROR ("Within the schedule input file, there is a flight for which the airports of segments and those of the legs do not correspond.");
        throw SegmentDateNotFoundException();
      }

      // Add the Cabin structure to the Segment Cabin structure.
      assert (itSegment != _segmentList.end());
      SegmentStruct_T& lSegment = *itSegment;
      lSegment._cabinList.push_back (iCabin);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void FlightPeriodStruct_T::
    addSegmentCabin (const SegmentCabinStruct_T& iCabin) {
      // Iterate on all the Segment structures (as they get the same cabin
      // definitions)
      
      for (SegmentStructList_T::iterator itSegment = _segmentList.begin();
           itSegment != _segmentList.end(); ++itSegment) {
        SegmentStruct_T& lSegment = *itSegment;

        lSegment._cabinList.push_back (iCabin);
      }
    }
    
  }
}
