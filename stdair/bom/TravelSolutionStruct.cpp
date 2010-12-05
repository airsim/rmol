// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_BookingClass.hpp>
#include <stdair/bom/TravelSolutionStruct.hpp>

namespace stdair {
  // ////////////////////////////////////////////////////////////////////
  TravelSolutionStruct::TravelSolutionStruct () 
    : _fare (DEFAULT_FARE_VALUE), _availability (DEFAULT_AVAILABILITY) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  TravelSolutionStruct::
  TravelSolutionStruct (const TravelSolutionStruct& iTravelSolutionStruct)
    : _segmentDateKeyList (iTravelSolutionStruct._segmentDateKeyList),
      _bookingClassKeyList (iTravelSolutionStruct._bookingClassKeyList),
      _fare (iTravelSolutionStruct._fare),
      _availability (iTravelSolutionStruct._availability) {
  }

  // ////////////////////////////////////////////////////////////////////
  TravelSolutionStruct::~TravelSolutionStruct () {
  }
  
  // //////////////////////////////////////////////////////////////////////
  void TravelSolutionStruct::toStream (std::ostream& ioOut) const {
    ioOut << describe();
  }

  // //////////////////////////////////////////////////////////////////////
  void TravelSolutionStruct::fromStream (std::istream& ioIn) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string TravelSolutionStruct::describe() const {
    std::ostringstream oStr;
      
    ClassList_String_T::const_iterator itClass = _bookingClassKeyList.begin();

    for (KeyList_T::const_iterator itSegmentKey = _segmentDateKeyList.begin ();
         itSegmentKey != _segmentDateKeyList.end(); ++itSegmentKey) {
      oStr << *itSegmentKey << ", ";
      if (itClass != _bookingClassKeyList.end()) {
        oStr << *itClass << ", ";
        ++itClass;
      }
    }

    oStr << _fare << ", " << _availability;
    
    return oStr.str();
  }
  
}
