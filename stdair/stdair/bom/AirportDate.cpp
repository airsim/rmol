// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/basic/BasConst_Inventory.hpp>
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
  void AirportDate::
  buildOutboundPathListList (OutboundPath& ioOutboundPath) {
    const OutboundPathKey_T& lOutboundPathKey = ioOutboundPath.getKey();
    const NbOfSegments_T& lNbOfSegments =
      lOutboundPathKey.getNbOfSegments ();
    assert (lNbOfSegments > 0
            && lNbOfSegments <= MAXIMUM_NUMBER_OF_SEGMENTS_IN_OND);
    const NbOfSegments_T lNbOfSegments_m1 =
      static_cast<const NbOfSegments_T> (lNbOfSegments - 1);

    // If needed, initialise the list of lists with empty fixed-length
    // outbound-path lists.
    while (_outboundPathListList.size() <= lNbOfSegments_m1) {
      OutboundPathLightList_T lOutboundPathLightList;
      _outboundPathListList.push_back (lOutboundPathLightList);
    }

    // Retrieve the i-fixed-length Outbound-Path list (i = number of
    // segments).
    OutboundPathLightList_T& lOutboundPathLightList =
      _outboundPathListList.at (lNbOfSegments-1);

    // Add the OutboundPath to that fixed-length-path list.
    lOutboundPathLightList.push_back (&ioOutboundPath);
  }
  
}

