// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/ModuleDescription.hpp>
#include <latus/com/service/ServiceContext.hpp>
#include <latus/com/service/LATUS_Service_Internal.hpp>
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

      // Retrieve the service context specific to that INV module
      const COM::ModuleDescription lInvModule (COM::ModuleDescription::INV,
                                               iModuleName);
      const COM::ServiceContext& lServiceContext =
        getServiceContext (lInvModule);

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

      // Retrieve the service context specific to that INV module
      const COM::ModuleDescription lInvModule (COM::ModuleDescription::INV,
                                               iModuleName);
      const COM::ServiceContext& lServiceContext =
        getServiceContext (lInvModule);

      return true;
    }
  
  }
}
