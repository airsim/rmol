// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// RMOL
#include "BomAbstract.hpp"
#include "FacAbstract.hpp"

namespace RMOL {
  
  // //////////////////////////////////////////////////////////////////////
  FacAbstract::~FacAbstract() {
    clean ();
  }

  // //////////////////////////////////////////////////////////////////////
  void FacAbstract::clean() {
    for (BomPool_T::iterator itBom = _pool.begin();
	 itBom != _pool.end(); itBom++) {
      BomAbstract* currentBom_ptr = *itBom;
      assert (currentBom_ptr != NULL);

      delete (currentBom_ptr); currentBom_ptr = NULL;
    }

    // Empty the pool of Factories
    _pool.clear();
  }

}
