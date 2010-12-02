// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <string>
#include <sstream>
// SOCI
#if defined(SOCI_HEADERS_BURIED)
#include <soci/core/soci.h>
#include <soci/backends/mysql/soci-mysql.h>
#else // SOCI_HEADERS_BURIED
#include <soci.h>
#include <mysql/soci-mysql.h>
#endif // SOCI_HEADERS_BURIED
// StdAir
#include <stdair/stdair_exceptions.hpp>
#include <stdair/basic/BasDBParams.hpp>
#include <stdair/service/DBSessionManager.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {

  DBSessionManager* DBSessionManager::_instance = NULL;
  
  // //////////////////////////////////////////////////////////////////////
  DBSessionManager::DBSessionManager () : _dbSession (NULL) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  DBSessionManager::DBSessionManager (const DBSessionManager&)
    : _dbSession (NULL) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  DBSessionManager::DBSessionManager (const BasDBParams& iDBParams) 
    : _dbSession (NULL) {
    dbInit (iDBParams);
  }

  // //////////////////////////////////////////////////////////////////////
  DBSessionManager::~DBSessionManager () {
    // std::cout << "In DBSessionManager destructor" << std::endl;
    dbFinalise();
  }

  // //////////////////////////////////////////////////////////////////////
  void DBSessionManager::dbInit (const BasDBParams& iDBParams) {

    // Database parameters
    std::ostringstream oStr;
    oStr << "db=" << iDBParams.getDBName() << " user=" << iDBParams.getUser()
         << " password=" << iDBParams.getPassword()
         << " port=" << iDBParams.getPort() << " host=" << iDBParams.getHost();
    const std::string lDBSessionConnectionString (oStr.str());

    // Instanciate the database session: nothing else is performed at that stage
    _dbSession = new DBSession_T;
    
    try {
      // Open the connection to the database
      _dbSession->open (soci::mysql, lDBSessionConnectionString);
      
    } catch (std::exception const& lException) {
      std::ostringstream oMessage;
      oMessage <<"Error while opening a connection to database: "
               << lException.what() << std::endl
               << "Database parameters used:"
               << " db=" << iDBParams.getDBName()
               << " user=" << iDBParams.getUser()
               << " port=" << iDBParams.getPort()
               << " host=" << iDBParams.getHost();
      throw SQLDatabaseConnectionImpossibleException (oMessage.str());
    }
  }
    
  // //////////////////////////////////////////////////////////////////////
  void DBSessionManager::dbFinalise () {
    delete _dbSession; _dbSession = NULL;
  }
  
  // //////////////////////////////////////////////////////////////////////
  void DBSessionManager::init (const BasDBParams& iDBParams) {
    // Sanity check
    if (_instance != NULL) {
      STDAIR_LOG_ERROR ("Error: the DB session has already been initialised");
      assert (false);
    }
    assert (_instance == NULL);

    _instance = new DBSessionManager (iDBParams);
  }
  
  // //////////////////////////////////////////////////////////////////////
  DBSessionManager& DBSessionManager::instance() {
    if (_instance == NULL) {
      throw NonInitialisedDBSessionManagerException("");
    }
    assert (_instance != NULL);
    return *_instance;
  }
  
  // //////////////////////////////////////////////////////////////////////
  void DBSessionManager::clean() {
    //std::cout<< "In DBSessionManager::clean(),before static instance deletion"
    //       << std::endl;
    delete _instance; _instance = NULL;
    //std::cout<< "In DBSessionManager::clean(),after static instance deletion"
    //       << std::endl;
  }
  
  // //////////////////////////////////////////////////////////////////////
  DBSession_T& DBSessionManager::getDBSession() const {
    if (_dbSession == NULL) {
      throw NonInitialisedDBSessionManagerException ("");
    }
    assert (_dbSession != NULL);
    return *_dbSession;
  }
  
}
