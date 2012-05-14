// STL
#include <sstream>
// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>

class MRTForNewQFFTestSuite : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE (MRTForNewQFFTestSuite);
  CPPUNIT_TEST (testMRTForNewQFF);
  //  CPPUNIT_TEST (errorCase);
  CPPUNIT_TEST_SUITE_END ();
public:

  /** Test the Monte-Carlo (MC) Optimisation functionality. */
  void testMRTForNewQFF();

  /** Test some error detection functionalities. */
  //  void errorCase ();

  /** Constructor. */
  MRTForNewQFFTestSuite ();
  
protected:
  std::stringstream _describeKey;
};

CPPUNIT_TEST_SUITE_REGISTRATION (MRTForNewQFFTestSuite);
