// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iostream> // DEBUG
// LATUS
#include <latus/crs/service/LATUS_CRS.hpp>

namespace LATUS {
  
  namespace CRS {

    // //////////////////////////////////////////////////////////////////////
    void LATUS_CRS::initialise() {
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_CRS::
    provideTravelSolution (const COM::AirportCode_T& iOrigin,
                           const COM::AirportCode_T& iDestination,
                           const COM::DateTime_T& iDate,
                           COM::TravelSolutionList_T& ioTSL) const {
      std::cout << "Distribution service always up!" << std::endl;

      // TODO: Remove the hard coding
      // Hard-code a few TSL
      const COM::AirlineCode_T lBA ("BA");
      const COM::FlightNumber_T l341 = 341;
      const COM::AirportCode_T lNCE ("NCE");
      const COM::AirportCode_T lLHR ("LHR");
      const COM::DateTime_T l21Apr (2007, boost::gregorian::Apr, 21);
      const COM::SegmentDateStruct_T lSegment1 (lBA, l341, lNCE, lLHR, l21Apr);

      const COM::AirportCode_T lMUC ("MUC");
      const COM::AirportCode_T lMIA ("MIA");
      const COM::AirportCode_T lLAX ("LAX");
      const COM::CabinCode_T lSHBusiness ("C");
      const COM::CabinCode_T lSHEconomy ("M");
      const COM::CabinCode_T lFirst ("F");
      const COM::CabinCode_T lLHBusiness ("J");
      const COM::CabinCode_T lTravelPlus ("W");
      const COM::CabinCode_T lLHEconomy ("M");
    }
    
    // //////////////////////////////////////////////////////////////////////
    bool LATUS_CRS::sell (const COM::TravelSolutionList_T& iTS,
                          const COM::BookingNumber_T& iPartySize) {
      return true;
    }
    
  }
  
}
