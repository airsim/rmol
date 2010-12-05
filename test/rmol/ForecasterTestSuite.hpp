// STL
#include <sstream>
// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>

class ForecasterTestSuite : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE (ForecasterTestSuite);
  CPPUNIT_TEST (testQForecaster);
  CPPUNIT_TEST_SUITE_END ();
public:

  /** Test Q-forecaster. */
  void testQForecaster();

  /** Constructor. */
  ForecasterTestSuite ();
  
protected:
  std::stringstream _describeKey;
};

CPPUNIT_TEST_SUITE_REGISTRATION (ForecasterTestSuite);
