#ifndef __LATUS_STDAIR_TST_TESTMANAGER_HPP
#define __LATUS_STDAIR_TST_TESTMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
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
//#include <test/archi_intru/FacRelationShipRoot.hpp>

/** Alias for the boost::intrusive namespace. */
namespace bi = boost::intrusive;

/** Class wrapping test functions. */
class TestManager {
public:
  /** Destructor. */
  ~TestManager() { clean(); }
  
public:
  /** Fill the standard (STL) vector. */
  void initStandard() {
    // Create several FlightDate objects, each one with a different value
    for (int idx = 0; idx < 100; ++idx) {
      stdair::FlightDate* lFlightDate_ptr = new stdair::FlightDate (idx);
      assert (lFlightDate_ptr != NULL);
      
      _flightDateVector.push_back (lFlightDate_ptr);
    }
  }

  /** Fill the (Boost) Intrusive list (and set). */
  void initIntrusive() {
    // Now insert them in the same order as in vector in the member hook list
    for (stdair::FlightDateVector_T::iterator itFlight (_flightDateVector.begin()),
           itend (_flightDateVector.end()); itFlight != itend; ++itFlight) {
      stdair::FlightDate* lFlightDate_ptr = *itFlight;
      assert (lFlightDate_ptr != NULL);
      
      _flightDateChildList.push_back (*lFlightDate_ptr);
      _flightDateChildSet.insert (*lFlightDate_ptr);
    }

    // DEBUG
    /*
      std::cout << "Size of the Boost.Intrusive list of FlightDate objects: "
                << lFlightDateChildList.size() << std::endl;
      std::cout << "Size of the Boost.Intrusive set of FlightDate objects: "
                << lFlightDateChildSet.size() << std::endl;
    */
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
  void clean() {
    _flightDateChildSet.clear();
    _flightDateChildList.clear_and_dispose (delete_disposer<stdair::FlightDate>());
  }
  
  /** Optimized search functions */
  stdair::FlightDate* getFromSet (const std::string& iKey) {
    stdair::FlightDate* oFlightDate_ptr = NULL;
    stdair::FlightDateChildSet::iterator itFlight =
      _flightDateChildSet.find (iKey, StrExpComp<stdair::FlightDate>());
    if (itFlight == _flightDateChildSet.end()) {
      return oFlightDate_ptr;
    }
    oFlightDate_ptr = &*itFlight;
    return oFlightDate_ptr;
  }

  /** Test (Boost) Intrusive lists. */
  bool testIntrusiveList() {
    bool oTestSuccessfull = true;
    
    stdair::FlightDateChildList::iterator mit (_flightDateChildList.begin()),
      mitend (_flightDateChildList.end());
    stdair::FlightDateVector_T::iterator itFlight (_flightDateVector.begin()),
      itend (_flightDateVector.end());

    // Test the objects inserted in the member hook list
    for (itFlight = _flightDateVector.begin();
         itFlight != itend; ++itFlight, ++mit) {
      stdair::FlightDate* lFlightDate_ptr = *itFlight;
      assert (lFlightDate_ptr != NULL);

      if (&*mit != lFlightDate_ptr) {
        oTestSuccessfull = false;
        break;
      }
    }

    return oTestSuccessfull;
  }

  /** Test (Boost) Intrusive iterator_to(). */
  bool testIntrusiveIteratorTo() {
    bool oTestSuccessfull = true;
    
    stdair::FlightDateChildList::iterator itChild(_flightDateChildList.begin());
    for (int idx = 0; idx < 100; ++idx, ++itChild) {
      stdair::FlightDate* lFlightDate_ptr = _flightDateVector.at(idx);
      assert (lFlightDate_ptr != NULL);
      
      if (_flightDateChildList.iterator_to (*lFlightDate_ptr) != itChild ||
          stdair::FlightDateChildList::s_iterator_to(*lFlightDate_ptr) != itChild) {
        oTestSuccessfull = false;
        break;
      }
    }
    
    return oTestSuccessfull;
  }

  /** Test (Boost) Intrusive sets. */
  bool testIntrusiveSets() {
    bool oTestSuccessfull = true;
    
    stdair::FlightDateChildSet::iterator itChild (_flightDateChildSet.begin()),
      itChildEnd (_flightDateChildSet.end());
    for (; itChild != itChildEnd; ++itChild) {
      const stdair::FlightDate& lFlightDate = *itChild;

      const std::string& lKey = lFlightDate.getKey();
      stdair::FlightDate* retrievedFlightDate_ptr = getFromSet (lKey);
      
      // DEBUG
      /*
      std::cout << "Key = '" << lKey << "', itFD = "
                << &lFlightDate << ", retrieved: " << retrievedFlightDate_ptr
                << std::endl;
      */

      if (retrievedFlightDate_ptr == NULL ||
          _flightDateChildSet.iterator_to (lFlightDate) != itChild ||
          _flightDateChildSet.iterator_to (*retrievedFlightDate_ptr) != itChild ||
          stdair::FlightDateChildSet::s_iterator_to (lFlightDate) != itChild ||
          stdair::FlightDateChildSet::s_iterator_to(*retrievedFlightDate_ptr) != itChild) {
        oTestSuccessfull = false;
        break;
      }
    }
    
    return oTestSuccessfull;
  }
    
public:
  // Standard STL container
  stdair::FlightDateVector_T _flightDateVector;
  
  // (Boost) Intrusive container
  stdair::FlightDateChildList _flightDateChildList;
  stdair::FlightDateChildSet _flightDateChildSet;
};

#endif // __LATUS_STDAIR_TST_TESTMANAGER_HPP
