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
    void LATUS_SIM::simulate () {

      // Get the parameters stored within the Service Context (passed through
      // by the caller)
      const int lSimulationRunNumber = getSimulationRunNumber ();
      const std::string& lDemandInputFilename = getDemandInputFilename ();
      const COM::DateTime_T& lStartDate = getStartDate ();
      const COM::DateTime_T& lEndDate = getEndDate ();

      // DEBUG
      /* LATUS_LOG_DEBUG ("Simulation for " << lSimulationRunNumber
                       << " runs, " << "with '" << lDemandInputFilename
                       << "' for the demand data. The simulations run between "
                       << lStartDate << " and " << lEndDate);*/
      
      // Perform K simulations    
      for (unsigned int i=1; i != lSimulationRunNumber; i++) {
        // Call the corresponding Use Case (command)
        Simulator lSimulator (lStartDate, lEndDate, lDemandInputFilename);
        lSimulator.simulate();
      }
    }

  }
  
}
