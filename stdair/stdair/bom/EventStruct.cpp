// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/bom/BookingRequestStruct.hpp>
#include <stdair/bom/EventStruct.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  EventStruct::
  EventStruct(const EventType_T& iEventType, const DateTime_T& iDateTime,
              const DemandStreamKeyStr_T& iDemandStreamKey,
              BookingRequestPtr_T ioRequestPtr)
    : _eventType (iEventType), _eventDateTime (iDateTime),
      _demandStreamKey (iDemandStreamKey) {
    _request = ioRequestPtr;
  }

  // //////////////////////////////////////////////////////////////////////
  EventStruct::
  EventStruct (const EventStruct& iEventStruct)
    : _eventType (iEventStruct._eventType),
      _eventDateTime (iEventStruct._eventDateTime),
      _demandStreamKey (iEventStruct._demandStreamKey) {
    _request = iEventStruct._request;
  }
  
  // //////////////////////////////////////////////////////////////////////
  EventStruct::EventStruct (const DateTime_T& iDateTime) 
    : _eventType (""), _eventDateTime (iDateTime),
      _demandStreamKey ("") {
  }
  
  // //////////////////////////////////////////////////////////////////////
  EventStruct::~EventStruct () {
  }

  // ////////////////////////////////////////////////////////////////////
  void EventStruct::moveForwardInTime () {
    _eventDateTime += DEFAULT_EPSILON_DURATION;
  }

}
