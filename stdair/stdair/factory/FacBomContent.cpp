// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/bom/BomStructure.hpp>
#include <stdair/bom/BomStructureRoot.hpp>
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/BomContentRoot.hpp>
#include <stdair/factory/FacSupervisor.hpp>
#include <stdair/factory/FacBomContent.hpp>

namespace stdair {
  
  FacBomContent* FacBomContent::_instance = NULL;

  // ////////////////////////////////////////////////////////////////////
  FacBomContent& FacBomContent::instance () {

    if (_instance == NULL) {
      _instance = new FacBomContent();
      assert (_instance != NULL);

      FacSupervisor::instance().registerBomContentFactory (_instance);
    }
    return *_instance;
  }

  // //////////////////////////////////////////////////////////////////////
  FacBomContent::~FacBomContent() {
    clean ();
  }

  // //////////////////////////////////////////////////////////////////////
  void FacBomContent::clean() {
    for (BomContentPool_T::iterator itBom = _contentPool.begin();
	 itBom != _contentPool.end(); itBom++) {
      BomContent* currentBom_ptr = *itBom;
      assert (currentBom_ptr != NULL);

      delete currentBom_ptr; currentBom_ptr = NULL;
    }

    // Empty the pool of Factories
    _contentPool.clear();

    // Reset the static instance
    _instance = NULL;
  }

}
