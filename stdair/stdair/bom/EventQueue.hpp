#ifndef __STDAIR_BAS_EVENTQUEUE_HPP
#define __STDAIR_BAS_EVENTQUEUE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/EventStruct.hpp>

namespace stdair {
  
  /** Event queue. */
  class EventQueue {
  
  public:
    typedef std::pair<DateTime_T, EventStruct> EventListElement_T;
    typedef std::multimap<DateTime_T, EventStruct> EventList_T;
  
  public:
    // ///////////// Getters ///////////
    // /** Get the event type */
    //const EventType_T& getEventType () const {
    //  return _eventType;
    //}
    
  public:
    // ////////// Constructors and destructors /////////
    /** Constructor. */
    EventQueue (const DateTime_T&);
  
    /** Destructor. */
    virtual ~EventQueue ();
  
  public:
    // ////////// Business methods /////////
    /** Pop event */
    EventStruct* popEvent ();
    
    /** Add event */
    void addEvent (const EventStruct&);
    
    /** Is queue done */
    const bool isQueueDone () const;
    
    
    // ////////// Debug methods /////////
    /** Queue size */
    const Count_T getQueueSize () const;
    
    /** Is queue empty */
    const bool isQueueEmpty () const;
    
    /** Get position of current */
    const Count_T getPositionOfCurrent () const;
  
  private:
    /** Default constructors. */
    EventQueue (const EventQueue&);

  private:
    // ////////// Attributes //////////
    
    /** Event list */
    EventList_T _eventList;
    
    /** Pointer to current event */
    EventList_T::iterator _currentEvent;

  };

}
#endif // __STDAIR_BAS_EVENTQUEUE_HPP
