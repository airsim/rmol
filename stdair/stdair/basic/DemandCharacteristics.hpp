#ifndef __STDAIR_BAS_DEMAND_CHARACTERISTICS_HPP
#define __STDAIR_BAS_DEMAND_CHARACTERISTICS_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/STDAIR_Types.hpp>
#include <stdair/basic/DemandCharacteristicTypes.hpp>
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

    /** Get the channel probability mass. */
    const ChannelProbabilityMass_T& getChannelProbabilityMass() const {
      return _channelProbabilityMass;
    }

    /** Get the trip type probability mass. */
    const TripTypeProbabilityMass_T& getTripTypeProbabilityMass() const {
      return _tripTypeProbabilityMass;
    }
    
    /** Get the stay duration probability mass. */
    const StayDurationProbabilityMass_T& getStayDurationProbabilityMass() const {
      return _stayDurationProbabilityMass;
    }

    /** Get the frequent flyer probability mass. */
    const FrequentFlyerProbabilityMass_T& getFrequentFlyerProbabilityMass() const {
      return _frequentFlyerProbabilityMass;
    }

    /** Get the preferred departure time cumulative distribution. */
    const PreferredDepartureTimeCumulativeDistribution_T& getPreferredDepartureTimeCumulativeDistribution () const {
      return _preferredDepartureTimeCumulativeDistribution;
    }

    /** Get the WTP cumulative distribution. */
    const WTPCumulativeDistribution_T& getWTPCumulativeDistribution() const {
      return _wtpCumulativeDistribution;
    }
    
  public:
    // ////////////// Display Support Methods //////////
    /** Display demand characteristics */
    std::string display() const;

    
  public:
    // ////////// Constructors and destructors /////////
    /** Default constructor. */
    DemandCharacteristics (const DemandStreamKey_T&,
                           const ContinuousFloatDuration_T&,
                           const ChannelProbabilityMass_T&,
                           const TripTypeProbabilityMass_T&,
                           const StayDurationProbabilityMass_T&,
                           const FrequentFlyerProbabilityMass_T&,
                           const PreferredDepartureTimeCumulativeDistribution_T&,
                           const WTPCumulativeDistribution_T&);
    
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
    const ContinuousFloatDuration_T _arrivalPattern;

    /** Channel probability mass. */
    const ChannelProbabilityMass_T _channelProbabilityMass;
    
    /** Trip type probability mass */
    const TripTypeProbabilityMass_T _tripTypeProbabilityMass;
    
    /** Stay duration probability mass */
    const StayDurationProbabilityMass_T _stayDurationProbabilityMass;
    
    /** Frequent flyer probability mass */
    const FrequentFlyerProbabilityMass_T _frequentFlyerProbabilityMass;

    /** Preferred departure time cumulative distribution. */
    const PreferredDepartureTimeCumulativeDistribution_T _preferredDepartureTimeCumulativeDistribution;
    
    /** Willingness-to-pay cumulative distribution */
    const WTPCumulativeDistribution_T _wtpCumulativeDistribution;
    
  };

}
#endif // __STDAIR_BAS_DEMAND_CHARACTERISTICS_HPP
