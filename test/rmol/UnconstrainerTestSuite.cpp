/*!
 * \page UnconstrainerTestSuite_cpp Command-Line Test to Demonstrate How To Test the RMOL Project
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
#define BOOST_TEST_MODULE UnconstrainerTestSuite
#include <boost/test/unit_test.hpp>
// StdAir
#include <stdair/basic/BasLogParams.hpp>
#include <stdair/basic/BasDBParams.hpp>
#include <stdair/basic/BasFileMgr.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/RMOL_Service.hpp>
#include <rmol/RMOL_UNCONSTRAINER_Types.hpp>
#include <rmol/RMOL_UTILITY_Types.hpp>

namespace boost_utf = boost::unit_test;

// (Boost) Unit Test XML Report
std::ofstream utfReportStream ("UnconstrainerTestSuite_utfresults.xml");

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
bool testUnconstrainerHelper (const unsigned short unconstrainingMethodFlag) {
  bool oPassedTests = false;
  
  // Output log File
  const stdair::Filename_T lLogFilename ("UnconstrainerTestSuite.log");
    
  // Methods of unconstraining: 
  // 0 = Unconstraining by Expectation Maximization
  const unsigned short METHOD_FLAG = unconstrainingMethodFlag;
    
  // Set the log parameters
  std::ofstream logOutputFile;
  // Open and clean the log outputfile
  logOutputFile.open (lLogFilename.c_str());
  logOutputFile.clear();
  std::ostringstream oDebugStr;

  // Initialise the RMOL service
  const stdair::BasLogParams lLogParams (stdair::LOG::DEBUG, logOutputFile);
  const stdair::AirlineCode_T lAirlineCode ("BA");
  RMOL::RMOL_Service rmolService (lLogParams, lAirlineCode);
    
  // A sample historical booking data to be processed by unconstrainer
  RMOL::ConstrainedDataHolder_T lConstrainedDataHolder;
  lConstrainedDataHolder.push_back(3);
  
  RMOL::UnconstrainedDataHolder_T lUnconstrainedDataHolder;
  lUnconstrainedDataHolder.push_back(4);
  lUnconstrainedDataHolder.push_back(3);
  lUnconstrainedDataHolder.push_back(7);
  lUnconstrainedDataHolder.push_back(5);

  // Sample price vector
  RMOL::StoppingCriterion_T lStoppingCriterion = 0.0001;

  switch (METHOD_FLAG) {

  case 0: {

    // Calculate expected unconstrained value of constrained data 
    rmolService.dataUnconstrainingByExpectationMaximization
      (lConstrainedDataHolder, lUnconstrainedDataHolder, lStoppingCriterion);

    // Verify if the test returned expected values
    oDebugStr << "Test Case 0: EM unconstraining method for a given example"
              << std::endl
              << "Before the test, the flag is " << oPassedTests << std::endl;
    if ( lConstrainedDataHolder.at(0) > 5.142 && 
         lConstrainedDataHolder.at(0) < 5.143) {
      oPassedTests = 1;
    }

    /*
    for (unsigned int k = 0; k < lConstrainedDataHolder.size(); k++) {
      std::vector<double> demandParametersOfAClass = 
        lForecastedDemandParameterList.at(k);
      if (k == 1 && demandParametersOfAClass.at(0) == 10.8125) {
        oPassedTests = 1;
      }
    }
    */
    
    oDebugStr << "After the test, the flag is " << oPassedTests << std::endl;
    break;
  }
    
  case 1: {
    oDebugStr << "Test Case 1: "
              << "Before the test, the flag is " << oPassedTests << std::endl;
    //
    oDebugStr << "After the test, the flag is " << oPassedTests << std::endl;
    break;
  }
    
    
  default: {
  }
  }
  
  logOutputFile << oDebugStr.str() << std::endl;
        
  // Close the log file
  logOutputFile.close();
  
  return oPassedTests;
}


// /////////////// Main: Unit Test Suite //////////////

// Set the UTF configuration (re-direct the output to a specific file)
BOOST_GLOBAL_FIXTURE (UnitTestConfig);

/**
 * Test different a suite of different revenue management unconstraining
 * pieces of algorithm.
 */
BOOST_AUTO_TEST_SUITE (master_test_suite)

/**
 * Test the Expectation-Maximisation (EM) algorithm
 */
BOOST_AUTO_TEST_CASE (rmol_unconstraining_em) {
  const bool lTestFlag = testUnconstrainerHelper(0);
  BOOST_CHECK_EQUAL (lTestFlag, true);
  BOOST_CHECK_MESSAGE (lTestFlag == true,
                       "The test has failed. Please see the log file for "
                       << "more details");
}

// End the test suite
BOOST_AUTO_TEST_SUITE_END()

/*!
 * \endcode
 */
