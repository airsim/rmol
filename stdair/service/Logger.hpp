#ifndef __STDAIR_SVC_LOGGER_HPP
#define __STDAIR_SVC_LOGGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
// StdAir
#include <stdair/stdair_log.hpp>
#include <stdair/basic/BasLogParams.hpp>

// /////////////// LOG MACROS /////////////////
#define STDAIR_LOG_CORE(iLevel, iToBeLogged) \
  { std::ostringstream ostr; ostr << iToBeLogged; \
    stdair::Logger::instance().log (iLevel, __LINE__, __FILE__, ostr.str()); }

#define STDAIR_LOG_CRITICAL(iToBeLogged) \
  STDAIR_LOG_CORE (stdair::LOG::CRITICAL, iToBeLogged)

#define STDAIR_LOG_ERROR(iToBeLogged) \
  STDAIR_LOG_CORE (stdair::LOG::ERROR, iToBeLogged)

#define STDAIR_LOG_NOTIFICATION(iToBeLogged) \
  STDAIR_LOG_CORE (stdair::LOG::NOTIFICATION, iToBeLogged)

#define STDAIR_LOG_WARNING(iToBeLogged) \
  STDAIR_LOG_CORE (stdair::LOG::WARNING, iToBeLogged)

#define STDAIR_LOG_DEBUG(iToBeLogged) \
  STDAIR_LOG_CORE (stdair::LOG::DEBUG, iToBeLogged)

#define STDAIR_LOG_VERBOSE(iToBeLogged) \
  STDAIR_LOG_CORE (stdair::LOG::VERBOSE, iToBeLogged)
// /////////// (END OF) LOG MACROS /////////////


namespace stdair {

  /** Class holding the stream for logs. 
      <br>Note that the error logs are seen as standard output logs, 
      but with a higher level of visibility. */
  class Logger {
    // Friend classes
    friend class FacSupervisor;
    friend class STDAIR_Service;
  public:
    
    /** Main log entry. */
    template <typename T>
    void log (const LOG::EN_LogLevel iLevel, const int iLineNumber,
              const std::string& iFileName, const T& iToBeLogged) {
      if (iLevel <= _level) {
        _logStream << "[" << LOG::_logLevels[iLevel] << "]" << iFileName << ":"
                   << iLineNumber << ": " << iToBeLogged << std::endl;
      }
    }
    
    /** Return the static Logger instance. */
    static Logger& instance();
    
    
  private:
    /** Default constructors are private so that only the required 
        constructor can be used. */
    Logger (const BasLogParams&);
    /** Default constructor. It must not be used. */
    Logger ();
    /** Default copy constructor. It must not be used. */
    Logger (const Logger&);
    /** Destructor. */
    ~Logger ();

    // TODO: migrate all the XXXXXX_Service to the new way to initialise
    //       Logger, and get rid of that 'public:' interface
  public:
    /** Initialise the static Logger instance. */
    static void init (const BasLogParams&);

  private:
    /** Delete the static Logger instance.*/
    static void clean();
    
  private:
    /** Instance object.*/
    static Logger* _instance;

    /** Log level. */
    LOG::EN_LogLevel _level;
    
    /** Stream dedicated to the logs. */
    std::ostream& _logStream;
  };
  
}
#endif // __STDAIR_SVC_LOGGER_HPP

