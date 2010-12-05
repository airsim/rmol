#ifndef __INTRUSIVE_TST_TESTINTRUSIVE_HPP
#define __INTRUSIVE_TST_TESTINTRUSIVE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// Local
#include <test/archi_intru/FlightDate.hpp>

/** Class wrapping test functions. */
class TestIntrusive {
public:
  /** Destructor. */
  ~TestIntrusive();
  
public:
  /** Perform the full test set. */
  static bool test();
  
private:
  /** Initialise the internal vector, list and set. */
  void init();

  /** Fill the standard (STL) vector. */
  void initStandard();

  /** Fill the (Boost) Intrusive list (and set). */
  void initIntrusive();
  
  /** Some memory cleaning.
      <br>Note: the FlightDate objects cannot be simply deleted (with the
      delete opearator).
      <br>See also, for more details:
      - http://www.boost.org/doc/libs/1_44_0/doc/html/intrusive/usage.html#intrusive.usage.usage_lifetime
      - http://www.boost.org/doc/libs/1_44_0/doc/html/intrusive/erasing_and_disposing.html
      <br>First, clear simply all the Boost.Intrusive containers but one. Then,
      clear the last Boost.Intrusive container while deleting the corresponding
      hooked objects.
  */
  void clean();

private:
  /** Optimized search functions */
  stdair::FlightDate* getFromSet (const std::string& iKey);

  /** Test (Boost) Intrusive lists. */
  bool testIntrusiveList();

  /** Test (Boost) Intrusive iterator_to(). */
  bool testIntrusiveIteratorTo();

  /** Test (Boost) Intrusive sets. */
  bool testIntrusiveSets();
    
private:
  // Standard STL container
  stdair::FlightDateVector_T _flightDateVector;
  
  // (Boost) Intrusive container
  stdair::FlightDateChildList _flightDateChildList;
  stdair::FlightDateChildSet _flightDateChildSet;
};

#endif // __INTRUSIVE_TST_TESTINTRUSIVE_HPP
