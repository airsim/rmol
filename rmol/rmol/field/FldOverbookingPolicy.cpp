// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
#include <rmol/field/FldOverbookingPolicy.hpp>

namespace RMOL {

  const std::string FldOverbookingPolicy::
  _labels[FldOverbookingPolicy::LAST_VALUE] = {"HEUR", "RISK", "SL1", "SL2",
                                               "HYBRID"};

  // //////////////////////////////////////////////////////////////////////
  FldOverbookingPolicy::
  FldOverbookingPolicy (const FldOverbookingPolicy& iPolicy) :
    _policy (iPolicy.getPolicy()) {
  }

  // //////////////////////////////////////////////////////////////////////
  FldOverbookingPolicy::
  FldOverbookingPolicy (const EN_Policy iPolicy) :
    _policy (iPolicy) {
  }

  // //////////////////////////////////////////////////////////////////////
  FldOverbookingPolicy::~FldOverbookingPolicy() {
  }
  
}
