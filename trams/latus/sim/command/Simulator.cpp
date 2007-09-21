// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream> // DEBUG
// LATUS Common
#include <latus/com/basic/BasConst_BOOST_DateTime.hpp>
#include <latus/com/basic/BasConst_BookingDay.hpp>
#include <latus/com/bom/Event.hpp>
#include <latus/com/bom/BookingDay.hpp>
#include <latus/com/bom/CityPair.hpp>
#include <latus/com/bom/CityPairDate.hpp>
#include <latus/com/bom/ClassPath.hpp>
#include <latus/com/factory/FacBookingDay.hpp>
#include <latus/com/command/FileMgr.hpp>
#include <latus/com/service/Logger.hpp>
#include <latus/com/bom/TravelSolution.hpp>
// LATUS INV
#include <latus/inv/service/LATUS_INV.hpp> // DEBUG
// LATUS CRS
#include <latus/crs/service/LATUS_CRS.hpp>
// LATUS Main
#include <latus/sim/command/Simulator.hpp>

namespace LATUS {

  namespace SIM {

    // //////////////////////////////////////////////////////////////////////
    Simulator::Simulator (const COM::DateTime_T& iStartDate,
                          const COM::DateTime_T& iEndDate,
                          const std::string& iInputFileName)
      : _bookingDay (NULL), _inputFileName (iInputFileName),
        _startDate (iStartDate), _endDate (iEndDate) {

      // Read the input file and build the CityPairList
       const bool hasSucceeded = init();
      assert (hasSucceeded == true);
    }
      
    // //////////////////////////////////////////////////////////////////////
    Simulator::~Simulator() {
    }
    
    // //////////////////////////////////////////////////////////////////////
    bool Simulator::init () {

      // Initialise the BookingDay object, which is the main entry point
      // for the demand-related event generation.
      _bookingDay =
        &COM::FacBookingDay::instance().create (COM::DEFAULT_BOOKING_DATE);
      assert (_bookingDay != NULL);
      
      // Read input data and parameters from a CSV-type file
      const bool hasFileBeenRead = 
        COM::FileMgr::readAndProcessDemandInputFile (_inputFileName,
                                                     *_bookingDay);
       if (hasFileBeenRead == false) {
        LATUS_LOG_ERROR ("Can not parse the \"" << _inputFileName 
                         << "\" file (hint: check that it exists).");
        return false;
       }

      return true;
    }
    
    // //////////////////////////////////////////////////////////////////////
    const COM::DateTime_T& Simulator::getCurrentDate () const {
      // Get the (current) booking date from the BookingDay object.
      const COM::BookingDay& lBookingDay = getBookingDayRef();
      return lBookingDay.getBookingDate();
    }
      
    // //////////////////////////////////////////////////////////////////////
    void Simulator::
    setCurrentDate (const COM::DateTime_T& iBookingDate) const {
      // Set the (current) booking date for the BookingDay object.
      COM::BookingDay& lBookingDay = getBookingDayRef();
      lBookingDay.setBookingDate (iBookingDate);
    }
      
    // //////////////////////////////////////////////////////////////////////
    void Simulator::incrementCurrentDate () const {
      COM::BookingDay& lBookingDay = getBookingDayRef();
      lBookingDay.incrementBookingDate ();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void Simulator::display () const {
      const COM::BookingDay& lBookingDay = getBookingDayRef();
      lBookingDay.display();
    }

    // //////////////////////////////////////////////////////////////////////
    void Simulator::playEvent (const COM::Event_T& iEvent) const {
      const COM::ClassPath* lClassPath_ptr = iEvent.second;
      assert (lClassPath_ptr != NULL);

      // Get the Travel Solutions corresponding to the city pair and
      // departure date
      const COM::AirportCode_T& lOrigin = lClassPath_ptr->getOrigin();
      const COM::AirportCode_T& lDestination = lClassPath_ptr->getDestination();
      const COM::DateTime_T& lDepDate = lClassPath_ptr->getDepartureDate();
      COM::TravelSolutionKeyList_T lTravelSolutionKeyList;

      CRS::LATUS_CRS::provideTravelSolution (lOrigin, lDestination, lDepDate,
                                             lTravelSolutionKeyList);
      
    }

    // //////////////////////////////////////////////////////////////////////
    void Simulator::generateAndPlayForCurrentDay () {
      COM::BookingDay& lBookingDay = getBookingDayRef();

      // Initialise the current time to midnight, re-calculate the (booking)
      // daily rates corresponding to the current date, and build the
      // daily rate distributions.
      lBookingDay.resetForCurrentDate();

      // If there is no generated reservation / event, there is nothing
      // more to be done here.
      if (lBookingDay.hasNoEvent() == true) {
        return;
      }
      
      // Extract a single CityPair-tied reservation / event from the
      // event queue until midnight is reached.
      while (lBookingDay.hasReachedEndOfDay() == false) {
        // Dequeue the next (i.e., the first) event from the event list
        const COM::Event_T& lEvent = lBookingDay.getFirstEvent();

        // Set the current / booking time to the event
        const COM::EventKey_T& lEventTime = lEvent.first;
        lBookingDay.setBookingTime (lEventTime);

		if (lBookingDay.hasReachedEndOfDay() == true) {
		  break;
		}

        // Play the reservation event
        playEvent (lEvent);
        
        // Remove the event from the event list
        lBookingDay.eraseEvent (lEventTime);

        // Draw the next event for the corresponding CityPair
        const COM::ClassPath* lClassPath_ptr = lEvent.second;
        assert (lClassPath_ptr != NULL);
        COM::CityPairDate& lCityPairDate = lClassPath_ptr->getCityPairDateRef();
        COM::CityPair& lCityPair = lCityPairDate.getCityPairRef();
        lBookingDay.drawCityPairNextEvent (lCityPair);
      }
    }

    // //////////////////////////////////////////////////////////////////////
    void Simulator::simulate () {
      COM::BookingDay& lBookingDay = getBookingDayRef();
      
      // Set the (current) booking date for the BookingDay object.
      setCurrentDate (_startDate);

      // Loop from the start date to the end date, typically during one year.
      while (getCurrentDate() <= _endDate) {
        generateAndPlayForCurrentDay ();
        incrementCurrentDate();        
      }
    }
    
    // //////////////////////////////////////////////////////////////////////
    void Simulator::sampleSimulate () {

      // Calculate the availabilities for the NCE-NYC / 12-JUN-2007
      const COM::AirportCode_T lOrigin ("NCE");
      const COM::AirportCode_T lDestination ("NYC");
      const COM::DateTime_T lDepartureDate (2007, boost::gregorian::Jun, 12);
      COM::BucketAvailabilities_T lAvlList;

      const COM::AirlineCode_T lAirlineCode ("BA");
      INV::LATUS_INV::calculateAvailabilities (lAirlineCode,
                                               lOrigin, lDestination,
                                               lDepartureDate, lAvlList);

      COM::BucketAvailabilities_T::const_iterator itAvl = lAvlList.begin();
      for (short i = 0; itAvl != lAvlList.end(); itAvl++, i++) {
        const double lAvl = *itAvl;
        std::cout << "Avl [" << i << "] = " << lAvl << std::endl;
      }
    }

  }
}
