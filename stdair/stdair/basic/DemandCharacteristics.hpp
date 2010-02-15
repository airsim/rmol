#ifndef __STDAIR_BAS_DEMAND_CHARACTERISTICS_HPP
#define __STDAIR_BAS_DEMAND_CHARACTERISTICS_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/STDAIR_Types.hpp>
#include <stdair/basic/ArrivalPattern.hpp>
#include <stdair/bom/DemandStreamKey.hpp>

namespace stdair {
  
  /** Class modeling the characteristics of a demand type. */
  struct DemandCharacteristics {
  public:
    
    // ///////////// Getters ///////////    
    /** Get the key. */
    const DemandStreamKey_T& getKey() const {
      return _key;
    }
    
    /** Get the origin. */
    const AirportCode_T& getOrigin() const;
    
    /** Get the destination. */
    const AirportCode_T& getDestination() const;
    
    /** Get the preferred departure date. */
    const Date_T& getPreferredDepartureDate() const;

    /** Get the preferred cabin. */
    const CabinCode_T& getPreferredCabin() const;
    
    /** Get the arrival pattern. */
    const ContinuousFloatDuration_T& getArrivalPattern() const {
      return _arrivalPattern;
    }

    
  public:
    // ///////////// Setters ///////////
    /** Set the arrival pattern. */
    void setArrivalPattern (const ContinuousFloatDuration_T& iArrivalPattern) {
      _arrivalPattern = iArrivalPattern;
    }

    
  public:
    // ////////////// Display Support Methods //////////
    /** Display demand characteristics */
    std::string display() const;

    
  public:
    // ////////// Constructors and destructors /////////
    /** Default constructor. */
    DemandCharacteristics (const DemandStreamKey_T& iKey);
    
    /** Default constructor. */
    // TODO: That copy constructor should be private
    DemandCharacteristics ();
    
    /** Copy constructor. */
    // TODO: That copy constructor should be private
    DemandCharacteristics (const DemandCharacteristics&);

    /** Destructor */
    virtual ~DemandCharacteristics ();
  

  private:
    // //////////////////// Attributes /////////////////////
    /** DemandStream Key */
    const DemandStreamKey_T _key;
    
    /** Arrival pattern (cumulative distribution of timing of arrival
        of requests (negative number of days between departure date
        and request date). */
    ContinuousFloatDuration_T _arrivalPattern;
    
    /** Trip type probability mass */
    // CategoricalAttribute<TripType_T> _tripTypeProbabilityMass;
    
    /** Willingness-to-pay cumulative distribution */
    // ContinuousAttribute<MonetaryValue_T> _willingnessToPayCumulativeDistribution;
    
  };

}
#endif // __STDAIR_BAS_DEMAND_CHARACTERISTICS_HPP
