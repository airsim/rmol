#ifndef __STDAIR_BAS_RANDOM_GENERATION_CONTEXT_HPP
#define __STDAIR_BAS_RANDOM_GENERATION_CONTEXT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
// STDAIR
#include <stdair/STDAIR_Types.hpp>

namespace stdair {

  /** Structure holding the context necessary for demand random generation. */
  struct RandomGenerationContext {
    
    // ////////// Constructors and destructors /////////
    /** Constructor by default */
    RandomGenerationContext ();
    /** Default constructors. */
    RandomGenerationContext (const RandomGenerationContext&);
    /** Destructor */
    ~RandomGenerationContext ();
    
    // /////////////// Business Methods //////////
    /** Increment counter of requests generated so far */
    void incrementGeneratedRequestsCounter ();

        // ////////// Attributes //////////
    /** Cumulative probability in arrival pattern for last request
        generated so far (needed for sequential generation)*/
    Probability_T _cumulativeProbabilitySoFar;
    
    /** Number of requests generated so far */
    Count_T _numberOfRequestsGeneratedSoFar;
    
  };

}
#endif // __STDAIR_BAS_RANDOM_GENERATION_CONTEXT_HPP
