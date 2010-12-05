// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/bom/BookingRequestStruct.hpp>
#include <stdair/bom/EventStruct.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  EventStruct::
  EventStruct (const EventType_T& iEventType,
               const DemandStreamKeyStr_T& iDemandStreamKey,
               BookingRequestPtr_T ioRequestPtr)
    : _eventType (iEventType), _demandStreamKey (iDemandStreamKey) {
    _request = ioRequestPtr;

    // Compute the number of seconds between iDateTime and DEFAULT_DATETIME.
    assert (ioRequestPtr != NULL);
    Duration_T lDuration = ioRequestPtr->getRequestDateTime() - DEFAULT_DATETIME;
    _eventTimestamp = lDuration.total_milliseconds();
  }

  // //////////////////////////////////////////////////////////////////////
  EventStruct::
  EventStruct (const EventStruct& iEventStruct)
    : _eventType (iEventStruct._eventType),
      _eventTimestamp (iEventStruct._eventTimestamp),
      _demandStreamKey (iEventStruct._demandStreamKey) {
    _request = iEventStruct._request;
  }
  
  // //////////////////////////////////////////////////////////////////////
  EventStruct::~EventStruct () {
  }

}
