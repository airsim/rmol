#ifndef __LATUS_TSP_BOM_FLIGHTPERIODSTRUCT_HPP
#define __LATUS_TSP_BOM_FLIGHTPERIODSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/StructAbstract.hpp>
// LATUS Travel Service Provider (TSP)
#include <latus/tsp/bom/LegCabinStruct.hpp>
#include <latus/tsp/bom/LegStruct.hpp>
#include <latus/tsp/bom/SegmentStruct.hpp>
#include <latus/tsp/bom/SegmentCabinStruct.hpp>
#include <latus/tsp/bom/DOWStruct.hpp>
#include <latus/tsp/bom/AirportList.hpp>

namespace LATUS {

  namespace TSP {

    /** Utility Structure for the parsing of Flight-Period structures. */
    struct FlightPeriodStruct_T : public COM::StructAbstract {
      // Attributes
      COM::AirlineCode_T _airlineCode;
      COM::FlightNumber_T _flightNumber;
      COM::DatePeriod_T _dateRange;
      DOWStruct_T _dow;
      LegStructList_T _legList;
      SegmentStructList_T _segmentList;

      /** Constructor. */
      FlightPeriodStruct_T ();

      /** Set the date from the staging details. */
      COM::DateTime_T getDate() const;

      /** Set the time from the staging details. */
      COM::Duration_T getTime() const;
  
      /** Give a description of the structure (for display purposes). */
      const std::string describe() const;

      /** Add the given airport to the internal lists (if not already
          existing). */
      void addAirport (const COM::AirportCode_T&);

      /** Build the list of SegmentStruct objects. */
      void buildSegments ();
      
      /** Add, to the Segment structure whose key corresponds to the
          given (board point, off point) pair, the specific segment cabin
          details (mainly, the list of the class codes).
          <br>Note that the Segment structure is retrieved from the internal
          list, already filled by a previous step (the buildSegments()
          method). */
      void addSegmentCabin (const SegmentStruct_T&,
                            const SegmentCabinStruct_T&);
      
      /** Add, to all the Segment structures, the general segment cabin details
          (mainly, the list of the class codes).
          <br>Note that the Segment structures are stored within the internal
          list, already filled by a previous step (the buildSegments()
          method). */
      void addSegmentCabin (const SegmentCabinStruct_T&);
      
      /** Staging Leg (resp. Cabin) structure, gathering the result of
          the iteration on one leg (resp. cabin). */
      bool _legAlreadyDefined;
      LegStruct_T _itLeg;
      LegCabinStruct_T _itLegCabin;

      /** Staging Date. */
      COM::DateTime_T _dateRangeStart;
      COM::DateTime_T _dateRangeEnd;
      unsigned int _itYear;
      unsigned int _itMonth;
      unsigned int _itDay;
      int _dateOffSet;
      
      /** Staging Time. */
      unsigned int _itHours;
      unsigned int _itMinutes;
      unsigned int _itSeconds;

      /** Staging Airport List (helper to derive the list of Segment
          structures). */
      AirportList_T _airportList;
      AirportOrderedList_T _airportOrderedList;

      /** Staging Segment-related attributes. */
      bool _areSegmentDefinitionsSpecific;
      SegmentStruct_T _itSegment;
      SegmentCabinStruct_T _itSegmentCabin;
    };

  }
}
#endif // __LATUS_TSP_BOM_FLIGHTPERIODSTRUCT_HPP
