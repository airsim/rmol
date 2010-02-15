#ifndef __STDAIR_BOM_DEMANDSTREAM_HPP
#define __STDAIR_BOM_DEMANDSTREAM_HPP

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
#include <stdair/bom/BookingRequestTypes.hpp>
#include <stdair/bom/DemandStreamKey.hpp>
#include <stdair/bom/DemandStreamTypes.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {
  
  /** Class modeling a demand stream. */
  class DemandStream  : public BomContent {
    friend class FacBomContent;
    
  public:
    // ///////////// Getters ///////////
    /** Get the key */
    const DemandStreamKey_T& getKey () const {
      return _key;
    }
    
    /** Get the total number of requests to be generated. */
    const NbOfRequests_T& getTotalNumberOfRequestsToBeGenerated() const {
      return _totalNumberOfRequestsToBeGenerated;
    }

    /** Get the origin. */
    const AirportCode_T& getOrigin() const {
      return _demandCharacteristics.getOrigin();
    }
    
    /** Get the destination. */
    const AirportCode_T& getDestination() const {
      return _demandCharacteristics.getDestination();
    }
    
    /** Get the preferred departure date. */
    const Date_T& getPreferredDepartureDate() const {
      return _demandCharacteristics.getPreferredDepartureDate();
    }

    /** Get the passenger type. */
    const PassengerType& getPaxType() const {
      return _demandCharacteristics.getPaxType();
    }
    
    /** Get the arrival pattern. */
    const ContinuousFloatDuration_T& getArrivalPattern() const {
      return _demandCharacteristics.getArrivalPattern();
    }

    /** Get the mean number of requests. */
    const NbOfRequests_T& getMeanNumberOfRequests() const {
      return _demandDistribution.getMeanNumberOfRequests();
    }
    
    /** Get the standard deviation of number of requests. */
    const StandardDeviationValue_T& getStandardDeviationNumberOfRequests() const {
      return _demandDistribution.getStandardDeviationNumberOfRequests();
    }
    
    /** Get the cumulative probability of arrival pattern for last
        request generated so far. */
    const Probability_T& getCumulativeProbabilitySoFar () const {
      return _randomGenerationContext.getCumulativeProbabilitySoFar();
    }
    
    /** Get the number of requests generated so far. */
    const Count_T getNumberOfRequestsGeneratedSoFar() const {
      return _randomGenerationContext.getCumulativeProbabilitySoFar();;
    }
    
    /** Get the seed of the random generator for the number of requests. */
    const RandomSeed_T& getNumberOfRequestsRandomGeneratorSeed () const {
      return _numberOfRequestsRandomGenerator.getSeed();
    }

    /** Get the seed of the random generator for the request datetime. */
    const RandomSeed_T& getRequestDateTimeRandomGeneratorSeed () const {
      return _requestDateTimeRandomGenerator.getSeed();
    }

    /** Get the seed of the random generator for the demand characteristics. */
    const RandomSeed_T& getDemandCharacteristicsRandomGeneratorSeed () const {
      return _demandCharacteristicsRandomGenerator.getSeed();
    }

  public:
    // //////////////// Setters //////////////////
    /** Set the cumulative probability of arrival pattern for last
        request generated so far. */
    void setCumulativeProbabilitySoFar (const Probability_T& iCumulativeProbability) {
      _randomGenerationContext.
        setCumulativeProbabilitySoFar (iCumulativeProbability);
    }
    
    /** Set the number of requests generated so far. */
    void setNumberOfRequestsGeneratedSoFar (const Count_T& iNumberOfRequests) {
      _randomGenerationContext.
        setNumberOfRequestsGeneratedSoFar (iNumberOfRequests);
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
    // /////////////// Business Methods //////////
    /** Increment counter of requests generated so far */
    void incrementGeneratedRequestsCounter () {
      _randomGenerationContext.incrementGeneratedRequestsCounter();
    }

    
    /** Generate a randomized number following a uniform distribution
        between 0 (included) and 1 (excluded). */
    RealNumber_T generateUniform01WithNumberOfRequestRandomGenerator () {
      return _numberOfRequestsRandomGenerator.generateUniform01();
    }
    RealNumber_T generateUniform01WithRequestDateTimeRandomGenerator() {
      return _requestDateTimeRandomGenerator.generateUniform01();
    }
    RealNumber_T generateUniform01WithDemandCharacteristicsRandomGenerator() {
      return _demandCharacteristicsRandomGenerator.generateUniform01();
    }
    
    /** Generate a randomized number following a uniform distribution
        between a minimum (included) and a maximum (excluded)
        value. */
    RealNumber_T generateUniformWithNumberOfRequestRandomGenerator (const RealNumber_T& iMinValue, const RealNumber_T& iMaxValue) {
      return _numberOfRequestsRandomGenerator.generateUniform (iMinValue,
                                                               iMaxValue);
    }
    RealNumber_T generateUniformWithRequestDateTimeRandomGenerator(const RealNumber_T& iMinValue, const RealNumber_T& iMaxValue) {
      return _requestDateTimeRandomGenerator.generateUniform (iMinValue,
                                                              iMaxValue);
    }
    RealNumber_T generateUniformWithDemandCharacteristicsRandomGenerator(const RealNumber_T& iMinValue, const RealNumber_T& iMaxValue) {
      return _demandCharacteristicsRandomGenerator.generateUniform (iMinValue,
                                                                    iMaxValue);
    }
    
    /** Generate a randomized number following a normal distribution
        specified by a mean and a standard deviation. */
    RealNumber_T generateNormalWithNumberOfRequestRandomGenerator (const RealNumber_T& mu, const RealNumber_T& sigma) {
      return _numberOfRequestsRandomGenerator.generateNormal (mu, sigma);
    }
    RealNumber_T generateNormalWithRequestDateTimeRandomGenerator(const RealNumber_T& mu, const RealNumber_T& sigma) {
      return _requestDateTimeRandomGenerator.generateNormal (mu, sigma);
    }
    RealNumber_T generateNormalWithDemandCharacteristicsRandomGenerator(const RealNumber_T& mu, const RealNumber_T& sigma) {
      return _demandCharacteristicsRandomGenerator.generateNormal (mu, sigma);
    }
       
  protected:
    // ////////// Constructors and destructors /////////
    /** Constructor by default */
    DemandStream (const DemandStreamKey_T&, const DemandCharacteristics&,
                  const DemandDistribution&,
                  const RandomSeed_T& iNumberOfRequestsSeed,
                  const RandomSeed_T& iRequestDateTimeSeed,
                  const RandomSeed_T& iDemandCharacteristicsSeed);
    /** Default constructors. */
    DemandStream ();
    DemandStream (const DemandStream&);
    /** Initialization. */
    void init();
    /** Destructor. */
    ~DemandStream ();

    
  protected:
    // ////////// Attributes //////////
    /** Key */
    DemandStreamKey_T _key;
    
    /** Demand characteristics */
    DemandCharacteristics _demandCharacteristics;

    /** Demand distribution */
    DemandDistribution _demandDistribution;
    
    /** Total number of requests to be generated*/
    NbOfRequests_T _totalNumberOfRequestsToBeGenerated;

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
#endif // __STDAIR_BOM_DEMANDSTREAM_HPP
