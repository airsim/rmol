// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/bom/AirlineFeatureStructure.hpp>
#include <stdair/bom/AirlineFeature.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  AirlineFeature::
  AirlineFeature (const BomKey_T& iKey,
                  const ForecasterMode_T& iForecastMode,
                  const HistoricalDataLimit_T& iHistoricalDataLimit,
                  const OptimizerStruct_T& iOptimizerStruct,
                  const ControlMode_T& iControlMode,
                  BomStructure_T& ioAirlineFeatureStructure)
    : AirlineFeatureContent (iKey, iForecastMode, iHistoricalDataLimit,
                             iOptimizerStruct, iControlMode),
      _airlineFeatureStructure (ioAirlineFeatureStructure) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  AirlineFeature::~AirlineFeature () {
  }

  // //////////////////////////////////////////////////////////////////////
  void AirlineFeature::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // //////////////////////////////////////////////////////////////////////
  void AirlineFeature::fromStream (std::istream& ioIn) {
  }

  // //////////////////////////////////////////////////////////////////////
  std::string AirlineFeature::toString() const {
    std::ostringstream oStr;
    oStr << describeShortKey() << std::endl;
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string AirlineFeature::describe() const {
    std::ostringstream ostr;
    ostr << describeKey()
         << ", " << _forecasterMode
         << ", " << _historicalDataLimit
         << ", " << _optimizerStruct.describe()
         << ", " << _controlMode;
    return ostr.str();
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string AirlineFeature::describeKey() const {
    return _key.toString();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string AirlineFeature::describeShortKey() const {
    return _key.toString();
  }
  
}

