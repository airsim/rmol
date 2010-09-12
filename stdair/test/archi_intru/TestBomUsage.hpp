#ifndef __INTRUSIVE_TST_TESTBOMUSAGE_HPP
#define __INTRUSIVE_TST_TESTBOMUSAGE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// Local
#include <test/archi_intru/FlightDate.hpp>

/** Class wrapping test functions. */
class TestBomUsage {
public:
  /** Destructor. */
  ~TestBomUsage();
  
public:
  /** Perform the full test set. */
  static bool test();
  
private:
  /** Initialise. */
  void init();

  /** Cleaning. */
  void clean();

private:
};

#endif // __INTRUSIVE_TST_TESTBOMUSAGE_HPP
