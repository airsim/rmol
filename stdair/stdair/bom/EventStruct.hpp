#ifndef __STDAIR_BAS_EVENTSTRUCT_HPP
#define __STDAIR_BAS_EVENTSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>

namespace stdair {
  
  /** Forward declaration */
  struct BookingRequestStruct;
  class DemandStream;
  
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
    
    /** Get the pointer Request event. */
    const BookingRequestStruct* getPointerToRequestEvent () const {
      return _request;
    }

    /** Get the demand stream of the event. */
    DemandStream& getDemandStream () const {
      assert (_demandStream != NULL);
      return *_demandStream;
    }
    
  public:
    // ////////// Constructors and destructors /////////
    /** Constructor. */
    EventStruct (const EventType_T&, const DateTime_T&,
                 DemandStream&, BookingRequestStruct* const);
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
    DemandStream* _demandStream;
    
    /** Pointer to Request event */
    BookingRequestStruct* _request;

  };

}
#endif // __STDAIR_BAS_EVENTSTRUCT_HPP
