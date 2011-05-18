/*!
 * \page YieldTestSuite_cpp Command-Line Test to Demonstrate How To Test the AirRAC Project
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
#define BOOST_TEST_MODULE YieldTestSuite
#include <boost/test/unit_test.hpp>
// StdAir
#include <stdair/basic/BasLogParams.hpp>
#include <stdair/basic/BasDBParams.hpp>
#include <stdair/basic/BasFileMgr.hpp>
#include <stdair/bom/TravelSolutionStruct.hpp>
#include <stdair/service/Logger.hpp>
// Airrac
#include <airrac/AIRRAC_Service.hpp>
#include <airrac/config/airrac-paths.hpp>

namespace boost_utf = boost::unit_test;

// (Boost) Unit Test XML Report
std::ofstream utfReportStream ("YieldTestSuite_utfresults.xml");

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


// /////////////// Main: Unit Test Suite //////////////

// Set the UTF configuration (re-direct the output to a specific file)
BOOST_GLOBAL_FIXTURE (UnitTestConfig);

// Start the test suite
BOOST_AUTO_TEST_SUITE (master_test_suite)

/**
 * Test a simple inventory sell
 */
BOOST_AUTO_TEST_CASE (airrac_simple_yield) {
    
  // Travel solution
  stdair::TravelSolutionStruct lTravelSolution;
  stdair::TravelSolutionList_T lTravelSolutionList;
    
  // Input file name
  const stdair::Filename_T lYieldInputFilename (STDAIR_SAMPLE_DIR
                                                "/yieldstore01.csv");

  // Check that the file path given as input corresponds to an actual file
  bool doesExistAndIsReadable =
    stdair::BasFileMgr::doesExistAndIsReadable (lYieldInputFilename);
  BOOST_CHECK_MESSAGE (doesExistAndIsReadable == true,
                       "The '" << lYieldInputFilename
                       << "' input file can not be open and read");

  // Output log File
  const stdair::Filename_T lLogFilename ("YieldTestSuite.log");
  
  // Set the log parameters
  std::ofstream logOutputFile;
  // Open and clean the log outputfile
  logOutputFile.open (lLogFilename.c_str());
  logOutputFile.clear();
  
  // Initialise the list of classes/buckets
  const stdair::BasLogParams lLogParams (stdair::LOG::DEBUG, logOutputFile);
  AIRRAC::AIRRAC_Service airracService (lLogParams, lYieldInputFilename);
  
  // Calculate the yields for the given travel solution
  lTravelSolutionList.push_back(lTravelSolution);
  airracService.calculateYields (lTravelSolutionList);

  // Close the log file
  logOutputFile.close();
}

// End the test suite
BOOST_AUTO_TEST_SUITE_END()

/*!
 * \endcode
 */

