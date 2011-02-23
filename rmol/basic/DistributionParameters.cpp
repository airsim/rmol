// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <sstream>
// RMOL
#include <rmol/basic/DistributionParameters.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  DistributionParameters::DistributionParameters () :
    _mean (0.0), _standardDeviation (1.0) {
  }

  // //////////////////////////////////////////////////////////////////////
  DistributionParameters::
  DistributionParameters (const DistributionParameters& iParams) :
    _mean (iParams.getMean()),
    _standardDeviation (iParams.getStandardDeviation()) {
  }

  // //////////////////////////////////////////////////////////////////////
  DistributionParameters::
  DistributionParameters (const double iMean,
                             const double iStandardDeviation) :
    _mean (iMean), _standardDeviation (iStandardDeviation) {
  }

  // //////////////////////////////////////////////////////////////////////
  DistributionParameters::~DistributionParameters() {
  }
  
  // //////////////////////////////////////////////////////////////////////
  void DistributionParameters::toStream (std::ostream& ioOut) const {
    ioOut << "N (" << _mean << ", " << _standardDeviation << ")";
  }
    
  // //////////////////////////////////////////////////////////////////////
  const std::string DistributionParameters::describe() const {
    std::ostringstream oStr;
    
    return oStr.str();
  }
  
  // //////////////////////////////////////////////////////////////////////
  void DistributionParameters::fromStream (std::istream& ioIn) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  double DistributionParameters::getVariance() const {
    return _standardDeviation * _standardDeviation;
  }
  
}
