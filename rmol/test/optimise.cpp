// STL
#include <iostream>
#include <sstream>
// RMOL
#include <rmol/RMOL.hpp>


// M A I N
int main (int argc, char* argv[]) {
  try {
    
  // Number of random draws to be generated (best if greater than 100)
  int K = 100000;

  // Cabin Capacity (it must be greater then 100 here)
  double cabinCapacity = 500.0;

  // Input file name
  std::string inputFileName ("class.csv");
  bool hasInputFile = false;
  
  if (argc >= 1 && argv[1] != NULL) {
    std::istringstream istr (argv[1]);
    istr >> K;
  }

  if (argc >= 2 && argv[2] != NULL) {
    std::istringstream istr (argv[2]);
    istr >> cabinCapacity;
  }

  if (argc >= 3 && argv[3] != NULL) {
    std::istringstream istr (argv[3]);
    istr >> inputFileName;
    hasInputFile = true;
  }

  // Initialise the list of classes/buckets
  RMOL::RMOL_Service rmolService (cabinCapacity);

  if (hasInputFile) {
    // Read the input file
    rmolService.readFromInputFile (inputFileName);

  } else {
    // No input file has been provided. So, process a sample.
  
    // STEP 0.
    // List of demand distribution parameters (mean and standard deviation)

    // Class/bucket 1: N (20, 9), p1 = 100
    rmolService.addBucket (100.0, 20, 9);
    
    // Class/bucket 2: N (45, 12), p2 = 70
    rmolService.addBucket (70.0, 45, 12);

    // Class/bucket 3: no need to define a demand distribution, p3 = 42
    rmolService.addBucket (42.0, 0, 0);
  }
  
  // Calculate the optimal protections by the Monte Carlo Integration approach
  rmolService.optimalOptimisationByMCIntegration (K);
  
  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    return -1;
    
  } catch (...) {
    return -1;
  }
  
  return 0;	
}
