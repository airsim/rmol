// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// GSL Random Number Distributions (GSL Reference Manual, version 1.7,
// Chapter 19)
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
// LATUS Common
#include <latus/com/basic/BasConst_GSL.hpp>
#include <latus/com/basic/BasConst_BOOST_DateTime.hpp>
#include <latus/com/bom/WholeDemand.hpp>
#include <latus/com/bom/BookingDay.hpp>
#include <latus/com/bom/CityPair.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {
  
  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    BookingDay::BookingDay (const boost::gregorian::date& iBookingDate)
      : _wholeDemand (NULL),
        _bookingDate (iBookingDate), _bookingTime (0, 0, 0, 0), 
        _dailyEventNumber (0),
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
    WholeDemand& BookingDay::getWholeDemandRef () const {
      assert (_wholeDemand != NULL);
      return *_wholeDemand;
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

      assert (_wholeDemand != NULL);
      _wholeDemand->display ();
      
      // DEBUG: Summary
      std::cout << _bookingDate << std::endl;

      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void BookingDay::displayCurrent() const {
      // DEBUG
      std::ios::fmtflags oldFlags = std::cout.flags();
      LATUS_LOG_DEBUG (_bookingDate << "; Current Time: " << _bookingTime 
                       << "; Daily Nb of Events: " << _dailyEventNumber);
      std::cout.flags (oldFlags);
    }

    // //////////////////////////////////////////////////////////////////////
    const double BookingDay::getDailyRate() const {
      assert (_wholeDemand != NULL);
      return _wholeDemand->getDailyRate();
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
      assert (_wholeDemand != NULL);
      _wholeDemand->updateDailyRate();
    }

    // //////////////////////////////////////////////////////////////////////
    void BookingDay::drawEventsForAllCityPairs () {
      assert (_wholeDemand != NULL);
      _wholeDemand->drawEventsForAllCityPairs (_eventList);
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
    void BookingDay::drawCityPairNextEvent (CityPair& ioCityPair) {
      ioCityPair.drawCityPairNextEvent (_eventList);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void BookingDay::
    removeEventFromList (const EventList_T::iterator& ioEventKey) {
      _eventList.erase (ioEventKey);
    }
    
  }
}
