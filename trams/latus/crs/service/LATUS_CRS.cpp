// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/bom/TravelSolutionList.hpp>
#include <latus/com/bom/TravelSolution.hpp>
#include <latus/com/bom/WorldSchedule.hpp>
#include <latus/com/service/Logger.hpp>
// LATUS CRS
#include <latus/crs/command/Distributor.hpp>
#include <latus/crs/service/LATUS_CRS.hpp>
// LATUS TSP
#include <latus/tsp/service/LATUS_TSP.hpp>
// LATUS FQT
#include <latus/fqt/service/LATUS_FQT.hpp>
// LATUS UCM
#include <latus/ucm/service/LATUS_UCM.hpp>

namespace LATUS {
  
  namespace CRS {

    // //////////////////////////////////////////////////////////////////////
    LATUS_CRS::LATUS_CRS () {
    }
    
    // //////////////////////////////////////////////////////////////////////
    LATUS_CRS::~LATUS_CRS () {
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_CRS::
    provideTravelSolution (COM::TravelSolutionBlock& iTSB) {

      TSP::LATUS_TSP::getTravelSolutions (iTSB);
  
      // Quote the fares of the travel solutions according to the profil
      // of the request
       FQT::LATUS_FQT::quoteTravelSolutions(iTSB);
      

      // Retrieve the schedule input filename from the CRS specific
      // service context
      const std::string& lInputFilename = getScheduleInputFilename ();

      Distributor lDistributor (lInputFilename);

      /* Provide availabilities for the cheaper solution of each travel solution route. */
      COM::TravelSolutionList_T lTravelSolutionList = iTSB.getTravelSolutionList();
      for (COM::TravelSolutionList_T::iterator itTravelSolution =
             lTravelSolutionList.begin();
           itTravelSolution != lTravelSolutionList.end(); ++itTravelSolution) {

        COM::TravelSolution* lTravelSolution_ptr = itTravelSolution->second;
        assert (lTravelSolution_ptr != NULL);
        const COM::SeatNumber_T& iSeatNumber =  iTSB.getSeatNumber();
        lDistributor.provideAvailabilities (*lTravelSolution_ptr, iSeatNumber);

        // DEBUG
        /*LATUS_LOG_DEBUG ("Travel Solution Description:");
          lTravelSolution_ptr->display();*/
     }

    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_CRS::
    arrangeTravelSolutions (COM::TravelSolutionBlock& ilTSL) {

      // Arrange the list of travel solutions depending on the UCM preferences
      UCM::LATUS_UCM::chooseTravelSolution(ilTSL);
      
    }
    
    // //////////////////////////////////////////////////////////////////////
    bool LATUS_CRS::sell (const COM::TravelSolutionBlock& iTS,
                          const COM::BookingNumber_T& iPartySize) {
      bool productSell = false;
      /* Get the best available travel solution. */
      COM::TravelSolution* iTravelSolution =
        iTS.getBestTravelSolution (iPartySize);
      if (iTravelSolution != NULL) {
        /* Sell the product: updating the airline inventory. */
        productSell = iTravelSolution->sell (iPartySize);
        if (!productSell) {
          LATUS_LOG_DEBUG ("Problem in the sell functionality of the simulator");
        }
        COM::WorldSchedule& lworldSchedule = getWorldSchedule ();
        lworldSchedule.recalculateAvailabilities ();        
      }
      return productSell;
    }
    
  }
}
