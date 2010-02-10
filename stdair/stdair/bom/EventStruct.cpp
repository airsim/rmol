// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BookingRequestStruct.hpp>
#include <stdair/bom/EventStruct.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  EventStruct::
  EventStruct(const EventType_T& iEventType, const DateTime_T& iDateTime,
              DemandStream& ioDemandStream,  BookingRequestPtr_T ioRequestPtr)
    : _eventType (iEventType),
      _eventDateTime (iDateTime),
      _demandStream (&ioDemandStream) {
    _request = ioRequestPtr;
  }

  // //////////////////////////////////////////////////////////////////////
  EventStruct::
  EventStruct (const EventStruct& iEventStruct)
    : _eventType (iEventStruct._eventType),
      _eventDateTime (iEventStruct._eventDateTime),
      _demandStream (iEventStruct._demandStream) {
    _request = iEventStruct._request;
  }
  
  // //////////////////////////////////////////////////////////////////////
  EventStruct::EventStruct (const DateTime_T& iDateTime) 
    : _eventType (""),
      _eventDateTime (iDateTime),
      _demandStream (NULL) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  EventStruct::~EventStruct () {
  }

}
