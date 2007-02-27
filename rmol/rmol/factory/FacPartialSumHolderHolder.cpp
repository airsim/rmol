// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// RMOL
#include <rmol/bom/PartialSumHolderHolder.hpp>
#include <rmol/factory/FacSupervisor.hpp>
#include <rmol/factory/FacPartialSumHolderHolder.hpp>

namespace RMOL {

  FacPartialSumHolderHolder* FacPartialSumHolderHolder::_instance = NULL;

  // //////////////////////////////////////////////////////////////////////
  FacPartialSumHolderHolder::~FacPartialSumHolderHolder () {
    _instance = NULL;
  }

  // //////////////////////////////////////////////////////////////////////
  FacPartialSumHolderHolder& FacPartialSumHolderHolder::instance () {

    if (_instance == NULL) {
      _instance = new FacPartialSumHolderHolder();
      assert (_instance != NULL);
      
      FacSupervisor::instance().registerBomFactory (_instance);
    }
    return *_instance;
  }

  // //////////////////////////////////////////////////////////////////////
  PartialSumHolderHolder& FacPartialSumHolderHolder::create () {
    PartialSumHolderHolder* aPartialSumHolderHolder_ptr = NULL;

    aPartialSumHolderHolder_ptr = new PartialSumHolderHolder ();
    assert (aPartialSumHolderHolder_ptr != NULL);

    // The new object is added to the Bom pool
    _pool.push_back (aPartialSumHolderHolder_ptr);

    return *aPartialSumHolderHolder_ptr;
  }

  // //////////////////////////////////////////////////////////////////////
  void FacPartialSumHolderHolder::
  addPartialSumHolder (PartialSumHolderHolder& ioPartialSumHolderHolder, 
		       PartialSumHolder& ioPartialSumHolder) {
    ioPartialSumHolderHolder.addPartialSumHolder (ioPartialSumHolder);
  }

}
