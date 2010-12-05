#ifndef __STDAIR_STDAIR_LOG_HPP
#define __STDAIR_STDAIR_LOG_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>

namespace stdair {

  // Forward declarations
  class STDAIR_Service;

  // /////////////// Log /////////////
  /** Level of logs. */
  namespace LOG {
    typedef enum {
      CRITICAL = 0,
      ERROR,
      NOTIFICATION,
      WARNING,
      DEBUG,
      VERBOSE,
      LAST_VALUE
    } EN_LogLevel;
    
    static const std::string _logLevels[LAST_VALUE] =
      {"C", "E", "N", "W", "D", "V"};
  }

}
#endif // __STDAIR_STDAIR_LOG_HPP
