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

  public:
    // ///////////// Getters ///////////
    /** Get the cumulative probability of arrival pattern for last
        request generated so far. */
    const Probability_T& getCumulativeProbabilitySoFar () const {
      return _cumulativeProbabilitySoFar;
    }
    
    /** Get the number of requests generated so far. */
    const Count_T& getNumberOfRequestsGeneratedSoFar() const {
      return _numberOfRequestsGeneratedSoFar;
    }
    
    /** Set the cumulative probability of arrival pattern for last
        request generated so far. */
    void setCumulativeProbabilitySoFar (const Probability_T& iCumulativeProbability) {
      _cumulativeProbabilitySoFar = iCumulativeProbability;
    }
    
    /** Set the number of requests generated so far. */
    void setNumberOfRequestsGeneratedSoFar (const Count_T& iNumberOfRequests) {
      _numberOfRequestsGeneratedSoFar = iNumberOfRequests;
    }
    
  public:
    // ////////// Constructors and destructors /////////
    /** Constructor by default */
    RandomGenerationContext ();
    /** Default constructors. */
    RandomGenerationContext (const RandomGenerationContext&);

    /** Destructor */
    virtual ~RandomGenerationContext ();
    
  public:
    // /////////////// Business Methods //////////
    /** Increment counter of requests generated so far */
    void incrementGeneratedRequestsCounter ();
    
  
  private:
    // ////////// Attributes //////////
    /** Cumulative probability in arrival pattern for last request
        generated so far (needed for sequential generation)*/
    Probability_T _cumulativeProbabilitySoFar;
    
    /** Number of requests generated so far */
    Count_T _numberOfRequestsGeneratedSoFar;
    
  };

}
#endif // __STDAIR_BAS_RANDOM_GENERATION_CONTEXT_HPP
