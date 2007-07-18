#ifndef __LATUS_COM_BOM_EVENT_HPP
#define __LATUS_COM_BOM_EVENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost (Extended STL)
#include <boost/date_time/posix_time/posix_time.hpp>

namespace LATUS {

  namespace COM {

    // Forward declaration
    class ClassPath;
  
    /** Define the key of a reservation / demand event. */
    typedef boost::posix_time::time_duration EventKey_T;

    /** Define a reservation / demand event. */
    typedef std::pair<EventKey_T, ClassPath*> Event_T;
    
  }
}
#endif // __LATUS_COM_BOM_EVENT_HPP
