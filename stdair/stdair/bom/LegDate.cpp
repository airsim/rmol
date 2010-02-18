// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/bom/LegDateStructure.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/BomList.hpp>
#include <stdair/bom/BomMap.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  LegDate::LegDate (const BomKey_T& iKey, BomStructure_T& ioLegStructure)
    : LegDateContent (iKey), _legDateStructure (ioLegStructure) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  LegDate::~LegDate () {
  }

  // ////////////////////////////////////////////////////////////////////
  void LegDate::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void LegDate::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string LegDate::toString() const {
    std::ostringstream oStr;

    // First, put the key of that level
    oStr << describeShortKey() << std::endl;

    // Then, browse the children
    // [...] (no child for now)
    
    return oStr.str();
  }
    
  // ////////////////////////////////////////////////////////////////////
  const std::string LegDate::describeKey() const {
    return _key.describe();
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string LegDate::describeShortKey() const {
    return _key.toString();
  }

  // ////////////////////////////////////////////////////////////////////
  LegCabinList_T LegDate::getLegCabinList () const {
    return _legDateStructure.getChildrenHolder();
  }

  // ////////////////////////////////////////////////////////////////////
  LegCabinMap_T LegDate::getLegCabinMap () const {
    return _legDateStructure.getChildrenHolder();
  }

  // ////////////////////////////////////////////////////////////////////
  LegCabin* LegDate::getLegCabin (const LegCabinKey_T& iKey) const {
    return _legDateStructure.getContentChild (iKey);
  }
  
}

