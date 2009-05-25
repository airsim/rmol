// STL
#include <fstream>
#include <string>
// CPPUNIT
#include <test/com/CppUnitCore.hpp>
// RMOL
#include <rmol/RMOL_Service.hpp>
#include <rmol/RMOL_Types.hpp>
// RMOL Test Suite
#include <test/OptimiseTestSuite.hpp>

// //////////////////////////////////////////////////////////////////////
void testOptimiseHelper(const unsigned short optimisationMethodFlag) {

  try {
    
    // Output log File
    std::string lLogFilename ("OptimiseTestSuite.log");
    
    // Number of random draws to be generated (best if greater than 100)
    const int K = 100000;
    
    // Methods of optimisation (0 = Monte-Carlo, 1 = Dynamic Programming, 
    // 2 = EMSR, 3 = EMSR-a, 4 = EMSR-b, 5 = EMSR-a with sellup prob.)
    const unsigned short METHOD_FLAG = optimisationMethodFlag;
    
    // Cabin Capacity (it must be greater then 100 here)
    const double cabinCapacity = 100.0;
    
    // Input file name
    const std::string inputFileName ("../samples/sample2.csv");
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

    case 5 : // Calculate the protection by EMSR-a with sellup
      {
        std::vector<double> sampleVector; 
        double sampleProbability = 0.2;
        // NOTE: size of sellup vector should be equal to no of buckets
        short nbOfSampleBucket = 4;
        for (short i = 1; i <= nbOfSampleBucket - 1; i++)
          sampleVector.push_back(sampleProbability);
        RMOL::SellupProbabilityVector_T& sellupProbabilityVector 
          = sampleVector;
        rmolService.heuristicOptimisationByEmsrAwithSellup (sellupProbabilityVector);
        break;
      }

    default : rmolService.optimalOptimisationByMCIntegration (K);
    }
    
  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    
  } catch (...) {
    std::cerr << "Unknown exception" << std::endl;
  }
}


// //////////////////////////////////////////////////////////////////////
// Monte-Carlo (MC)
void OptimiseTestSuite::testOptimiseMC() {
  CPPUNIT_ASSERT_NO_THROW (testOptimiseHelper(0););
}

// //////////////////////////////////////////////////////////////////////
// Dynamic Programming (DP)
void OptimiseTestSuite::testOptimiseDP() {
  CPPUNIT_ASSERT_NO_THROW (testOptimiseHelper(1););
}

// //////////////////////////////////////////////////////////////////////
// EMSR
void OptimiseTestSuite::testOptimiseEMSR() {
  CPPUNIT_ASSERT_NO_THROW (testOptimiseHelper(2););
}

// //////////////////////////////////////////////////////////////////////
// EMSR-a
void OptimiseTestSuite::testOptimiseEMSRa() {
  CPPUNIT_ASSERT_NO_THROW (testOptimiseHelper(3););
}

// //////////////////////////////////////////////////////////////////////
// EMSR-b
void OptimiseTestSuite::testOptimiseEMSRb() {
  CPPUNIT_ASSERT_NO_THROW (testOptimiseHelper(4););
}

// //////////////////////////////////////////////////////////////////////
// EMSR-a with sell-up
void OptimiseTestSuite::testOptimiseEMSRaWithSU() {
  CPPUNIT_ASSERT_NO_THROW (testOptimiseHelper(5););
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
