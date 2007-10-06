// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream> // DEBUG
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/basic/BasConst_BOOST_DateTime.hpp>
#include <latus/com/basic/BasConst_BookingDay.hpp>
#include <latus/com/bom/Event.hpp>
#include <latus/com/bom/BookingDay.hpp>
#include <latus/com/bom/CityPair.hpp>
#include <latus/com/bom/CityPairDate.hpp>
#include <latus/com/bom/WTP.hpp>
#include <latus/com/factory/FacBookingDay.hpp>
#include <latus/com/service/Logger.hpp>
#include <latus/com/bom/TravelSolutionBlock.hpp>
#include <latus/com/bom/TravelSolutionBlockKey.hpp>
#include <latus/com/factory/FacTravelSolutionBlock.hpp>
// LATUS DEG
#include <latus/deg/service/LATUS_DEG.hpp>
// LATUS INV
#include <latus/inv/service/LATUS_INV.hpp> // DEBUG
// LATUS CRS
#include <latus/crs/service/LATUS_CRS.hpp>
// LATUS SIM
#include <latus/sim/command/Simulator.hpp>

namespace LATUS {

  namespace SIM {

    // //////////////////////////////////////////////////////////////////////
    Simulator::~Simulator() {
    }
    
    // //////////////////////////////////////////////////////////////////////
    void Simulator::playEvent (const COM::Event_T& iEvent,
                               COM::BookingNumber_T& iTotalBookingRequestNumber,
                               COM::BookingNumber_T& iTotalBookingNumber) {
      
      const COM::WTP* lWTP_ptr = iEvent.second;
      assert (lWTP_ptr != NULL);

      // Get the Travel Solutions corresponding to the city pair and
      // departure date
      const COM::AirportCode_T& lOrigin = lWTP_ptr->getOrigin();
      const COM::AirportCode_T& lDestination = lWTP_ptr->getDestination();
      const COM::DateTime_T& lDepDate = lWTP_ptr->getDepartureDate();
      const COM::SeatNumber_T& lSeatNumber = lWTP_ptr->getSeatNumber();

      //increment the total request number of the simulation
      iTotalBookingRequestNumber = iTotalBookingRequestNumber + lSeatNumber;

      // Creation of the TravelSolutions wrapper
      const COM::TravelSolutionBlockKey_T lTravelSolutionBlockKey (lOrigin, lDestination, lDepDate, lSeatNumber);
      COM::TravelSolutionBlock& lTravelSolutionBlock =
          COM::FacTravelSolutionBlock::instance().create (lTravelSolutionBlockKey, lWTP_ptr);
      
      CRS::LATUS_CRS::provideTravelSolution (lTravelSolutionBlock);

      CRS::LATUS_CRS::arrangeTravelSolutions (lTravelSolutionBlock);

      const bool sellStatus = CRS::LATUS_CRS::sell(lTravelSolutionBlock, lSeatNumber);

      if (sellStatus == true) {
        iTotalBookingNumber = iTotalBookingNumber + lSeatNumber;
        // LATUS_LOG_DEBUG ("Booking made ");
      }
      else {
         LATUS_LOG_DEBUG ("Booking not made because no travel solution are available ");
      }
    }

    // //////////////////////////////////////////////////////////////////////
    void Simulator::
    generateAndPlayForCurrentDay (COM::BookingDay& ioBookingDay,
                                  COM::BookingNumber_T& ioTotalBookingRequestNumber,
                                  COM::BookingNumber_T& ioTotalBookingNumber) {
      // Initialise the current time to midnight, re-calculate the (booking)
      // daily rates corresponding to the current date, and build the
      // daily rate distributions.
      ioBookingDay.resetForCurrentDate();

      // If there is no generated reservation / event, there is nothing
      // more to be done here.
      if (ioBookingDay.hasNoEvent() == true) {
        return;
      }
      
      // Extract a single CityPair-tied reservation / event from the
      // event queue until midnight is reached.
      while (ioBookingDay.hasReachedEndOfDay() == false) {
        // Dequeue the next (i.e., the first) event from the event list
        const COM::Event_T& lEvent = ioBookingDay.getFirstEvent();

        // Set the current / booking time to the event
        const COM::EventKey_T& lEventTime = lEvent.first;
        ioBookingDay.setBookingTime (lEventTime);

		if (ioBookingDay.hasReachedEndOfDay() == true) {
		  break;
		}

        // DEBUG
        /* LATUS_LOG_DEBUG ("Booking Date: " << ioBookingDay.getBookingDate()
           << ", Booking Time: " << ioBookingDay.getBookingTime());*/
        
        // Play the reservation event
        playEvent (lEvent, ioTotalBookingRequestNumber, ioTotalBookingNumber );
        
        // Remove the event from the event list
        ioBookingDay.eraseEvent (lEventTime);

        // Draw the next event for the corresponding CityPair
        const COM::WTP* lWTP_ptr = lEvent.second;
        assert (lWTP_ptr != NULL);
        COM::CityPairDate& lCityPairDate = lWTP_ptr->getCityPairDateRef();
        COM::CityPair& lCityPair = lCityPairDate.getCityPairRef();
        ioBookingDay.drawCityPairNextEvent (lCityPair);
      }
    }

    // //////////////////////////////////////////////////////////////////////
    void Simulator::simulate (COM::WholeDemand& ioWholeDemand,
                              const COM::DateTime_T& iStartDate,
                              const COM::DateTime_T& iEndDate) {
      // Initialisation of the total booking request number
      COM::BookingNumber_T totalBookingRequestNumber = 0;
      // Initialisation of the total booking number
      COM::BookingNumber_T totalBookingNumber = 0;
      
      // TODO: Study whether a BookingDay strcuture (rather than a BOM class)
      // would not be more appropriate.
      
      // Initialise the BookingDay object, which is the main entry point
      // for the demand-related event generation, and link it to the
      // Demand (BOM) objects.
      COM::BookingDay& lBookingDay =
        COM::FacBookingDay::instance().create (COM::DEFAULT_BOOKING_DATE);
      
      COM::FacBookingDay::initLinkWithWholeDemand (lBookingDay, ioWholeDemand);

      // Loop from the start date to the end date, typically during one year.
      while (lBookingDay.getBookingDate() <= iEndDate) {
        generateAndPlayForCurrentDay (lBookingDay,totalBookingRequestNumber,
                                      totalBookingNumber);
        lBookingDay.incrementBookingDate ();
      }
      // DEBUG
      LATUS_LOG_DEBUG ("Total number of booking request: "
                        << totalBookingRequestNumber
                        << " and total number of bookings: "
                        << totalBookingNumber);    
    }
    
  }
}
