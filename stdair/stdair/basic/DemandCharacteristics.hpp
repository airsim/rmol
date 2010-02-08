#ifndef __STDAIR_BAS_DEMAND_CHARACTERISTICS_HPP
#define __STDAIR_BAS_DEMAND_CHARACTERISTICS_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/basic/ContinuousAttribute.hpp>

namespace stdair {
  
  /** Class modeling the characteristics of a demand type. */
  struct DemandCharacteristics {
  public:
    
    // ///////////// Getters ///////////    
    /** Get the origin. */
    const LocationCode_T& getOrigin() const {
      return _origin;
    }
    
    /** Get the preferred departure date. */
    const Date_T& getPreferredDepartureDate() const {
      return _preferredDepartureDate;
    }
    
    /** Get the arrival pattern. */
    const ContinuousAttribute<FloatDuration_T>& getArrivalPattern() const {
      return _arrivalPattern;
    }

  public:
    // ///////////// Setters ///////////
    /** Set the origin. */
    void setOrigin (const LocationCode_T& iOrigin) {
      _origin = iOrigin;
    }
    
    /** Set the preferred departure date. */
    void setPreferredDepartureDate (const Date_T& iPreferredDepartureDate) {
      _preferredDepartureDate = iPreferredDepartureDate;
    }
    
    /** Set the arrival pattern. */
    void setArrivalPattern (const ContinuousAttribute<FloatDuration_T>& iArrivalPattern) {
      _arrivalPattern = iArrivalPattern;
    }

  public:
    // ////////////// Display Support Methods //////////
    /** Display demand characteristics */
    std::string display() const;

    
  public:
    // ////////// Constructors and destructors /////////
    /** Constructor by default */
    DemandCharacteristics ();
    
    /** Copy constructor */
    DemandCharacteristics (const DemandCharacteristics&); // Should be private, but well...

    /** Destructor */
    virtual ~DemandCharacteristics ();
  
  
  private:
    // ////////// Attributes //////////
    /** Origin */
    LocationCode_T _origin;
    
    /** Preferred departure date */
    Date_T _preferredDepartureDate;
    
    /** Arrival pattern (cumulative distribution of timing of arrival
        of requests (negative number of days between departure date
        and request date)*/
    ContinuousAttribute<FloatDuration_T> _arrivalPattern;
    
    /** Trip type probability mass */
    //CategoricalAttribute<TripType_T> _tripTypeProbabilityMass;
    
    /** Willingness-to-pay cumulative distribution */
    //ContinuousAttribute<MonetaryValue_T> _willingnessToPayCumulativeDistribution;
    
  };

}
#endif // __STDAIR_BAS_DEMAND_CHARACTERISTICS_HPP
