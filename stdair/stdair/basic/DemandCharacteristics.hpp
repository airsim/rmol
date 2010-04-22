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
    /** Get the arrival pattern. */
    const ContinuousFloatDuration_T& getArrivalPattern() const {
      return _arrivalPattern;
    }

    /** Get the point-of-sale probability mass. */
    const POSProbabilityMass_T& getPOSProbabilityMass() const {
      return _posProbabilityMass;
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

    /** Get the value of time cumulative distribution. */
    const ValueOfTimeCumulativeDistribution_T& getValueOfTimeCumulativeDistribution () const {
      return _valueOfTimeCumulativeDistribution;
    }
    
  public:
    // ////////////// Display Support Methods //////////
    /** Display demand characteristics */
    std::string display() const;

    
  public:
    // ////////// Constructors and destructors /////////
    /** Default constructor. */
    DemandCharacteristics (const ArrivalPatternCumulativeDistribution_T&,
                           const POSProbabilityMassFunction_T&,
                           const ChannelProbabilityMassFunction_T&,
                           const TripTypeProbabilityMassFunction_T&,
                           const StayDurationProbabilityMassFunction_T&,
                           const FrequentFlyerProbabilityMassFunction_T&,
                           const PreferredDepartureTimeContinuousDistribution_T&,
                           const WTPContinuousDistribution_T&,
                           const ValueOfTimeContinuousDistribution_T&);
    
    /** Destructor */
    ~DemandCharacteristics ();
  private:
    /** Default constructor. */
    DemandCharacteristics ();
    /** Copy constructor. */
    DemandCharacteristics (const DemandCharacteristics&);

  private:
    // //////////////////// Attributes /////////////////////
    /** Arrival pattern (cumulative distribution of timing of arrival
        of requests (negative number of days between departure date
        and request date). */
    const ContinuousFloatDuration_T _arrivalPattern;

    /** POS probability mass. */
    const POSProbabilityMass_T _posProbabilityMass;
    
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

    /** Value of time cumulative distribution. */
    const ValueOfTimeCumulativeDistribution_T _valueOfTimeCumulativeDistribution;
  };

}
#endif // __STDAIR_BAS_DEMAND_CHARACTERISTICS_HPP
