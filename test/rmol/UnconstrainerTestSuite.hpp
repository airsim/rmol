// STL
#include <sstream>
// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>

class UnconstrainerTestSuite : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE (UnconstrainerTestSuite);
  CPPUNIT_TEST (testUnconstrainingByEM);
  CPPUNIT_TEST_SUITE_END ();
public:

  /** Test data unconstraining by Expectation Maximization. */
  void testUnconstrainingByEM();

  /** Constructor. */
  UnconstrainerTestSuite ();
  
protected:
  std::stringstream _describeKey;
};

CPPUNIT_TEST_SUITE_REGISTRATION (UnconstrainerTestSuite);
