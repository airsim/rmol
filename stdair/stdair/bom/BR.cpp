// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/Structure.hpp>
#include <stdair/bom/BR.hpp>
#include <stdair/bom/YieldStore.hpp>
#include <stdair/bom/IN.hpp>
#include <stdair/bom/BomList.hpp>
#include <stdair/bom/BomMap.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  BR::BR (const BomKey_T& iKey, BomStructure_T& ioBRStructure)
    : BomRootContent (iKey), _structure (ioBRStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  BR::~BR () {
  }

  // ////////////////////////////////////////////////////////////////////
  const YieldStoreList_T BR::getYieldStoreList () const {
    return _structure.getChildrenHolder<YieldStore>();
  }
  
  // ////////////////////////////////////////////////////////////////////
  const YieldStoreMap_T BR::getYieldStoreMap () const {
    return _structure.getChildrenHolder<YieldStore>();
  }

  // ////////////////////////////////////////////////////////////////////
  const INList_T BR::getINList () const {
    return _structure.getChildrenHolder<IN>();
  }
  
  // ////////////////////////////////////////////////////////////////////
  const INMap_T BR::getINMap () const {
    return _structure.getChildrenHolder<IN>();
  }

}
