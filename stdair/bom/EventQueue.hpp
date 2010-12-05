#ifndef __STDAIR_BOM_EVENTQUEUE_HPP
#define __STDAIR_BOM_EVENTQUEUE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/basic/StructAbstract.hpp>
#include <stdair/bom/EventTypes.hpp>

namespace stdair {
  
  /** Event queue. */
  struct EventQueue : public StructAbstract {
  public:
    // ////////// Display methods //////////
   /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) {}

    /** Display of the structure. */
    const std::string describe() const { return ""; }
    
  public:
    // ////////// Business methods /////////
    /** Pop event. */
    EventStruct& popEvent ();
    
    /** Add event.
     <br>If there already is an event with the same datetime, move the given
    event one nanosecond forward and retry the insertion until succeed. */
    void addEvent (EventStruct&);

    /** Erase the last used event. */
    void eraseLastUsedEvent ();
    
    /** Is queue done */
    const bool isQueueDone () const;
        
    // ////////// Debug methods /////////
    /** Queue size */
    const Count_T getQueueSize () const;
    
    /** Is queue empty */
    const bool isQueueEmpty () const;
    
  public:
    // ////////// Constructors and destructors /////////
    /** Default constructors. */
    EventQueue ();
    /** Copy constructor. */
    EventQueue (const EventQueue&);
    /** Destructor. */
     ~EventQueue ();

  private:
    // ////////// Attributes //////////
    /** Event list */
    EventList_T _eventList;
  };

}
#endif // __STDAIR_BOM_EVENTQUEUE_HPP
