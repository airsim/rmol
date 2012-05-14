// STL
#include <sstream>
// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>

class OptimiseForQFFTestSuite : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE (OptimiseForQFFTestSuite);
  CPPUNIT_TEST (testOptimiseForQFFMC);
  CPPUNIT_TEST (testOptimiseForQFFEMSRb);
  //  CPPUNIT_TEST (errorCase);
  CPPUNIT_TEST_SUITE_END ();
public:

  /** Test the Monte-Carlo (MC) Optimisation functionality. */
  void testOptimiseForQFFMC();

  /** Test the Expected Marginal Seat Revenue, variant b (EMSR-b),
      Optimisation functionality. */
  void testOptimiseForQFFEMSRb();

  /** Test some error detection functionalities. */
  //  void errorCase ();

  /** Constructor. */
  OptimiseForQFFTestSuite ();
  
protected:
  std::stringstream _describeKey;
};

CPPUNIT_TEST_SUITE_REGISTRATION (OptimiseForQFFTestSuite);
