// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
#include <rmol/field/FldDistributionParameters.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  FldDistributionParameters::FldDistributionParameters () :
    _mean (0.0), _standardDeviation (1.0) {
  }

  // //////////////////////////////////////////////////////////////////////
  FldDistributionParameters::
  FldDistributionParameters (const FldDistributionParameters& iParams) :
    _mean (iParams.getMean()),
    _standardDeviation (iParams.getStandardDeviation()) {
  }

  // //////////////////////////////////////////////////////////////////////
  FldDistributionParameters::
  FldDistributionParameters (const double iMean,
                             const double iStandardDeviation) :
    _mean (iMean), _standardDeviation (iStandardDeviation) {
  }

  // //////////////////////////////////////////////////////////////////////
  FldDistributionParameters::~FldDistributionParameters() {
  }
  
  // //////////////////////////////////////////////////////////////////////
  double FldDistributionParameters::getVariance() const {
    return _standardDeviation * _standardDeviation;
  }
  
}