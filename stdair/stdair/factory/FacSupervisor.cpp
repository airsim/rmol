// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/factory/FacBomStructure.hpp>
#include <stdair/factory/FacBomContent.hpp>
#include <stdair/factory/FacSupervisor.hpp>
#include <stdair/service/Logger.hpp>

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
    cleanLoggerService();
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
  void FacSupervisor::cleanLoggerService() {
    // Clean the static instance of the log service
    Logger::clean();
  }
  
  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::cleanFactory () {
    // Clean the static instance of the log service
    Logger::clean();

    // Clean the static instance of the FacSupervisor
    delete _instance; _instance = NULL;
  }

}
