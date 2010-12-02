// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_EVENTTYPES_HPP
#define __STDAIR_BOM_EVENTTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
// STDAIR
#include <stdair/stdair_date_time_types.hpp>
#include <stdair/bom/key_types.hpp>

namespace stdair {

  // Forward declarations.
  struct EventStruct;
  
  // Define a list of events.
  typedef std::map<const LongDuration_T, EventStruct> EventList_T;

  // Define an element of a event list.
  typedef std::pair<const LongDuration_T, EventStruct> EventListElement_T;
  
}
#endif // __STDAIR_BOM_EVENTTYPES_HPP

