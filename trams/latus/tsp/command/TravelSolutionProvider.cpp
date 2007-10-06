// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/basic/BasConst_LATUS_Service.hpp>
#include <latus/com/bom/Network.hpp>
#include <latus/com/bom/NetworkDate.hpp>
#include <latus/com/bom/AirportDate.hpp>
#include <latus/com/bom/OutboundPath.hpp>
#include <latus/com/service/Logger.hpp>
#include <latus/com/factory/FacTravelSolution.hpp>
#include <latus/com/bom/TravelSolution.hpp>
#include <latus/com/bom/TravelSolutionList.hpp>


// LATUS TSP
#include <latus/tsp/command/TravelSolutionProvider.hpp>

namespace LATUS {

  namespace TSP {

    // //////////////////////////////////////////////////////////////////////
    void  TravelSolutionProvider::
    provideTravelSolution (const COM::Network& ioNetwork,                           
                           COM::TravelSolutionBlock& ioTSolutions) {

      // Retrieve the NetworkDate for that departure date.
      const COM::NetworkDate* lNetworkDate_ptr =
        ioNetwork.getNetworkDate (ioTSolutions.getDepartureDate());

      // If there is no NetworkDate for that departure date, there is no
      // travel solution, and there is therefore nothing more to be done
      // (the list of Travel Solutions stay empty).
      if (lNetworkDate_ptr == NULL) {
        return;
      }
      assert (lNetworkDate_ptr != NULL);

      // Retrieve the AirportDate for that origin.
      COM::AirportDate* lAirportDate_ptr =
        lNetworkDate_ptr->getAirportDate (ioTSolutions.getOrigin());
      
      // If there is no AirportDate for that departure date, there is no
      // travel solution, and there is therefore nothing more to be done
      // (the list of Travel Solutions stay empty).
      if (lAirportDate_ptr == NULL) {
        return;
      }
      assert (lAirportDate_ptr != NULL);

      ioTSolutions.setAirportDate(lAirportDate_ptr);

      const COM::OutboundPathList_T& lOutboundPathList = lAirportDate_ptr->getOutboundPathList();

      createTravelSolutions(lOutboundPathList, ioTSolutions);
    }

    // //////////////////////////////////////////////////////////////////////
    void  TravelSolutionProvider::
    createTravelSolutions (const COM::OutboundPathList_T& ioOutboundPathList,
                           COM::TravelSolutionBlock& ioTSolutions) {

      for (COM::OutboundPathList_T::const_iterator itPath =
             ioOutboundPathList.begin();
           itPath != ioOutboundPathList.end(); ++itPath) {
        COM::OutboundPath* lOutboundPath_ptr = itPath->second;
        assert (lOutboundPath_ptr != NULL);

        // Retrieve the destination of the outbound path
        const COM::AirportCode_T& lDestination = lOutboundPath_ptr->getDestination();

        if (lDestination == ioTSolutions.getDestination()) {          
          // Creation of a new TravelSolution only made by the outbound path. */
          const COM::OutboundPathKey_T& lOutboundPathKey = lOutboundPath_ptr->getOutboundPathKey();
          const COM::TravelSolutionKey_T lTravelSolutionKey (lOutboundPathKey);

          COM::TravelSolution& lTravelSolution =
            COM::FacTravelSolution::instance().create (lTravelSolutionKey);

          lTravelSolution.setOutboundPath(lOutboundPath_ptr);

          COM::TravelSolutionList_T& lTravelSolutionList = ioTSolutions.getTravelSolutionList();
          
          lTravelSolutionList.insert (COM::TravelSolutionList_T::
                value_type (lTravelSolution.describeShortKey(),
                            &lTravelSolution));
          
          ioTSolutions.incrementTravelSolutionNumber();
        }
      }
      
    }
  }
}
