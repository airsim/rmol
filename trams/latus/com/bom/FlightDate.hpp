#ifndef __LATUS_COM_BOM_FLIGHTDATE_HPP
#define __LATUS_COM_BOM_FLIGHTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/FlightDateKey.hpp>
#include <latus/com/bom/LegDateList.hpp>
#include <latus/com/bom/SegmentDateList.hpp>

namespace LATUS {

  namespace COM {

    /** Class wrapping the Flight-Date specific attributes and methods. */
    class FlightDate : public BomAbstract {
      friend class FacFlightDate;
    public:
      // /////////// Getters //////////////
      /** Get the primary key. */
      const FlightDateKey_T& getPrimaryKey() const {
        return getFlightDateKey();
      }

      /** Get the flight-date key. */
      const FlightDateKey_T& getFlightDateKey() const {
        return _key;
      }

      // ///////// Setters //////////


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
      FlightDate (const FlightDateKey_T&); 

      /** Destructor. */
      virtual ~FlightDate();

    private:
      /** Get the list of (children) LegDate objects. */
      const LegDateList_T& getLegDateList () const {
        return _legDateList;
      }

      /** Retrieve, if existing, the LegDate corresponding to the
          given board point.
          <br>If not existing, return the NULL pointer. */
      LegDate* getLegDate (const std::string& iLegDateKey) const;
      
      /** Get the list of (children) SegmentDate objects. */
      const SegmentDateList_T& getSegmentDateList () const {
        return _segmentDateList;
      }

      /** Retrieve, if existing, the SegmentDate corresponding to the
          given (board point, off point) pair.
          <br>If not existing, return the NULL pointer. */
      SegmentDate* getSegmentDate (const std::string& iSegmentDateKey) const;
      

    private:
      // Primary Key
      /** Flight-Date Key is composed of the airline code, flight number and
          departure date of the first segment. */
      FlightDateKey_T _key;
      
      /** Children: list of LegDate objects. */
      LegDateList_T _legDateList;

      /** Children: list of SegmentDate objects. */
      SegmentDateList_T _segmentDateList;
    };

  }
}
#endif // __LATUS_COM_BOM_FLIGHTDATE_HPP
