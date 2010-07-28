
// StdAir
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>

namespace LH {

  /**
   * \brief LH own implementation of the BomRoot class
   */
  class BomRootImpl : public stdair::BomRootContent {
  };

  /**
   * \brief LH own implementation of the FlightDate class
   */
  class FlightDateImpl : public stdair::FlightDateContent {
  };

  /**
   * \brief Initialisation of objects
   */
  void init() {
    stdair::BomRoot<BomRootImpl> lhBomRoot;
    stdair::Inventory<stdair::InventoryImpl> lhInventory;
    stdair::link(lhBomRoot, lhInventory);
  
    stdair::FlightDate<lh::FlightDateImpl> lhFlightDate;
    stdair::link (lhInventory, lhFlightDate);
  }
  
}  
