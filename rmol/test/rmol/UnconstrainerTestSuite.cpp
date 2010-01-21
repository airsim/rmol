// STL
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
// CPPUNIT
#include <extracppunit/CppUnitCore.hpp>
// RMOL
#include <rmol/RMOL_Service.hpp>
#include <rmol/RMOL_Types.hpp>
#include <rmol/RMOL_UNCONSTRAINER_Types.hpp>
#include <rmol/RMOL_UTILITY_Types.hpp>
// RMOL Test Suite
#include <test/rmol/UnconstrainerTestSuite.hpp>

// //////////////////////////////////////////////////////////////////////
int testUnconstrainerHelper (const unsigned short unconstrainingMethodFlag) {
  int passedTests = 0;
  try {

    // Output log File
    std::string lLogFilename ("UnconstrainerTestSuite.log");
    
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

    case 0 : // Calculate expected unconstrained value of constrained data 
	  {
       	rmolService.dataUnconstrainingByExpectationMaximization
        (lConstrainedDataHolder, lUnconstrainedDataHolder, lStoppingCriterion);

        // Verify if the test returned expected values
        oDebugStr << "Test Case 0: EM unconstraining method for a given example\n"
                  << "Before the test, the flag is " << passedTests << "\n";
        if ( lConstrainedDataHolder.at(0) > 5.142 && 
             lConstrainedDataHolder.at(0) < 5.143) {
          passedTests = 1;
        }
        // for (unsigned int k = 0; k < lConstrainedDataHolder.size(); k++) {
        //   std::vector<double> demandParametersOfAClass = 
        //                       lForecastedDemandParameterList.at(k);
        //   if (k == 1 && demandParametersOfAClass.at(0) == 10.8125) {passedTests = 1;};
        // }
        oDebugStr << "After the test, the flag is " << passedTests << "\n";
      	break;
	  }
    case 1 : 
      {
        oDebugStr << "Test Case 1: "
                  << "Before the test, the flag is " << passedTests << "\n";
        //
        oDebugStr << "After the test, the flag is " << passedTests << "\n";
        break;
      }

      
    default : 
      {
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
void UnconstrainerTestSuite::testUnconstrainingByEM() {
   const int lTestSuccessFlag = testUnconstrainerHelper(0);
   CPPUNIT_ASSERT (lTestSuccessFlag == 1);
}

// //////////////////////////////////////////////////////////////////////
UnconstrainerTestSuite::UnconstrainerTestSuite () {
  _describeKey << "Running tests on RMOL data unconstraining methods";  
}

// /////////////// M A I N /////////////////
CPPUNIT_MAIN()

