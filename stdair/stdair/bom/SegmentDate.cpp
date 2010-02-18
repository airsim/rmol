// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/basic/BasConst_TravelSolution.hpp>
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
    return _key.describe();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string SegmentDate::describeShortKey() const {
    return _key.toString();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentCabinList_T SegmentDate::getSegmentCabinList () const {
    return _segmentDateStructure.getChildrenHolder();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentCabinMap_T SegmentDate::getSegmentCabinMap () const {
    return _segmentDateStructure.getChildrenHolder();
  }

  // //////////////////////////////////////////////////////////////////////
  LegDateList_T SegmentDate::getLegDateList () const {
    return _segmentDateStructure.getLegDateHolder();
  }
  
  // ///////// ///////////////////////////////////////////////////////////////
  bool SegmentDate::
  isConnectable (const SegmentDate& iSegmentDate) const {
    bool oIsConnectable = false;
    
    const Date_T& lOffDate = getOffDate();
    const Date_T& lBoardingDate = iSegmentDate.getBoardingDate();
    const DateOffSet_T lDateOffSet = lBoardingDate - lOffDate;
    const Duration_T lDateOffSetInHours (lDateOffSet.days() * 24, 0, 0);
    
    const Duration_T& lOffTime = getOffTime();
    const Duration_T& lBoardingTime = iSegmentDate.getBoardingTime();
    
    const Duration_T lStopOverTime =
      lBoardingTime - lOffTime + lDateOffSetInHours;

    oIsConnectable = lStopOverTime >= DEFAULT_MINIMUM_CONNECTION_TIME;

    return oIsConnectable;
  }
  
}

