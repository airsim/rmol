// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/Inventory.hpp>
// RMOL 
#include <rmol/bom/Inventory.hpp>
#include <rmol/bom/FlightDate.hpp>
#include <rmol/bom/SegmentDate.hpp>
#include <rmol/bom/LegDate.hpp>
#include <rmol/service/Logger.hpp>

namespace RMOL {

  // ////////////////////////////////////////////////////////////////////
  Inventory::Inventory (BomStructure_T& ioInventoryStructure)
    : _inventoryStructure (ioInventoryStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  Inventory::~Inventory () {
  }

  // //////////////////////////////////////////////////////////////////////
  void Inventory::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // //////////////////////////////////////////////////////////////////////
  void Inventory::fromStream (std::istream& ioIn) {
  }

  // //////////////////////////////////////////////////////////////////////
  std::string Inventory::toString() const {
    std::ostringstream oStr;

    _inventoryStructure.describeFull (oStr);
      
    return oStr.str();
  }
    
  // //////////////////////////////////////////////////////////////////////
  const std::string Inventory::describeKey() const {
    return _inventoryStructure.describeKey();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string Inventory::describeShortKey() const {
    return _inventoryStructure.describeShortKey();
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory::
  list_const_iterator Inventory::flightDateListConstIteratorBegin () const {
    return _inventoryStructure.flightDateListConstIteratorBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory::
  list_const_iterator Inventory::flightDateListConstIteratorEnd () const {
    return _inventoryStructure.flightDateListConstIteratorEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory::list_const_reverse_iterator Inventory::flightDateListConstIteratorRBegin () const {
    return _inventoryStructure.flightDateListConstIteratorRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory::list_const_reverse_iterator Inventory::flightDateListConstIteratorREnd () const {
    return _inventoryStructure.flightDateListConstIteratorREnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory::
  list_iterator Inventory::flightDateListIteratorBegin () const {
    return _inventoryStructure.flightDateListIteratorBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory::
  list_iterator Inventory::flightDateListIteratorEnd () const {
    return _inventoryStructure.flightDateListIteratorEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory::
  list_reverse_iterator Inventory::flightDateListIteratorRBegin () const {
    return _inventoryStructure.flightDateListIteratorRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory::
  list_reverse_iterator Inventory::flightDateListIteratorREnd () const {
    return _inventoryStructure.flightDateListIteratorREnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory::
  map_const_iterator Inventory::flightDateMapConstIteratorBegin () const {
    return _inventoryStructure.flightDateMapConstIteratorBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory::
  map_const_iterator Inventory::flightDateMapConstIteratorEnd () const {
    return _inventoryStructure.flightDateMapConstIteratorEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory::map_const_reverse_iterator Inventory::flightDateMapConstIteratorRBegin () const {
    return _inventoryStructure.flightDateMapConstIteratorRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory::map_const_reverse_iterator Inventory::flightDateMapConstIteratorREnd () const {
    return _inventoryStructure.flightDateMapConstIteratorREnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory::
  map_iterator Inventory::flightDateMapIteratorBegin () const {
    return _inventoryStructure.flightDateMapIteratorBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory::
  map_iterator Inventory::flightDateMapIteratorEnd () const {
    return _inventoryStructure.flightDateMapIteratorEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory::
  map_reverse_iterator Inventory::flightDateMapIteratorRBegin () const {
    return _inventoryStructure.flightDateMapIteratorRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory::
  map_reverse_iterator Inventory::flightDateMapIteratorREnd () const {
    return _inventoryStructure.flightDateMapIteratorREnd ();
  }

}

