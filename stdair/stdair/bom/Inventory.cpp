// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/InventoryStructure.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/FlightDateList.hpp>
#include <stdair/bom/FlightDateMap.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/BookingClass.hpp>

namespace stdair {

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
  FlightDateList_T Inventory::getFlightDateList () const {
    return _inventoryStructure.getChildrenList();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDateMap_T Inventory::getFlightDateMap () const {
    return _inventoryStructure.getChildrenList();
  }

}

