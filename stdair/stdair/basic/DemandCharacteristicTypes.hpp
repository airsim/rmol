#ifndef __STDAIR_BAS_DEMANDCHARACTERISTICTYPES_HPP
#define __STDAIR_BAS_DEMANDCHARACTERISTICTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/STDAIR_Types.hpp>
#include <stdair/basic/ContinuousAttribute.hpp>
#include <stdair/basic/CategoricalAttribute.hpp>

namespace stdair {

  /** Type definition for the continuous distribition of the duration
      (as a float number). */
  typedef ContinuousAttribute<FloatDuration_T> ContinuousFloatDuration_T;
   
  /** Type definition for the arrival pattern. */
  typedef ContinuousFloatDuration_T::ContinuousDistribution_T ArrivalPattern_T;

  /** Type definition for the arrival pattern cumulative distribution. */
  typedef std::multimap<FloatDuration_T, Probability_T> ArrivalPatternCumulativeDistribution_T;

  /** Type definition for the arrival pattern inverse cumulative distribution. */
  typedef std::multimap<Probability_T, FloatDuration_T> ArrivalPatternInverseCumulativeDistribution_T;

  /** Define the booking channel probablity mass. */
  typedef CategoricalAttribute<ChannelLabel_T> ChannelProbabilityMass_T;

  /** Define the probability mass function type of booking channel. */
  typedef ChannelProbabilityMass_T::ProbabilityMassFunction_T ChannelProbabilityMassFunction_T;

  /** Define the inverse cumulative distribution of channel. */
  typedef ChannelProbabilityMass_T::InverseCumulativeDistribution_T ChannelInverserCumulativeDistribution_T;

  /** Define the trip type probablity mass. */
  typedef CategoricalAttribute<TripType_T> TripTypeProbabilityMass_T;

  /** Define the probability mass function type of trip type. */
  typedef TripTypeProbabilityMass_T::ProbabilityMassFunction_T TripTypeProbabilityMassFunction_T;

  /** Define the inverse cumulative distribution of trip type. */
  typedef TripTypeProbabilityMass_T::InverseCumulativeDistribution_T TripTypeInverserCumulativeDistribution_T;
  
  /** Define the stay duration probablity mass. */
  typedef CategoricalAttribute<DayDuration_T> StayDurationProbabilityMass_T;

  /** Define the probability mass function type of stay duration. */
  typedef StayDurationProbabilityMass_T::ProbabilityMassFunction_T StayDurationProbabilityMassFunction_T;

  /** Define the inverse cumulative distribution of stay duration. */
  typedef StayDurationProbabilityMass_T::InverseCumulativeDistribution_T StayDurationInverserCumulativeDistribution_T;

  /** Define the frequent flyer probablity mass. */
  typedef CategoricalAttribute<FrequentFlyer_T> FrequentFlyerProbabilityMass_T;

  /** Define the probability mass function type of frequent flyer. */
  typedef FrequentFlyerProbabilityMass_T::ProbabilityMassFunction_T FrequentFlyerProbabilityMassFunction_T;

  /** Define the inverse cumulative distribution of frequent flyer. */
  typedef FrequentFlyerProbabilityMass_T::InverseCumulativeDistribution_T FrequentFlyerInverserCumulativeDistribution_T;

  /** Define the preferred departure time cumulative distribution. */
  typedef ContinuousAttribute<IntDuration_T> PreferredDepartureTimeCumulativeDistribution_T;

  /** Define the preferred departure time continuous distribution. */
  typedef PreferredDepartureTimeCumulativeDistribution_T::ContinuousDistribution_T PreferredDepartureTimeContinuousDistribution_T;

  /** Define the preferred departure time continuous inverse distribution. */
  typedef PreferredDepartureTimeCumulativeDistribution_T::ContinuousInverseDistribution_T PreferredDepartureTimeContinuousInverseDistribution_T;

  /** Define the willingness-to-pay cumulative distribution. */
  typedef ContinuousAttribute<WTP_T> WTPCumulativeDistribution_T;

  /** Define the willingness-to-pay continuous distribution. */
  typedef WTPCumulativeDistribution_T::ContinuousDistribution_T WTPContinuousDistribution_T;

  /** Define the willingness-to-pay continuous inverse distribution. */
  typedef WTPCumulativeDistribution_T::ContinuousInverseDistribution_T WTPContinuousInverseDistribution_T;
  
}
#endif // __STDAIR_BAS_DEMANDCHARACTERISTICTYPES_HPP
