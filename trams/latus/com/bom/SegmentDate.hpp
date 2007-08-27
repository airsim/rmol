#ifndef __LATUS_COM_BOM_SEGMENTDATE_HPP
#define __LATUS_COM_BOM_SEGMENTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/SegmentDateKey.hpp>
#include <latus/com/bom/SegmentCabinList.hpp>
#include <latus/com/bom/LegDateList.hpp>

namespace LATUS {

  namespace COM {

    // Forward declarations
    class FlightDate;
    
    /** Class wrapping the Segment-Date specific attributes and methods. */
    class SegmentDate : public BomAbstract {
      friend class FacSegmentDate;
    public:
      // /////////// Getters //////////////
      /** Get the parent class. */
      FlightDate* getParent() const {
        return getFlightDate();
      }

      /** Get the FlightDate (parent class). */
      FlightDate* getFlightDate() const {
        return _flightDate;
      }

      /** Get the primary key. */
      const SegmentDateKey_T& getPrimaryKey() const {
        return getSegmentDateKey();
      }

      /** Get the flight-date key. */
      const SegmentDateKey_T& getSegmentDateKey() const {
        return _key;
      }

      /** Get the board point (part of the primary key). */
      const AirportCode_T& getBoardPoint () const {
        return _key.airportPairKey.boardPoint;
      }

      /** Get the off point (part of the primary key). */
      const AirportCode_T& getOffPoint () const {
        return _key.airportPairKey.offPoint;
      }

      /** Get the airline code (from the parent class). */
      const AirlineCode_T& getAirlineCode() const;
      
      /** Get the flight number (from the parent class). */
      const FlightNumber_T& getFlightNumber() const;
      
      /** Get the board date. */
      const DateTime_T& getBoardDate () const {
        return _boardDate;
      }

      /** Get the board time. */
      const Duration_T& getBoardTime () const {
        return _boardTime;
      }

      /** Get the off date. */
      const DateTime_T& getOffDate () const {
        return _offDate;
      }

      /** Get the off time. */
      const Duration_T& getOffTime () const {
        return _offTime;
      }

      /** Get the elapsed time. */
      const Duration_T& getElapsedTime() const {
        return _elapsedTime;
      }

      /** Get the date off set (off date - board date). */
      const DateOffSet_T getDateOffSet () const {
        return _offDate - _boardDate;
      }

      /** Get the time off set between board and off points.
          <br>It is defined as being:
          TimeOffSet = (OffTime - BoardTime) + (OffDate - BoardDate) * 24
                        - ElapsedTime. */
      const Duration_T getTimeOffSet() const;


      // ///////// Setters //////////
      /** Set the FlightDate (parent class). */
      void setFlightDate (FlightDate* ioFlightDatePtr) {
        _flightDate = ioFlightDatePtr;
      }

      /** Set the board date. */
      void setBoardDate (const DateTime_T& iBoardDate) {
        _boardDate = iBoardDate;
      }

      /** Set the board time. */
      void setBoardTime (const Duration_T& iBoardTime) {
        _boardTime = iBoardTime;
      }

      /** Set the off date. */
      void setOffDate (const DateTime_T& iOffDate) {
        _offDate = iOffDate;
      }

      /** Set the off time. */
      void setOffTime (const Duration_T& iOffTime) {
        _offTime = iOffTime;
      }

      /** Set the elapsed time. */
      void setElapsedTime (const Duration_T& iElapsedTime) {
        _elapsedTime = iElapsedTime;
      }


      // ///////// Display Methods //////////
      /** Get a string describing the key. */
      const std::string describeKey() const;

      /** Get a string describing the short key. */
      const std::string describeShortKey() const;

      /** Display the full BookingDay context. */
      void display() const;

      
    private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      SegmentDate (const SegmentDateKey_T&); 

      /** Destructor. */
      virtual ~SegmentDate();

    private:
      /** Get the list of (children) SegmentCabin objects. */
      const SegmentCabinList_T& getSegmentCabinList () const {
        return _segmentCabinList;
      }

      /** Retrieve, if existing, the SegmentCabin corresponding to the
          given board point.
          <br>If not existing, return the NULL pointer. */
      SegmentCabin* getSegmentCabin(const std::string& iSegmentCabinKey) const;
      
      /** Get the (ordered) list of (children) LegDate objects. */
      const LegDateOrderedList_T& getLegDateList () const {
        return _legDateList;
      }

      /** Fill the attributes derived from the routing legs (e.g., board
          and off dates). */
      void fillFromRouting();

      /** Calculate and set the elapsed time according to the leg routing.
          <br>Actually, the elapsed time of the segment is the sum of the
          elapsed times of the routing legs, plus the stop-over times.
          The stop-over time is the difference between the board time of a
          routing leg, and the off time of the previous leg. That is, it is
          the time spent at the corresponding airport.
          <br>Of course, in case of mono-leg segments, there is no stop-over,
          and the elapsed time of the segment is equal to the elapsed time
          of the single routing leg. */
      void updateElapsedTimeFromRouting();

      
    private:
      // Parent
      /** Parent class: FlightDate. */
      FlightDate* _flightDate;
      
      // Primary Key
      /** Segment-Date Key is composed of the airline code, flight number, 
          departure date, board point and off point. */
      SegmentDateKey_T _key;

      /** Children: list of SegmentCabin objects. */
      SegmentCabinList_T _segmentCabinList;
      SegmentCabinOrderedList_T _segmentCabinOrderedList;

      /** List of routing LegDate objects. */
      LegDateOrderedList_T _legDateList;

      // Attributes
      /** Board Date. */
      DateTime_T _boardDate;

      /** Board Time. */
      Duration_T _boardTime;

      /** Off Date. */
      DateTime_T _offDate;

      /** Off Time. */
      Duration_T _offTime;

      /** Elapsed Time. */
      Duration_T _elapsedTime;
    };

  }
}
#endif // __LATUS_COM_BOM_SEGMENTDATE_HPP
