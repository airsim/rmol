// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomSource.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  LegDate::LegDate (const Key_T& iKey, Structure_T& ioLegStructure)
    : LegDateContent (iKey), _structure (ioLegStructure) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  LegDate::~LegDate () {
  }

  // ////////////////////////////////////////////////////////////////////
  void LegDate::init () {
    _structure.initChildrenHolder<LegCabin> ();
    _structure.initChildrenHolder<SegmentDate> ();
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
    std::ostringstream oStr;
    oStr << _structure.describeParentKey() << ", " << describeShortKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  LegCabinList_T LegDate::getLegCabinList () const {
    return _structure.getChildrenHolder<LegCabin>();
  }

  // ////////////////////////////////////////////////////////////////////
  LegCabinMap_T LegDate::getLegCabinMap () const {
    return _structure.getChildrenHolder<LegCabin>();
  }

  // ////////////////////////////////////////////////////////////////////
  LegCabin* LegDate::getLegCabin (const CabinCode_T& iCabinCode) const {
    return _structure.getChildPtr<LegCabin> (iCabinCode);
  }
  
}

