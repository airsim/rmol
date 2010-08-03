// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
// STDAIR
#include <stdair/basic/RandomGenerationContext.hpp>

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  RandomGenerationContext::RandomGenerationContext ()
    : _cumulativeProbabilitySoFar (0.0),
      _numberOfRequestsGeneratedSoFar (0) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  RandomGenerationContext::RandomGenerationContext (const RandomGenerationContext& iRandomGenerationContext)
    : _cumulativeProbabilitySoFar (iRandomGenerationContext._cumulativeProbabilitySoFar),
      _numberOfRequestsGeneratedSoFar (iRandomGenerationContext._numberOfRequestsGeneratedSoFar) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  RandomGenerationContext::~RandomGenerationContext () {
  }
    
  // //////////////////////////////////////////////////////////////////////
  void RandomGenerationContext::incrementGeneratedRequestsCounter () {
    ++_numberOfRequestsGeneratedSoFar;
  }

  // //////////////////////////////////////////////////////////////////////
  void RandomGenerationContext::reset () {
    _cumulativeProbabilitySoFar = 0.0;
    _numberOfRequestsGeneratedSoFar = 0;
  }

}
