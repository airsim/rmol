// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/bom/AirportDateStructure.hpp>
#include <stdair/bom/AirportDate.hpp>
#include <stdair/bom/OutboundPath.hpp>
#include <stdair/bom/BomList.hpp>
#include <stdair/bom/BomMap.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  AirportDate::AirportDate (const BomKey_T& iKey, 
                            BomStructure_T& ioAirportStructure)
    : AirportDateContent (iKey), _airportDateStructure (ioAirportStructure) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  AirportDate::~AirportDate () {
  }

  // ////////////////////////////////////////////////////////////////////
  void AirportDate::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void AirportDate::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string AirportDate::toString() const {
    std::ostringstream oStr;

    // First, put the key of that level
    oStr << describeShortKey() << std::endl;

    // Then, browse the children
    // [...] (no child for now)
    
    return oStr.str();
  }
    
  // ////////////////////////////////////////////////////////////////////
  const std::string AirportDate::describeKey() const {
    return _airportDateStructure.describeKey();
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string AirportDate::describeShortKey() const {
    return _airportDateStructure.describeShortKey();
  }

  // ////////////////////////////////////////////////////////////////////
  OutboundPathList_T AirportDate::getOutboundPathList () const {
    return _airportDateStructure.getChildrenHolder();
  }

  // ////////////////////////////////////////////////////////////////////
  OutboundPathMap_T AirportDate::getOutboundPathMap () const {
    return _airportDateStructure.getChildrenHolder();
  }

  // ////////////////////////////////////////////////////////////////////
  OutboundPath* AirportDate::
  getOutboundPath (const OutboundPathKey_T& iKey) const {
    return _airportDateStructure.getContentChild (iKey);
  }
  
}

