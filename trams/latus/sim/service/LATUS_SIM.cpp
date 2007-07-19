// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/service/ServiceContext.hpp>
#include <latus/com/service/Logger.hpp>
// LATUS Inventory
#include <latus/sim/command/Simulator.hpp>
#include <latus/sim/service/LATUS_SIM.hpp>

namespace LATUS {
  
  namespace SIM {

    // //////////////////////////////////////////////////////////////////////
    LATUS_SIM::LATUS_SIM (const std::string& iModuleName) :
      LATUS_ServiceAbstract(COM::ModuleDescription(COM::ModuleDescription::SIM,
                                                   iModuleName)) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    LATUS_SIM::~LATUS_SIM () {
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_SIM::initSpecificContext () {
      
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_SIM::setSimulationRunNumber (const int iSimulationRunNumber) {
      COM::ServiceContext& lServiceContext = getServiceContext();
      lServiceContext.setSimulationRunNumber (iSimulationRunNumber);
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_SIM::setInputFilename (const std::string& iInputFilename) {
      COM::ServiceContext& lServiceContext = getServiceContext();
      lServiceContext.setInputFilename (iInputFilename);
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_SIM::setStartDate (const boost::gregorian::date& iStartDate) {
      COM::ServiceContext& lServiceContext = getServiceContext();
      lServiceContext.setStartDate (iStartDate);
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_SIM::setEndDate (const boost::gregorian::date& iEndDate) {
      COM::ServiceContext& lServiceContext = getServiceContext();
      lServiceContext.setEndDate (iEndDate);
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_SIM::simulate () const {

      // Retrieve the service context specific to the SIM module
      const COM::ServiceContext& lServiceContext = getServiceContext();

      // Get the parameters stored within the Service Context (passed through
      // by the caller)
      const int lSimulationRunNumber = lServiceContext.getSimulationRunNumber();
      const std::string& lInputFilename = lServiceContext.getInputFilename();
      const boost::gregorian::date& lStartDate = lServiceContext.getStartDate();
      const boost::gregorian::date& lEndDate = lServiceContext.getEndDate();

      // Perform K simulations    
      for (int i=1; i != lSimulationRunNumber; i++) {
        // Call the corresponding Use Case (command)
        Simulator lSimulator (lStartDate, lEndDate, lInputFilename);
        lSimulator.simulate();
      }
    }

  }
  
}
