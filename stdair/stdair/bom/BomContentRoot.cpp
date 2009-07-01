// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/bom/BomStructureRoot.hpp>
#include <stdair/bom/BomContentRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/InventoryList.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  BomContentRoot::BomContentRoot (const BomStructure_T& iBomStructure)
    : _bomStructure (iBomStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  BomContentRoot::~BomContentRoot () {
  }

  // //////////////////////////////////////////////////////////////////////
  void BomContentRoot::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // //////////////////////////////////////////////////////////////////////
  void BomContentRoot::fromStream (std::istream& ioIn) {
  }

  // //////////////////////////////////////////////////////////////////////
  std::string BomContentRoot::toString() const {
    std::ostringstream oStr;

    // First, put the key of that level
    oStr << describeShortKey() << std::endl;

    // Retrieve the list of inventory holders
    const InventoryList_T& lInventoryList = _bomStructure.getInventoryList();

    // Browse the tree structure, i.e., the inventories
    unsigned short idx = 0;
    for (InventoryList_T::const_iterator itInventory = lInventoryList.begin();
         itInventory != lInventoryList.end(); ++itInventory, ++idx) {
      const Inventory* lInventoryStructure_ptr = itInventory->second;
      assert (lInventoryStructure_ptr != NULL);

      // Get the content out of the structure/holder
      const Inventory& lInventory =
        lInventoryStructure_ptr->getContent<Inventory>();

      oStr << "[" << idx << "]: " << lInventory.toString() << std::endl;
    }
    
    return oStr.str();
  }
    
  // //////////////////////////////////////////////////////////////////////
  const std::string BomContentRoot::describeKey() const {
    return _bomStructure.describeKey();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string BomContentRoot::describeShortKey() const {
    return _bomStructure.describeShortKey();
  }

}

