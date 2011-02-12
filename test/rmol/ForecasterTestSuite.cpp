/*!
 * \page ForecasterTestSuite_cpp Command-Line Test to Demonstrate How To Test the RMOL Project
 * \code
 */
// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
// Boost Unit Test Framework (UTF)
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE ForecasterTestSuite
#include <boost/test/unit_test.hpp>
// StdAir
#include <stdair/basic/BasLogParams.hpp>
#include <stdair/basic/BasDBParams.hpp>
#include <stdair/basic/BasFileMgr.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/RMOL_Service.hpp>
#include <rmol/RMOL_FORECASTER_Types.hpp>

namespace boost_utf = boost::unit_test;

// (Boost) Unit Test XML Report
std::ofstream utfReportStream ("ForecasterTestSuite_utfresults.xml");

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
bool testForecasterHelper (const unsigned short forecastingMethodFlag) {
  bool oPassedTests = false;

  // Output log File
  const stdair::Filename_T lLogFilename ("ForecasterTestSuite.log");
    
  // Methods of forecasting (0 = Q-Forecasting)
  const unsigned short METHOD_FLAG = forecastingMethodFlag;
  
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
  
  // A sample historical demand data to be processed by forecaster
  // Class |  Q  |  M  |  B  |  Y  |
  // Price | 100 | 200 | 300 | 400 |
  // Historical uncensored demand data at a DCP
  //       | 10  |   5 |  0  |  0  | <- 2008/01/01
  //       |  0  |  10 |  0  |  0  | <- 2008/01/08
  //       |  0  |  12 |  0  |  0  | <- 2008/01/15
  //       |  0  |   0 |  5  |  2  | <- 2008/01/22
  // The order of the vectors: M, Q, Y, B 
  
  // Sample historical data vector
  RMOL::HistoricalDataHolderHolder_T lHistoricalDataHolderHolder;
  std::vector<double> azeroVector(3,0); // 3 copies of 0 element
  std::vector<double> sampleHistoricalDataHolder;
  
  // Historical data of M class
  sampleHistoricalDataHolder.push_back(5); 
  sampleHistoricalDataHolder.push_back(10);
  sampleHistoricalDataHolder.push_back(12); 
  sampleHistoricalDataHolder.push_back(0); 
  lHistoricalDataHolderHolder.push_back(sampleHistoricalDataHolder);
  
  // Historical data of Q class
  sampleHistoricalDataHolder = azeroVector;
  sampleHistoricalDataHolder.insert
    (sampleHistoricalDataHolder.begin(), 1, 10);
  lHistoricalDataHolderHolder.push_back(sampleHistoricalDataHolder);
    
  // Historical data of Y class
  sampleHistoricalDataHolder = azeroVector;
  sampleHistoricalDataHolder.insert
    (sampleHistoricalDataHolder.end(), 1, 2);
  lHistoricalDataHolderHolder.push_back(sampleHistoricalDataHolder);
    
  // Historical data of B class
  sampleHistoricalDataHolder = azeroVector;
  sampleHistoricalDataHolder.insert
    (sampleHistoricalDataHolder.end(), 1, 5);
  lHistoricalDataHolderHolder.push_back(sampleHistoricalDataHolder);

  // Sample price vector
  RMOL::PriceHolder_T lPriceVector;
  lPriceVector.push_back(200);
  lPriceVector.push_back(100);
  lPriceVector.push_back(400);
  lPriceVector.push_back(300);

  // Sample Sellup Factor Vector
  // that makes sell up probability of [Q,M,B,Y] = [1, 0.5, 0.4, 0.2]
  RMOL::SellupFactorHolder_T lSellupFactorHolder;
  lSellupFactorHolder.push_back(log(2));
  lSellupFactorHolder.push_back(1);
  lSellupFactorHolder.push_back(log(5)/3);
  lSellupFactorHolder.push_back(log(2.5)/2);

  // Forecaster output container 
  RMOL::ForecastedDemandParameterList_T lForecastedDemandParameterList;
  switch (METHOD_FLAG) {

  case 0: {
    // Calculate Q-equivalent demand 
    rmolService.demandForecastByQForecasting (lForecastedDemandParameterList,
                                              lHistoricalDataHolderHolder,
                                              lPriceVector,
                                              lSellupFactorHolder);

    //
    oDebugStr << "Case 0: Tested Q-Forecasting algorithm for the given example"
              << std::endl
              << "Before the test, the flag is " << oPassedTests << std::endl;

    // Verify the known mean is returned
    std::vector<double> demandParametersOfAClass = 
      lForecastedDemandParameterList.at(1);
    
    if (demandParametersOfAClass.at(0) == 10.8125) {
      oPassedTests = true;
    }

    //
    oDebugStr << "After the test, the flag is " << oPassedTests << std::endl;
    break;
  }
      
  case 1: {
    //
    oDebugStr << "Case 1: Tested  "
              << "Before the test, the flag is " << oPassedTests << std::endl;
    //
    oDebugStr << "After the test, the flag is " << oPassedTests << std::endl;
    break;
  }
      
  default: {
    //
    rmolService.demandForecastByQForecasting (lForecastedDemandParameterList,
                                              lHistoricalDataHolderHolder,
                                              lPriceVector,
                                              lSellupFactorHolder);

    //
    oDebugStr << "Default case Tested Q-Forecasting algorithm for the given example"
              << std::endl
              << "Before the test, the flag is " << oPassedTests << std::endl;

    std::vector<double> demandParametersOfAClass = 
      lForecastedDemandParameterList.at(1);

    if (demandParametersOfAClass.at(0) == 10.8125) {
      oPassedTests = true;
    }

    //
    oDebugStr << "After the test, the flag is " << oPassedTests << std::endl;
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
 * Test different a suite of different revenue management optimisation
 * pieces of algorithm.
 */
BOOST_AUTO_TEST_SUITE (master_test_suite)

/**
 * Test the Q-Forecasting algorithm
 */
BOOST_AUTO_TEST_CASE (rmol_forecaster_q_forecasting) {
  const bool lTestFlag = testForecasterHelper(0);
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
