// STL
#include <iostream>
#include <sstream>
// LATUS
#include <latus/LATUS_Service.hpp>
#include <latus/tsp/service/LATUS_TSP.hpp>

/** As the LATUS_TSP::generateInventories() method is not exposed in the
    LATUS_Service interface (since it's an internal initialisation method),
    we have to use directly the LATUS_TSP interface.
 */

// /////////////// M A I N /////////////////
int main (int argc, char* argv[]) {
  try {
    
    // Input Schedule File
    std::string lScheduleFilename ("samples/world_schedule.csv");

    // Read the command-line parameters
    if (argc >= 1 && argv[1] != NULL) {
      std::istringstream istr (argv[1]);
      istr >> lScheduleFilename;
    }

    // Initialise the context
    LATUS::LATUS_Service latusService;

    // Set the log parameters
    latusService.setLogParameters (LATUS::LOG::DEBUG, std::cout);

    // Set the schedule input filename (for test purposes)
    latusService.setScheduleInputFilename (lScheduleFilename);

    // Parse the CSV-formatted schedule input file, and generate the
    // corresponding Inventories for the airlines.
    LATUS::TSP::LATUS_TSP::generateInventories ();
    
  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    return -1;
    
  } catch (...) {
    return -1;
  }
  
  return 0;
}
