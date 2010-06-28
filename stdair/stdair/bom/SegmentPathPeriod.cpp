// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomSource.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentPathPeriod::SegmentPathPeriod (const Key_T& iKey,
                              Structure_T& ioSegmentPathPeriodStructure)
    : SegmentPathPeriodContent (iKey),
      _structure (ioSegmentPathPeriodStructure) {
    init ();
  }
  
  // ////////////////////////////////////////////////////////////////////
  SegmentPathPeriod::~SegmentPathPeriod () {
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentPathPeriod::init () {
    _structure.initChildrenHolder<SegmentPeriod>();
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentPathPeriod::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentPathPeriod::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string SegmentPathPeriod::toString() const {
    std::ostringstream oStr;

    // First, put the key of that level
    oStr << describeShortKey() << std::endl;

    // Then, browse the children
    // [...] (no child for now)
    
    return oStr.str();
  }
    
  // ////////////////////////////////////////////////////////////////////
  const std::string SegmentPathPeriod::describeKey() const {
    std::ostringstream oStr;
    oStr << _structure.describeParentKey() << ", " << describeShortKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentPeriodList_T SegmentPathPeriod::getSegmentPeriodList () const {
    return _structure.getChildrenHolder<SegmentPeriod>();
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentPeriodMap_T SegmentPathPeriod::getSegmentPeriodMap () const {
    return _structure.getChildrenHolder<SegmentPeriod>();
  }

  // ////////////////////////////////////////////////////////////////////
  const SegmentPathPeriod::Parent_T& SegmentPathPeriod::getParent () const {
    return _structure.getParent().getContent();
  }

  // ////////////////////////////////////////////////////////////////////
  const SegmentPeriod* SegmentPathPeriod::getLastSegmentPeriod () const {
    const SegmentPeriod* oSegment_ptr = NULL;
    
    // Retrieve the last segment of the list
    SegmentPeriodList_T lSegmentPeriodList = getSegmentPeriodList();
    SegmentPeriodList_T::reverse_iterator itLastSegment =
      lSegmentPeriodList.rbegin();

    if (itLastSegment == lSegmentPeriodList.rend()) {
      return oSegment_ptr;
    }
    
    oSegment_ptr = &*itLastSegment;
    assert (oSegment_ptr != NULL);

    return oSegment_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  const SegmentPeriod* SegmentPathPeriod::getFirstSegmentPeriod () const {
    const SegmentPeriod* oSegment_ptr = NULL;
    
    // Retrieve the first segment of the list
    SegmentPeriodList_T lSegmentPeriodList = getSegmentPeriodList();
    SegmentPeriodList_T::iterator itFirstSegment= lSegmentPeriodList.begin();

    if (itFirstSegment == lSegmentPeriodList.end()) {
      return oSegment_ptr;
    }
    
    oSegment_ptr = &*itFirstSegment;
    assert (oSegment_ptr != NULL);

    return oSegment_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  const AirportCode_T& SegmentPathPeriod::getDestination () const {
    const SegmentPeriod* lLastSegment_ptr = getLastSegmentPeriod();
    assert (lLastSegment_ptr != NULL);
    return lLastSegment_ptr->getOffPoint();
  }  
  
  // ////////////////////////////////////////////////////////////////////
  void SegmentPathPeriod::updateAirlineCode() {
    // TODO: to be optimised.
    // std::ostringstream ostr;
    // SegmentPeriodList_T lSegmentPeriodList = getSegmentPeriodList();
    
    // for (SegmentPeriodList_T::iterator itSegmentPeriod = 
    //        lSegmentPeriodList.begin();
    //      itSegmentPeriod != lSegmentPeriodList.end(); ++itSegmentPeriod) {
    //   const SegmentPeriod& lSegmentPeriod = *itSegmentPeriod;
    //   ostr << lSegmentPeriod.getAirlineCode();
    // }
    
    // const AirlineCode_T lAirlineCode (ostr.str());
    // setAirlineCode(lAirlineCode);
  }

  // ////////////////////////////////////////////////////////////////////
  bool SegmentPathPeriod::
  isAirlineFlown (const AirlineCode_T& iAirlineCode) const {
    bool oAirlineFlown = false;

    // const SegmentPeriodList_T& lSegmentPeriodList = getSegmentPeriodList ();
    // for (SegmentPeriodList_T::iterator itSegmentPeriod =
    //        lSegmentPeriodList.begin();
    //      itSegmentPeriod != lSegmentPeriodList.end(); ++itSegmentPeriod) {
    //   const SegmentPeriod& lSegmentPeriod = *itSegmentPeriod;

    //   const AirlineCode_T& lSegmentAirlineCode =
    //     lSegmentPeriod.getAirlineCode();
    //   if (lSegmentAirlineCode == iAirlineCode) {
    //     oAirlineFlown = true;
    //     break;
    //   }
    // }

    return oAirlineFlown;
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentPathPeriod::
  updateAfterAddingSegmentPeriod (const SegmentPeriod& iSegmentPeriod) {
    // Increment the flight path code
    // std::ostringstream ostr;
    // FlightPathCode_T lPreviousFPCode = getCurrentFlightPathCode();
    // ostr << lPreviousFPCode
    //      << iSegmentPeriod.getFlightNumber();
    // setFlightPathCode(ostr.str());
  }

  // ////////////////////////////////////////////////////////////////////
  const SegmentPathPeriodKey_T SegmentPathPeriod::
  connectWithAnotherSegment(const SegmentPathPeriod& iSingleSegmentPath) const {
    SegmentPathPeriodKey_T oSegmentPathPeriodKey;

    // Retrieve the (only) segment period of the single segment path.
    const SegmentPeriod* lSegmentPeriod_ptr = getFirstSegmentPeriod ();
    assert (lSegmentPeriod_ptr != NULL);

    // Check if the new segment period will create a circle.
    const AirportCode_T& lDestination = lSegmentPeriod_ptr->getOffPoint();
    if (checkCircle (lDestination) == true) {
      return oSegmentPathPeriodKey;
    }
    

    return oSegmentPathPeriodKey;
  }

  // ////////////////////////////////////////////////////////////////////
  bool SegmentPathPeriod::
  isConnectable (const SegmentPathPeriod& iSegmentPathPeriod) const {
    // Delegate the check on the two (potentially) connecting SegmentPeriod
    // objects, i.e., the last SegmentPeriod of the current SegmentPathPeriod,
    // and the first SegmentPeriod of the given SegmentPathPeriod.
    const SegmentPeriod* lOffSegment_ptr = getLastSegmentPeriod();
    assert (lOffSegment_ptr != NULL);

    const SegmentPeriod* lBoardingSegment_ptr =
      iSegmentPathPeriod.getFirstSegmentPeriod();
    assert (lBoardingSegment_ptr != NULL);
      
    return lOffSegment_ptr->isConnectable (*lBoardingSegment_ptr);
    // TODO
  }

  // ////////////////////////////////////////////////////////////////////
  bool SegmentPathPeriod::
  checkCircle (const AirlineCode_T& iDestination) const {
    const SegmentPeriodList_T& lSegmentPeriodList = getSegmentPeriodList();
    for (SegmentPeriodList_T::iterator itSegment = lSegmentPeriodList.begin();
         itSegment != lSegmentPeriodList.end(); ++itSegment) {
      const SegmentPeriod& lCurrentSegment = *itSegment;
      const AirlineCode_T& lCurrentBoardingPoint =
        lCurrentSegment.getBoardingPoint();
      if (lCurrentBoardingPoint == iDestination) {
        return true;
      }
    }
    return false;
  }
  
}

