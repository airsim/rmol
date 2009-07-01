// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/bom/BomStructure.hpp>
#include <stdair/factory/FacSupervisor.hpp>
#include <stdair/factory/FacBomStructure.hpp>

namespace stdair {
  
  FacBomStructure* FacBomStructure::_instance = NULL;

  // //////////////////////////////////////////////////////////////////////
  FacBomStructure::~FacBomStructure() {
    clean ();
  }

  // ////////////////////////////////////////////////////////////////////
  FacBomStructure& FacBomStructure::instance () {

    if (_instance == NULL) {
      _instance = new FacBomStructure();
      assert (_instance != NULL);

      FacSupervisor::instance().registerBomStructureFactory (_instance);
    }
    return *_instance;
  }

  // //////////////////////////////////////////////////////////////////////
  void FacBomStructure::clean() {
    for (BomStructurePool_T::iterator itBom = _structurePool.begin();
	 itBom != _structurePool.end(); itBom++) {
      BomStructure* currentBom_ptr = *itBom;
      assert (currentBom_ptr != NULL);

      delete currentBom_ptr; currentBom_ptr = NULL;
    }

    // Empty the pool of Factories
    _structurePool.clear();

    // Reset the static instance
    _instance = NULL;
  }

}
