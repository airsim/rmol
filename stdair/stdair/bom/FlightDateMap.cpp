// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomChildrenHolderImp.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/FlightDateMap.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  FlightDateMap_T::
  FlightDateMap_T (const FlightDateHolder_T& iFlightDateHolder)
    : _flightDateHolder (iFlightDateHolder) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDateMap_T::
  FlightDateMap_T (const FlightDateMap_T& iFDMap)
    : _flightDateHolder (iFDMap._flightDateHolder) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDateMap_T::~FlightDateMap_T () {
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDateMap_T::iterator FlightDateMap_T::begin () const {
    return _flightDateHolder.mapBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDateMap_T::iterator FlightDateMap_T::end () const {
    return _flightDateHolder.mapEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDateMap_T::reverse_iterator FlightDateMap_T::rbegin () const {
    return _flightDateHolder.mapRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDateMap_T::reverse_iterator FlightDateMap_T::rend () const {
    return _flightDateHolder.mapREnd ();
  }

}

