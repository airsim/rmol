#ifndef __LATUS_COM_BOM_BOOKINGDAY_HPP
#define __LATUS_COM_BOM_BOOKINGDAY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// GSL Random Number Generation (GSL Reference Manual, version 1.7, Chapter 17)
#include <gsl/gsl_rng.h>
// LATUS General
#include <latus/LatusTypes.hpp>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/Event.hpp>

namespace LATUS {
  
  namespace COM {

    // Forward declarations
    class WholeDemand;
    class WTP;
    class CityPair;

    /** Class storing the context for a Booking Day. */
    class BookingDay : public BomAbstract {
      friend class FacBookingDay;
    public:
      // /////////// Getters //////////////
      /** Get the WholeDemand object reference. */
      WholeDemand* getWholeDemand () const {
        return _wholeDemand;
      }

      /** Get the WholeDemand object reference. */
      WholeDemand& getWholeDemandRef () const;

      /** Get the primary key. */
      const DateTime_T& getPrimaryKey() const {
        return getBookingDate();
      }

      /** Get the current simulation/booking date. */
      const DateTime_T& getBookingDate() const {
        return _bookingDate;
      }

      /** Get the time of next reservation / event for that Booking Day. */
      const Duration_T& getBookingTime () const {
        return _bookingTime;
      }

      /** Get the daily rate. */
      const double getDailyRate() const;

      /** States whether the (current) booking time has reached the end of
          the day (midnight). */
      bool hasReachedEndOfDay () const;

      /** States whether the list of reservations / events is empty. */
      bool hasNoEvent () const;

      /** Get the first reservation / event of the queue / list.
          <br>Note: the caller should test whether the event list is empty
          before calling, thanks to hasNoEvent(). Otherwise, an assertion
          will fail when the event list is empty. */
      const Event_T getFirstEvent () const;

      /** Erase the reservation / event corresponding to the key
          from the queue / list. */
      void eraseEvent (const EventKey_T&);


      // ///////// Setters //////////
      /** Set the WholeDemand object reference. */
      void setWholeDemand (WholeDemand* ioWholeDemand) {
        _wholeDemand = ioWholeDemand;
      }

      /** Set the current simulation / booking date. */
      void setBookingDate (const DateTime_T& iBookingDate) {
        _bookingDate = iBookingDate;
      }

      /** Add one day to the current date of the simulation. */
      void incrementBookingDate ();

      /** Set the time of next reservation / event for that Booking Day. */
      void setBookingTime(const Duration_T& iBookingTime) {
        _bookingTime = iBookingTime;
      }


      // /////////// Main Business Methods ////////////
      /** Update the daily rates for all the CityPair objects of the
          WholeDemand object.
          <br>The daily rate depends on:
          <br><ol>
          <li>The current / booking date.</li>
          <li>The departure date of each CityPairDate object.</li>
          </ol>
          Indeed, the daily rate depends on the remaining
          Days-To-Departure (DTD), calculated as being the difference between
          the departure date and the date at which the booking is made.
          <br>Note that that method also builds the daily rate
          distributions (helper objects) stored within the CityPair and
          CityPairDate objects. */
      void updateDailyRate();
      
      /** Initialisation of the reservation / event list.
          <br>Draw / generate a reservation / event for each CityPair object.
          <br>Each CityPair must get one (and only one) reservation / event. */
      void drawEventsForAllCityPairs();

      /** At the start of the booking day, the following actions are
          undertaken:
          <br><ol>
          <li>Re-set the current / booking time to midnight.</li>
          <li>Reset the number of played reservations / events to zero.</li>
          <li>Clear the list of (CityPair-related) reservations / events.</li>
          <li>Re-calculate and set the daily rate for all the CityPair objects:
            the daily rate depends on both the current / booking date and
            the departure date. Indeed, it depends on the remaining
            Days-To-Departure (DTD) when the booking is made.</li>
          <li>For each CityPair, draw / generate an event, and add that latter
            to the reservation / event queue. The events are indexed (within
            the list) by their booking time, and contain a reference on the
            reservation details (city pair, departure date, class-path)
            to perform.</li>
          </ol> */
      void resetForCurrentDate ();

      /** Draw / generate a reservation / event for the given CityPair,
          and add it to the dedicated queue.
          <br>That encompasses the following steps:
          <br><ol>
            <li>Draw / generate the inter-arrival time of the next event.
            That inter-arrival time is then added to the current (booking)
            time (of the Booking Day) to give the (booking) time of the
            next event. For example, if the current booking time is 10:45:22
            and the inter-arrival time is 05:12:30, then the (booking) time
            of the next event is: 15:57:52.</li>
		    <li>Draw / generate a departure date, according to the uniform 
			daily rate distribution (helper object) attached to the given
			CityPair object.</li>
			<li>Draw / generate a class-path, according to the uniform
			daily rate distribution (helper object) attached to each of the
			CityPairDate objects of the given CityPair.</li>
			<li>Build a reservation / event object with those elements
			(booking time and the combination of departure date and 
			class-path).</li>
          </ol>. */
      void drawCityPairNextEvent (CityPair&);
      

      // ///////// Display Methods //////////
      /** Get a string describing the key. */
      const std::string describeKey() const;

      /** Display the full BookingDay context. */
      void display() const;

      /** Display the current BookingDay context. */
      void displayCurrent() const;

    private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      BookingDay (const DateTime_T& iBookingDate); 

      /** Destructor. */
      virtual ~BookingDay();

      /** Initialise the BookingDay context:
          <br>Mainly, the random generator is initialised. */
      void initRandomGenerator();

      /** Get the list of Event objects. */
      const EventList_T& getEventList () const {
        return _eventList;
      }

      /** Remove the reservation / event corresponding to the given key
          from the queue / list. */
      void removeEventFromList (const EventList_T::iterator&);

    private:
      // Attributes
      /** Children: WholeDemand object. */
      WholeDemand* _wholeDemand;
      
      /** Current Simulation / Booking Date. */
      DateTime_T _bookingDate;

      /** Time of the next reservation/event for the booking day. */
      Duration_T _bookingTime;

      /** Number of reservations / events made during the simulation day. */
      int _dailyEventNumber;

      /** List of reservations / events made during the simulation day. */
      EventList_T _eventList;
      
      /** (GSL) Random seed. */
      gsl_rng* _rngExponentialPtr;
      gsl_rng* _rngUniformIntPtr;
    };
  }
}
#endif // __LATUS_COM_BOM_BOOKINGDAY_HPP
