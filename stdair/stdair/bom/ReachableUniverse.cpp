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
  ReachableUniverse::ReachableUniverse (const Key_T& iKey, 
                            Structure_T& ioAirportStructure)
    : ReachableUniverseContent (iKey), _structure (ioAirportStructure) {
    init ();
  }
  
  // ////////////////////////////////////////////////////////////////////
  ReachableUniverse::~ReachableUniverse () {
  }

  // ////////////////////////////////////////////////////////////////////
  void ReachableUniverse::init () {
    _structure.initChildrenHolder<OriginDestinationSet>();
  }

  // ////////////////////////////////////////////////////////////////////
  void ReachableUniverse::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void ReachableUniverse::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string ReachableUniverse::toString() const {
    std::ostringstream oStr;
    oStr << describeShortKey() << std::endl;
    return oStr.str();
  }
    
  // ////////////////////////////////////////////////////////////////////
  const std::string ReachableUniverse::describeKey() const {
    std::ostringstream oStr;
    oStr << _structure.describeParentKey() << ", " << describeShortKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const ReachableUniverse::Parent_T& ReachableUniverse::getParent () const {
    return _structure.getParent().getContent();
  }

  // ////////////////////////////////////////////////////////////////////
  OriginDestinationSetList_T ReachableUniverse::
  getOriginDestinationSetList () const {
    return _structure.getChildrenHolder<OriginDestinationSet>();
  }

  // ////////////////////////////////////////////////////////////////////
  OriginDestinationSetMap_T ReachableUniverse::
  getOriginDestinationSetMap () const {
    return _structure.getChildrenHolder<OriginDestinationSet>();
  }

  // ////////////////////////////////////////////////////////////////////
  OriginDestinationSet* ReachableUniverse::
  getOriginDestinationSet (const AirportCode_T& iAirportCode) const {
    return _structure.getChildPtr<OriginDestinationSet> (iAirportCode);
  }
  
  // ////////////////////////////////////////////////////////////////////
  void ReachableUniverse::
  addSegmentPathPeriod (const SegmentPathPeriod& iSegmentPathPeriod) {
    const NbOfSegments_T& lNbOfSegments = iSegmentPathPeriod.getNbOfSegments ();
    assert (lNbOfSegments > 0
            && lNbOfSegments <= MAXIMAL_NUMBER_OF_SEGMENTS_IN_OND);

    // If needed, initialise the list of lists with empty fixed-length
    // segment path period lists.
    while (_segmentPathPeriodListList.size() < lNbOfSegments) {
      SegmentPathPeriodLightList_T lSegmentPathPeriodLightList;
      _segmentPathPeriodListList.push_back (lSegmentPathPeriodLightList);
    }

    // Retrieve the i-fixed-length segment path period list (i = number of
    // segments).
    SegmentPathPeriodLightList_T& lSegmentPathPeriodLightList =
      _segmentPathPeriodListList.at (lNbOfSegments-1);

    // Add the SegmentPathPeriod to that fixed-length-path list.
    lSegmentPathPeriodLightList.push_back (&iSegmentPathPeriod);
  }
  
}

