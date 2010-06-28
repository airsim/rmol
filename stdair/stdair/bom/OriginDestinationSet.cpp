// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomSource.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  OriginDestinationSet::OriginDestinationSet (const Key_T& iKey,
                    Structure_T& ioOriginDestinationSetStructure)
    : OriginDestinationSetContent (iKey),
      _structure (ioOriginDestinationSetStructure) {
    init ();
  }

  // ////////////////////////////////////////////////////////////////////
  OriginDestinationSet::~OriginDestinationSet () {
  }

  // ////////////////////////////////////////////////////////////////////
  void OriginDestinationSet::init () {
    _structure.initChildrenHolder<SegmentPathPeriod>();
  }

  // ////////////////////////////////////////////////////////////////////
  void OriginDestinationSet::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void OriginDestinationSet::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string OriginDestinationSet::toString() const {
    std::ostringstream oStr;
    oStr << _key.toString();
    return oStr.str();
  }
    
  // ////////////////////////////////////////////////////////////////////
  const std::string OriginDestinationSet::describeKey() const {
    return _key.toString();
  }

  // ////////////////////////////////////////////////////////////////////
  const OriginDestinationSet::Parent_T& OriginDestinationSet::
  getParent () const {
    return _structure.getParent().getContent();
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentPathPeriodList_T OriginDestinationSet::
  getSegmentPathPeriodList () const {
    return _structure.getChildrenHolder<SegmentPathPeriod>();
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentPathPeriodMultimap_T OriginDestinationSet::
  getSegmentPathPeriodMultimap () const {
    return _structure.getChildrenHolder<SegmentPathPeriod>();
  }

}

