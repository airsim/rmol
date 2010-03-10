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
                const RandomSeed_T& iDemandCharacteristicsSeed,
                BomStructure_T& ioDemandStreamStructure)
    : DemandStreamContent (iKey, iArrivalPattern, iPOSProbMass,
                           iChannelProbMass, iTripTypeProbMass,
                           iStayDurationProbMass, iFrequentFlyerProbMass,
                           iPreferredDepartureTimeContinuousDistribution,
                           iWTPContinuousDistribution,
                           iValueOfTimeContinuousDistribution,
                           iDemandDistribution, iNumberOfRequestsSeed,
                           iRequestDateTimeSeed, iDemandCharacteristicsSeed),
      _demandStreamStructure (ioDemandStreamStructure) {
  }

  // //////////////////////////////////////////////////////////////////////
  DemandStream::~DemandStream () {
  }
}
