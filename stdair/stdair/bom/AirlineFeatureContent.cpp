// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/AirlineFeatureContent.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  AirlineFeatureContent::
  AirlineFeatureContent (const BomKey_T& iKey)
    : _key (iKey) {
  }

  // ////////////////////////////////////////////////////////////////////
  AirlineFeatureContent::~AirlineFeatureContent () {
  }

  // ////////////////////////////////////////////////////////////////////
  void AirlineFeatureContent::
  init (const ForecasterMode_T& iForecastMode,
        const HistoricalDataLimit_T& iHistoricalDataLimit,
        const OptimizerStruct_T& iOptimizerStruct,
        const ControlMode_T& iControlMode) {
    _forecasterMode = iForecastMode;
    _historicalDataLimit = iHistoricalDataLimit;
    _optimizerStruct = iOptimizerStruct;
    _controlMode = iControlMode;
  }
  
}

