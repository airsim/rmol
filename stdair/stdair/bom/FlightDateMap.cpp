// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/InventoryStructure.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/FlightDateMap.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  FlightDateMap_T::
  FlightDateMap_T (const InventoryStructure_T& iInventoryStructure)
    : _inventoryStructure (iInventoryStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDateMap_T::
  FlightDateMap_T (const FlightDateMap_T& iFDMap)
    : _inventoryStructure (iFDMap._inventoryStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDateMap_T::~FlightDateMap_T () {
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDateMap_T::iterator FlightDateMap_T::begin () const {
    return _inventoryStructure.flightDateMapBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDateMap_T::iterator FlightDateMap_T::end () const {
    return _inventoryStructure.flightDateMapEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDateMap_T::reverse_iterator FlightDateMap_T::rbegin () const {
    return _inventoryStructure.flightDateMapRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDateMap_T::reverse_iterator FlightDateMap_T::rend () const {
    return _inventoryStructure.flightDateMapREnd ();
  }

}

