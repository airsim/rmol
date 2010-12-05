// STL
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
// CPPUNIT
#include <extracppunit/CppUnitCore.hpp>
// RMOL
#include <rmol/RMOL_Service.hpp>
#include <rmol/RMOL_Types.hpp>
#include <rmol/RMOL_FORECASTER_Types.hpp>
// RMOL Test Suite
#include <test/rmol/ForecasterTestSuite.hpp>

// //////////////////////////////////////////////////////////////////////
int testForecasterHelper (const unsigned short forecastingMethodFlag) {
  int passedTests = 0;
  try {

    // Output log File
    std::string lLogFilename ("ForecasterTestSuite.log");
    
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

    case 0 : // Calculate Q-equivalent demand 
	  {
       	rmolService.demandForecastByQForecasting (lForecastedDemandParameterList,
                                                  lHistoricalDataHolderHolder,
                                                  lPriceVector,
                                                  lSellupFactorHolder);
        // Verify the known mean is returned
        oDebugStr << "Case 0: Tested Q-Forecasting algorithm for the given example\n"
                  << "Before the test, the flag is " << passedTests << "\n";
        std::vector<double> demandParametersOfAClass = 
                                      lForecastedDemandParameterList.at(1);
        if (demandParametersOfAClass.at(0) == 10.8125) {passedTests = 1;};
        oDebugStr << "After the test, the flag is " << passedTests << "\n";
      	break;
	  }
    case 1 : 
      {
        oDebugStr << "Case 1: Tested  "
                  << "Before the test, the flag is " << passedTests << "\n";
        //
        oDebugStr << "After the test, the flag is " << passedTests << "\n";
        break;
      }

      
    default : 
      {
        rmolService.demandForecastByQForecasting (lForecastedDemandParameterList,
                                                  lHistoricalDataHolderHolder,
                                                  lPriceVector,
                                                  lSellupFactorHolder);
        oDebugStr << "Default case Tested Q-Forecasting algorithm for the given example\n"
                  << "Before the test, the flag is " << passedTests << "\n";
        std::vector<double> demandParametersOfAClass = 
          lForecastedDemandParameterList.at(1);
        if (demandParametersOfAClass.at(0) == 10.8125) {passedTests = 1;};
        oDebugStr << "After the test, the flag is " << passedTests << "\n";
      }
    }
    logOutputFile << oDebugStr.str() << "\n";
    logOutputFile.close();
        
  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    
  } catch (...) {
    std::cerr << "Unknown exception" << std::endl;
  }

    return passedTests;
}

// //////////////////////////////////////////////////////////////////////
void ForecasterTestSuite::testQForecaster() {
   const int lTestSuccessFlag = testForecasterHelper(0);
   CPPUNIT_ASSERT (lTestSuccessFlag == 1);
}

// //////////////////////////////////////////////////////////////////////
ForecasterTestSuite::ForecasterTestSuite () {
  _describeKey << "Running test on RMOL Forecast function";  
}

// /////////////// M A I N /////////////////
CPPUNIT_MAIN()

