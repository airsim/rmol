// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/bom/DemandStream.hpp>


namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  DemandStream::
  DemandStream (const Key_T& iKey,
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
                Structure_T& ioDemandStreamStructure)
    : DemandStreamContent (iKey, iArrivalPattern, iPOSProbMass,
                           iChannelProbMass, iTripTypeProbMass,
                           iStayDurationProbMass, iFrequentFlyerProbMass,
                           iPreferredDepartureTimeContinuousDistribution,
                           iWTPContinuousDistribution,
                           iValueOfTimeContinuousDistribution,
                           iDemandDistribution, iNumberOfRequestsSeed,
                           iRequestDateTimeSeed, iDemandCharacteristicsSeed),
      _structure (ioDemandStreamStructure) {
    init ();
  }

  // ////////////////////////////////////////////////////////////////////
  DemandStream::~DemandStream () {
  }

  // ////////////////////////////////////////////////////////////////////
  void DemandStream::init () {
  }

  // ////////////////////////////////////////////////////////////////////
  void DemandStream::reset () {
    DemandStreamContent::init ();
    _randomGenerationContext.reset();
  }  
}
