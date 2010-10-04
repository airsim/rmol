// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/bom/BomRoot.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  BomRoot::BomRoot (const Key_T& iKey)
    : _key (iKey), _seed (DEFAULT_RANDOM_SEED), _generator (_seed),
      _uniformGenerator (_generator, boost::uniform_real<> (0, 1)) {
  }

  // ////////////////////////////////////////////////////////////////////
  BomRoot::~BomRoot () {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string BomRoot::toString() const {
    std::ostringstream oStr;
    oStr << _key.toString();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  RandomSeed_T BomRoot::generateSeed () {
    RealNumber_T lVariateUnif = _uniformGenerator() * 1e9;
    RandomSeed_T oSeed = static_cast<RandomSeed_T> (lVariateUnif);
    return oSeed;
  }

}
