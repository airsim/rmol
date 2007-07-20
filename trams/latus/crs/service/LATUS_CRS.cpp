// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/service/ServiceContext.hpp>
#include <latus/com/service/Logger.hpp>
// LATUS CRS
#include <latus/crs/command/Distributor.hpp>
#include <latus/crs/service/LATUS_CRS.hpp>

namespace LATUS {
  
  namespace CRS {

    // //////////////////////////////////////////////////////////////////////
    LATUS_CRS::LATUS_CRS (const std::string& iModuleName) :
      LATUS_ServiceAbstract(COM::ModuleDescription(COM::ModuleDescription::CRS,
                                                   iModuleName)) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    LATUS_CRS::~LATUS_CRS () {
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_CRS::initSpecificContext () {
      
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_CRS::
    provideTravelSolution (const COM::AirportCode_T& iOrigin,
                           const COM::AirportCode_T& iDestination,
                           const COM::DateTime_T& iDate,
                           COM::TravelSolutionKeyList_T& ioTSL) const {

      // Retrieve the service context specific to the SIM module
      const COM::ServiceContext& lServiceContext = getServiceContext();

      // Get the parameters stored within the Service Context (passed through
      // by the caller)
      const std::string& lInputFilename = lServiceContext.getInputFilename();

      std::cout << "Distribution service always up!" << std::endl;

      Distributor lDistributor (lInputFilename);

      // TODO: Remove the hard coding
      // Hard-code a few TSL
      const COM::AirlineCode_T lBA ("BA");
      const COM::FlightNumber_T l341 = 341;
      const COM::FlightKey_T lBA341 (lBA, l341);
      const COM::DateTime_T l21Apr (2007, boost::gregorian::Apr, 21);
      const COM::AirportCode_T lNCE ("NCE");
      const COM::AirportCode_T lLHR ("LHR");
      const COM::AirportPair_T lNCELHR (lNCE, lLHR);
      const COM::SegmentDateKey_T lSegment1 (lBA341, l21Apr, lNCELHR);

      lDistributor.provideAvailabilities (lSegment1, ioTSL);
    }
    
    // //////////////////////////////////////////////////////////////////////
    bool LATUS_CRS::sell (const COM::TravelSolutionKeyList_T& iTS,
                          const COM::BookingNumber_T& iPartySize) {
      return true;
    }
    
  }
  
}
