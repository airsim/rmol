#ifndef __LATUS_COM_BOM_SEGMENTPERIOD_HPP
#define __LATUS_COM_BOM_SEGMENTPERIOD_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/bom/SegmentPeriodKey.hpp>
#include <latus/com/bom/BomAbstract.hpp>

namespace LATUS {

  namespace COM {

    /** Class wrapping the Segment-Period specific attributes and methods. */
    class SegmentPeriod : public BomAbstract {
    public:
      // /////////// Getters //////////////
      /** Get the primary key. */
      const SegmentPeriodKey_T& getPrimaryKey() const {
        return getSegmentPeriodKey();
      }

      /** Get the flight-period key. */
      const SegmentPeriodKey_T& getSegmentPeriodKey() const {
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
      SegmentPeriod (const SegmentPeriodKey_T&); 

      /** Destructor. */
      virtual ~SegmentPeriod();


    private:
      // Primary Key
      /** Segment-Period Key is composed of the airline code, flight number, 
          departure period, board point and off point. */
      SegmentPeriodKey_T _key;

      // Attributes
    };

  }
}
#endif // __LATUS_COM_BOM_SEGMENTPERIOD_HPP
