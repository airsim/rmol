#ifndef __STDAIR_BAS_ARRIVALPATTERN_HPP
#define __STDAIR_BAS_ARRIVALPATTERN_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/STDAIR_Types.hpp>
#include <stdair/basic/ContinuousAttribute.hpp>

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
  
}
#endif // __STDAIR_BAS_ARRIVALPATTERN_HPP
