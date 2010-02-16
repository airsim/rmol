// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/STDAIR_Types.hpp>
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/basic/DemandCharacteristics.hpp>

namespace stdair {
  
  // /////////////////////////////////////////////////////
  DemandCharacteristics::
  DemandCharacteristics (const DemandStreamKey_T& iKey,
                         const ContinuousFloatDuration_T& iArrivalPattern,
                         const ChannelProbabilityMass_T& iChannelProbMass,
                         const TripTypeProbabilityMass_T& iTripTypeProbMass,
                         const StayDurationProbabilityMass_T& iStayDurationProbMass,
                         const FrequentFlyerProbabilityMass_T& iFrequentFlyerProbMass,
                         const PreferredDepartureTimeCumulativeDistribution_T& iPreferredDepartureTimeCumulativeDistribution,
                         const WTPCumulativeDistribution_T& iWTPCumulativeDistribution)
    : _key (iKey), _arrivalPattern (iArrivalPattern),
      _channelProbabilityMass (iChannelProbMass),
      _tripTypeProbabilityMass (iTripTypeProbMass),
      _stayDurationProbabilityMass (iStayDurationProbMass),
      _frequentFlyerProbabilityMass (iFrequentFlyerProbMass),
      _preferredDepartureTimeCumulativeDistribution (iPreferredDepartureTimeCumulativeDistribution),
      _wtpCumulativeDistribution (iWTPCumulativeDistribution) {
  }
  
  // /////////////////////////////////////////////////////
  DemandCharacteristics::DemandCharacteristics ()
    : _key (DemandStreamKey_T ("", "", DEFAULT_DATE, "")) {
  }
  
  // /////////////////////////////////////////////////////
  DemandCharacteristics::~DemandCharacteristics () {
  }
  
  // /////////////////////////////////////////////////////
  DemandCharacteristics::
  DemandCharacteristics (const DemandCharacteristics& iDemandCharacteristics) 
    : _key (iDemandCharacteristics._key),
      _arrivalPattern (iDemandCharacteristics._arrivalPattern),
      _channelProbabilityMass (iDemandCharacteristics._channelProbabilityMass),
      _tripTypeProbabilityMass (iDemandCharacteristics._tripTypeProbabilityMass),
      _stayDurationProbabilityMass (iDemandCharacteristics._stayDurationProbabilityMass),
      _frequentFlyerProbabilityMass (iDemandCharacteristics._frequentFlyerProbabilityMass),
      _preferredDepartureTimeCumulativeDistribution (iDemandCharacteristics._preferredDepartureTimeCumulativeDistribution),
      _wtpCumulativeDistribution (iDemandCharacteristics._wtpCumulativeDistribution) {
  }
  
  // /////////////////////////////////////////////////////
  const AirportCode_T& DemandCharacteristics::getOrigin() const {
    return _key.getOrigin();
  }
    
  // /////////////////////////////////////////////////////
  const AirportCode_T& DemandCharacteristics::getDestination() const {
    return _key.getDestination();
  }
    
  // /////////////////////////////////////////////////////
  const Date_T& DemandCharacteristics::getPreferredDepartureDate() const {
    return _key.getPreferredDepartureDate();
  }

  // /////////////////////////////////////////////////////
  const CabinCode_T& DemandCharacteristics::getPreferredCabin() const {
    return _key.getPreferredCabin();
  }
  
  // /////////////////////////////////////////////////////
  std::string DemandCharacteristics::display() const {
    std::ostringstream oStr;

    //
    oStr << "****************** Demand characteristics ******************"
         << std::endl;
    oStr << "Origin ........................... : " << _key.getOrigin()
         << std::endl;
    oStr << "Destination ...................... : " << _key.getDestination()
         << std::endl;
    oStr << "Preferred departure date ......... : "
         << _key.getPreferredDepartureDate() << std::endl;
    oStr << "Preferred cabin .................. : " << _key.getPreferredCabin()
         << std::endl;
    oStr << "Arrival pattern (days from departure, proportion): ";
    oStr << _arrivalPattern.displayCumulativeDistribution() << std::endl;
    oStr << "Channel probability mass (channel, propotion): ";
    oStr << _channelProbabilityMass.displayProbabilityMassFunction()
         << std::endl;
    oStr << "Trip type probability mass (trip type, propotion): ";
    oStr << _tripTypeProbabilityMass.displayProbabilityMassFunction()
         << std::endl;
    oStr << "Stay duration probability mass (number of days, propotion): ";
    oStr << _stayDurationProbabilityMass.displayProbabilityMassFunction()
         << std::endl;
    oStr << "Frequent flyer probability mass (frequent flyer, propotion): ";
    oStr << _frequentFlyerProbabilityMass.displayProbabilityMassFunction()
         << std::endl;
    oStr << "Preferred departure time cumulative distribution (time, proportion: ";
    oStr << _preferredDepartureTimeCumulativeDistribution.displayCumulativeDistribution() << std::endl;
    oStr << "WTP cumulative distribution (WTP, proportion: ";
    oStr << _wtpCumulativeDistribution.displayCumulativeDistribution()
         << std::endl;

    
    return oStr.str();
  }
    
}

