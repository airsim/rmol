// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/factory/FacBomStructure.hpp>
#include <stdair/factory/FacBomContent.hpp>
#include <stdair/factory/FacSupervisor.hpp>

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
  void FacSupervisor::
  registerBomStructureFactory (FacBomStructure* ioFacBomStructure_ptr) {
    _facBomStructurePool.push_back (ioFacBomStructure_ptr);
  }

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::
  registerBomContentFactory (FacBomContent* ioFacBomContent_ptr) {
    _facBomContentPool.push_back (ioFacBomContent_ptr);
  }

  // //////////////////////////////////////////////////////////////////////
  FacSupervisor::~FacSupervisor() {
    cleanBomStructureLayer();
    cleanBomContentLayer();
  }

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::cleanBomStructureLayer() {
    for (BomStructureFactoryPool_T::const_iterator itFactory =
           _facBomStructurePool.begin();
         itFactory != _facBomStructurePool.end(); itFactory++) {
      const FacBomStructure* currentFactory_ptr = *itFactory;
      assert (currentFactory_ptr != NULL);

      delete (currentFactory_ptr); currentFactory_ptr = NULL;
    }

    // Empty the pool of BomStructure Factories
    _facBomStructurePool.clear();
  }

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::cleanBomContentLayer() {
    for (BomContentFactoryPool_T::const_iterator itFactory =
           _facBomContentPool.begin();
         itFactory != _facBomContentPool.end(); itFactory++) {
      const FacBomContent* currentFactory_ptr = *itFactory;
      assert (currentFactory_ptr != NULL);

      delete (currentFactory_ptr); currentFactory_ptr = NULL;
    }

    // Empty the pool of BomContent Factories
    _facBomContentPool.clear();
  }

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::cleanFactory () {
	if (_instance != NULL) {
		_instance->cleanBomStructureLayer();
		_instance->cleanBomContentLayer();
 	}
    delete _instance; _instance = NULL;
  }

}
