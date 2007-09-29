#ifndef __LATUS_CRS_SVC_LATUS_CRS_HPP
#define __LATUS_CRS_SVC_LATUS_CRS_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/TravelSolutionBlock.hpp>
#include <latus/com/service/LATUS_ServiceAbstract.hpp>

namespace LATUS {
  
  namespace CRS {

    /** Service (Interface) class for the CRS (Central Reservation System)
        module. */
    class LATUS_CRS : public COM::LATUS_ServiceAbstract {
    public:

      /** Calculate the availabilities corresponding to a given
          list of products and return Travel Solutions matching the booking number.
          @return The vector of Travel Solutions (TS). */
      static void provideTravelSolution (const COM::AirportCode_T& iOrigin,
                                         const COM::AirportCode_T& iDestination,
                                         const COM::DateTime_T& iDate,
                                         COM::TravelSolutionBlock& ioTSL);

      /** Organize the list of Travel Solution according to the UCM preferences. */
      static void  arrangeTravelSolutions (COM::TravelSolutionBlock& iTSL);
      
      /** Register the sell of a given number of travellers on a given
          Travel Solution.
          <br>The party size may be a floating number, so as to cope with
          overbooking. */
      static bool sell (const COM::TravelSolutionBlock& iTS,
                        const COM::BookingNumber_T& iPartySize);

    private:
      /** Constructors. */
      LATUS_CRS ();
      /** Destructor. */
      ~LATUS_CRS();
    };
  }
}
#endif // __LATUS_CRS_SVC_LATUS_CRS_HPP
