// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL Limits
#include <limits>
// RMOL
#include <rmol/field/FldYieldRange.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  FldYieldRange::FldYieldRange() :
    _upperYield (std::numeric_limits<double>::max()),
    _averageYield (std::numeric_limits<double>::max()),
    _lowerYield (std::numeric_limits<double>::min()) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  FldYieldRange::FldYieldRange (const FldYieldRange& iYieldRange) :
    _upperYield (iYieldRange.getUpperYield()),
    _averageYield (iYieldRange.getAverageYield()),
    _lowerYield (std::numeric_limits<double>::min()) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  FldYieldRange::FldYieldRange (const double iUpperYield) :
    _upperYield (iUpperYield), _averageYield (iUpperYield),
    _lowerYield (iUpperYield) {
  }

  // //////////////////////////////////////////////////////////////////////
  FldYieldRange::FldYieldRange (const double iUpperYield,
                                const double iAverageYield) :
    _upperYield (iUpperYield), _averageYield (iAverageYield),
    _lowerYield (std::numeric_limits<double>::min()) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  FldYieldRange::FldYieldRange (const double iUpperYield,
                                const double iAverageYield,
                                const double iLowerYield) :
    _upperYield (iUpperYield), _averageYield (iAverageYield),
    _lowerYield (iLowerYield) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  FldYieldRange::~FldYieldRange() {
  }
  
  // //////////////////////////////////////////////////////////////////////
  void FldYieldRange::toStream (std::ostream& ioOut) const {
    ioOut << _averageYield << "([" << _lowerYield << ", "
          << _upperYield << "])";
  }
  
  // //////////////////////////////////////////////////////////////////////
  void FldYieldRange::fromStream (std::istream& ioIn) {
  }
  
}
