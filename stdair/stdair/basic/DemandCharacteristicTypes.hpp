#ifndef __STDAIR_BAS_DEMANDCHARACTERISTICTYPES_HPP
#define __STDAIR_BAS_DEMANDCHARACTERISTICTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/STDAIR_Types.hpp>
#include <stdair/basic/ContinuousAttributeLite.hpp>
#include <stdair/basic/CategoricalAttributeLite.hpp>

namespace stdair {

  /** Type definition for the continuous distribition of the duration
      (as a float number). */
  typedef ContinuousAttributeLite<FloatDuration_T> ContinuousFloatDuration_T;
   
  /** Type definition for the arrival pattern cumulative distribution. */
  typedef ContinuousFloatDuration_T::ContinuousDistribution_T ArrivalPatternCumulativeDistribution_T;

  /** Define the point-of-sale probablity mass. */
  typedef CategoricalAttributeLite<AirportCode_T> POSProbabilityMass_T;

  /** Define the probability mass function type of point-of-sale. */
  typedef POSProbabilityMass_T::ProbabilityMassFunction_T POSProbabilityMassFunction_T;
  
  /** Define the booking channel probablity mass. */
  typedef CategoricalAttributeLite<ChannelLabel_T> ChannelProbabilityMass_T;

  /** Define the probability mass function type of booking channel. */
  typedef ChannelProbabilityMass_T::ProbabilityMassFunction_T ChannelProbabilityMassFunction_T;

  /** Define the trip type probablity mass. */
  typedef CategoricalAttributeLite<TripType_T> TripTypeProbabilityMass_T;

  /** Define the probability mass function type of trip type. */
  typedef TripTypeProbabilityMass_T::ProbabilityMassFunction_T TripTypeProbabilityMassFunction_T;
  
  /** Define the stay duration probablity mass. */
  typedef CategoricalAttributeLite<DayDuration_T> StayDurationProbabilityMass_T;

  /** Define the probability mass function type of stay duration. */
  typedef StayDurationProbabilityMass_T::ProbabilityMassFunction_T StayDurationProbabilityMassFunction_T;

  /** Define the frequent flyer probablity mass. */
  typedef CategoricalAttributeLite<FrequentFlyer_T> FrequentFlyerProbabilityMass_T;

  /** Define the probability mass function type of frequent flyer. */
  typedef FrequentFlyerProbabilityMass_T::ProbabilityMassFunction_T FrequentFlyerProbabilityMassFunction_T;

  /** Define the preferred departure time cumulative distribution. */
  typedef ContinuousAttributeLite<IntDuration_T> PreferredDepartureTimeCumulativeDistribution_T;

  /** Define the preferred departure time continuous distribution. */
  typedef PreferredDepartureTimeCumulativeDistribution_T::ContinuousDistribution_T PreferredDepartureTimeContinuousDistribution_T;

  /** Define the willingness-to-pay cumulative distribution. */
  typedef ContinuousAttributeLite<WTP_T> WTPCumulativeDistribution_T;

  /** Define the willingness-to-pay continuous distribution. */
  typedef WTPCumulativeDistribution_T::ContinuousDistribution_T WTPContinuousDistribution_T;

  /** Define the value of time cumulative distribution. */
  typedef ContinuousAttributeLite<PriceValue_T> ValueOfTimeCumulativeDistribution_T;

  /** Define the value of time continuous distribution. */
  typedef ValueOfTimeCumulativeDistribution_T::ContinuousDistribution_T ValueOfTimeContinuousDistribution_T;
}
#endif // __STDAIR_BAS_DEMANDCHARACTERISTICTYPES_HPP
