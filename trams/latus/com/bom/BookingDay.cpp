// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// GSL Random Number Distributions (GSL Reference Manual, version 1.7,
// Chapter 19)
#include <gsl/gsl_math.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
// LATUS Common
#include <latus/com/basic/BasConst_GSL.hpp>
#include <latus/com/basic/BasConst_BOOST_DateTime.hpp>
#include <latus/com/bom/CityPair.hpp>
#include <latus/com/bom/CityPairDate.hpp>
#include <latus/com/bom/ClassPath.hpp>
#include <latus/com/bom/BookingDay.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {
  
  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    BookingDay::BookingDay (const boost::gregorian::date& iBookingDate)
      : _bookingDate (iBookingDate), _bookingTime (0, 0, 0, 0), 
        _dailyRate (0.0), _dailyEventNumber (0),
        _rngExponentialPtr (NULL), _rngUniformIntPtr (NULL) {

      initRandomGenerator();
    }
    
    // //////////////////////////////////////////////////////////////////////
    BookingDay::~BookingDay () {
      gsl_rng_free (_rngExponentialPtr); _rngExponentialPtr = NULL;
      gsl_rng_free (_rngUniformIntPtr); _rngUniformIntPtr = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    void BookingDay::initRandomGenerator() {
      // Initialise the Random Generator
      gsl_rng_env_setup ();
      
      _rngExponentialPtr = gsl_rng_alloc (DEFAULT_LATUS_RANDOM_GENERATOR_TYPE);
      assert (_rngExponentialPtr != NULL);
      _rngUniformIntPtr = gsl_rng_alloc (DEFAULT_LATUS_RANDOM_GENERATOR_TYPE);
      assert (_rngUniformIntPtr != NULL);
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string BookingDay::describeKey() const {
      std::ostringstream ostr;
      ostr << _bookingDate;
      return ostr.str();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void BookingDay::display() const {

      // Store current formatting flags of std::cout
      std::ios::fmtflags oldFlags = std::cout.flags();

      std::cout << _bookingDate << " - " << _bookingTime << "; " << std::endl;
      
      int j = 1;
      for (CityPairList_T::const_iterator itCityPair = _cityPairList.begin();
           itCityPair != _cityPairList.end(); itCityPair++, j++) {
        const CityPair* lCityPair_ptr = itCityPair->second;
        assert (lCityPair_ptr != NULL);

        lCityPair_ptr->display ();
      }
      
      // DEBUG: Summary
      std::cout << _bookingDate
                << "; Total daily rate: " << _dailyRate
                << std::endl;

      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void BookingDay::displayCurrent() const {
      // DEBUG
      std::ios::fmtflags oldFlags = std::cout.flags();
      LATUS_LOG_DEBUG (_bookingDate << "; Daily Rate: " 
                       << std::fixed << std::setprecision(2) << _dailyRate
                       << "; Current Time: " << _bookingTime 
                       << "; Daily Nb of Events: " << _dailyEventNumber);
      std::cout.flags (oldFlags);
    }

    // //////////////////////////////////////////////////////////////////////
    CityPair* BookingDay::getCityPair (const std::string& iDescription) const {
      CityPair* resultCityPair_ptr = NULL;
      
      CityPairList_T::const_iterator itCityPair =
        _cityPairList.find (iDescription);

      if (itCityPair != _cityPairList.end()) {
        resultCityPair_ptr = itCityPair->second;
      }

      return resultCityPair_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    bool BookingDay::hasReachedEndOfDay () const {
      return (_bookingTime >= BOOST_TIME_DURATION_FOR_A_DAY);
    }

    // //////////////////////////////////////////////////////////////////////
    bool BookingDay::hasNoEvent () const {
      return (_eventList.empty() == true);
    }

    // //////////////////////////////////////////////////////////////////////
    const Event_T BookingDay::getFirstEvent () const {
      assert (_eventList.empty() == false);
      
      EventList_T::const_iterator itFirstEvent = _eventList.begin();
      // const Event_T result (itFirstEvent.first, itFirstEvent.second);
      return *itFirstEvent;
    }

    // //////////////////////////////////////////////////////////////////////
    void BookingDay::eraseEvent (const EventKey_T& iEventKey) {
      EventList_T::iterator itEvent = _eventList.find (iEventKey);
      if (itEvent != _eventList.end()) {
        // Remove the event from the event list
        _eventList.erase (itEvent);
      }
    }
    
    // //////////////////////////////////////////////////////////////////////
    void BookingDay::incrementBookingDate () {
      _bookingDate += BOOST_DATE_DURATION_FOR_A_DAY;
    }
    
    // //////////////////////////////////////////////////////////////////////
    void BookingDay::updateDailyRate () {
      double oDailyRate = 0.0;
      
      // Empty the daily rate distribution, as it will be (re-)filled
      // by the below main loop on CityPair objects.
      _cityPairDistribution.clear();
      
      // Update the daily rates
      for (CityPairList_T::const_iterator itCityPair = _cityPairList.begin();
           itCityPair != _cityPairList.end(); itCityPair++) {
        CityPair* lCityPair_ptr = itCityPair->second;
        assert (lCityPair_ptr != NULL);

        /** Re-calculate the daily rate (final demand weighted by a modulation,
            e.g., here, according to a Weibull distribution). */
        lCityPair_ptr->updateDailyRate();

        const double lCityPairDailyRate = lCityPair_ptr->getDailyRate();

        // If the daily rate is null, then no event should be generated
        // for the corresponding CityPair object: the departure date is
        // probably too far.
        if (gsl_fcmp (lCityPairDailyRate, 0.0, 1e-3) == 0) {
          continue;
        }

        oDailyRate += lCityPairDailyRate;
        
        // Insert the current cumulated daily rate within the daily rate
        // distribution vector
        const bool insertSucceeded = _cityPairDistribution.
          insert (CityPairDistribution_T::
                  value_type (oDailyRate,
                              lCityPair_ptr->getPrimaryKey())).second;

        if (insertSucceeded == false) {
          LATUS_LOG_ERROR ("Insertion failed for " << oDailyRate
                           << " and " << lCityPair_ptr->describeKey());
          assert (insertSucceeded == true);
        }
      }

      setDailyRate (oDailyRate);
    }

    // //////////////////////////////////////////////////////////////////////
    void BookingDay::drawEventsForAllCityPairs () {
      for (CityPairList_T::const_iterator itCityPair = _cityPairList.begin();
           itCityPair != _cityPairList.end(); itCityPair++) {
        CityPair* lCityPair_ptr = itCityPair->second;
        assert (lCityPair_ptr != NULL);

        // Draw the next event corresponding to the CityPair (derived from the
        // CityPair daily rate), and add it to the event queue.
        drawCityPairNextEvent (*lCityPair_ptr);
      }
    }

    // //////////////////////////////////////////////////////////////////////
    void BookingDay::resetForCurrentDate () {
      // Reset the current/booking time to midnight
      setBookingTime (boost::posix_time::time_duration (0, 0, 0, 0));

      // Reset the list of reservations / events for the current day
      _eventList.clear();
      
      // Reset the daily number of events
      _dailyEventNumber = 0;

      // Update the daily rates of the CityPairs, and for the overall current
      // booking day. At the same time, build the daily rate distributions.
      updateDailyRate();

      // Generate a reservation / event per CityPair: it initialises the
      // event list.
      drawEventsForAllCityPairs();
    }

    // //////////////////////////////////////////////////////////////////////
    void BookingDay::
    removeEventFromList (const EventList_T::iterator& ioEventKey) {
      _eventList.erase (ioEventKey);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void BookingDay::drawCityPairNextEvent (CityPair& ioCityPair) {
      
      // Draw the inter-arrival time corresponding to the CityPair daily rate
      const boost::posix_time::time_duration& lNextEventTime =
        ioCityPair.drawNextEventTime ();
        
      // Generate the next event:
      // 1. Generate a departure date (hence, we derive the CityPairDate)
      CityPairDate* lCityPairDate_ptr = ioCityPair.drawCityPairDate();
      if (lCityPairDate_ptr == NULL) {
        return;
      }
      assert (lCityPairDate_ptr != NULL);
      
      // 1. Generate a class-path (hence, we derive the ClassPath)
      ClassPath* lClassPath_ptr = lCityPairDate_ptr->drawClassPath();
      if (lClassPath_ptr == NULL) {
        return;
      }
      assert (lClassPath_ptr != NULL);

      /*
      LATUS_LOG_DEBUG ("Drawn ClassPath: " << lClassPath_ptr->describeKey()
                       << " for event time: " << lNextEventTime);
      */
        
      // Add the event to the dedicated list
      _eventList.insert (EventList_T::value_type (lNextEventTime,
                                                  lClassPath_ptr));
    }

  }
}
