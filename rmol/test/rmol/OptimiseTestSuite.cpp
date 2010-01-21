// STL
#include <fstream>
#include <string>
// CPPUNIT
#include <extracppunit/CppUnitCore.hpp>
// RMOL
#include <rmol/RMOL_Service.hpp>
#include <rmol/RMOL_Types.hpp>
// RMOL Test Suite
#include <test/rmol/OptimiseTestSuite.hpp>

// //////////////////////////////////////////////////////////////////////
int testOptimiseHelper (const unsigned short optimisationMethodFlag) {

  // Return value
  int oExpectedBookingLimit = 0;

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
    const std::string inputFileName ("../samples/rm02.csv");
    const bool hasInputFile = true;
    
    // Set the log parameters
    std::ofstream logOutputFile;
    // Open and clean the log outputfile
    logOutputFile.open (lLogFilename.c_str());
    logOutputFile.clear();
    
    // Initialise the RMOL service
    const stdair::BasLogParams lLogParams (stdair::LOG::DEBUG, logOutputFile);
    const stdair::AirlineCode_T lAirlineCode ("BA");
    RMOL::RMOL_Service rmolService (lLogParams, lAirlineCode, cabinCapacity);
    rmolService.setUpStudyStatManager();
    
    // Define bid price and booking Limit vectors
    RMOL::BidPriceVector_T lBidPriceVector;
    RMOL::ProtectionLevelVector_T lProtectionLevelVector;
    RMOL::BookingLimitVector_T lBookingLimitVector;

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
    case 0 : {
      // Calculate the optimal protections by the Monte Carlo
      // Integration approach        
      rmolService.optimalOptimisationByMCIntegration (K);
      break;
    }
      
    case 1 : {
      // Calculate the optimal protections by DP.
      rmolService.optimalOptimisationByDP ();
      break;
    }
      
    case 2 : {
      // Calculate the Bid-Price Vector by EMSR
      rmolService.heuristicOptimisationByEmsr ();
      break;
    }
      
    case 3 : {
      // Calculate the protections by EMSR-a
      // Test the EMSR-a algorithm implementation
      rmolService.heuristicOptimisationByEmsrA (lBidPriceVector, 
                                                lProtectionLevelVector,
                                                lBookingLimitVector);

      // Return a cumulated booking limit value to test
      oExpectedBookingLimit = static_cast<int> (lBookingLimitVector.at(2));
      break;
    }
      
    case 4 : {
      // Calculate the protections by EMSR-b
      rmolService.heuristicOptimisationByEmsrB ();
      break;
    }
      
    case 5 : {
      // Calculate the protection by EMSR-a with sellup
      // Create an empty sell-up probability vector
      std::vector<double> sellupProbabilityVector; 
      
      // Define the sell-up probability to be 20%
      const double sampleProbability = 0.2;
      
      // NOTE: size of sellup vector should be equal to no of buckets - 1
      // TODO: check that with an assertion
      const short nbOfSampleBucket = 4;
      for (short i = 1; i <= nbOfSampleBucket - 1; i++) {
        sellupProbabilityVector.push_back (sampleProbability);
      }
      
      // Test the algorithm with the sample sell-up vector
      rmolService.heuristicOptimisationByEmsrAwithSellup 
        (sellupProbabilityVector, lProtectionLevelVector, 
         lBidPriceVector, lBookingLimitVector);
      
      // Return a cumulated booking limit value to test
      oExpectedBookingLimit = static_cast<int> (lBookingLimitVector.at(2));
      
      break;
    }

    default: rmolService.optimalOptimisationByMCIntegration (K);
    }
        
  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    
  } catch (...) {
    std::cerr << "Unknown exception" << std::endl;
  }

  return oExpectedBookingLimit;
}


// //////////////////////////////////////////////////////////////////////
// Test is based on the following inputs values
// price; mean; standard deviation;
// 1050; 17.3; 5.8;
// 567; 45.1; 15.0;
// 534; 39.6; 13.2;
// 520; 34.0; 11.3;
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
  const int lExpectedBookingLimit = testOptimiseHelper(3);
  CPPUNIT_ASSERT (lExpectedBookingLimit == 61);
}

// //////////////////////////////////////////////////////////////////////
// EMSR-b
void OptimiseTestSuite::testOptimiseEMSRb() {
  CPPUNIT_ASSERT_NO_THROW (testOptimiseHelper(4););
}

// //////////////////////////////////////////////////////////////////////
// EMSR-a with sell-up
void OptimiseTestSuite::testOptimiseEMSRaWithSU() {
  const int lExpectedBookingLimit = testOptimiseHelper(5);
  CPPUNIT_ASSERT(lExpectedBookingLimit == 59);
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

