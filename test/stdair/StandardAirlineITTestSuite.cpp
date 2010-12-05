// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iostream>
#include <string>
// CPPUNIT
#include <extracppunit/CppUnitCore.hpp>
// StdAir Test Suite
#include <test/stdair/StdairTestLib.hpp>
#include <test/stdair/StandardAirlineITTestSuite.hpp>

// //////////////////////////////////////////////////////////////////////
void StandardAirlineITTestSuite::testServiceInitialisation() {
  CPPUNIT_ASSERT_NO_THROW ( StdairTestLib::testServiceInitialisation(); );
}

// //////////////////////////////////////////////////////////////////////
void StandardAirlineITTestSuite::testMPLStructure() {
  CPPUNIT_ASSERT_NO_THROW ( StdairTestLib::testMPLStructure(); );
}

// //////////////////////////////////////////////////////////////////////
void StandardAirlineITTestSuite::testBomStructureInstantiation() {
  CPPUNIT_ASSERT_NO_THROW ( StdairTestLib::testBomStructureInstantiation(); );
}

// //////////////////////////////////////////////////////////////////////
void StandardAirlineITTestSuite::testErrorCase () {
  const bool shouldBeFalse = StdairTestLib::testErrorCase();
  CPPUNIT_ASSERT ( shouldBeFalse );
}

// //////////////////////////////////////////////////////////////////////
StandardAirlineITTestSuite::StandardAirlineITTestSuite () {
  _describeKey << "Running test on StdAir initialisation";  
}

// /////////////// M A I N /////////////////
CPPUNIT_MAIN()
