// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/basic/DemandDistribution.hpp>

namespace stdair {

  // /////////////////////////////////////////////////////
  DemandDistribution::
  DemandDistribution (const NbOfRequests_T& iMean,
                      const StandardDeviationValue_T& iStandardDeviation)
    : _meanNumberOfRequests (iMean),
      _standardDeviationNumberOfRequests (iStandardDeviation){
  }
  
  // /////////////////////////////////////////////////////
  DemandDistribution::DemandDistribution () {
  }
  
  // /////////////////////////////////////////////////////
  DemandDistribution::~DemandDistribution () {
  }
  
  // /////////////////////////////////////////////////////
  DemandDistribution::
  DemandDistribution (const DemandDistribution& iDemandDistribution)
    : _meanNumberOfRequests (iDemandDistribution._meanNumberOfRequests),
      _standardDeviationNumberOfRequests (iDemandDistribution._standardDeviationNumberOfRequests) {
  }
  
  // /////////////////////////////////////////////////////
  std::string DemandDistribution::display() const {
    std::ostringstream oStr;

    oStr << "****************** Demand distribution ******************"
         << std::endl;
    oStr << "Mean number of requests .......... : "
         << _meanNumberOfRequests << std::endl;
    oStr << "Std dev of number of requests .... : "
         << _standardDeviationNumberOfRequests << std::endl;

    return oStr.str();
  }
    
}

