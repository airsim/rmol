#ifndef __STDAIR_TST_STDAIR_TEST_LIB_HPP
#define __STDAIR_TST_STDAIR_TEST_LIB_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

/**
 * Class wrapping test functions
 */
class StdairTestLib {
public:

  /**
   * Test the initialisation of the Standard Airline IT base library.
   */
  static void testServiceInitialisation();

  /**
   * Test MPL-based type handling, just as a proof-of-concept. It does
   * not use StdAir BOM.
   */
  static void testMPLStructure();

  /**
   * Test the initialisation of Standard Airline IT BOM objects.
   */
  static void testBomStructureInstantiation();
  
  /**
   * Test some error detection functionalities.
   */
  static bool testErrorCase();

private:
  /**
   * Default constructor.
   *
   * It should not be used, as all the methods
   * are defined as static.
   */
  StdairTestLib() {}

  /**
   * Default copy constructor.
   *
   * It should not be used, as all the methods
   * are defined as static.
   */
  StdairTestLib (const StdairTestLib&) {}
  
  /**
   * Default copy constructor.
   *
   */  
  ~StdairTestLib() {}
};

#endif // __STDAIR_TST_STDAIR_TEST_LIB_HPP
