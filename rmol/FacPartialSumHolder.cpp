// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// RMOL
#include "FacSupervisor.hpp"
#include "FacPartialSumHolder.hpp"

namespace RMOL {

  FacPartialSumHolder* FacPartialSumHolder::_instance = NULL;

  // //////////////////////////////////////////////////////////////////////
  FacPartialSumHolder::~FacPartialSumHolder () {
    _instance = NULL;
  }

  // //////////////////////////////////////////////////////////////////////
  FacPartialSumHolder& FacPartialSumHolder::instance () {

    if (_instance == NULL) {
      _instance = new FacPartialSumHolder();
      assert (_instance != NULL);
      
      FacSupervisor::instance().registerFactory (_instance);
    }
    return *_instance;
  }

  // //////////////////////////////////////////////////////////////////////
  PartialSumHolder& FacPartialSumHolder::create (const int K) {
    PartialSumHolder* aPartialSumHolder_ptr = NULL;

    aPartialSumHolder_ptr = new PartialSumHolder (K);
    assert (aPartialSumHolder_ptr != NULL);

    // The new object is added to the Bom pool
    _pool.push_back (aPartialSumHolder_ptr);

    return *aPartialSumHolder_ptr;
  }

}
