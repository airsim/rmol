// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/factory/FacBomAbstract.hpp>
#include <latus/com/factory/FacServiceAbstract.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/service/ServiceContextManager.hpp>

namespace LATUS {

  namespace COM {

    FacSupervisor* FacSupervisor::_instance = NULL;

    // //////////////////////////////////////////////////////////////////////
    FacSupervisor::FacSupervisor () : _serviceContextManager (NULL) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    FacSupervisor& FacSupervisor::instance() {
      if (_instance == NULL) {
        _instance = new FacSupervisor();
      }

      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    void FacSupervisor::
    registerBomFactory (FacBomAbstract* ioFacBomAbstract_ptr) {
      _bomPool.push_back (ioFacBomAbstract_ptr);
    }

    // //////////////////////////////////////////////////////////////////////
    void FacSupervisor::
    registerServiceFactory (FacServiceAbstract* ioFacServiceAbstract_ptr) {
      _svcPool.push_back (ioFacServiceAbstract_ptr);
    }

    // //////////////////////////////////////////////////////////////////////
    void FacSupervisor::
    registerServiceContextManager (ServiceContextManager* ioServiceCtxMgr_ptr) {
      _serviceContextManager = ioServiceCtxMgr_ptr;
    }

    // //////////////////////////////////////////////////////////////////////
    FacSupervisor::~FacSupervisor() {
      cleanBomLayer();
      cleanServiceLayer();
    }

    // //////////////////////////////////////////////////////////////////////
    void FacSupervisor::cleanBomLayer() {
      for (BomFactoryPool_T::const_iterator itFactory = _bomPool.begin();
           itFactory != _bomPool.end(); itFactory++) {
        const FacBomAbstract* currentFactory_ptr = *itFactory;
        assert (currentFactory_ptr != NULL);

        delete (currentFactory_ptr); currentFactory_ptr = NULL;
      }

      // Empty the pool of Bom Factories
      _bomPool.clear();
    }

    // //////////////////////////////////////////////////////////////////////
    void FacSupervisor::cleanServiceLayer() {
      for (ServiceFactoryPool_T::const_iterator itFactory = _svcPool.begin();
           itFactory != _svcPool.end(); itFactory++) {
        const FacServiceAbstract* currentFactory_ptr = *itFactory;
        assert (currentFactory_ptr != NULL);

        delete (currentFactory_ptr); currentFactory_ptr = NULL;
      }

      // Empty the pool of Service Factories
      _svcPool.clear();
    }

    // //////////////////////////////////////////////////////////////////////
    void FacSupervisor::cleanServiceContextManager() {
      delete (_serviceContextManager); _serviceContextManager = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    void FacSupervisor::cleanFactory () {
      if (_instance != NULL) {
		_instance->cleanBomLayer();
		_instance->cleanServiceLayer();
		_instance->cleanServiceContextManager();
      }
      delete (_instance); _instance = NULL;
    }

  }
}
