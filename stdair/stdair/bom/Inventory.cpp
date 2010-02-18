// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/InventoryStructure.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/BomList.hpp>
#include <stdair/bom/BomMap.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  Inventory::Inventory (const BomKey_T& iKey,
                        BomStructure_T& ioInventoryStructure)
    : InventoryContent (iKey), _inventoryStructure (ioInventoryStructure) {
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
    oStr << _key.toString();
    return oStr.str();
  }
    
  // //////////////////////////////////////////////////////////////////////
  const std::string Inventory::describeKey() const {
    return _key.describe();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string Inventory::describeShortKey() const {
    return _key.toString();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDateList_T Inventory::getFlightDateList () const {
    return _inventoryStructure.getChildrenHolder();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDateMap_T Inventory::getFlightDateMap () const {
    return _inventoryStructure.getChildrenHolder();
  }

  // //////////////////////////////////////////////////////////////////////
  BookingClassList_T Inventory::getBookingClassList () const {
    return _inventoryStructure.getBookingClassHolder();
  }

  // //////////////////////////////////////////////////////////////////////
  BookingClassMap_T Inventory::getBookingClassMap () const {
    return _inventoryStructure.getBookingClassHolder();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate* Inventory::
  getFlightDate (const FlightDateKey_T& iKey) const {
    return _inventoryStructure.getContentChild (iKey);
  }
}

