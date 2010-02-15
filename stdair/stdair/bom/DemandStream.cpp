// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <iosfwd>
#include <ostream>
#include <sstream>
#include <cmath>
// Boost
#include <boost/math/distributions/normal.hpp>
// StdAir
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/basic/DemandCharacteristics.hpp>
#include <stdair/basic/RandomGeneration.hpp>
#include <stdair/basic/RandomGenerationContext.hpp>
#include <stdair/bom/BookingRequestStruct.hpp>
#include <stdair/bom/DemandStream.hpp>
#include <stdair/service/Logger.hpp>


namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  DemandStream::
  DemandStream (const DemandStreamKey_T& iKey,
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
  DemandStream::~DemandStream () {
  }

  // //////////////////////////////////////////////////////////////////////
  void DemandStream::init() {
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
