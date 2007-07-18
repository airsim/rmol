#ifndef __LATUS_SVC_LOGGER_HPP
#define __LATUS_SVC_LOGGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream>
#include <sstream>
#include <string>
// LATUS
#include <latus/LatusTypes.hpp>
#include <latus/com/service/ServiceAbstract.hpp>

// /////////////// LOG MACROS /////////////////
#define LATUS_LOG_CORE(iLevel, iToBeLogged) \
  { std::ostringstream ostr; ostr << iToBeLogged; \
  COM::Logger::instance().log (iLevel, __LINE__, __FILE__, ostr.str()); }

#define LATUS_LOG_CRITICAL(iToBeLogged) \
  LATUS_LOG_CORE (LOG::CRITICAL, iToBeLogged)

#define LATUS_LOG_ERROR(iToBeLogged) \
  LATUS_LOG_CORE (LOG::ERROR, iToBeLogged)

#define LATUS_LOG_NOTIFICATION(iToBeLogged) \
  LATUS_LOG_CORE (LOG::NOTIFICATION, iToBeLogged)

#define LATUS_LOG_WARNING(iToBeLogged) \
  LATUS_LOG_CORE (LOG::WARNING, iToBeLogged)

#define LATUS_LOG_DEBUG(iToBeLogged) \
  LATUS_LOG_CORE (LOG::DEBUG, iToBeLogged)

#define LATUS_LOG_VERBOSE(iToBeLogged) \
  LATUS_LOG_CORE (LOG::VERBOSE, iToBeLogged)
// /////////// (END OF) LOG MACROS /////////////


namespace LATUS {

  namespace COM {

    /** Class holding the stream for logs. 
	<br>Note that the error logs are seen as standard output logs, 
	but with a higher level of visibility. */
    class Logger : public ServiceAbstract {
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

    private:
      /** Log level. */
      LOG::EN_LogLevel _level;

      /** Stream dedicated to the logs. */
      std::ostream* _logStream;

      /** Instance object.*/
      static Logger* _instance;
    };

  }

}
#endif // __LATUS_SVC_LOGGER_HPP
