// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/bom/SegmentDateStructure.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/BomList.hpp>
#include <stdair/bom/BomMap.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentDate::SegmentDate (const BomKey_T& iKey,
                            BomStructure_T& ioSegmentStructure)
    : SegmentDateContent (iKey), _segmentDateStructure (ioSegmentStructure) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  SegmentDate::~SegmentDate () {
  }

  // //////////////////////////////////////////////////////////////////////
  void SegmentDate::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // //////////////////////////////////////////////////////////////////////
  void SegmentDate::fromStream (std::istream& ioIn) {
  }

  // //////////////////////////////////////////////////////////////////////
  std::string SegmentDate::toString() const {
    std::ostringstream oStr;

    // First, put the key of that level
    oStr << describeShortKey() << std::endl;

    // Then, browse the children
    // [...] (no child for now)
    
    return oStr.str();
  }
    
  // //////////////////////////////////////////////////////////////////////
  const std::string SegmentDate::describeKey() const {
    return _segmentDateStructure.describeKey();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string SegmentDate::describeShortKey() const {
    return _segmentDateStructure.describeShortKey();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentCabinList_T SegmentDate::getSegmentCabinList () const {
    return _segmentDateStructure.getChildrenList();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentCabinMap_T SegmentDate::getSegmentCabinMap () const {
    return _segmentDateStructure.getChildrenList();
  }

  // //////////////////////////////////////////////////////////////////////
  LegDateList_T SegmentDate::getLegDateList () const {
    return _segmentDateStructure.getLegDateHolder();
  }
  
  // ///////// ///////////////////////////////////////////////////////////////
//   bool SegmentDate::
//   isConnectable (const SegmentDate& iSegmentDate) const {
//     bool oIsConnectable = false;

//     const Date_T& lOffDate = getOffDate();
//     const Date_T& lBoardDate = iSegmentDate.getBoardDate();
//     const DateOffSet_T lDateOffSet = lBoardDate - lOffDate;
//     const Duration_T lDateOffSetInHours (lDateOffSet.days() * 24, 0, 0);

//     const Duration_T& lOffTime = getOffTime();
//     const Duration_T& lBoardTime = iSegmentDate.getBoardTime();

//     const Duration_T lStopOverTime =
//       lBoardTime - lOffTime + lDateOffSetInHours;

//     oIsConnectable = lStopOverTime >= DEFAULT_MINIMUM_CONNECTION_TIME;

//     return oIsConnectable;
//   }
  
}

