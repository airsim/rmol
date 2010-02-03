// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <istream>
#include <ostream>
#include <sstream>
// StdAir
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
      _bookingClassList (iTravelSolutionStruct._bookingClassList) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  TravelSolutionStruct::
  TravelSolutionStruct (OutboundPath& ioOutboundPath,
                        const BookingClassSTLList_T& iBookingClassList)
    : _outboundPath_ptr (&ioOutboundPath),
      _bookingClassList (iBookingClassList) {
  }

  // ////////////////////////////////////////////////////////////////////
  TravelSolutionStruct::~TravelSolutionStruct () {
  }
      
  // //////////////////////////////////////////////////////////////////////
  OutboundPath& TravelSolutionStruct::getOutboundPath() const {
    assert (_outboundPath_ptr != NULL);
    return *_outboundPath_ptr;
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
    return "";
  }

}
