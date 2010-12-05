#ifndef __INTRUSIVE_TST_TESTBOMUSAGE_HPP
#define __INTRUSIVE_TST_TESTBOMUSAGE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// Local
#include <test/archi_intru/FlightDate.hpp>

// Forward declarations
namespace stdair {
  class BomRoot;
}

/** Class wrapping test functions. */
class TestBomUsage {
public:
  /** Constructor. */
  TestBomUsage();
  /** Destructor. */
  ~TestBomUsage();
  
public:
  /** Perform the full test set. */
  static bool test();

private:
  /** Test the building of the BOM tree. */
  bool testBomBuilding();
  
  /** Test the search within the BOM tree. */
  bool testBomSearching();
  
private:
  /** Initialise. */
  void init();

  /** Cleaning. */
  void clean();

private:
  stdair::BomRoot* _bomRoot;
};

#endif // __INTRUSIVE_TST_TESTBOMUSAGE_HPP
