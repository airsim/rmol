// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <ostream>
#include <sstream>
// STDAIR
#include <airrac/bom/YieldRuleFeaturesKey.hpp>

namespace AIRRAC  {

   // ////////////////////////////////////////////////////////////////////
  YieldRuleFeaturesKey::YieldRuleFeaturesKey (const stdair::CabinCode_T& iCabin,
                                              const stdair::Yield_T& iYield)
    : _cabinCode(iCabin), _yield(iYield) {
  }

  // ////////////////////////////////////////////////////////////////////
  YieldRuleFeaturesKey::YieldRuleFeaturesKey (const YieldRuleFeaturesKey& iKey)
    : _cabinCode(iKey.getCabinCode()), _yield(iKey.getYield()) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  YieldRuleFeaturesKey::~YieldRuleFeaturesKey () {
  }

  // ////////////////////////////////////////////////////////////////////
  void YieldRuleFeaturesKey::toStream (std::ostream& ioOut) const {
    ioOut << "YieldRuleFeaturesKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void YieldRuleFeaturesKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string YieldRuleFeaturesKey::toString() const {
    std::ostringstream oStr;
    oStr << _cabinCode << "-" << _yield;
    return oStr.str();
  }

}

