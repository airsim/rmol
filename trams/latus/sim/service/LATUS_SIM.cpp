// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <fstream>
#include <stdexcept>
// LATUS Common
#include <latus/com/bom/WorldSchedule.hpp>
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
      const unsigned int lSimulationRunNumber = getSimulationRunNumber ();
      const std::string& lDemandInputFilename = getDemandInputFilename ();
      const COM::DateTime_T& lStartDate = getStartDate ();
      const COM::DateTime_T& lEndDate = getEndDate ();
      COM::WholeDemand& lWholeDemand = getWholeDemand();
      // outputFile
      std::ofstream outputFile;

      // Retrieve the worldSchedule output filename from the SIM specific
        // service context
      const std::string& lWorldScheduleOutputFilename =
          getWorldScheduleOutputFilename ();

      try {
        outputFile.open(lWorldScheduleOutputFilename.c_str());
        outputFile.clear();
        // Perform K simulations    
        for (unsigned int i=1; i != lSimulationRunNumber+1; ++i) {
        // DEBUG
          outputFile << "Simulation run " << i << " with '"
                         << lDemandInputFilename
                         << "' for the demand data. The simulations run between "
                   << lStartDate << " and " << lEndDate
                   << std::endl;
      
          // Call the corresponding Use Case (command)
          Simulator::simulate (lWholeDemand, lStartDate, lEndDate);

          // Write the world schedule in a result file
          COM::WorldSchedule& lWorldSchedule = getWorldSchedule();
          lWorldSchedule.exportInformations(outputFile);
        }
      
        // Close the worldSchedule output file
        outputFile.close();
      }
      
      catch (const std::exception& e){
        std::cout << "Error in exporting the output file: " << e.what() << std::endl;
      }
    }

  }
  
}
