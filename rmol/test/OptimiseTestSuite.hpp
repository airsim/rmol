// STL
#include <sstream>
// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>

class OptimiseTestSuite : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE (OptimiseTestSuite);
  CPPUNIT_TEST (testOptimise);
  //  CPPUNIT_TEST (errorCase);
  CPPUNIT_TEST_SUITE_END ();
public:

  /** Test the Optimisation functionality. */
  void testOptimise ();

  /** Test some error detection functionalities. */
  //  void errorCase ();

  /** Constructor. */
  OptimiseTestSuite ();
  
protected:
  std::stringstream _describeKey;
};
CPPUNIT_TEST_SUITE_REGISTRATION (OptimiseTestSuite);
