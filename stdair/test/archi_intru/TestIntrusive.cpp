// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
// Boost.Intrusive
#include <boost/intrusive/list.hpp>
// Local
#include <test/archi_intru/FacBom.hpp>
#include <test/archi_intru/FlightDate.hpp>
#include <test/archi_intru/IntrusiveHelper.hpp>
#include <test/archi_intru/TestIntrusive.hpp>

/** Alias for the boost::intrusive namespace. */
namespace bi = boost::intrusive;

// //////////////////////////////////////////////////////////////////////
TestIntrusive::~TestIntrusive() {
  clean();
}

// //////////////////////////////////////////////////////////////////////
void TestIntrusive::init() {
  initStandard();
  initIntrusive();
}

// //////////////////////////////////////////////////////////////////////
void TestIntrusive::initStandard() {
  // Create several FlightDate objects, each one with a different value
  for (int idx = 0; idx < 100; ++idx) {
    stdair::FlightDate& lFlightDate =
      stdair::FacBom<stdair::FlightDate>::instance().create (idx);
    
    _flightDateVector.push_back (&lFlightDate);
  }
}

// //////////////////////////////////////////////////////////////////////
void TestIntrusive::initIntrusive() {
  // Now insert them in the same order as in vector in the member hook list
  for (stdair::FlightDateVector_T::iterator itFlight(_flightDateVector.begin()),
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

// //////////////////////////////////////////////////////////////////////
void TestIntrusive::clean() {
  _flightDateChildSet.clear();
  _flightDateChildList.clear_and_dispose(delete_disposer<stdair::FlightDate>());
}
  
// //////////////////////////////////////////////////////////////////////
stdair::FlightDate* TestIntrusive::getFromSet (const std::string& iKey) {
  stdair::FlightDate* oFlightDate_ptr = NULL;
  stdair::FlightDateChildSet::iterator itFlight =
    _flightDateChildSet.find (iKey, StrExpComp<stdair::FlightDate>());
  if (itFlight == _flightDateChildSet.end()) {
    return oFlightDate_ptr;
  }
  oFlightDate_ptr = &*itFlight;
  return oFlightDate_ptr;
}

// //////////////////////////////////////////////////////////////////////
bool TestIntrusive::testIntrusiveList() {
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

// //////////////////////////////////////////////////////////////////////
bool TestIntrusive::testIntrusiveIteratorTo() {
  bool oTestSuccessfull = true;
    
  stdair::FlightDateChildList::iterator itChild(_flightDateChildList.begin());
  for (int idx = 0; idx < 100; ++idx, ++itChild) {
    stdair::FlightDate* lFlightDate_ptr = _flightDateVector.at(idx);
    assert (lFlightDate_ptr != NULL);
      
    if (_flightDateChildList.iterator_to (*lFlightDate_ptr) != itChild ||
        stdair::FlightDateChildList::s_iterator_to(*lFlightDate_ptr)!= itChild){
      oTestSuccessfull = false;
      break;
    }
  }
    
  return oTestSuccessfull;
}

// //////////////////////////////////////////////////////////////////////
bool TestIntrusive::testIntrusiveSets() {
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

// //////////////////////////////////////////////////////////////////////
bool TestIntrusive::test() {
  bool oTestSuccessfull = true;

  //
  TestIntrusive lTestIntrusive;
  
  // Initialise the internal (STL) vector, (Boost.Intrusive) list and set
  lTestIntrusive.init();
  
  // Now test lists
  oTestSuccessfull = lTestIntrusive.testIntrusiveList();
  if (oTestSuccessfull == false) {
    return oTestSuccessfull;
  }
  
  // Now, test iterator_to()
  oTestSuccessfull = lTestIntrusive.testIntrusiveIteratorTo();
  if (oTestSuccessfull == false) {
    return oTestSuccessfull;
  }
  
  // Now, test sets
  oTestSuccessfull = lTestIntrusive.testIntrusiveSets();
  if (oTestSuccessfull == false) {
    return oTestSuccessfull;
  }

  return oTestSuccessfull;
}
