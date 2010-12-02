// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir Logger
#include <stdair/stdair_exceptions.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {

  Logger* Logger::_instance = NULL;
  
  // //////////////////////////////////////////////////////////////////////
  Logger::Logger () : _level (LOG::DEBUG), _logStream (std::cout) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  Logger::Logger (const Logger&) : _level (LOG::DEBUG), _logStream (std::cout) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  Logger::Logger (const BasLogParams& iLogParams) 
    : _level (iLogParams._logLevel), _logStream (iLogParams._logStream) {
  }

  // //////////////////////////////////////////////////////////////////////
  Logger::~Logger () {
    // std::cout << "In Logger destructor" << std::endl;
  }

  // //////////////////////////////////////////////////////////////////////
  void Logger::init (const BasLogParams& iLogParams) {
    // Sanity check
    if (_instance != NULL) {
      STDAIR_LOG_ERROR ("Error: the log stream has already been initialised");
      assert (false);
    }
    assert (_instance == NULL);

    _instance = new Logger (iLogParams);
  }

  // //////////////////////////////////////////////////////////////////////
  Logger& Logger::instance() {
    if (_instance == NULL) {
      throw NonInitialisedLogServiceException("");
    }
    assert (_instance != NULL);
    return *_instance;
  }
  
  // //////////////////////////////////////////////////////////////////////
  void Logger::clean() {
    // std::cout << "In Logger::clean(), before static instance deletion"
    //       << std::endl;
    delete _instance; _instance = NULL;
    // std::cout << "In Logger::clean(), after static instance deletion"
    //       << std::endl;
  }
  
}
