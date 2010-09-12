// STL
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
// Boost
#include <boost/intrusive/list.hpp>
// Local
#include <test/archi_intru/FlightDate.hpp>

/** Alias for the boost::intrusive namespace. */
namespace bi = boost::intrusive;


// Optimized search functions
stdair::FlightDate* getFromSet(const std::string& iKey,
                               stdair::FlightDateChildSet& ioFlightDateChildSet) {
  stdair::FlightDate* oFlightDate_ptr = NULL;
  stdair::FlightDateChildSet::iterator itFlight =
    ioFlightDateChildSet.find (iKey, StrExpComp<stdair::FlightDate>());
  if (itFlight == ioFlightDateChildSet.end()) {
    return oFlightDate_ptr;
  }
  oFlightDate_ptr = &*itFlight;
  return oFlightDate_ptr;
}

// /////////////////////////// M A I N /////////////////////////
/** Main.
    <br>Run with the following command:
    <tt>make check && ((./bom && echo "Success") || echo "Failure")</tt>
    <br>To run the program with Valgrind, type:
    <tt>libtool --mode=execute valgrind --leak-check=full ./bom</tt>
*/
int main (int argc, char* argv[]) {

  //
  typedef std::vector<stdair::FlightDate*> FlightDateVector_T;

  // Standard STL container
  FlightDateVector_T lFlightDateVector;
  
  // Create several FlightDate objects, each one with a different value
  for (int idx = 0; idx < 100; ++idx) {
    stdair::FlightDate* lFlightDate_ptr = new stdair::FlightDate (idx);
    assert (lFlightDate_ptr != NULL);
    
    lFlightDateVector.push_back (lFlightDate_ptr);
  }

  // (Boost) Intrusive container
  stdair::FlightDateChildList lFlightDateChildList;
  stdair::FlightDateChildSet lFlightDateChildSet;

  // Now insert them in the same order as in vector in the member hook list
  for (FlightDateVector_T::iterator itFlight (lFlightDateVector.begin()),
         itend (lFlightDateVector.end()); itFlight != itend; ++itFlight) {
    stdair::FlightDate* lFlightDate_ptr = *itFlight;
    assert (lFlightDate_ptr != NULL);

    lFlightDateChildList.push_back (*lFlightDate_ptr);
    lFlightDateChildSet.insert (*lFlightDate_ptr);
  }

  // DEBUG
  /*
  std::cout << "Size of the Boost.Intrusive list of FlightDate objects: "
            << lFlightDateChildList.size() << std::endl;
  std::cout << "Size of the Boost.Intrusive set of FlightDate objects: "
            << lFlightDateChildSet.size() << std::endl;
  */

  // Now test lists
  {
    stdair::FlightDateChildList::iterator mit (lFlightDateChildList.begin()),
      mitend (lFlightDateChildList.end());
    FlightDateVector_T::iterator itFlight (lFlightDateVector.begin()),
      itend (lFlightDateVector.end());

    // Test the objects inserted in the member hook list
    for (itFlight = lFlightDateVector.begin();
         itFlight != itend; ++itFlight, ++mit) {
      stdair::FlightDate* lFlightDate_ptr = *itFlight;
      assert (lFlightDate_ptr != NULL);

      if (&*mit != lFlightDate_ptr) {
        return 1;
      }
    }
  }

  // Now, test iterator_to()
  {
    stdair::FlightDateChildList::iterator itChild(lFlightDateChildList.begin());
    for (int idx = 0; idx < 100; ++idx, ++itChild) {
      stdair::FlightDate* lFlightDate_ptr = lFlightDateVector.at(idx);
      assert (lFlightDate_ptr != NULL);
      
      if (lFlightDateChildList.iterator_to (*lFlightDate_ptr) != itChild ||
          stdair::FlightDateChildList::s_iterator_to(*lFlightDate_ptr) != itChild) {
        return 1;
      }
    }
  }

  // Now, test sets
  {
    stdair::FlightDateChildSet::iterator itChild (lFlightDateChildSet.begin()),
      itChildEnd (lFlightDateChildSet.end());
    for (; itChild != itChildEnd; ++itChild) {
      const stdair::FlightDate& lFlightDate = *itChild;

      const std::string& lKey = lFlightDate.getKey();
      stdair::FlightDate* retrievedFlightDate_ptr =
        getFromSet (lKey, lFlightDateChildSet);
      
      // DEBUG
      /*
      std::cout << "Key = '" << lKey << "', itFD = "
                << &lFlightDate << ", retrieved: " << retrievedFlightDate_ptr
                << std::endl;
      */

      if (retrievedFlightDate_ptr == NULL ||
          lFlightDateChildSet.iterator_to (lFlightDate) != itChild ||
          lFlightDateChildSet.iterator_to (*retrievedFlightDate_ptr) != itChild ||
          stdair::FlightDateChildSet::s_iterator_to (lFlightDate) != itChild ||
          stdair::FlightDateChildSet::s_iterator_to(*retrievedFlightDate_ptr) != itChild) {
        return 1;
      }
    }
  }
  

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
  lFlightDateChildSet.clear();
  lFlightDateChildList.clear_and_dispose(delete_disposer<stdair::FlightDate>());
  
  return 0;
}
