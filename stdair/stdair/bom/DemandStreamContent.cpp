// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <iosfwd>
#include <ostream>
#include <sstream>
// Boost
#include <boost/math/distributions/normal.hpp>
// Math
#include <math.h>
// STDAIR
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/bom/DemandStreamContent.hpp>
#include <stdair/service/Logger.hpp>


namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  DemandStreamContent::
  DemandStreamContent (const BomKey_T& iKey,
                       const DemandCharacteristics& iDemandCharacteristics,
                       const DemandDistribution& iDemandDistribution,
                       const RandomSeed_T& iNumberOfRequestsSeed,
                       const RandomSeed_T& iRequestDateTimeSeed,
                       const RandomSeed_T& iDemandCharacteristicsSeed)
    : _key (iKey),
      _demandCharacteristics (iDemandCharacteristics),
      _demandDistribution (iDemandDistribution),
      _totalNumberOfRequestsToBeGenerated (0),
      _numberOfRequestsRandomGenerator (iNumberOfRequestsSeed),
      _requestDateTimeRandomGenerator (iRequestDateTimeSeed),
      _demandCharacteristicsRandomGenerator (iDemandCharacteristicsSeed) {
    init();
  }

  // //////////////////////////////////////////////////////////////////////
  DemandStreamContent::~DemandStreamContent () {
  }

  // //////////////////////////////////////////////////////////////////////
  void DemandStreamContent::init() {
    // Generate the number of requests
    const RealNumber_T lMu = _demandDistribution.getMeanNumberOfRequests ();
    const RealNumber_T lSigma =
      _demandDistribution.getStandardDeviationNumberOfRequests ();
    
    const RealNumber_T lRealNumberOfRequestsToBeGenerated =
      _numberOfRequestsRandomGenerator.generateNormal (lMu, lSigma);

    NbOfRequests_T lIntegerNumberOfRequestsToBeGenerated = 0;
    if (lRealNumberOfRequestsToBeGenerated < 0.5) {
    	lIntegerNumberOfRequestsToBeGenerated = 0;
        
    } else {
      lIntegerNumberOfRequestsToBeGenerated =
        static_cast<NbOfRequests_T> (lRealNumberOfRequestsToBeGenerated + 0.5);
    }
    
    _totalNumberOfRequestsToBeGenerated = lIntegerNumberOfRequestsToBeGenerated;
  }

}
