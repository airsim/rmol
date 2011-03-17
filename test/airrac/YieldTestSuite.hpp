// STL
#include <iosfwd>
// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>

/** Utility class for CPPUnit-based testing. */
class YieldTestSuite : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE (YieldTestSuite);
  CPPUNIT_TEST (simpleYield);
  //  CPPUNIT_TEST (errorCase);
  CPPUNIT_TEST_SUITE_END ();
public:

  /** Test a simple yield functionality. */
  void simpleYield();

  /** Test some error detection functionalities. */
  //  void errorCase ();

  /** Constructor. */
  YieldTestSuite ();
  
private:
  /** Test a simple yield functionality. */
  void simpleYieldHelper();

protected:
  std::stringstream _describeKey;
};

CPPUNIT_TEST_SUITE_REGISTRATION (YieldTestSuite);
