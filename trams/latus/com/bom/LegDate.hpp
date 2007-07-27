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
      LegDate (const LegDateKey_T&); 

      /** Destructor. */
      virtual ~LegDate();

    private:
      /** Get the list of (children) LegCabin objects. */
      const LegCabinList_T& getLegCabinList () const {
        return _legCabinList;
      }

      /** Retrieve, if existing, the LegCabin corresponding to the
          given board point.
          <br>If not existing, return the NULL pointer. */
      LegCabin* getLegCabin (const std::string& iLegCabinKey) const;
      
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

      /** Children: list of LegCabin objects. */
      LegCabinList_T _legCabinList;

      /** List of crossing SegmentDate objects. */
      SegmentDateList_T _segmentDateList;

      // Attributes
      /** Off Date. */
      DateTime_T _offDate;

      /** Elapsed Time. */
      Duration_T _elapsedTime;
    };

  }
}
#endif // __LATUS_COM_BOM_LEGDATE_HPP
