#ifndef __LATUS_COM_BOM_LEGDATE_HPP
#define __LATUS_COM_BOM_LEGDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/LegDateKey.hpp>
#include <latus/com/bom/LegCabinList.hpp>
#include <latus/com/bom/SegmentDateList.hpp>

namespace LATUS {

  namespace COM {

    // Forward declarations
    class FlightDate;
    
    /** Class wrapping the Leg-Date specific attributes and methods. */
    class LegDate : public BomAbstract {
      friend class FacLegDate;
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
      const LegDateKey_T& getPrimaryKey() const {
        return getLegDateKey();
      }

      /** Get the flight-date key. */
      const LegDateKey_T& getLegDateKey() const {
        return _key;
      }

      /** Get the board point (part of the primary key). */
      const AirportCode_T& getBoardPoint () const {
        return _key.boardPoint;
      }

      /** Get the off point. */
      const AirportCode_T& getOffPoint () const {
        return _offPoint;
      }

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

      /** Retrieve, if existing, the LegCabin corresponding to the
          given cabin code (LegCabin key).
          <br>If not existing, return the NULL pointer. */
      LegCabin* getLegCabin (const CabinCode_T& iCabinCode) const;


      // ///////// Setters //////////
      /** Set the FlightDate (parent class). */
      void setFlightDate (FlightDate* ioFlightDatePtr) {
        _flightDate = ioFlightDatePtr;
      }

      /** Set the off point. */
      void setOffPoint (const AirportCode_T& iOffPoint) {
        _offPoint = iOffPoint;
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
      
       // ///////// Counting methods  //////////
       /** Update the counters of booked seats. */
       void updateBookingsAndSeatCounters() const;

       /** Update the values of commited spaces. */
       void updateCommitedSpaces() const;

      /** Update the availability pools for Legs. */
      void updateAvailabilityPools() const;

      /** Update the availabilities for Legs. */
      void updateAllAvailabilities() const;
      
      
    private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      LegDate (const LegDateKey_T&); 

      /** Destructor. */
      virtual ~LegDate();

    private:
      /** Get the list of (children) LegCabin objects. */
      const LegCabinList_T& getLegCabinList () const {
        return _legCabinList;
      }

      /** Get the ordered list of (children) LegCabin objects. */
      const LegCabinOrderedList_T& getLegCabinOrderedList () const {
        return _legCabinOrderedList;
      }

      /** Retrieve, if existing, the LegCabin corresponding to the
          given LegCabin key (LegDateKey + cabin code).
          <br>If not existing, return the NULL pointer.
          <br>Note that the string must be formed thanks to the
          LegCabinKey::describeShort() method, as that latter is used when
          inserting the LegCabin within the LegDate dedicated list. */
      LegCabin* getLegCabinInternal (const std::string& iLegCabinKey) const;
      
      /** Get the list of (children) SegmentDate objects. */
      const SegmentDateList_T& getSegmentDateList () const {
        return _segmentDateList;
      }

      /** Retrieve, if existing, the SegmentDate corresponding to the
          given board point.
          <br>If not existing, return the NULL pointer. */
      SegmentDate* getSegmentDate (const std::string& iSegmentDateKey) const;
      
      
    private:
      // Parent
      /** Parent class: FlightDate. */
      FlightDate* _flightDate;
      
      // Primary Key
      /** Leg-Date Key is composed of the airline code, flight number, 
          departure date, board point and off point. */
      LegDateKey_T _key;

      /** Children: lists of LegCabin objects. */
      LegCabinList_T _legCabinList;
      LegCabinOrderedList_T _legCabinOrderedList;

      /** List of crossing SegmentDate objects. */
      SegmentDateList_T _segmentDateList;

      // Attributes
      /** Off Point. */
      AirportCode_T _offPoint;

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
#endif // __LATUS_COM_BOM_LEGDATE_HPP
