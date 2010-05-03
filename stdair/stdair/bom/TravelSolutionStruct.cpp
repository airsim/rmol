// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <istream>
#include <ostream>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_BookingClass.hpp>
#include <stdair/bom/OutboundPath.hpp>
#include <stdair/bom/TravelSolutionStruct.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  TravelSolutionStruct::TravelSolutionStruct ()
    : _outboundPath_ptr (NULL) {
    assert (false);
  }
  
  // ////////////////////////////////////////////////////////////////////
  TravelSolutionStruct::
  TravelSolutionStruct (const TravelSolutionStruct& iTravelSolutionStruct)
    : _outboundPath_ptr (iTravelSolutionStruct._outboundPath_ptr),
      _bookingClassList (iTravelSolutionStruct._bookingClassList),
      _fare (iTravelSolutionStruct._fare),
      _availability (iTravelSolutionStruct._availability) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  TravelSolutionStruct::
  TravelSolutionStruct (OutboundPath& ioOutboundPath,
                        const BookingClassSTLList_T& iBookingClassList)
    : _outboundPath_ptr (&ioOutboundPath), _bookingClassList (iBookingClassList),
      _fare (DEFAULT_FARE_VALUE), _availability (DEFAULT_AVAILABILITY) {
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
    if (_outboundPath_ptr != NULL) {
      oStr << *_outboundPath_ptr;
    }
    
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string TravelSolutionStruct::describeKey() const {
    std::string oString;
    if (_outboundPath_ptr != NULL) {
      oString = _outboundPath_ptr->describeKey();
    }
    return oString;
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string TravelSolutionStruct::describeShortKey() const {
    std::string oString;
    if (_outboundPath_ptr != NULL) {
      oString = _outboundPath_ptr->describeShortKey();
    }
    return oString;
  }
  
}
