// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/service/Logger.hpp>
// LATUS INV
#include <latus/inv/service/LATUS_INV.hpp>

namespace LATUS {
  
  namespace INV {

    // //////////////////////////////////////////////////////////////////////
    LATUS_INV::LATUS_INV () {
    }
    
    // //////////////////////////////////////////////////////////////////////
    LATUS_INV::~LATUS_INV () {
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_INV::
    calculateAvailabilities (const std::string& iModuleName,
                             const COM::AirportCode_T& iOrigin,
                             const COM::AirportCode_T& iDestination,
                             const COM::DateTime_T& iDate,
                             COM::BucketAvailabilities_T& ioAvl) {

      std::cout << "Inventory Service always up!" << std::endl;

      // TODO: Remove the hard coding
      // Hard-code a few availabilities
      ioAvl.push_back (12.1);
      ioAvl.push_back (8.4);
      ioAvl.push_back (5.7);
      ioAvl.push_back (3.3);
    }
    
    // //////////////////////////////////////////////////////////////////////
    bool LATUS_INV::sell (const std::string& iModuleName,
                          const COM::AirportCode_T& iOrigin,
                          const COM::AirportCode_T& iDestination,
                          const COM::DateTime_T& iDate,
                          const COM::BookingNumber_T& iPartySize) {

      return true;
    }
  
  }
}
