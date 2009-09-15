// STL
#include <sstream>
// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>

class SimulateTestSuite : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE (SimulateTestSuite);
  CPPUNIT_TEST (testSimulate);
  //  CPPUNIT_TEST (errorCase);
  CPPUNIT_TEST_SUITE_END ();
public:

  /** Test the Simulation functionality. */
  void testSimulate ();

  /** Test some error detection functionalities. */
  //  void errorCase ();

  /** Constructor. */
  SimulateTestSuite ();
  
protected:
  std::stringstream _describeKey;
};
CPPUNIT_TEST_SUITE_REGISTRATION (SimulateTestSuite);
