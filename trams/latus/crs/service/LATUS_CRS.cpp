// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/service/Logger.hpp>
#include <latus/com/bom/OutboundPathList.hpp>
#include <latus/com/bom/OutboundPath.hpp>
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
                           COM::TravelSolutionKeyList_T& ioTSL) {
      
      COM::OutboundPathLightList_T iTravelSolutionList;

      TSP::LATUS_TSP::getTravelSolutions (iOrigin, iDestination, iDate,
                                          iTravelSolutionList);
  
      unsigned short idx = 0;
      for (COM::OutboundPathLightList_T::const_iterator itPath =
             iTravelSolutionList.begin();
           itPath != iTravelSolutionList.end(); ++itPath, ++idx) {
        const COM::OutboundPath* iOutboundPath_ptr = *itPath;
        assert (iOutboundPath_ptr != NULL);

        std::cout << "[" << idx << "]: "
                  << iOutboundPath_ptr->describeKey() << std::endl;
      }

      // Quote the fares of the travel solutions according to the profil
      // of the request
      FQT::LATUS_FQT::quoteTravelSolutions(iOrigin, iDate, ioTSL);
      

      // Retrieve the schedule input filename from the CRS specific
      // service context
      const std::string& lInputFilename = getScheduleInputFilename ();

      Distributor lDistributor (lInputFilename);

      //lDistributor.provideAvailabilities (lSegment1, ioTSL);

    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_CRS::
    arrangeTravelSolutions (const COM::AirportCode_T& iOrigin,
                           const COM::AirportCode_T& iDestination,
                           const COM::DateTime_T& iDate,
                           COM::TravelSolutionKeyList_T& iTSL) {

      // Arrange the list of travel solutions depending on the UCM preferences
      UCM::LATUS_UCM::chooseTravelSolution(iOrigin, iDestination, iDate,
                                           iTSL);
      
    }
    
    // //////////////////////////////////////////////////////////////////////
    bool LATUS_CRS::sell (const COM::TravelSolutionKeyList_T& iTS,
                          const COM::BookingNumber_T& iPartySize) {
      return true;
    }
    
  }
}
