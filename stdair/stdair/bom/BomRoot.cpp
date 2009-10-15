// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomRootStructure.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/InventoryList.hpp>
#include <stdair/bom/InventoryMap.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/BookingClass.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  BomRoot::BomRoot (BomStructure_T& ioBomRootStructure)
    : _bomRootStructure (ioBomRootStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  BomRoot::~BomRoot () {
  }

  // //////////////////////////////////////////////////////////////////////
  InventoryList_T BomRoot::getInventoryList () const {
    return _bomRootStructure.getChildrenList();
  }

  // //////////////////////////////////////////////////////////////////////
  InventoryMap_T BomRoot::getInventoryMap () const {
    return _bomRootStructure.getChildrenList();
  }
}
