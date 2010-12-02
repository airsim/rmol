// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/stdair_types.hpp>
#include <stdair/bom/AirlineFeature.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  AirlineFeature::AirlineFeature (const Key_T& iKey) : _key (iKey) {
  }

  // ////////////////////////////////////////////////////////////////////
  AirlineFeature::~AirlineFeature () {
  }

  // ////////////////////////////////////////////////////////////////////
  void AirlineFeature::init (const ForecasterMode_T& iForecastMode,
                             const HistoricalDataLimit_T& iHistoricalDataLimit,
                             const OptimizerStruct& iOptimizerStruct,
                             const ControlMode_T& iControlMode) {
    _forecasterMode = iForecastMode;
    _historicalDataLimit = iHistoricalDataLimit;
    _optimizerStruct = iOptimizerStruct;
    _controlMode = iControlMode;
  }

  // ////////////////////////////////////////////////////////////////////
  std::string AirlineFeature::toString() const {
    std::ostringstream ostr;
    ostr << describeKey()
         << ", " << _forecasterMode
         << ", " << _historicalDataLimit
         << ", " << _optimizerStruct.describe()
         << ", " << _controlMode;
    return ostr.str();
  }
  
}

