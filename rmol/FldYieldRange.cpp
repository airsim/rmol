// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL Limits
#include <limits>
// RMOL
#include "FldYieldRange.hpp"

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  FldYieldRange::FldYieldRange() :
    _upperYield (std::numeric_limits<double>::max()),
    _averageYield (std::numeric_limits<double>::max()) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  FldYieldRange::FldYieldRange (const FldYieldRange& iYieldRange) :
    _upperYield (iYieldRange.getUpperYield()),
    _averageYield (iYieldRange.getAverageYield()) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  FldYieldRange::FldYieldRange (const double iUpperYield) :
    _upperYield (iUpperYield), _averageYield (iUpperYield) {
  }

  // //////////////////////////////////////////////////////////////////////
  FldYieldRange::FldYieldRange (const double iUpperYield,
                                const double iAverageYield) :
    _upperYield (iUpperYield), _averageYield (iAverageYield) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  FldYieldRange::~FldYieldRange() {
  }
  
}
