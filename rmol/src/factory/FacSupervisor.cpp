// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// RMOL
#include "FacAbstract.hpp"
#include "FacSupervisor.hpp"

namespace RMOL {

  FacSupervisor* FacSupervisor::_instance = NULL;

  // //////////////////////////////////////////////////////////////////////
  FacSupervisor& FacSupervisor::instance() {
    if (_instance == NULL) {
      _instance = new FacSupervisor();
    }

    return *_instance;
  }

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::registerFactory (FacAbstract* ioFacAbstract_ptr) {
    _pool.push_back (ioFacAbstract_ptr);
  }

  // //////////////////////////////////////////////////////////////////////
  FacSupervisor::~FacSupervisor() {
    clean();
  }

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::clean() {
    for (FactoryPool_T::const_iterator itFactory = _pool.begin();
	 itFactory != _pool.end(); itFactory++) {
      const FacAbstract* currentFactory_ptr = *itFactory;
      assert (currentFactory_ptr != NULL);

      delete (currentFactory_ptr); currentFactory_ptr = NULL;
    }

    // Empty the pool of Factories
    _pool.clear();
  }

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::cleanFactory () {
	if (_instance != NULL) {
		_instance->clean();
	}
    delete (_instance); _instance = NULL;
  }

}
