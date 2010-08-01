// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>

/**
 * Class wrapping test functions
 */
class StandardAirlineITTestSuite : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE (StandardAirlineITTestSuite);
  CPPUNIT_TEST (testServiceInitialisation);
  CPPUNIT_TEST (testMPLStructure);
  CPPUNIT_TEST (testBomStructureInstantiation);
  //  CPPUNIT_TEST (testErrorCase);
  CPPUNIT_TEST_SUITE_END ();
public:

  /**
   * Test MPL-based type handling, just as a proof-of-concept. It does
   * not use StdAir BOM.
   */
  void testServiceInitialisation();

  /**
   * Test MPL-based type handling, just as a proof-of-concept. It does
   * not use StdAir BOM.
   */
  void testMPLStructure();

  /**
   * Test the initialisation of Standard Airline IT BOM objects.
   */
  void testBomStructureInstantiation();
  
  /**
   * Test some error detection functionalities.
   */
  void testErrorCase ();

  /**
   * Default constructor.
   *
   */
  StandardAirlineITTestSuite ();
  
protected:
  std::stringstream _describeKey;
};
CPPUNIT_TEST_SUITE_REGISTRATION (StandardAirlineITTestSuite);
