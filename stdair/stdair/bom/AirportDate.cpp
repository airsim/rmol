// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/BomSource.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  AirportDate::AirportDate (const Key_T& iKey, 
                            Structure_T& ioAirportStructure)
    : AirportDateContent (iKey), _structure (ioAirportStructure) {
    init ();
  }
  
  // ////////////////////////////////////////////////////////////////////
  AirportDate::~AirportDate () {
  }

  // ////////////////////////////////////////////////////////////////////
  void AirportDate::init () {
    _structure.initChildrenHolder<OutboundPath>();
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
    oStr << describeShortKey() << std::endl;
    return oStr.str();
  }
    
  // ////////////////////////////////////////////////////////////////////
  const std::string AirportDate::describeKey() const {
    std::ostringstream oStr;
    oStr << _structure.describeParentKey() << ", " << describeShortKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  OutboundPathList_T AirportDate::getOutboundPathList () const {
    return _structure.getChildrenHolder<OutboundPath>();
  }

  // ////////////////////////////////////////////////////////////////////
  OutboundPathMultimap_T AirportDate::getOutboundPathMultimap () const {
    return _structure.getChildrenHolder<OutboundPath>();
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

