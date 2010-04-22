// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <istream>
#include <ostream>
#include <sstream>
// STDAIR
#include <stdair/bom/AirlineFeature.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  AirlineFeature::
  AirlineFeature (const Key_T& iKey,
                  Structure_T& ioAirlineFeatureStructure)
    : AirlineFeatureContent (iKey),
      _structure (ioAirlineFeatureStructure) {
    init ();
  }
  
  // ////////////////////////////////////////////////////////////////////
  AirlineFeature::~AirlineFeature () {
  }

  // ////////////////////////////////////////////////////////////////////
  void AirlineFeature::init () {
  }

  // ////////////////////////////////////////////////////////////////////
  void AirlineFeature::
  init (const ForecasterMode_T& iForecastMode,
        const HistoricalDataLimit_T& iHistoricalDataLimit,
        const OptimizerStruct_T& iOptimizerStruct,
        const ControlMode_T& iControlMode) {
    AirlineFeatureContent::init (iForecastMode, iHistoricalDataLimit,
                                 iOptimizerStruct, iControlMode);
  }
  
  // ////////////////////////////////////////////////////////////////////
  void AirlineFeature::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void AirlineFeature::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string AirlineFeature::toString() const {
    std::ostringstream oStr;
    oStr << describeKey() << std::endl;
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string AirlineFeature::describe() const {
    std::ostringstream ostr;
    ostr << describeKey()
         << ", " << _forecasterMode
         << ", " << _historicalDataLimit
         << ", " << _optimizerStruct.describe()
         << ", " << _controlMode;
    return ostr.str();
  }
  
  // ////////////////////////////////////////////////////////////////////
  const std::string AirlineFeature::describeKey() const {
    return _key.toString();
  }
  
}

