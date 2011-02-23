// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <limits>
#include <sstream>
// RMOL
#include <rmol/basic/YieldRange.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  YieldRange::YieldRange() :
    _upperYield (std::numeric_limits<double>::max()),
    _averageYield (std::numeric_limits<double>::max()),
    _lowerYield (std::numeric_limits<double>::min()) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  YieldRange::YieldRange (const YieldRange& iYieldRange) :
    _upperYield (iYieldRange.getUpperYield()),
    _averageYield (iYieldRange.getAverageYield()),
    _lowerYield (std::numeric_limits<double>::min()) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  YieldRange::YieldRange (const double iUpperYield) :
    _upperYield (iUpperYield), _averageYield (iUpperYield),
    _lowerYield (iUpperYield) {
  }

  // //////////////////////////////////////////////////////////////////////
  YieldRange::YieldRange (const double iUpperYield,
                                const double iAverageYield) :
    _upperYield (iUpperYield), _averageYield (iAverageYield),
    _lowerYield (std::numeric_limits<double>::min()) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  YieldRange::YieldRange (const double iUpperYield,
                                const double iAverageYield,
                                const double iLowerYield) :
    _upperYield (iUpperYield), _averageYield (iAverageYield),
    _lowerYield (iLowerYield) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  YieldRange::~YieldRange() {
  }
  
  // //////////////////////////////////////////////////////////////////////
  void YieldRange::toStream (std::ostream& ioOut) const {
    ioOut << _averageYield << "([" << _lowerYield << ", "
          << _upperYield << "])";
  }
  
  // //////////////////////////////////////////////////////////////////////
  void YieldRange::fromStream (std::istream& ioIn) {
  } 
  
  // //////////////////////////////////////////////////////////////////////
  const std::string YieldRange::describe() const {
    std::ostringstream oStr;
    
    return oStr.str();
  }
  
}
