// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// Rmol Logger
#include <rmol/factory/FacSupervisor.hpp>
#include <rmol/service/Logger.hpp>

namespace RMOL {

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
      _logStream = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    LOG::EN_LogLevel Logger::getLogLevel() {
      return _level;
    }

    // //////////////////////////////////////////////////////////////////////
    std::ostream& Logger::getLogStream() {
      assert (_logStream != NULL);
      return *_logStream;
    }

    // //////////////////////////////////////////////////////////////////////
    void Logger::setLogParameters (const LOG::EN_LogLevel iLogLevel, 
                                   std::ostream& ioLogStream) {
      _level = iLogLevel;
      _logStream = &ioLogStream;
    }

    // //////////////////////////////////////////////////////////////////////
    Logger& Logger::instance() {
      if (_instance == NULL) {
        _instance = new Logger (LOG::DEBUG, std::cout);
        
        assert (_instance != NULL);

        FacSupervisor::instance().registerLoggerService (_instance);
      }
      return *_instance;
    }

}
