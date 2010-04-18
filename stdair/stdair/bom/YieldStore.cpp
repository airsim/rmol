// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/Structure.hpp>
#include <stdair/bom/BR.hpp>
#include <stdair/bom/YieldStore.hpp>
#include <stdair/bom/BomList.hpp>
#include <stdair/bom/BomMap.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  YieldStore::YieldStore (const BomKey_T& iKey,
                          BomStructure_T& ioYieldStoreStructure)
    : YieldStoreContent (iKey), _structure (ioYieldStoreStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  YieldStore::~YieldStore () {
  }

}
