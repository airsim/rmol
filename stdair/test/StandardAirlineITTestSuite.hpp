// STL
#include <sstream>
// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>

class StandardAirlineITTestSuite : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE (StandardAirlineITTestSuite);
  CPPUNIT_TEST (testStandardAirlineIT);
  //  CPPUNIT_TEST (errorCase);
  CPPUNIT_TEST_SUITE_END ();
public:

  /** Test the Standard Airline IT base library. */
  void testStandardAirlineIT ();

  /** Test some error detection functionalities. */
  //  void errorCase ();

  /** Constructor. */
  StandardAirlineITTestSuite ();
  
protected:
  std::stringstream _describeKey;
};
CPPUNIT_TEST_SUITE_REGISTRATION (StandardAirlineITTestSuite);
