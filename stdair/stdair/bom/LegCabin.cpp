// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomSource.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  LegCabin::LegCabin (const Key_T& iKey, Structure_T& ioLegStructure)
    : LegCabinContent (iKey),  _structure (ioLegStructure) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  LegCabin::~LegCabin () {
  }

  // ////////////////////////////////////////////////////////////////////
  void LegCabin::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void LegCabin::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string LegCabin::toString() const {
    std::ostringstream oStr;

    // First, put the key of that level
    oStr << describeShortKey() << std::endl;

    // Then, browse the children
    // [...] (no child for now)
    
    return oStr.str();
  }
    
  // ////////////////////////////////////////////////////////////////////
  const std::string LegCabin::describeKey() const {
    std::ostringstream oStr;
    oStr << _structure.describeParentKey() << ", " << describeShortKey();
    return oStr.str();
  }
  
  // ////////////////////////////////////////////////////////////////////
  void LegCabin::setCapacity(const CabinCapacity_T& iCapacity,
                             const AnalysisStatus_T& iAnalysisStatus) {
    _capacity = iCapacity;
    // LegDate* lLegDate = getParent();
//     assert (lLegDate!= NULL);
//       lLegDate->updateCapacityAndLegASK(iCapacity, iAnalysisStatus);
  }
  
}

