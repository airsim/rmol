#ifndef __STDAIR_BAS_EVENTSTRUCT_HPP
#define __STDAIR_BAS_EVENTSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost
#include <boost/shared_ptr.hpp>
// STDAIR
#include <stdair/STDAIR_Types.hpp>

namespace stdair {
  
  /** Forward declaration */
  struct BookingRequestStruct;
  class DemandStream;

  // Type definitions.
  /** Define the smart pointer to a booking request. */
  typedef boost::shared_ptr<BookingRequestStruct> BookingRequestPtr_T;
  
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
    DemandStream& getDemandStream () const {
      assert (_demandStream != NULL);
      return *_demandStream;
    }
    
  public:
    // ////////// Constructors and destructors /////////
    /** Constructor. */
    EventStruct (const EventType_T&, const DateTime_T&,
                 DemandStream&, BookingRequestPtr_T);
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
    BookingRequestPtr_T _request;

  };

}
#endif // __STDAIR_BAS_EVENTSTRUCT_HPP
