#ifndef __STDAIR_BAS_DEMAND_STREAM_HPP
#define __STDAIR_BAS_DEMAND_STREAM_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost
#include <boost/shared_ptr.hpp>
// STL
#include <iosfwd>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/basic/DemandCharacteristics.hpp>
#include <stdair/basic/DemandDistribution.hpp>
#include <stdair/basic/RandomGeneration.hpp>
#include <stdair/basic/RandomGenerationContext.hpp>
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/BookingRequestStruct.hpp>

namespace stdair {

  // Type definitions.
  /** Define the smart pointer to a booking request. */
  typedef boost::shared_ptr<BookingRequestStruct> BookingRequestPtr_T;
  
  /** Class modeling a demand stream. */
  class DemandStream : public BomContent {
    friend class FacBomContent;
    
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
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const { ioOut << toString(); }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object. */
    std::string toString() const { return describeKey(); }
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const { return std::string (""); }

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return std::string (""); }

  public:
    // /////////////// Business Methods //////////////
    /** Check whether enough requests have already been generated. */
    const bool stillHavingRequestsToBeGenerated () const;
    
    /** Generate the next request. */
    BookingRequestPtr_T generateNext ();

  private:
    // ////////// Constructors and destructors /////////
    /** Constructor by default */
    DemandStream (const DemandStreamKey_T&, const DemandCharacteristics&,
                  const DemandDistribution&, const RandomSeed_T&, 
                  const RandomSeed_T&, const RandomSeed_T&);

    /** Destructor */
    virtual ~DemandStream ();

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
