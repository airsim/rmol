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

      // Retrieve the schedule input filename from the CRS specific
      // service context
      const std::string& lInputFilename = getScheduleInputFilename ();

      Distributor lDistributor (lInputFilename);

      // TODO: Remove the hard coding
      // Hard-code a few TSL
      //const COM::AirlineCode_T lBA ("BA");
      //const COM::FlightNumber_T l341 = 341;
      //const COM::FlightKey_T lBA341 (lBA, l341);
      //const COM::DateTime_T l21Apr (2007, boost::gregorian::Apr, 21);
      //const COM::FlightDateKey_T lBA34121Apr2007 (lBA341, l21Apr);
      //const COM::AirportCode_T lNCE ("NCE");
      //const COM::AirportCode_T lLHR ("LHR");
      //const COM::AirportPairKey_T lNCELHR (lNCE, lLHR);
      //const COM::SegmentDateKey_T lSegment1 (lBA34121Apr2007, lNCELHR);

      //lDistributor.provideAvailabilities (lSegment1, ioTSL);
    }
    
    // //////////////////////////////////////////////////////////////////////
    bool LATUS_CRS::sell (const COM::TravelSolutionKeyList_T& iTS,
                          const COM::BookingNumber_T& iPartySize) {
      return true;
    }
    
  }
}
