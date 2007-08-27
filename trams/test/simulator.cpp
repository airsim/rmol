// C
#include <assert.h>
// STL
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
// Boost (Extended STL)
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
// LATUS
#include <latus/LATUS_Service.hpp>


// /////////////// M A I N /////////////////
int main (int argc, char* argv[]) {
  try {
    
    // Length of the Simulation (number of runs)
    int K = 2;

    // Input O&D Demand File
    std::string lDemandFilename ("samples/demand.csv");

    // Input Schedule File
    std::string lScheduleFilename ("samples/world_schedule.csv");

    // Read the command-line parameters
    if (argc >= 1 && argv[1] != NULL) {
      std::istringstream istr (argv[1]);
      istr >> K;
    }

    if (argc >= 2 && argv[2] != NULL) {
      std::istringstream istr (argv[2]);
      istr >> lDemandFilename;
    }

    if (argc >= 3 && argv[3] != NULL) {
      std::istringstream istr (argv[3]);
      istr >> lScheduleFilename;
    }

    // Initialise the context
    LATUS::LATUS_Service latusService;

    // Set the log parameters
    latusService.setLogParameters (LATUS::LOG::DEBUG, std::cout);

    // Set the number of simulation runs
    latusService.setSimulationRunNumber (K);

    // Set the demand input filename (for test purposes)
    latusService.setDemandInputFilename (lDemandFilename);

    // Set the input filename (for test purposes)
    latusService.setScheduleInputFilename (lScheduleFilename);

    // Set the start date of the simulation
    latusService.setStartDate (boost::gregorian::date (2007,
                                                       boost::gregorian::Jan,
                                                       1));
    
    // Set the end date of the simulation
    latusService.setEndDate (boost::gregorian::date (2008,
                                                     boost::gregorian::Jan, 1));
    
    // Launch a simulation
    latusService.simulate ();

    
  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    return -1;
    
  } catch (...) {
    return -1;
  }
  
  return 0;
}
