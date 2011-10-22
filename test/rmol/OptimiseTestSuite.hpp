// STL
#include <sstream>
// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>

class OptimiseTestSuite : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE (OptimiseTestSuite);
  CPPUNIT_TEST (testOptimiseMC);
  CPPUNIT_TEST (testOptimiseDP);
  CPPUNIT_TEST (testOptimiseEMSR);
  CPPUNIT_TEST (testOptimiseEMSRa);
  CPPUNIT_TEST (testOptimiseEMSRb);
  CPPUNIT_TEST (testOptimiseEMSRaWithSU);
  //  CPPUNIT_TEST (errorCase);
  CPPUNIT_TEST_SUITE_END ();
public:

  /** Test the Monte-Carlo (MC) Optimisation functionality. */
  void testOptimiseMC();

  /** Test the Dynamic Programming (DP) Optimisation functionality. */
  void testOptimiseDP();

  /** Test the Expected Marginal Seat Revenue (EMSR) Optimisation
      functionality. */
  void testOptimiseEMSR();

  /** Test the Expected Marginal Seat Revenue, variant a (EMSR-a),
      Optimisation functionality. */
  void testOptimiseEMSRa();

  /** Test the Expected Marginal Seat Revenue, variant b (EMSR-b),
      Optimisation functionality. */
  void testOptimiseEMSRb();

  /** Test some error detection functionalities. */
  //  void errorCase ();

  /** Constructor. */
  OptimiseTestSuite ();
  
protected:
  std::stringstream _describeKey;
};

CPPUNIT_TEST_SUITE_REGISTRATION (OptimiseTestSuite);
