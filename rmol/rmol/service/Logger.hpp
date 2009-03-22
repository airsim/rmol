#ifndef __RMOL_SVC_LOGGER_HPP
#define __RMOL_SVC_LOGGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream>
#include <sstream>
#include <string>
// RMOL
#include <rmol/RMOL_Types.hpp>

// /////////////// LOG MACROS /////////////////
#define RMOL_LOG_CORE(iLevel, iToBeLogged) \
  { std::ostringstream ostr; ostr << iToBeLogged; \
    RMOL::Logger::instance().log (iLevel, __LINE__, __FILE__, ostr.str()); }

#define RMOL_LOG_CRITICAL(iToBeLogged) \
  RMOL_LOG_CORE (RMOL::LOG::CRITICAL, iToBeLogged)

#define RMOL_LOG_ERROR(iToBeLogged) \
  RMOL_LOG_CORE (RMOL::LOG::ERROR, iToBeLogged)

#define RMOL_LOG_NOTIFICATION(iToBeLogged) \
  RMOL_LOG_CORE (RMOL::LOG::NOTIFICATION, iToBeLogged)

#define RMOL_LOG_WARNING(iToBeLogged) \
  RMOL_LOG_CORE (RMOL::LOG::WARNING, iToBeLogged)

#define RMOL_LOG_DEBUG(iToBeLogged) \
  RMOL_LOG_CORE (RMOL::LOG::DEBUG, iToBeLogged)

#define RMOL_LOG_VERBOSE(iToBeLogged) \
  RMOL_LOG_CORE (RMOL::LOG::VERBOSE, iToBeLogged)
// /////////// (END OF) LOG MACROS /////////////


namespace RMOL {

  /** Class holding the stream for logs. 
      <br>Note that the error logs are seen as standard output logs, 
      but with a higher level of visibility. */
  class Logger {
    // Friend classes
    friend class FacSupervisor;
  public:
    
    /** Main log entry. */
    template <typename T>
    void log (const LOG::EN_LogLevel iLevel, const int iLineNumber,
              const std::string& iFileName, const T& iToBeLogged) {
      if (iLevel <= _level) {
        assert (_logStream != NULL);
        *_logStream << iFileName << ":" << iLineNumber
                    << ": " << iToBeLogged << std::endl;
      }
    }
    
    /** Get the log level. */
    LOG::EN_LogLevel getLogLevel();
    
    /** get the log stream. */
    std::ostream& getLogStream();
    
    /** Set the logger parameters (level and stream). */
    void setLogParameters (const LOG::EN_LogLevel iLogLevel, 
                           std::ostream& ioLogStream);
    
    /** Returns a current Logger instance.*/
    static Logger& instance();
    
  private:
    /** Default constructors are private so that only the required 
        constructor can be used. */
    Logger ();
    Logger (const Logger&);
    Logger (const LOG::EN_LogLevel iLevel, std::ostream& ioLogStream);
    /** Destructor. */
    ~Logger ();
    
  private:
    /** Log level. */
    LOG::EN_LogLevel _level;
    
    /** Stream dedicated to the logs. */
    std::ostream* _logStream;
    
    /** Instance object.*/
    static Logger* _instance;
  };
  
}
#endif // __RMOL_SVC_LOGGER_HPP
