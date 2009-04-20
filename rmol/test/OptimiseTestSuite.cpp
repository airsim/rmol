// STL
#include <iostream>
#include <string>
// CPPUNIT
#include <test/com/CppUnitCore.hpp>
// RMOL
#include <rmol/RMOL_Service.hpp>
// RMOL Test Suite
#include <test/OptimiseTestSuite.hpp>

// //////////////////////////////////////////////////////////////////////
void testOptimiseHelper() {

  try {
    
    // Output log File
    std::string lLogFilename ("OptimiseTestSuite.log");
    
    // Number of random draws to be generated (best if greater than 100)
    const int K = 100000;
    
    // Methods of optimisation (0 = Monte-Carlo, 1 = Dynamic Programming, 
    // 2 = EMSR, 3 = EMSR-a, 4 = EMSR-b)
    const short METHOD_FLAG = 0;
    
    // Cabin Capacity (it must be greater then 100 here)
    const double cabinCapacity = 100.0;
    
    // Input file name
    const std::string inputFileName ("samples/sample2.csv");
    const bool hasInputFile = true;
    
    // Set the log parameters
    std::ofstream logOutputFile;
    // open and clean the log outputfile
    logOutputFile.open (lLogFilename.c_str());
    logOutputFile.clear();
    
    // Initialise the list of classes/buckets
    RMOL::RMOL_Service rmolService (logOutputFile, cabinCapacity);
    
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
    
    switch (METHOD_FLAG) {

    case 0 : // Calculate the optimal protections by the Monte Carlo
             // Integration approach
      rmolService.optimalOptimisationByMCIntegration (K);
      break;

    case 1 : // Calculate the optimal protections by DP.
      rmolService.optimalOptimisationByDP ();
      break;
      
    case 2 : // Calculate the Bid-Price Vector by EMSR
      rmolService.heuristicOptimisationByEmsr ();
      break;

    case 3 : // Calculate the protections by EMSR-a
      rmolService.heuristicOptimisationByEmsrA ();
      break;
      
    case 4 : // Calculate the protections by EMSR-b
      rmolService.heuristicOptimisationByEmsrB ();
      break;

    default : rmolService.optimalOptimisationByMCIntegration (K);
    }
    
  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    
  } catch (...) {
    std::cerr << "Unknown exception" << std::endl;
  }
}

// //////////////////////////////////////////////////////////////////////
void OptimiseTestSuite::testOptimise() {
  CPPUNIT_ASSERT_NO_THROW (testOptimiseHelper(););
}

// //////////////////////////////////////////////////////////////////////
// void OptimiseTestSuite::errorCase () {
//  CPPUNIT_ASSERT (false);
// }

// //////////////////////////////////////////////////////////////////////
OptimiseTestSuite::OptimiseTestSuite () {
  _describeKey << "Running test on RMOL Optimisation function";  
}

// /////////////// M A I N /////////////////
CPPUNIT_MAIN()
