#ifndef __STDAIR_BAS_EVENTSTRUCT_HPP
#define __STDAIR_BAS_EVENTSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BookingRequestTypes.hpp>

namespace stdair {

  /** Event struct. */
  struct EventStruct {
  
  public:
    // ///////////// Getters ///////////
    /** Get the event type */
    const EventType_T& getEventType () const {
      return _eventType;
    }
    
    /** Get the event datetime */
    const DateTime_T& getEventDateTime () const {
      return _eventDateTime;
    }
    
    /** Get the Request event. */
    const BookingRequestStruct& getBookingRequest () const {
      assert (_request != NULL);
      return *_request;
    }

    /** Get the demand stream of the event. */
    const DemandStreamKey_T& getDemandStreamKey () const {
      return _demandStreamKey;
    }

    // ///////////////// Business Methods /////////////////
    /** Move the event forward in time by one nanosecond. */
    void moveForwardInTime ();
    
  public:
    // ////////// Constructors and destructors /////////
    /** Constructor. */
    EventStruct (const EventType_T&, const DateTime_T&,
                 const DemandStreamKey_T&, BookingRequestPtr_T);
    EventStruct (const DateTime_T&);
    
    /** Copy constructor. */
    EventStruct (const EventStruct&);
  
    /** Destructor. */
    virtual ~EventStruct ();
  
  private:
    /** Default constructors. */
    EventStruct ();
    

  private:
    // ////////// Attributes //////////
    
    /** Event type */
    EventType_T _eventType;
    
    /** Event datetime */
    DateTime_T _eventDateTime;

    /** The demand stream which generated this event. */
    DemandStreamKey_T _demandStreamKey;
    
    /** Pointer to Request event */
    BookingRequestPtr_T _request;

  };

}
#endif // __STDAIR_BAS_EVENTSTRUCT_HPP
