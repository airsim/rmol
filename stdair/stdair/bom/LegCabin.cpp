// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/bom/LegCabinStructure.hpp>
#include <stdair/bom/LegCabin.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  LegCabin::LegCabin (const BomKey_T& iKey, BomStructure_T& ioLegStructure)
    : LegCabinContent (iKey),  _legCabinStructure (ioLegStructure) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  LegCabin::~LegCabin () {
  }

  // //////////////////////////////////////////////////////////////////////
  void LegCabin::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // //////////////////////////////////////////////////////////////////////
  void LegCabin::fromStream (std::istream& ioIn) {
  }

  // //////////////////////////////////////////////////////////////////////
  std::string LegCabin::toString() const {
    std::ostringstream oStr;

    // First, put the key of that level
    oStr << describeShortKey() << std::endl;

    // Then, browse the children
    // [...] (no child for now)
    
    return oStr.str();
  }
    
  // //////////////////////////////////////////////////////////////////////
  const std::string LegCabin::describeKey() const {
    return _key.describe();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string LegCabin::describeShortKey() const {
    return _key.toString();
  }
  
  // //////////////////////////////////////////////////////////////////////
  void LegCabin::setCapacity(const CabinCapacity_T& iCapacity,
                             const AnalysisStatus_T& iAnalysisStatus) {
    _capacity = iCapacity;
    // LegDate* lLegDate = getParent();
//     assert (lLegDate!= NULL);
//       lLegDate->updateCapacityAndLegASK(iCapacity, iAnalysisStatus);
  }
  
}

