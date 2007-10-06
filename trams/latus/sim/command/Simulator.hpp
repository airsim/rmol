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
    class WholeDemand;
  }

  namespace SIM {

    /** Class wrapping the simulation methods. */
    class Simulator : public COM::CmdAbstract {
      // Only LATUS_SIM can instantiate Simulator
      friend class LATUS_SIM;
    public:
      // ////////// Main Methods ///////////      
      /**
         Main call-back.
      */
      static void simulate (COM::WholeDemand&,
                            const COM::DateTime_T& iStartDate,
                            const COM::DateTime_T& iEndDate);


      // ///////// DISPLAY METHODS /////////
      /** Display the BOM objects. */
      void display () const;
      

    private:
      /** Constructors. */
      Simulator ();
      Simulator (const Simulator&);
      
      /** Destructor. */
      virtual ~Simulator();

    private:
      /** Play a reservation / event.
          <br>The reservation / event object contains both the time of the
          event and the reservation details (city pair description,
          departure date, class-path). */
      static void playEvent (const COM::Event_T& iEvent,
                             COM::BookingNumber_T&,
                             COM::BookingNumber_T&);
      
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
      static void generateAndPlayForCurrentDay (COM::BookingDay&,
                                                COM::BookingNumber_T&,
                                                COM::BookingNumber_T&);
      
    private:
      // BOM (the BookingDay class is the entry point to the BOM)
      COM::BookingDay* _bookingDay;
    };
  }
}
#endif // __LATUS_SIM_CMD_SIMULATOR_HPP
