// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/bom/Network.hpp>
#include <latus/com/bom/NetworkDate.hpp>
#include <latus/com/bom/AirportDate.hpp>
#include <latus/com/service/Logger.hpp>
// LATUS FQT
#include <latus/fqt/command/FareQuoter.hpp>
#include <latus/fqt/service/LATUS_FQT.hpp>

namespace LATUS {

  namespace FQT {

    // //////////////////////////////////////////////////////////////////////
    LATUS_FQT::LATUS_FQT () {
    }
    
    // //////////////////////////////////////////////////////////////////////
    LATUS_FQT::~LATUS_FQT () {
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_FQT::
    quoteTravelSolutions (const COM::AirportCode_T& ioOrigin,
                          const COM::DateTime_T& ioDate,
                          COM::TravelSolutionKeyList_T& ioTSL) {

       // Retrieve the Network
      const COM::Network& lNetwork = getNetwork();

      // Retrieve the NetworkDate for that departure date.
      const COM::NetworkDate* lNetworkDate_ptr =
        lNetwork.getNetworkDate (ioDate);

      // If there is no NetworkDate for that departure date, there is no
      // travel solution, and there is therefore nothing more to be done
      // (the list of Travel Solutions stay empty).
      if (lNetworkDate_ptr == NULL) {
        return;
      }
      assert (lNetworkDate_ptr != NULL);

      // Retrieve the AirportDate for that origin.
      const COM::AirportDate* lAirportDate_ptr =
        lNetworkDate_ptr->getAirportDate (ioOrigin);
      
      // If there is no AirportDate for that departure date, there is no
      // travel solution, and there is therefore nothing more to be done
      // (the list of Travel Solutions stay empty).
      if (lAirportDate_ptr == NULL) {
        return;
      }
      assert (lAirportDate_ptr != NULL);

      const COM::AirportDate& lAirportDate = *lAirportDate_ptr;

      FareQuoter::quoteTravelSolutions(lAirportDate, ioTSL); 
      
    }

  }
}
