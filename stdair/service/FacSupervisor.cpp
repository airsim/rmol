// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/factory/FacAbstract.hpp>
#include <stdair/service/FacSupervisor.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/service/DBSessionManager.hpp>

namespace stdair {

  FacSupervisor* FacSupervisor::_instance = NULL;

  // //////////////////////////////////////////////////////////////////////
  FacSupervisor& FacSupervisor::instance() {
    if (_instance == NULL) {
      _instance = new FacSupervisor();
    }

    return *_instance;
  }

  // //////////////////////////////////////////////////////////////////////
  FacSupervisor::~FacSupervisor() {
    cleanBomLayer();
  }

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::
  registerFacBom (FacAbstract* ioFac_ptr) {
    _facPool.push_back (ioFac_ptr);
  }

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::cleanBomLayer() {
    for (FactoryPool_T::const_iterator itFactory =
           _facPool.begin();
         itFactory != _facPool.end(); itFactory++) {
      const FacAbstract* currentFactory_ptr = *itFactory;
      assert (currentFactory_ptr != NULL);

      delete (currentFactory_ptr); currentFactory_ptr = NULL;
    }

    // Empty the pool of factories
    _facPool.clear();
  }

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::cleanLoggerService() {
    // Clean the static instance of the log service
    Logger::clean();
  }

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::cleanDBSessionManager() {
    // Clean the static instance of the database session manager
    DBSessionManager::clean();
  }
  
  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::cleanAll () {
    // Clean the static instance of the database session manager
    cleanDBSessionManager();

    // Clean the static instance of the log service
    cleanLoggerService();

    // Clean the static instance of the FacSupervisor.
    // This in turn will invoke the destructor (~FacSupervisor() method)
    // of the static instance.
    delete _instance; _instance = NULL;
  }

}
