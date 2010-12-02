#ifndef __STDAIR_BAS_EVENTSTRUCT_HPP
#define __STDAIR_BAS_EVENTSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_date_time_types.hpp>
#include <stdair/stdair_demand_types.hpp>
#include <stdair/bom/BookingRequestTypes.hpp>

namespace stdair {

  /** Event struct. */
  struct EventStruct {
    friend struct EventQueue;
    
  public:
    // ///////////// Getters ///////////
    /** Get the event type */
    const EventType_T& getEventType () const {
      return _eventType;
    }
    
    /** Get the Request event. */
    const BookingRequestStruct& getBookingRequest () const {
      assert (_request != NULL);
      return *_request;
    }

    /** Get the demand stream of the event. */
    const DemandStreamKeyStr_T& getDemandStreamKey () const {
      return _demandStreamKey;
    }
    
  public:
    // ////////// Constructors and destructors /////////
    /** Constructor. */
    EventStruct (const EventType_T&, const DemandStreamKeyStr_T&, 
                 BookingRequestPtr_T);
    /** Copy constructor. */
    EventStruct (const EventStruct&);
    /** Destructor. */
    ~EventStruct ();
  private:
    /** Default constructors. */
    EventStruct ();
    
  private:
    // ////////// Attributes //////////
    /** Event type */
    EventType_T _eventType;
    /** Reprentative timestamp of the event, which is the number of
     milliseconds between the event date-time and the default
     date-time (2010-01-01 00:00:00) */
    LongDuration_T _eventTimestamp;
    /** The demand stream which generated this event. */
    DemandStreamKeyStr_T _demandStreamKey;
    /** Pointer to Request event */
    BookingRequestPtr_T _request;

  };

}
#endif // __STDAIR_BAS_EVENTSTRUCT_HPP
