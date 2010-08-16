// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomSource.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  Inventory::Inventory (const Key_T& iKey,
                        Structure_T& ioInventoryStructure)
    : InventoryContent (iKey), _structure (ioInventoryStructure) {
    init ();
  }

  // ////////////////////////////////////////////////////////////////////
  Inventory::~Inventory () {
  }

  // ////////////////////////////////////////////////////////////////////
  void Inventory::init () {
    _structure.initChildrenHolder<FlightDate> ();
    _structure.initChildrenHolder<FlightPeriod> ();
  }

  // ////////////////////////////////////////////////////////////////////
  void Inventory::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void Inventory::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string Inventory::toString() const {
    std::ostringstream oStr;
    oStr << _key.toString();
    return oStr.str();
  }
    
  // ////////////////////////////////////////////////////////////////////
  const std::string Inventory::describeKey() const {
    return _key.toString();
  }

  // ////////////////////////////////////////////////////////////////////
  const Inventory::Parent_T& Inventory::getParent () const {
    return _structure.getParent().getContent();
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDateList_T Inventory::getFlightDateList () const {
    return _structure.getChildrenHolder<FlightDate>();
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDateMap_T Inventory::getFlightDateMap () const {
    return _structure.getChildrenHolder<FlightDate>();
  }

  // ////////////////////////////////////////////////////////////////////
  FlightPeriodList_T Inventory::getFlightPeriodList () const {
    return _structure.getChildrenHolder<FlightPeriod>();
  }

  // ////////////////////////////////////////////////////////////////////
  FlightPeriodMap_T Inventory::getFlightPeriodMap () const {
    return _structure.getChildrenHolder<FlightPeriod>();
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDate* Inventory::
  getFlightDate (const FlightDateKey_T& iKey) const {
    return _structure.getChildPtr<FlightDate> (iKey.toString());
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDate* Inventory::
  getFlightDate (const std::string& iKey) const {
    return _structure.getChildPtr<FlightDate> (iKey);
  }

  // ////////////////////////////////////////////////////////////////////
  FlightPeriod* Inventory::
  getFlightPeriod (const FlightPeriodKey_T& iKey) const {
    return _structure.getChildPtr<FlightPeriod> (iKey.toString());
  }
}

