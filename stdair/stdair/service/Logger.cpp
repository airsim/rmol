// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Stdair Logger
//#include <stdair/factory/FacSupervisor.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {

  Logger* Logger::_instance = NULL;
  
  // //////////////////////////////////////////////////////////////////////
  Logger::Logger () : _logStream (std::cout), _level (LOG::DEBUG) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  Logger::Logger (const Logger&) : _logStream (std::cout), _level (LOG::DEBUG) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  Logger::Logger (const stdair::BasLogParams& iLogParams) 
    : _level (iLogParams._logLevel), _logStream (iLogParams._logStream) {
  }

  // //////////////////////////////////////////////////////////////////////
  Logger::~Logger () {
  }

  // //////////////////////////////////////////////////////////////////////
  void Logger::init (const BasLogParams& iLogParams) {
    // Sanity check
    if (_instance != NULL) {
      STDAIR_LOG_ERROR ("Error: the log stream has already been initialised");
      // TODO: throw an exception?

    } else {
      _instance = new Logger (iLogParams);
    }
  }

  // //////////////////////////////////////////////////////////////////////
  Logger& Logger::instance() {
    if (_instance == NULL) {
      throw NonInitialisedLogServiceException();
    }
    assert (_instance != NULL);
    return *_instance;
  }
  
  // //////////////////////////////////////////////////////////////////////
  void Logger::clean() {
    delete _instance; _instance = NULL;
  }
  
}
