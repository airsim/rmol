#ifndef __LATUS_COM_BOM_BOOKINGDAY_HPP
#define __LATUS_COM_BOM_BOOKINGDAY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <map>
// Boost (Extended STL)
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
// GSL Random Number Generation (GSL Reference Manual, version 1.7, Chapter 17)
#include <gsl/gsl_rng.h>
// LATUS General
#include <latus/LatusTypes.hpp>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/CityPairList.hpp>
#include <latus/com/bom/Event.hpp>

namespace LATUS {
  
  namespace COM {

    // Forward declarations
    class BookingDay;
    class ClassPath;

    /** Class storing the context for a Booking Day. */
    class BookingDay : public BomAbstract {
      friend class FacBookingDay;
    private:
      // Private type definitions
      /** Type, for a given BookingDay, corresponding to the City Pair
          probability distribution.
          <br>Note that that probability distribution is normally not used:
          it is here for debugging purpose only. */
      typedef std::map<double, std::string> CityPairDistribution_T;
                       
      /** Queue of reservations / events.
          <br>Each event is defined by a reservation time and by the full
          reservation details, provided through the ClassPath object.
          Indeed, that latter encompasses the city pair, the travel departure
          date and the class-path information (as the CityPair C++ class is the
          parent of the CityPairDate C++ class, itself parent of the ClassPath
          C++ class).
          <br>For example, an event can take the shape of a reservation for the
          H-H class combination, made at (with a booking time of) 14:02:50
          for a NCE-MIA travel departing on 21-Apr-2007. */
      typedef std::multimap<boost::posix_time::time_duration,
                            ClassPath*> EventList_T;
    
    public:
      // /////////// Getters //////////////
      /** Get the primary key. */
      const boost::gregorian::date& getPrimaryKey() const {
        return getBookingDate();
      }

      /** Get the current simulation/booking date. */
      const boost::gregorian::date& getBookingDate() const {
        return _bookingDate;
      }

      /** Get the time of next reservation / event for that Booking Day. */
      const boost::posix_time::time_duration& getBookingTime () const {
        return _bookingTime;
      }

      /** Get the daily rate. */
      const double getDailyRate() const {
        return _dailyRate;
      }

      /** Retrieve, if existing, the CityPair corresponding to the
          given description.
          <br>If not existing, return the NULL pointer. */
      CityPair* getCityPair (const AirportCode_T& iOrigin,
                             const AirportCode_T& iDestination) const;
      
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
      /** Set the current simulation / booking date. */
      void setBookingDate (const boost::gregorian::date& iBookingDate) {
        _bookingDate = iBookingDate;
      }

      /** Add one day to the current date of the simulation. */
      void incrementBookingDate ();

      /** Set the time of next reservation / event for that Booking Day. */
      void setBookingTime(const boost::posix_time::time_duration& iBookingTime) {
        _bookingTime = iBookingTime;
      }

      /** Set the daily rate. */
      void setDailyRate (const double iDailyRate) {
        _dailyRate = iDailyRate;
      }


      // /////////// Main Business Methods ////////////
      /** Update the daily rates for all the CityPair objects.
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

      /** Generate and play the reservations / events for the
          current / booking date.
		  <br>After calling resetForCurrentDate(), that method enters
		  the main loop where the following steps are processed, until
		  the current (booking) time gets above midnight:
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
			  (simply by calling the drawCityPairNextEvent() method).</li>
			<li>Insert that newly generated event in the dedicated 
			  queue / list.</li>
		  </ol> */
      void generateAndPlay ();


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
      BookingDay (const boost::gregorian::date& iBookingDate); 

      /** Destructor. */
      virtual ~BookingDay();

      /** Initialise the BookingDay context:
          <br>Mainly, the random generator is initialised. */
      void initRandomGenerator();

      /** Get the list of (children) CityPair objects. */
      const CityPairList_T& getCityPairList () const {
        return _cityPairList;
      }

      /** Retrieve, if existing, the CityPair corresponding to the
          given CityPair key (i.e., (board point, off point) pair).
          <br>If not existing, return the NULL pointer.
          <br>Note that the string must be formed thanks to the
          CityPairKey_T::describeShort() method, as that latter is used when
          inserting the CityPair within the BookingDay dedicated list. */
      CityPair*
      getCityPairInternal (const std::string& iCityPairKey) const;
      
      /** Get the list of Event objects. */
      const EventList_T& getEventList () const {
        return _eventList;
      }

      /** Remove the reservation / event corresponding to the given key
          from the queue / list. */
      void removeEventFromList (const EventList_T::iterator&);

    private:
      // Attributes
      /** Children: list of CityPair objects. */
      CityPairList_T _cityPairList;

      /** Current Simulation / Booking Date. */
      boost::gregorian::date _bookingDate;

      /** Time of the next reservation/event for the booking day. */
      boost::posix_time::time_duration _bookingTime;

      /** Daily rate, corresponding to the final demand pro-rated/weighted
          according to the distribution in City Pairs. */
      double _dailyRate;

      /** Number of reservations / events made during the simulation day. */
      int _dailyEventNumber;

      /** List, for a given BookingDay, holding the Departure date probability
          (discrete) distribution. */
      CityPairDistribution_T _cityPairDistribution;

      /** List of reservations / events made during the simulation day. */
      EventList_T _eventList;
      
      /** (GSL) Random seed. */
      gsl_rng* _rngExponentialPtr;
      gsl_rng* _rngUniformIntPtr;
    };
  }
}
#endif // __LATUS_COM_BOM_BOOKINGDAY_HPP
