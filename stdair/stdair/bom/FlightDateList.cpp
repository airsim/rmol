// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomChildrenHolderImp.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/FlightDateList.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  FlightDateList_T::
  FlightDateList_T (const FlightDateHolder_T& iFlightDateHolder)
    : _flightDateHolder (iFlightDateHolder) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDateList_T::
  FlightDateList_T (const FlightDateList_T& iFDList)
    : _flightDateHolder (iFDList._flightDateHolder) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDateList_T::~FlightDateList_T () {
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDateList_T::iterator FlightDateList_T::begin () const {
    return _flightDateHolder.listBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDateList_T::iterator FlightDateList_T::end () const {
    return _flightDateHolder.listEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDateList_T::reverse_iterator FlightDateList_T::rbegin () const {
    return _flightDateHolder.listRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDateList_T::reverse_iterator FlightDateList_T::rend () const {
    return _flightDateHolder.listREnd ();
  }

}

