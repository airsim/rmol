// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/service/Logger.hpp>
// LATUS Inventory
#include <latus/sim/command/Simulator.hpp>
#include <latus/sim/service/LATUS_SIM.hpp>

namespace LATUS {
  
  namespace SIM {

    // //////////////////////////////////////////////////////////////////////
    LATUS_SIM::LATUS_SIM () {
    }
    
    // //////////////////////////////////////////////////////////////////////
    LATUS_SIM::~LATUS_SIM () {
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_SIM::simulate (const std::string& iModuleName) {

      // Get the parameters stored within the Service Context (passed through
      // by the caller)
      const int lSimulationRunNumber = getSimulationRunNumber (iModuleName);
      const std::string& lDemandInputFilename =
        getDemandInputFilename (iModuleName);
      const COM::DateTime_T& lStartDate = getStartDate (iModuleName);
      const COM::DateTime_T& lEndDate = getEndDate (iModuleName);

      // Perform K simulations    
      for (unsigned int i=1; i != lSimulationRunNumber; i++) {
        // Call the corresponding Use Case (command)
        Simulator lSimulator (lStartDate, lEndDate, lDemandInputFilename);
        lSimulator.simulate();
      }
    }

  }
  
}
