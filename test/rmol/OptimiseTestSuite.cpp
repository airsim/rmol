/*!
 * \page OptimiseTestSuite_cpp Command-Line Test to Demonstrate How To Test the RMOL Project
 * \code
 */
// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <sstream>
#include <fstream>
#include <string>
// Boost Unit Test Framework (UTF)
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE OptimiseTestSuite
#include <boost/test/unit_test.hpp>
// StdAir
#include <stdair/basic/BasLogParams.hpp>
#include <stdair/basic/BasDBParams.hpp>
#include <stdair/basic/BasFileMgr.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/basic/BasConst_General.hpp>
#include <rmol/RMOL_Service.hpp>
#include <rmol/config/rmol-paths.hpp>

namespace boost_utf = boost::unit_test;

// (Boost) Unit Test XML Report
std::ofstream utfReportStream ("OptimiseTestSuite_utfresults.xml");

/**
 * Configuration for the Boost Unit Test Framework (UTF)
 */
struct UnitTestConfig {
  /** Constructor. */
  UnitTestConfig() {
    boost_utf::unit_test_log.set_stream (utfReportStream);
    boost_utf::unit_test_log.set_format (boost_utf::XML);
    boost_utf::unit_test_log.set_threshold_level (boost_utf::log_test_units);
    //boost_utf::unit_test_log.set_threshold_level (boost_utf::log_successful_tests);
  }

  /** Destructor. */
  ~UnitTestConfig() {
  }
};


// //////////////////////////////////////////////////////////////////////
int testOptimiseHelper (const unsigned short optimisationMethodFlag,
                        const bool isBuiltin) {

  // Return value
  int oExpectedBookingLimit = 0;

  // Output log File
  std::ostringstream oStr;
  oStr << "OptimiseTestSuite_" << optimisationMethodFlag << "_" << isBuiltin << ".log";
  const stdair::Filename_T lLogFilename (oStr.str());
    
  // Number of random draws to be generated (best if greater than 100)
  const int K = RMOL::DEFAULT_NUMBER_OF_DRAWS_FOR_MC_SIMULATION;
    
  // Methods of optimisation (0 = Monte-Carlo, 1 = Dynamic Programming, 
  // 2 = EMSR, 3 = EMSR-a, 4 = EMSR-b, 5 = EMSR-a with sellup prob.)
  const unsigned short METHOD_FLAG = optimisationMethodFlag;
    
  // Cabin Capacity (it must be greater then 100 here)
  const double cabinCapacity = 100.0;
    
  // Set the log parameters
  std::ofstream logOutputFile;
  // Open and clean the log outputfile
  logOutputFile.open (lLogFilename.c_str());
  logOutputFile.clear();
    
  // Initialise the RMOL service
  const stdair::BasLogParams lLogParams (stdair::LOG::DEBUG, logOutputFile);
  RMOL::RMOL_Service rmolService (lLogParams);

  // Check wether or not a (CSV) input file should be read
  if (isBuiltin == true) {

    // Build the default sample BOM tree and build a dummy BOM tree.
    rmolService.buildSampleBom();

  } else {

    // Parse the optimisation data and build a dummy BOM tree 
    const stdair::Filename_T lRMInputFileName (STDAIR_SAMPLE_DIR "/rm02.csv");
    rmolService.parseAndLoad (cabinCapacity, lRMInputFileName);
  }

  switch (METHOD_FLAG) {
  case 0: {
    // DEBUG
    STDAIR_LOG_DEBUG ("Optimisation by Monte-Carlo (MC)");

    // Calculate the optimal protections by the Monte Carlo
    // Integration approach        
    rmolService.optimalOptimisationByMCIntegration (K);
    break;
  }
      
  case 1: {
    // DEBUG
    STDAIR_LOG_DEBUG ("Optimisation by Dynamic Programming (DP)");
    
    // Calculate the optimal protections by DP.
    rmolService.optimalOptimisationByDP ();
    break;
  }
      
  case 2: {
    // DEBUG
    STDAIR_LOG_DEBUG ("Calculate the Bid-Price Vectors (BPV) by EMSR");
    
    // Calculate the Bid-Price Vector by EMSR
    rmolService.heuristicOptimisationByEmsr ();
    break;
  }
      
  case 3: {
    // DEBUG
    STDAIR_LOG_DEBUG ("Calculate the Authorisation Levels (AUs) by EMSRa");
    
    // Calculate the protections by EMSR-a
    // Test the EMSR-a algorithm implementation
    rmolService.heuristicOptimisationByEmsrA ();

    // Return a cumulated booking limit value to test
    // oExpectedBookingLimit = static_cast<int> (lBookingLimitVector.at(2));
    break;
  }
      
  case 4: {
    // DEBUG
    STDAIR_LOG_DEBUG ("Calculate the Authorisation Levels (AUs) by EMSRb");
    
    // Calculate the protections by EMSR-b
    rmolService.heuristicOptimisationByEmsrB ();
    break;
  }

  default: rmolService.optimalOptimisationByMCIntegration (K);
  }
        
  // Close the log file
  logOutputFile.close();
  
  return oExpectedBookingLimit;
}


// /////////////// Main: Unit Test Suite //////////////

// Set the UTF configuration (re-direct the output to a specific file)
BOOST_GLOBAL_FIXTURE (UnitTestConfig);

// //////////////////////////////////////////////////////////////////////
// Tests are based on the following input values
// price; mean; standard deviation;
// 1050; 17.3; 5.8;
// 567; 45.1; 15.0;
// 534; 39.6; 13.2;
// 520; 34.0; 11.3;
// //////////////////////////////////////////////////////////////////////

/**
 * Test different a suite of different revenue management optimisation
 * pieces of algorithm.
 */
BOOST_AUTO_TEST_SUITE (master_test_suite)

/**
 * Test the Monte-Carlo (MC) algorithm
 */
BOOST_AUTO_TEST_CASE (rmol_optimisation_monte_carlo) {
  
  // State whether the BOM tree should be built-in or parsed from an input file
  const bool isBuiltin = false;
  
  BOOST_CHECK_NO_THROW (testOptimiseHelper(0, isBuiltin););
}

/**
 * Test the Dynamic Programming (DP) algorithm
 */
BOOST_AUTO_TEST_CASE (rmol_optimisation_dynamic_programming) {
  
  // State whether the BOM tree should be built-in or parsed from an input file
  const bool isBuiltin = false;
  
  BOOST_CHECK_NO_THROW (testOptimiseHelper(1, isBuiltin););
}

/**
 * Test the calculation of Bid-Price Vectors (BPV) thanks to the
 * Expected Marginal Seat Revenue (EMSR) algorithm
 */
BOOST_AUTO_TEST_CASE (rmol_optimisation_emsr_bpv) {
  
  // State whether the BOM tree should be built-in or parsed from an input file
  const bool isBuiltin = false;
  
  BOOST_CHECK_NO_THROW (testOptimiseHelper(2, isBuiltin););
}

/**
 * Test the calculation of Authorisation levels (AU) thanks to the
 * Expected Marginal Seat Revenue (EMSRa) algorithm
 */
BOOST_AUTO_TEST_CASE (rmol_optimisation_emsr_a) {

  // State whether the BOM tree should be built-in or parsed from an input file
  const bool isBuiltin = false;
  
  BOOST_CHECK_NO_THROW (testOptimiseHelper(3, isBuiltin););
  // const int lBookingLimit = testOptimiseHelper(3);
  // const int lExpectedBookingLimit = 61;
  // BOOST_CHECK_EQUAL (lBookingLimit, lExpectedBookingLimit);
  // BOOST_CHECK_MESSAGE (lBookingLimit == lExpectedBookingLimit,
  //                      "The booking limit is " << lBookingLimit
  //                      << ", but it is expected to be "
  //                      << lExpectedBookingLimit);
}

/**
 * Test the calculation of Authorisation levels (AU) thanks to the
 * Expected Marginal Seat Revenue (EMSRb) algorithm
 */
BOOST_AUTO_TEST_CASE (rmol_optimisation_emsr_b) {

  // State whether the BOM tree should be built-in or parsed from an input file
  const bool isBuiltin = false;
  
  BOOST_CHECK_NO_THROW (testOptimiseHelper(4, isBuiltin););
}

/**
 * Test the Monte-Carlo (MC) algorithm with the built-in BOM tree.
 */
BOOST_AUTO_TEST_CASE (rmol_optimisation_monte_carlo_built_in) {
  
  // State whether the BOM tree should be built-in or parsed from an input file
  const bool isBuiltin = true;
  
  BOOST_CHECK_NO_THROW (testOptimiseHelper(0, isBuiltin););
}

/**
 * Test the Dynamic Programming (DP) algorithm with the built-in BOM tree.
 */
BOOST_AUTO_TEST_CASE (rmol_optimisation_dynamic_programming_built_in) {
  
  // State whether the BOM tree should be built-in or parsed from an input file
  const bool isBuiltin = true;
  
  BOOST_CHECK_NO_THROW (testOptimiseHelper(1, isBuiltin););
}

/**
 * Test the calculation of Bid-Price Vectors (BPV) thanks to the
 * Expected Marginal Seat Revenue (EMSR) algorithm with the built-in BOM tree.
 */
BOOST_AUTO_TEST_CASE (rmol_optimisation_emsr_bpv_built_in) {
  
  // State whether the BOM tree should be built-in or parsed from an input file
  const bool isBuiltin = true;
  
  BOOST_CHECK_NO_THROW (testOptimiseHelper(2, isBuiltin););
}

/**
 * Test the calculation of Authorisation levels (AU) thanks to the
 * Expected Marginal Seat Revenue (EMSRa) algorithm with the built-in BOM tree.
 */
BOOST_AUTO_TEST_CASE (rmol_optimisation_emsr_a_built_in) {

  // State whether the BOM tree should be built-in or parsed from an input file
  const bool isBuiltin = true;
  
  BOOST_CHECK_NO_THROW (testOptimiseHelper(3, isBuiltin););
}

/**
 * Test the calculation of Authorisation levels (AU) thanks to the
 * Expected Marginal Seat Revenue (EMSRb) algorithm with the built-in BOM tree.
 */
BOOST_AUTO_TEST_CASE (rmol_optimisation_emsr_b_built_in) {

  // State whether the BOM tree should be built-in or parsed from an input file
  const bool isBuiltin = true;
  
  BOOST_CHECK_NO_THROW (testOptimiseHelper(4, isBuiltin););
}

// End the test suite
BOOST_AUTO_TEST_SUITE_END()

/*!
 * \endcode
 */
