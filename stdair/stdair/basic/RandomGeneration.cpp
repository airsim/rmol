// STL
#include <cassert>
#include <iostream>
// Boost
#include <boost/version.hpp>
#if BOOST_VERSION >= 103500
#include <boost/math/distributions/normal.hpp>
#endif // BOOST_VERSION >= 103500
//STDAIR
#include <stdair/basic/RandomGeneration.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  RandomGeneration::RandomGeneration (const RandomSeed_T& iSeed)
    : _seed (iSeed), _generator (iSeed),
      _uniformGenerator (_generator, boost::uniform_real<> (0, 1)) {
    init ();
  }

  // //////////////////////////////////////////////////////////////////////
  RandomGeneration::RandomGeneration (const RandomGeneration& iRandomGeneration)
    : _seed (iRandomGeneration._seed),
      _generator (iRandomGeneration._generator),
      _uniformGenerator (iRandomGeneration._uniformGenerator) {
  }

  // //////////////////////////////////////////////////////////////////////
  RandomGeneration::RandomGeneration ()
    : _seed (0), _generator (0),
      _uniformGenerator (_generator, boost::uniform_real<> (0, 1)) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  RandomGeneration::~RandomGeneration () {
  }

  // //////////////////////////////////////////////////////////////////////
  void RandomGeneration::init () {
  }

  // //////////////////////////////////////////////////////////////////////
  RealNumber_T RandomGeneration::generateUniform01 () {
    const RealNumber_T lVariateUnif = _uniformGenerator();
    return lVariateUnif;
  }
  
  // //////////////////////////////////////////////////////////////////////
  RealNumber_T RandomGeneration::
  generateUniform (const RealNumber_T& iMinValue, const RealNumber_T& iMaxValue){
    const RealNumber_T lVariateUnif = 
      iMinValue + _uniformGenerator() * (iMaxValue - iMinValue);
    return lVariateUnif;
  }

  // //////////////////////////////////////////////////////////////////////
  RealNumber_T RandomGeneration::
  generateNormal (const RealNumber_T& mu, const RealNumber_T& sigma) {
#if BOOST_VERSION >= 103500
    const Probability_T lVariateUnif = generateUniform01 ();
    const boost::math::normal lNormal (mu, sigma);
    const RealNumber_T lRealNumberOfRequestsToBeGenerated =
      boost::math::quantile(lNormal, lVariateUnif);
#else // BOOST_VERSION >= 103500
    // TODO: rely on GSL when Boost version smaller than 1.35
    const RealNumber_T lRealNumberOfRequestsToBeGenerated = 0.0;
#endif // BOOST_VERSION >= 103500

    return lRealNumberOfRequestsToBeGenerated;
  }
}
