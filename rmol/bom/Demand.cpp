// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
#include <rmol/bom/Demand.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  Demand::Demand () :
    _yieldRange (FldYieldRange()),
    _distributionParameters (FldDistributionParameters()) {
  }

  // //////////////////////////////////////////////////////////////////////
  Demand::Demand (const Demand& iDemand) :
    _yieldRange (iDemand.getYieldRange()),
    _distributionParameters (iDemand.getDistributionParameters()) {
  }

  // //////////////////////////////////////////////////////////////////////
  Demand::Demand (const FldDistributionParameters& iDistributionParameters,
		  const FldYieldRange& iYieldRange) :
    _yieldRange (iYieldRange),
    _distributionParameters (iDistributionParameters) {
  }

  // //////////////////////////////////////////////////////////////////////
  Demand::~Demand() {
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string Demand::describeShortKey() const {
    std::ostringstream oStr;
    oStr << _yieldRange;
    return oStr.str();
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string Demand::describeKey() const {
    return describeShortKey();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string Demand::toString() const {
    std::ostringstream oStr;
    oStr << describeShortKey() << ", ";
    oStr << _distributionParameters;
    return oStr.str();
  }   

  // //////////////////////////////////////////////////////////////////////
  void Demand::toStream (std::ostream& ioOut) const {
    ioOut << toString();
  }
  
  // //////////////////////////////////////////////////////////////////////
  void Demand::fromStream (std::istream& ioIn) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string Demand::shortDisplay() const {
    std::ostringstream oStr;
    oStr << describeKey();
    oStr << ", distribution parameters = " << _distributionParameters
         << std::endl;
    return oStr.str();
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string Demand::display() const {
    std::ostringstream oStr;
    oStr << shortDisplay();
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  double Demand::getUpperYield() const {
    return _yieldRange.getUpperYield();
  }

  // //////////////////////////////////////////////////////////////////////
  double Demand::getAverageYield() const {
    return _yieldRange.getAverageYield();
  }

  // //////////////////////////////////////////////////////////////////////
  double Demand::getLowerYield() {
    return _yieldRange.getLowerYield();
  }

  // //////////////////////////////////////////////////////////////////////
  double Demand::getMean() const {
    return _distributionParameters.getMean();
  }

  // //////////////////////////////////////////////////////////////////////
  double Demand::getStandardDeviation() const {
    return _distributionParameters.getStandardDeviation();
  }

  // //////////////////////////////////////////////////////////////////////
  double Demand::getVariance() const {
    return _distributionParameters.getVariance();
  }

  // //////////////////////////////////////////////////////////////////////
  void Demand::setMean (const double iMean) {
    _distributionParameters.setMean (iMean);
  }

  // /////////////////////////////////////////////////////////////////////
  void Demand::setSD (const double iSD) {
    _distributionParameters.setStandardDeviation (iSD);
  }
}
