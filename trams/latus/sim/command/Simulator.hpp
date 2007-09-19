#ifndef __LATUS_SIM_CMD_SIMULATOR_HPP
#define __LATUS_SIM_CMD_SIMULATOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <map>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/Event.hpp>
#include <latus/com/command/CmdAbstract.hpp>
// LATUS General
#include <latus/LatusTypes.hpp>

namespace LATUS {

  // Forward declarations
  namespace COM {
    class BookingDay;
    class CityPair;
  }

  namespace SIM {

    /** Queue of reservations/events. */
    typedef std::map<COM::Duration_T, COM::CityPair*> EventList_T;

    /** Class wrapping the simulation methods. */
    class Simulator : public COM::CmdAbstract {
      // Only LATUS_SIM can instantiate Simulator
      friend class LATUS_SIM;
    public:
      // /////////// GETTERS //////////
      /** Get the start date of the simulation. */
      const COM::DateTime_T& getStartDate () const {
        return _startDate;
      }

      /** Get the end date of the simulation. */
      const COM::DateTime_T& getEndDate () const {
        return _endDate;
      }

      /** Get a reference on the (child) BookingDay object. */
      COM::BookingDay* getBookingDay() const {
        return _bookingDay;
      }

      /** Get a reference on the (child) BookingDay object. */
      COM::BookingDay& getBookingDayRef() const {
        assert (_bookingDay != NULL);
        return *_bookingDay;
      }

      // /////////// SETTERS //////////
      /** Set the start date of the simulation. */
      void setStartDate (const COM::DateTime_T& iStartDate) {
        _startDate = iStartDate;
      }

      /** Set the end date of the simulation. */
      void setEndDate (const COM::DateTime_T& iEndDate) {
        _endDate = iEndDate;
      }


      // ////////// Main Methods ///////////      
      /**
         Main call-back.
      */
      void simulate ();

      /**
         Main sample call-back.
      */
      static void sampleSimulate ();

      
      // ///////// DISPLAY METHODS /////////
      /** Display the BOM objects. */
      void display () const;
      

    private:
      /** Constructors. */
      Simulator (const COM::DateTime_T& iStartDate,
                 const COM::DateTime_T& iEndDate,
                 const std::string& iInputFileName);
      
      /** Destructor. */
      virtual ~Simulator();

    private:
      /** Build the BOM thanks to the input file.
          <br>The BOM is composed of BookingDay, CityPair, CityPairDate
          and ClassPath objects. */
      bool init ();

      /** Get the current booking date of the simulation.
          <br>The current date of the simulation is the one held by the
          BookingDay object (acting as a wrapper for that). */
      const COM::DateTime_T& getCurrentDate () const;
      
      /** Set the current booking date of the simulation.
          <br>The current date of the simulation is the one held by the
          BookingDay object (acting as a wrapper for that). */
      void setCurrentDate (const COM::DateTime_T&) const;
      
      /** Add one day to the current date of the simulation.
          <br>The current date of the simulation is the one held by the
          BookingDay object (acting as a wrapper for that). */
      void incrementCurrentDate () const;

      /** Play a reservation / event.
          <br>The reservation / event object contains both the time of the
          event and the reservation details (city pair description,
          departure date, class-path). */
      void playEvent (const COM::Event_T& iEvent) const;
      
      /** Generate and play the reservations / events for the current
          booking date.
		  <br>After calling BookingDay::resetForCurrentDate(), that method
          enters the main loop where the following steps are processed,
          until the current (booking) time gets above midnight:
		  <br><ol>
			<li>Get the first (closest in time) reservation / event,
		      containing (by construction) the combination of
			  the city pair, departure date and class-path
			  information.</li>
			<li>Set the current (booking) time to the (booking) time of
			  the reservation / event.</li>
			<li>Remove that event from the dedicated queue / list.</li>
			<li>Play that event (give it back to the Simulator).</li>
			<li>Draw / generate, for that CityPair object, a new event
			  (simply by calling the BookingDay::drawCityPairNextEvent()
              method).</li>
			<li>Insert that newly generated event in the dedicated 
			  queue / list.</li>
		  </ol> */
      void generateAndPlayForCurrentDay ();
      
    private:
      // Filename of the input file (for test purposes)
      std::string _inputFileName;

      // BOM (the BookingDay class is the entry point to the BOM)
      COM::BookingDay* _bookingDay;

      // Simulation length (time length) / date range for the simulation
      COM::DateTime_T _startDate;
      COM::DateTime_T _endDate;
    };
  }
}
#endif // __LATUS_SIM_CMD_SIMULATOR_HPP