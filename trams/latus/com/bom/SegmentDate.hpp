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

      /** Get the off date. */
      const DateTime_T& getOffDate () const {
        return _offDate;
      }

      /** Get the elapsed time. */
      const Duration_T& getElapsedTime() const {
        return _elapsedTime;
      }


      // ///////// Setters //////////
      /** Set the FlightDate (parent class). */
      void setFlightDate (FlightDate* ioFlightDatePtr) {
        _flightDate = ioFlightDatePtr;
      }

      /** Set the off date. */
      void setOffDate (const DateTime_T& iOffDate) {
        _offDate = iOffDate;
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
      
      /** Get the list of (children) LegDate objects. */
      const LegDateList_T& getLegDateList () const {
        return _legDateList;
      }

      /** Retrieve, if existing, the LegDate corresponding to the
          given board point.
          <br>If not existing, return the NULL pointer. */
      LegDate* getLegDate (const std::string& iLegDateKey) const;
      
      
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

      /** List of routing LegDate objects. */
      LegDateList_T _legDateList;

      // Attributes
      /** Off Date. */
      DateTime_T _offDate;

      /** Elapsed Time. */
      Duration_T _elapsedTime;
    };

  }
}
#endif // __LATUS_COM_BOM_SEGMENTDATE_HPP
