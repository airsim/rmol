// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/bom/TravelSolutionList.hpp>
#include <latus/com/bom/TravelSolution.hpp>
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
    provideTravelSolution (const COM::AirportCode_T& iOrigin,
                           const COM::AirportCode_T& iDestination,
                           const COM::DateTime_T& iDate,
                           COM::TravelSolutionBlock& iTSB) {

      TSP::LATUS_TSP::getTravelSolutions (iOrigin, iDestination, iDate,
                                          iTSB);
      iTSB.display();
  
      // Quote the fares of the travel solutions according to the profil
      // of the request
       FQT::LATUS_FQT::quoteTravelSolutions(iTSB);
      

      // Retrieve the schedule input filename from the CRS specific
      // service context
      const std::string& lInputFilename = getScheduleInputFilename ();

      Distributor lDistributor (lInputFilename);

      COM::TravelSolutionList_T lTravelSolutionList = iTSB.getTravelSolutionList();
      for (COM::TravelSolutionList_T::iterator itTravelSolution =
             lTravelSolutionList.begin();
           itTravelSolution != lTravelSolutionList.end(); ++itTravelSolution) {
        COM::TravelSolution* lTravelSolution_ptr = itTravelSolution->second;
        assert (lTravelSolution_ptr != NULL);
        const COM::SeatNumber_T& iSeatNumber =  iTSB.getSeatNumber();
        lDistributor.provideAvailabilities (*lTravelSolution_ptr, iSeatNumber);
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
      COM::TravelSolution* iTravelSolution = NULL;

      iTS.getBestTravelSolution (iTravelSolution, iPartySize);
      if (iTravelSolution != NULL) {
        productSell = true;
      }
      return productSell;
    }
    
  }
}
