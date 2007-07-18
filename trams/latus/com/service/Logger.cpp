// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// OPTREAC
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    Logger* Logger::_instance = NULL;
  
    // //////////////////////////////////////////////////////////////////////
    Logger::Logger () : _logStream (&std::cout) {
      assert (false);
    }

    // //////////////////////////////////////////////////////////////////////
    Logger::Logger (const Logger&) : _logStream (&std::cout) {
      assert (false);
    }

    // //////////////////////////////////////////////////////////////////////
    Logger::Logger (const LOG::EN_LogLevel iLevel, std::ostream& ioLogStream) 
      : _level (iLevel), _logStream (&ioLogStream) {
    }

    // //////////////////////////////////////////////////////////////////////
    Logger::~Logger () {
    }

    // //////////////////////////////////////////////////////////////////////
    void Logger::setLogParameters (const LOG::EN_LogLevel iLogLevel, 
				   std::ostream& ioLogStream) {
      _logStream = &ioLogStream;
      _level = iLogLevel;
    }

    // //////////////////////////////////////////////////////////////////////
    Logger& Logger::instance() {
      if (_instance == NULL) {
	_instance = new Logger (LOG::DEBUG, std::cout);
	assert (_instance != NULL);
      }
      return *_instance;
    }

  }

}
