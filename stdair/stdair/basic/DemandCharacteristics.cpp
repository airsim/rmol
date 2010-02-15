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
  DemandCharacteristics::DemandCharacteristics (const DemandStreamKey_T& iKey)
    : _key (iKey) {
  }
  
  // /////////////////////////////////////////////////////
  DemandCharacteristics::DemandCharacteristics ()
    : _key (DemandStreamKey_T("", "", DEFAULT_DATE, PassengerType::LAST_VALUE)) {
  }
  
  // /////////////////////////////////////////////////////
  DemandCharacteristics::~DemandCharacteristics () {
  }
  
  // /////////////////////////////////////////////////////
  DemandCharacteristics::
  DemandCharacteristics (const DemandCharacteristics& iDemandCharacteristics) 
    : _key (iDemandCharacteristics._key),
      _arrivalPattern (iDemandCharacteristics._arrivalPattern) {
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
  const PassengerType& DemandCharacteristics::getPaxType() const {
    return _key.getPassengerType();
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
    oStr << "Passenger type ................... : " << _key.getPassengerType()
         << std::endl;
    oStr << "Arrival pattern (days from departure, proportion): ";

    //
    oStr << _arrivalPattern.displayCumulativeDistribution() << std::endl;
    
    return oStr.str();
  }
    
}

