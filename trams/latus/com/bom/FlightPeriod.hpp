#ifndef __LATUS_COM_BOM_FLIGHTPERIOD_HPP
#define __LATUS_COM_BOM_FLIGHTPERIOD_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/LegPeriodList.hpp>
#include <latus/com/bom/SegmentPeriodList.hpp>

namespace LATUS {

  namespace COM {

    /** Class wrapping the Flight-Period specific attributes and methods. */
    class FlightPeriod : public BomAbstract {
    public:
      // /////////// Getters //////////////
      /** Get the primary key. */
      const FlightPeriodKey_T& getPrimaryKey() const {
        return getFlightPeriodKey();
      }

      /** Get the flight-period key. */
      const FlightPeriodKey_T& getFlightPeriodKey() const {
        return _key;
      }

      // ///////// Setters //////////


      // ///////// Display Methods //////////
      /** Get a string describing the key. */
      const std::string describeKey() const;

      /** Display the full BookingDay context. */
      void display() const;

      
    private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      FlightPeriod (const FlightPeriodKey_T&); 

      /** Destructor. */
      virtual ~FlightPeriod();

      /** Get the list of (children) LegPeriod objects. */
      const LegPeriodList_T& getLegPeriodList () const {
        return _legPeriodList;
      }

      /** Retrieve, if existing, the LegPeriod corresponding to the
          given board point.
          <br>If not existing, return the NULL pointer. */
      LegPeriod* getLegPeriod (const std::string& iLegPeriodKey) const;
      
      /** Get the list of (children) SegmentPeriod objects. */
      const SegmentPeriodList_T& getSegmentPeriodList () const {
        return _segmentPeriodList;
      }

      /** Retrieve, if existing, the SegmentPeriod corresponding to the
          given (board point, off point) pair.
          <br>If not existing, return the NULL pointer. */
      SegmentPeriod* getSegmentPeriod(const std::string& iSegmentPeriodKey)const;
      

    private:
      // Primary Key
      /** Flight-Period Key is composed of the airline code, flight number and
          departure period of the first segment. */
      FlightPeriodKey_T _key;
      
      /** Children: list of LegPeriod objects. */
      LegPeriodList_T _legPeriodList;

      /** Children: list of SegmentPeriod objects. */
      SegmentPeriodList_T _segmentPeriodList;
    };

  }
}
#endif // __LATUS_COM_BOM_FLIGHTPERIOD_HPP
