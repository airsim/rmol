// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/factory/FacBomAbstract.hpp>

namespace LATUS {
  
  namespace COM {
    
    // //////////////////////////////////////////////////////////////////////
    FacBomAbstract::~FacBomAbstract() {
      clean ();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void FacBomAbstract::clean() {
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
}
