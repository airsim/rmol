#ifndef __STDAIR_BAS_DEMAND_STREAM_HPP
#define __STDAIR_BAS_DEMAND_STREAM_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/basic/DemandCharacteristics.hpp>
#include <stdair/basic/DemandDistribution.hpp>
#include <stdair/basic/RandomGeneration.hpp>
#include <stdair/basic/RandomGenerationContext.hpp>
#include <stdair/bom/BookingRequestStruct.hpp>

namespace stdair {
  
  /** Class modeling a demand stream. */
  class DemandStream {

  public:
    // ///////////// Getters ///////////
    /** Get the key */
    const DemandStreamKey_T& getKey () const {
      return _key;
    }
    
    /** Get the total number of requests to be generated. */
    const Count_T& getTotalNumberOfRequestsToBeGenerated() const {
      return _totalNumberOfRequestsToBeGenerated;
    }

  public:
    // ///////////// Setters ///////////
    /** Set the demand characteristics */
    void setKey (const DemandStreamKey_T& iKey) {
      _key = iKey;
    }

  public:
    // /////////////// Business Methods //////////
    /** Generate the next request. */
    bool generateNext (BookingRequestStruct&);

  public:
    // ////////// Constructors and destructors /////////
    /** Constructor by default */
    DemandStream (const DemandStreamKey_T&, const DemandCharacteristics&,
                  const DemandDistribution&, const RandomSeed_T&, 
                  const RandomSeed_T&, const RandomSeed_T&);

    /** Destructor */
    virtual ~DemandStream ();

  private:
    /** Default constructors. */
    DemandStream ();
    DemandStream (const DemandStream&);

    /** Initialization. */
    void init();
  
  private:
    // ////////// Attributes //////////
    
    /** Key */
    DemandStreamKey_T _key;
    
    /** Demand characteristics */
    DemandCharacteristics _demandCharacteristics;

    /** Demand distribution */
    DemandDistribution _demandDistribution;
    
    /** Total number of requests to be generated*/
    Count_T _totalNumberOfRequestsToBeGenerated;

    /** Random generation context */
    RandomGenerationContext _randomGenerationContext;
  
    /** Random generator for number of requests */
    RandomGeneration _numberOfRequestsRandomGenerator;
    
    /** Random generator for request datetime */
    RandomGeneration _requestDateTimeRandomGenerator;
    
    /** Random generator for demand characteristics */
    RandomGeneration _demandCharacteristicsRandomGenerator;
    
  };

}
#endif // __STDAIR_BAS_DEMAND_STREAM_HPP
