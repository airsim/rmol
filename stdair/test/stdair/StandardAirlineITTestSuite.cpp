// STL
#include <iostream>
#include <string>
// CPPUNIT
#include <test/com/CppUnitCore.hpp>
// STDAIR
//#include <stdair/STDAIR_Service.hpp>
// STDAIR Test Suite
#include <test/stdair/StandardAirlineITTestSuite.hpp>

// //////////////////////////////////////////////////////////////////////
void testStandardAirlineITHelper() {

  try {
    
    // Output log File
    const std::string lLogFilename ("StandardAirlineITTestSuite.log");
    
    // Set the log parameters
    std::ofstream logOutputFile;

    // Open and clean the log outputfile
    logOutputFile.open (lLogFilename.c_str());
    logOutputFile.clear();
    
    // Initialise the stdair BOM
    // STDAIR::STDAIR_Service stdairService (logOutputFile);
    
  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    
  } catch (...) {
    std::cerr << "Unknown exception" << std::endl;
  }
}

// //////////////////////////////////////////////////////////////////////
void StandardAirlineITTestSuite::testStandardAirlineIT() {
  CPPUNIT_ASSERT_NO_THROW (testStandardAirlineITHelper(););
}

// //////////////////////////////////////////////////////////////////////
// void StandardAirlineITTestSuite::errorCase () {
//  CPPUNIT_ASSERT (false);
// }

// //////////////////////////////////////////////////////////////////////
StandardAirlineITTestSuite::StandardAirlineITTestSuite () {
  _describeKey << "Running test on STDAIR Optimisation function";  
}

// /////////////// M A I N /////////////////
CPPUNIT_MAIN()
