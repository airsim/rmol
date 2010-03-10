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
                       const ArrivalPatternCumulativeDistribution_T& iArrivalPattern,
                       const POSProbabilityMassFunction_T& iPOSProbMass,
                       const ChannelProbabilityMassFunction_T& iChannelProbMass,
                       const TripTypeProbabilityMassFunction_T& iTripTypeProbMass,
                       const StayDurationProbabilityMassFunction_T& iStayDurationProbMass,
                       const FrequentFlyerProbabilityMassFunction_T& iFrequentFlyerProbMass,
                       const PreferredDepartureTimeContinuousDistribution_T& iPreferredDepartureTimeContinuousDistribution,
                       const WTPContinuousDistribution_T& iWTPContinuousDistribution,
                       const ValueOfTimeContinuousDistribution_T& iValueOfTimeContinuousDistribution,
                       const DemandDistribution& iDemandDistribution,
                       const RandomSeed_T& iNumberOfRequestsSeed,
                       const RandomSeed_T& iRequestDateTimeSeed,
                       const RandomSeed_T& iDemandCharacteristicsSeed)
    : _key (iKey),
      _demandCharacteristics (iKey, iArrivalPattern, iPOSProbMass,
                              iChannelProbMass, iTripTypeProbMass,
                              iStayDurationProbMass, iFrequentFlyerProbMass,
                              iPreferredDepartureTimeContinuousDistribution,
                              iWTPContinuousDistribution,
                              iValueOfTimeContinuousDistribution),
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
