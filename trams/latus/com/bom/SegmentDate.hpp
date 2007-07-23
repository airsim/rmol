#ifndef __LATUS_COM_BOM_SEGMENTDATE_HPP
#define __LATUS_COM_BOM_SEGMENTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/SegmentDateKey.hpp>

namespace LATUS {

  namespace COM {

    /** Class wrapping the Segment-Date specific attributes and methods. */
    class SegmentDate : public BomAbstract {
    public:
      // /////////// Getters //////////////
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

      /** Display the full BookingDay context. */
      void display() const;

      
    private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      SegmentDate (const SegmentDateKey_T&); 

      /** Destructor. */
      virtual ~SegmentDate();


    private:
      // Primary Key
      /** Segment-Date Key is composed of the airline code, flight number, 
          departure date, board point and off point. */
      SegmentDateKey_T _key;

      // Attributes
      /** Off Date. */
      DateTime_T _offDate;

      /** Elapsed Time. */
      Duration_T _elapsedTime;
    };

  }
}
#endif // __LATUS_COM_BOM_SEGMENTDATE_HPP
