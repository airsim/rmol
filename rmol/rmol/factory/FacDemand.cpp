// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// RMOL
#include <rmol/bom/Demand.hpp>
#include <rmol/factory/FacSupervisor.hpp>
#include <rmol/factory/FacDemand.hpp>

namespace RMOL {

  FacDemand* FacDemand::_instance = NULL;

  // //////////////////////////////////////////////////////////////////////
  FacDemand::~FacDemand () {
    _instance = NULL;
  }

  // //////////////////////////////////////////////////////////////////////
  FacDemand& FacDemand::instance () {

    if (_instance == NULL) {
      _instance = new FacDemand();
      assert (_instance != NULL);
      
      FacSupervisor::instance().registerBomFactory (_instance);
    }
    return *_instance;
  }

  // //////////////////////////////////////////////////////////////////////
  Demand& FacDemand::
  create (const FldDistributionParameters& iDistributionParameters,
	  const FldYieldRange& iYieldRange) {
    Demand* aDemand_ptr = NULL;

    aDemand_ptr = new Demand (iDistributionParameters, iYieldRange);
    assert (aDemand_ptr != NULL);

    // The new object is added to the Bom pool
    _pool.push_back (aDemand_ptr);

    return *aDemand_ptr;
  }

}
